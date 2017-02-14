#ifndef COMMON_RESOURCE_HPP
#define COMMON_RESOURCE_HPP
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
///露篓脪氓redis驴芒
#define KV_SYS_PARAMS 0
#define KV_MF 1
#define KV_SESSION 2
#define KV_VISIT_RECORDS 3
#define KV_SHOPPING_CART 4
#define KV_OBJ_SNAPSHOT 5
#define KV_OPERATION_LOG 6
// response error code define -8001 ~ -9000 赂么-10禄貌-5
//JSON_READ_OR_WRITE_ERROR(-8010, "json read or write error", "json 赂帽脢陆脦脢脤芒")
#define JSON_READ_OR_WRITE_ERROR -8010
//CREATE_SESSION_UNKNOWN_ERROR(-8020, "create session unknown error", "麓麓陆篓session脢卤脦麓脰陋碌脛麓铆脦贸")
#define CREATE_SESSION_UNKNOWN_ERROR -8020
//CREATE_SESSION_KEY_EXIST(-8025, "key already exist when create session", "麓麓陆篓session脢卤key脪脩戮颅麓忙脭脷")
#define CREATE_SESSION_KEY_EXIST -8025
//ADD_USERID_UNDER_SESSION_UNKNOWN_ERROR(-8030, "add userid unknown error", "脭枚录脫userid脢卤脦麓脰陋碌脛麓铆脦贸")
#define ADD_USERID_UNDER_SESSION_UNKNOWN_ERROR -8030
//ADD_USERID_KEY_NOT_EXIST(-8035, "key does not exist when add userid", "脭枚录脫userid脢卤key虏禄麓忙脭脷")
#define ADD_USERID_KEY_NOT_EXIST -8035
//DELETE_SESSION_UNKNOWN_ERROR(-8040, "del session unknown error", "脡戮鲁媒session脢卤脦麓脰陋碌脛麓铆脦贸")
#define DELETE_SESSION_UNKNOWN_ERROR -8040
//DELETE_SESSION_KEY_NOT_EXIST(-8045, "key does not exist when del session", "脡戮鲁媒session脢卤key虏禄麓忙脭脷")
#define DELETE_SESSION_KEY_NOT_EXIST -8045
//QUERY_SESSION_UNKNOWN_ERROR(-8050, "unknown error when query session ", "虏茅脩炉session脢卤脦麓脰陋碌脛麓铆脦贸")
#define QUERY_SESSION_UNKNOWN_ERROR -8050
//QUERY_SESSION_KEY_NOT_EXIST(-8055, "key does not exist when query session", "虏茅脩炉session脢卤key虏禄麓忙脭脷")
#define QUERY_SESSION_KEY_NOT_EXIST -8055
//UPDATE_SESSION_DEADLINE_UNKNOWN_ERROR(-8060, "update session unknown error", "赂眉脨脗session脢卤脦麓脰陋碌脛麓铆脦贸")
#define UPDATE_SESSION_DEADLINE_UNKNOWN_ERROR -8060
//UPDATE_SESSION_DEADLINE_KEY_NOT_EXIST(-8065, "key does not exist when update session", "赂眉脨脗session脢卤key虏禄麓忙脭脷")
#define UPDATE_SESSION_DEADLINE_KEY_NOT_EXIST -8065
//*********************************************************
//BATCH_CREATE_AREAS_KEY_EXIST(-8070, "key already exists when batch create areas", "脜煤脕驴脭枚录脫碌脴脟酶key脢卤key脪脩戮颅麓忙脭脷")
#define BATCH_CREATE_AREAS_KEY_EXIST -8070
//BATCH_CREATE_AREAS_UNKNOWN_ERROR(-8080, "unknown error when batch create areas", "脜煤脕驴脭枚录脫碌脴脟酶key脢卤脦麓脰陋麓铆脦贸")
#define BATCH_CREATE_AREAS_UNKNOWN_ERROR -8080
//UNKNOWN_ERROR(-8085, "unknown error", "脦麓脰陋麓铆脦贸")
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

//set global variable value ThreadPoolCluster::ptr_t cluster_p;拢卢set value through timer
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




//////only for test web server
void t_area(HttpServer& server)
{
	try
	{
	//set t_area:J4YVQ3SW2Y1KTJEWJWU7 "{\"area_id\":\"J4YVQ3SW2Y1KTJEWJWU7\",\"area_code\":\"1\",\"parent_area_code\":\"\",\"full_name\":\"Africa\",\"short_name\":\"Africa\",\"dr\":0,\"data_version\":1}"
    server.resource["^/t_area$"]["POST"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
        try {
            ptree pt;
			read_json(request->content, pt);
			
            string area_id=pt.get<string>("area_id");
			string area_code=pt.get<string>("area_code");
			string parent_area_code=pt.get<string>("parent_area_code");
			string full_name=pt.get<string>("full_name");
			string short_name=pt.get<string>("short_name");
			int dr=pt.get<int>("dr");
			int data_version=pt.get<int>("data_version");
			/*std::cout<<"area_id:"<<area_id<<endl;
			std::cout<<"area_code:"<<area_code<<endl;
			std::cout<<"parent_area_code:"<<parent_area_code<<endl;
			std::cout<<"full_name:"<<full_name<<endl;
			std::cout<<"short_name:"<<short_name<<endl;
			std::cout<<"dr:"<<dr<<endl;
			std::cout<<"data_version:"<<data_version<<endl;*/

			//********脰脴脨脗脝麓陆脫json掳眉虏垄脨麓脠脮脰戮潞脥redis**********************8
			//ptree pt;
			//pt.put ("foo", "bar");
			std::ostringstream buf; 
			write_json(buf, pt,false);
			std::string json = buf.str();
			//cout<<json<<endl;
			// write to redis
			Connection conn(redisHost, redisPort, redisPassword);
			if(!conn.set("t_area:"+area_id, json))
			{
				throw std::runtime_error(std::string("error set to redis"));
			}

			//******************************************************

			response << "HTTP/1.1 200 OK\r\nContent-Length: " << 3 << "\r\n\r\n" << "200";
            //response << "200";
        }
        catch(exception& e) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        }
    };
	}
	catch(exception& e) 
	{
          BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();
	}
}

#endif  