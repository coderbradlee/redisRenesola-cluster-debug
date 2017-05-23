#ifndef SERVER_RESOURCE_BASE_HPP
#define	SERVER_RESOURCE_BASE_HPP
#define BOOST_SPIRIT_THREADSAFE

#include "renesolalog.h"
#include "redispp.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <boost/bind.hpp>
#include <list>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/lexical_cast.hpp>
//#include <queue>
//#include <thread>
#include <condition_variable>
#include <assert.h>

#include "hirediscommand.h"
using namespace RedisCluster;
using namespace redispp;
using namespace boost::posix_time;

#include "server_http.hpp"
#include "client_http.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
//Added for the default_resource example
#include<fstream>
using namespace std;
//Added for the json:
using namespace boost::property_tree;

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;
//Connection *connRedis;
string redisHost;
string redisPort;
string redisPassword;
string url;
string flow_number_param1;
string flow_number_param2;
///定义redis库
#define KV_SYS_PARAMS 0
#define KV_MF 1
#define KV_SESSION 2
#define KV_VISIT_RECORDS 3
#define KV_SHOPPING_CART 4
#define KV_OBJ_SNAPSHOT 5
#define KV_OPERATION_LOG 6
// response error code define -8001 ~ -9000 隔-10或-5
//JSON_READ_OR_WRITE_ERROR(-8010, "json read or write error", "json 格式问题")
#define JSON_READ_OR_WRITE_ERROR -8010
//CREATE_SESSION_UNKNOWN_ERROR(-8020, "create session unknown error", "创建session时未知的错误")
#define CREATE_SESSION_UNKNOWN_ERROR -8020
//CREATE_SESSION_KEY_EXIST(-8025, "key already exist when create session", "创建session时key已经存在")
#define CREATE_SESSION_KEY_EXIST -8025
//ADD_USERID_UNDER_SESSION_UNKNOWN_ERROR(-8030, "add userid unknown error", "增加userid时未知的错误")
#define ADD_USERID_UNDER_SESSION_UNKNOWN_ERROR -8030
//ADD_USERID_KEY_NOT_EXIST(-8035, "key does not exist when add userid", "增加userid时key不存在")
#define ADD_USERID_KEY_NOT_EXIST -8035
//DELETE_SESSION_UNKNOWN_ERROR(-8040, "del session unknown error", "删除session时未知的错误")
#define DELETE_SESSION_UNKNOWN_ERROR -8040
//DELETE_SESSION_KEY_NOT_EXIST(-8045, "key does not exist when del session", "删除session时key不存在")
#define DELETE_SESSION_KEY_NOT_EXIST -8045
//QUERY_SESSION_UNKNOWN_ERROR(-8050, "unknown error when query session ", "查询session时未知的错误")
#define QUERY_SESSION_UNKNOWN_ERROR -8050
//QUERY_SESSION_KEY_NOT_EXIST(-8055, "key does not exist when query session", "查询session时key不存在")
#define QUERY_SESSION_KEY_NOT_EXIST -8055
//UPDATE_SESSION_DEADLINE_UNKNOWN_ERROR(-8060, "update session unknown error", "更新session时未知的错误")
#define UPDATE_SESSION_DEADLINE_UNKNOWN_ERROR -8060
//UPDATE_SESSION_DEADLINE_KEY_NOT_EXIST(-8065, "key does not exist when update session", "更新session时key不存在")
#define UPDATE_SESSION_DEADLINE_KEY_NOT_EXIST -8065
//*********************************************************
//BATCH_CREATE_AREAS_KEY_EXIST(-8070, "key already exists when batch create areas", "批量增加地区key时key已经存在")
#define BATCH_CREATE_AREAS_KEY_EXIST -8070
//BATCH_CREATE_AREAS_UNKNOWN_ERROR(-8080, "unknown error when batch create areas", "批量增加地区key时未知错误")
#define BATCH_CREATE_AREAS_UNKNOWN_ERROR -8080
//UNKNOWN_ERROR(-8085, "unknown error", "未知错误")
#define UNKNOWN_ERROR -8085

//*********************************************************

///////////////redis cluster thread pool//////////////////////


template<typename redisConnection>
class ThreadedPool
{
    static const int poolSize_ = 10;
    typedef Cluster<redisConnection, ThreadedPool> RCluster;
    // We will save our pool in std::queue here
    typedef std::queue<redisConnection*> ConQueue;
    // Define pair with condition variable, so we can notify threads, when new connection is released from some thread
    typedef std::pair<std::condition_variable, ConQueue> ConPool;
    // Container for saving connections by their slots, just as
    typedef std::map <typename RCluster::SlotRange, ConPool*, typename RCluster::SlotComparator> ClusterNodes;
    // Container for saving connections by host and port (for redirecting)
    typedef std::map <typename RCluster::Host, ConPool*> RedirectConnections;
    // rename cluster types
    typedef typename RCluster::SlotConnection SlotConnection;
    typedef typename RCluster::HostConnection HostConnection;
    
public:
    
    ThreadedPool( typename RCluster::pt2RedisConnectFunc conn,
                 typename RCluster::pt2RedisFreeFunc disconn,
                 void* userData ) :
    data_( userData ),
    connect_(conn),
    disconnect_(disconn)
    {
    }
    
    ~ThreadedPool()
    {
        disconnect();
    }
    
    // helper function for creating connections in loop
    inline void fillPool( ConPool &pool, const char* host, int port )
    {
        for( int i = 0; i < poolSize_; ++i )
        {
            redisConnection *conn = connect_( host,
                                            port,
                                            data_ );
            
            if( conn == NULL || conn->err )
            {
                throw ConnectionFailedException();
            }
            pool.second.push( conn );
        }
    }
    
    // helper for fetching connection from pool
    inline redisConnection* pullConnection( std::unique_lock<std::mutex> &locker, ConPool &pool )
    {
        redisConnection *con = NULL;
        // here we wait for other threads for release their connections if the queue is empty
        while (pool.second.empty())
        {
            // if queue is empty here current thread is waiting for somethread to release one
            pool.first.wait(locker);
        }
        // get a connection from queue
        con = pool.second.front();
        pool.second.pop();
        
        return con;
    }
    // helper for releasing connection and placing it in pool
    inline void pushConnection( std::unique_lock<std::mutex> &locker, ConPool &pool, redisConnection* con )
    {
        pool.second.push(con);
        locker.unlock();
        // notify other threads for their wake up in case of they are waiting
        // about empty connection queue
        pool.first.notify_one();
    }
    
    // function inserts new connection by range of slots during cluster initialization
    inline void insert( typename RCluster::SlotRange slots, const char* host, int port )
    {
        std::unique_lock<std::mutex> locker(conLock_);
        
        ConPool* &pool = nodes_[slots];
        pool = new ConPool();
        fillPool(*pool, host, port);
    }
    
    // function inserts or returning existing one connection used for redirecting (ASKING or MOVED)
    inline HostConnection insert( string host, string port )
    {
        std::unique_lock<std::mutex> locker(conLock_);
        string key( host + ":" + port );
        HostConnection con = { key, NULL };
        try
        {
            con.second = pullConnection( locker, *connections_.at( key ) );
        }
        catch( const std::out_of_range &oor )
        {
        }
        // create new connection in case if we didn't redirecting to this
        // node before
        if( con.second == NULL )
        {
            ConPool* &pool = connections_[key];
            pool = new ConPool();
            fillPool(*pool, host.c_str(), std::stoi(port));
            con.second = pullConnection( locker, *pool );
        }
        
        return con;
    }
    
    
    inline SlotConnection getConnection( typename RCluster::SlotIndex index )
    {
        std::unique_lock<std::mutex> locker(conLock_);
        
        typedef typename ClusterNodes::iterator iterator;
        iterator found = DefaultContainer<redisConnection>::template searchBySlots(index, nodes_);
        
        return { found->first, pullConnection( locker, *found->second ) };
    }
    
    // this function is invoked when library whants to place initial connection
    // back to the storage and the connections is taken by slot range from storage
    inline void releaseConnection( SlotConnection conn )
    {
        std::unique_lock<std::mutex> locker(conLock_);
        pushConnection( locker, *nodes_[conn.first], conn.second );
    }
    // same function for redirection connections
    inline void releaseConnection( HostConnection conn )
    {
        std::unique_lock<std::mutex> locker(conLock_);
        pushConnection( locker, *connections_[conn.first], conn.second );
    }
    
    // disconnect both thread pools
    inline void disconnect()
    {
        disconnect<ClusterNodes>( nodes_ );
        disconnect<RedirectConnections>( connections_ );
    }
    
    template <typename T>
    inline void disconnect(T &cons)
    {
        std::unique_lock<std::mutex> locker(conLock_);
        if( disconnect_ != NULL )
        {
            typename T::iterator it(cons.begin()), end(cons.end());
            while ( it != end )
            {
                for( int i = 0; i < poolSize_; ++i )
                {
                    // pullConnection will wait for all connection
                    // to be released
                    disconnect_( pullConnection( locker, *it->second) );
                }
                if( it->second != NULL )
                {
                    delete it->second;
                    it->second = NULL;
                }
                ++it;
            }
        }
        cons.clear();
    }
    
    void* data_;
private:
    typename RCluster::pt2RedisConnectFunc connect_;
    typename RCluster::pt2RedisFreeFunc disconnect_;
    RedirectConnections connections_;
    ClusterNodes nodes_;
    std::mutex conLock_;
};

typedef Cluster<redisContext, ThreadedPool<redisContext> > ThreadPoolCluster;

volatile int cnt = 0;
std::mutex lockRedis;

//set global variable value ThreadPoolCluster::ptr_t cluster_p;£¬set value through timer
ThreadPoolCluster::ptr_t cluster_p;
//std::mutex lockRedis;
void commandThread( ThreadPoolCluster::ptr_t cluster_p )
{
    redisReply * reply;
    // use defined custom cluster as template parameter for HiredisCommand here
    reply = static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, "FOO", "SET %d %s", cnt, "BAR1" ) );
    
    // check the result with assert
    assert( reply->type == REDIS_REPLY_STATUS && string(reply->str) == "OK" );
    
    {
        std::lock_guard<std::mutex> locker(lockRedis);
        cout << ++cnt << endl;
    }
    
    freeReplyObject( reply );
}

void processCommandPool()
{
    const int threadsNum = 1000;
    
    // use defined ThreadedPool here
    ThreadPoolCluster::ptr_t cluster_p;
    // and here as template parameter
    cout<<__LINE__<<":"<<redisHost<<endl;
    cout<<__LINE__<<":"<<redisPort<<endl;
    cluster_p = HiredisCommand<ThreadPoolCluster>::createCluster( redisHost.c_str(),boost::lexical_cast<int>(redisPort) );
    
    std::thread thr[threadsNum];
    for( int i = 0; i < threadsNum; ++i )
    {
        thr[i] = std::thread( commandThread, cluster_p );
    }
    
    for( int i = 0; i < threadsNum; ++i )
    {
        thr[i].join();
    }
    
    delete cluster_p;
}

///////////////redis cluster thread pool//////////////////////

void deal_with_subflowno_number_with_systemno(HttpServer::Response& response,const std::vector<std::string>& one_pair)
{
     try 
        {
            //3/JP/SO/2/PI
            string systemno=one_pair[0];
            string company=one_pair[1];
            string type=one_pair[2];
            string num=one_pair[3];
            string sub_type=one_pair[4];
            if(company.length()>3||type.length()>3)
            {
                string temp="path error";
                response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << temp.length()<< "\r\n\r\n" << temp;
                return;
            }
            
            //hincrby {scm_no} FR_PO_day_2017_03_09 1
            string id_name="{flow_no_sub_"+systemno+"}";
            
            string key=id_name+" "+company+"_"+type+"_"+num+"_"+sub_type;
            string incr_command="hincrby "+key+" 1";
            string get_command="hget "+key;
            cout<<incr_command<<endl;
            cout<<get_command<<endl;
            redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, id_name.c_str(), incr_command.c_str()));
            freeReplyObject(reply);
        // cout<<__FILE__<<""<<__LINE__<<endl;
            reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, id_name.c_str(), get_command.c_str()));
        string value="";
        //cout<<__LINE__<<endl;
        if(reply->str!=nullptr)
        {
            //cout<<reply->type<<endl;
          value+=reply->str;
          //retJson.put<std::string>("flow_number",value);
        }
        freeReplyObject(reply);
        cout<<value<<":"<<__FILE__<<""<<__LINE__<<endl;
        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        string temp="{\"flowNo\":\""+value+"\",\"replyTime\" : \""+now_str+"\"}";

        cout<<temp<<":"<<__FILE__<<""<<__LINE__<<endl;
        
        response <<"HTTP/1.1 200 OK\r\nContent-Length: " << temp.length() << "\r\n\r\n" <<temp;
        }
        catch(json_parser_error& e) 
        {
            string temp="json error";
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << temp.length()<< "\r\n\r\n" << temp;
        }
        catch(exception& e) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        }
        catch(...) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen("unknown error") << "\r\n\r\n" << "unknown error";
        }
}

void deal_with_subflowno_number(HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request)
{
     try 
        {
            //BOOST_LOG_SEV(slg, notification)<<"request: "<<request->method<<" "<<request->path<<;
            //BOOST_LOG(test_lg::get())<<"request: "<<request->method<<" "<<request->path;initsink->flush();
            //cout<<request->path<<endl;
            string temp_flowno="/subFlowNo/";
            string left_path=request->path.substr(temp_flowno.length(), request->path.length());
            cout<<left_path<<endl;
            std::vector<std::string> one_pair;
            boost::split(one_pair,left_path , boost::is_any_of("/"));
            // cout<<one_pair.size()<<endl;
            if(one_pair.size()>4)
            {
                deal_with_subflowno_number_with_systemno(response,one_pair);
                return;
            }
            string company=one_pair[0];
            string type=one_pair[1];
            string num=one_pair[2];
            string sub_type=one_pair[3];
            if(company.length()>3||type.length()>3)
            {
                string temp="path error";
                response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << temp.length()<< "\r\n\r\n" << temp;
                return;
            }
            
            //hincrby {scm_no} FR_PO_day_2017_03_09 1
            string id_name="{flow_no_sub}";
            
            string key=id_name+" "+company+"_"+type+"_"+num+"_"+sub_type;
            string incr_command="hincrby "+key+" 1";
            string get_command="hget "+key;
            cout<<incr_command<<endl;
            cout<<get_command<<endl;
            redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, id_name.c_str(), incr_command.c_str()));
            freeReplyObject(reply);
        // cout<<__FILE__<<""<<__LINE__<<endl;
            reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, id_name.c_str(), get_command.c_str()));
        string value="";
        //cout<<__LINE__<<endl;
        if(reply->str!=nullptr)
        {
            //cout<<reply->type<<endl;
          value+=reply->str;
          //retJson.put<std::string>("flow_number",value);
        }
        freeReplyObject(reply);
        cout<<value<<":"<<__FILE__<<""<<__LINE__<<endl;
        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        string temp="{\"flowNo\":\""+value+"\",\"replyTime\" : \""+now_str+"\"}";

        cout<<temp<<":"<<__FILE__<<""<<__LINE__<<endl;
        
        response <<"HTTP/1.1 200 OK\r\nContent-Length: " << temp.length() << "\r\n\r\n" <<temp;
        }
        catch(json_parser_error& e) 
        {
            string temp="json error";
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << temp.length()<< "\r\n\r\n" << temp;
        }
        catch(exception& e) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        }
        catch(...) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen("unknown error") << "\r\n\r\n" << "unknown error";
        }
}
void deal_with_flow_number_with_systemno(HttpServer::Response& response,const std::vector<std::string>& one_pair)
{
     try 
        {
            string systemno=one_pair[0];
            string company=one_pair[1];
            string type=one_pair[2];
            //UK,ZA,FR,IT,DE,TR,RU，这些先用新规则
            if((company=="UK")||(company=="ZA")||(company=="FR")||(company=="IT")||(company=="DE")||(company=="TR")||(company=="RU")||(company=="PA")||(company=="US")||(company=="CA")||(company=="MX")||(company=="BR")||(company=="JP")||(company=="TH"))
            {
                type="OVERSEAS";
            }
            // if(company!="JS")
            // {
            //     type="OVERSEAS";
            // }
            string id_name="{"+company+"_"+type+"_"+"flow_number_"+systemno+"}:id";
            string incr_command="incr "+id_name;
            string get_command="get "+id_name;
            cout<<id_name<<endl;
            cout<<incr_command<<endl;
            cout<<get_command<<endl;
            
        //redisReply * incr=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, "{flow_number}:id", "incr {flow_number}:id"));
            redisReply * incr=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, id_name.c_str(), incr_command.c_str()));
        freeReplyObject(incr);
        //redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, "{flow_number}:id", "get {flow_number}:id"));
        cout<<__FILE__<<""<<__LINE__<<endl;
        redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, id_name.c_str(), get_command.c_str()));
        string value="";
        //cout<<__LINE__<<endl;
        if(reply->str!=nullptr)
        {
            //cout<<reply->type<<endl;
          value+=reply->str;
          //retJson.put<std::string>("flow_number",value);
        }
        freeReplyObject(reply);
        cout<<value<<":"<<__FILE__<<""<<__LINE__<<endl;
        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        string temp="{\"flowNo\":\""+value+"\",\"replyTime\" : \""+now_str+"\"}";

        cout<<temp<<":"<<__FILE__<<""<<__LINE__<<endl;
        // std::stringstream ss;
        // write_json(ss, retJson);
        // //ÔÚÕâÀïÅÐ¶ÏÀïÃæµÄchildren¼°childrensµÄÖµ£¬Èç¹ûÎª¿Õ£¬ÉèÖÃÎª¿ÕÊý×é,ÓÃreplace
        // string temp=ss.str();
        response <<"HTTP/1.1 200 OK\r\nContent-Length: " << temp.length() << "\r\n\r\n" <<temp;
        }
        catch(json_parser_error& e) 
        {
            string temp="json error";
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << temp.length()<< "\r\n\r\n" << temp;
        }
        catch(exception& e) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        }
        catch(...) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen("unknown error") << "\r\n\r\n" << "unknown error";
        }
}

string CREATE_SESSION_HTTP_SESSION2(const ptree& pt)
{
    try
    {   
        ptree pChild = pt.get_child("requestData");
        string key="";
        for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
        {
            std::ostringstream buf; 
            write_json(buf,(it->second),false);
            std::string json = buf.str();
            cout<<json<<":"<<__FILE__<<":"<<__LINE__<<endl;
            if(json.empty())
            {
                throw std::runtime_error(std::string("requestData is empty!"));
            }
            key=it->second.get<string>("token");

            string value=json;
            
            string tempkey="{KV_TOKEN}:"+key;
            //cout<<tempkey<<endl;
            
            if(!(bool)static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "set %s %s", tempkey.c_str(), value.c_str())))
            {
                throw std::runtime_error(std::string("error set to redis"));
            }
        }
        //return
        basic_ptree<std::string, std::string> retJson;
        key="token:"+key;
        retJson.put<int>("errorCode",200);
        retJson.put<std::string>("message","write to cache[KV_TOKEN] successfully");
        retJson.put<std::string>("replyData",key);
        retJson.put<std::string>("replier","pandora-cache");
        //获取时间
        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        retJson.put<std::string>("replyTime",now_str);
        std::stringstream ss;
        write_json(ss, retJson);
        return ss.str();
    }
    catch(json_parser_error& e) 
    {
        basic_ptree<std::string, std::string> retJson;
        retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
        retJson.put<std::string>("message","json read or write error");
        retJson.put<std::string>("replyData",e.what());
        retJson.put<std::string>("replier","pandora-cache");

        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        retJson.put<std::string>("replyTime",now_str);
        std::stringstream ss;
        write_json(ss, retJson);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();
        return ss.str();
    }
    catch(exception& e) 
    {
        basic_ptree<std::string, std::string> retJson;
        retJson.put<int>("errorCode",CREATE_SESSION_UNKNOWN_ERROR);
        retJson.put<std::string>("message","create session unknown error");
        retJson.put<std::string>("replyData",e.what());
        retJson.put<std::string>("replier","pandora-cache");

        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        ////cout<<now_str<<endl;
        retJson.put<std::string>("replyTime",now_str);
        std::stringstream ss;
        write_json(ss, retJson);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();
        return ss.str();
    }
}
string QUERY_SESSION(const ptree& pt)
{
    try
    {   
        ptree pChild = pt.get_child("requestData");
        string token="";
        string value="";
        for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
        {
            token=it->second.get<string>("token");
            
            string tempkey="{KV_TOKEN}:"+token;
            string get_command="get "+tempkey;
            redisReply * reply=static_cast<redisReply*>(HiredisCommand<ThreadPoolCluster>::Command(cluster_p, tempkey.c_str(), get_command.c_str()));
            if(reply->str!=nullptr)
            {
                //cout<<reply->type<<endl;
              value+=reply->str;
              //retJson.put<std::string>("flow_number",value);
            }
        }
        //return
        basic_ptree<std::string, std::string> retJson;
        ptree value_tree;
        if(!value.empty())
        {
            std::istringstream is(value);
            read_json(is, value_tree);
        }
        
        retJson.put<int>("errorCode",200);
        retJson.put<std::string>("message","query successfully");
        // retJson.put<std::string>("replyData",value);
        retJson.add_child("replyData", value_tree);
        retJson.put<std::string>("replier","pandora-cache");
        //获取时间
        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        retJson.put<std::string>("replyTime",now_str);
        std::stringstream ss;
        write_json(ss, retJson);
        return ss.str();
    }
    catch(json_parser_error& e) 
    {
        basic_ptree<std::string, std::string> retJson;
        retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
        retJson.put<std::string>("message","json read or write error");
        retJson.put<std::string>("replyData",e.what());
        retJson.put<std::string>("replier","pandora-cache");

        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        retJson.put<std::string>("replyTime",now_str);
        std::stringstream ss;
        write_json(ss, retJson);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();
        return ss.str();
    }
    catch(exception& e) 
    {
        basic_ptree<std::string, std::string> retJson;
        retJson.put<int>("errorCode",CREATE_SESSION_UNKNOWN_ERROR);
        retJson.put<std::string>("message","create session unknown error");
        retJson.put<std::string>("replyData",e.what());
        retJson.put<std::string>("replier","pandora-cache");

        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        ////cout<<now_str<<endl;
        retJson.put<std::string>("replyTime",now_str);
        std::stringstream ss;
        write_json(ss, retJson);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();
        return ss.str();
    }
}
string DELETE_SESSION(const ptree& pt)
{
    try
    {   
        ptree pChild = pt.get_child("requestData");
        string token="";
        string value="";
        for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
        {
            token=it->second.get<string>("token");
            
            string tempkey="{KV_TOKEN}:"+token;
            string get_command="del "+tempkey;
            redisReply * reply=static_cast<redisReply*>(HiredisCommand<ThreadPoolCluster>::Command(cluster_p, tempkey.c_str(), get_command.c_str()));
            if(reply->str!=nullptr)
            {
                //cout<<reply->type<<endl;
              value+=reply->str;
              //retJson.put<std::string>("flow_number",value);
            }
        }
        //return
        basic_ptree<std::string, std::string> retJson;
        token="token:"+token;
        retJson.put<int>("errorCode",200);
        retJson.put<std::string>("message","delete successfully");
        retJson.put<std::string>("replyData",token);
        retJson.put<std::string>("replier","pandora-cache");
        //获取时间
        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        retJson.put<std::string>("replyTime",now_str);
        std::stringstream ss;
        write_json(ss, retJson);
        return ss.str();
    }
    catch(json_parser_error& e) 
    {
        basic_ptree<std::string, std::string> retJson;
        retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
        retJson.put<std::string>("message","json read or write error");
        retJson.put<std::string>("replyData",e.what());
        retJson.put<std::string>("replier","pandora-cache");

        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        retJson.put<std::string>("replyTime",now_str);
        std::stringstream ss;
        write_json(ss, retJson);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();
        return ss.str();
    }
    catch(exception& e) 
    {
        basic_ptree<std::string, std::string> retJson;
        retJson.put<int>("errorCode",CREATE_SESSION_UNKNOWN_ERROR);
        retJson.put<std::string>("message","create session unknown error");
        retJson.put<std::string>("replyData",e.what());
        retJson.put<std::string>("replier","pandora-cache");

        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        ////cout<<now_str<<endl;
        retJson.put<std::string>("replyTime",now_str);
        std::stringstream ss;
        write_json(ss, retJson);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();
        return ss.str();
    }
}
#endif	