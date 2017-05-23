#ifndef SERVER_RESOURCE_HPP
#define	SERVER_RESOURCE_HPP

#include "serverResource_base.hpp"
// #include "json_parser/json_map.hpp"
// #include "json_parser/json_fifo_map.hpp"
// #include "json_parser/json.hpp"
void deal_with_flow_number(HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request)
{
     try 
        {
            //BOOST_LOG_SEV(slg, notification)<<"request: "<<request->method<<" "<<request->path<<;
            //BOOST_LOG(test_lg::get())<<"request: "<<request->method<<" "<<request->path;initsink->flush();
            //cout<<request->path<<endl;
            string temp_flowno="/flowNo/";
            string left_path=request->path.substr(temp_flowno.length(), request->path.length());
            cout<<left_path<<endl;
            std::vector<std::string> one_pair;
            boost::split(one_pair,left_path , boost::is_any_of("/"));

            if(one_pair.size()>2)
            {
                deal_with_flow_number_with_systemno(response,one_pair);
                return;
            }
            string company=one_pair[0];
            string type=one_pair[1];
            //UK,ZA,FR,IT,DE,TR,RU，这些先用新规则
            if((company=="UK")||(company=="ZA")||(company=="FR")||(company=="IT")||(company=="DE")||(company=="TR")||(company=="RU")||(company=="PA")||(company=="US")||(company=="CA")||(company=="MX")||(company=="BR")||(company=="JP")||(company=="TH"))
            {
                type="OVERSEAS";
            }
            // if(company!="JS")
            // {
            //     type="OVERSEAS";
            // }
            string id_name="{"+company+"_"+type+"_"+"flow_number}:id";
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
void get_scm_flow_no(HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request)
{
     try 
        {
            //BOOST_LOG_SEV(slg, notification)<<"request: "<<request->method<<" "<<request->path<<;
            //BOOST_LOG(test_lg::get())<<"request: "<<request->method<<" "<<request->path;initsink->flush();
            //cout<<request->path<<endl;
            string temp_flowno="/scm_flow_no/";
            string left_path=request->path.substr(temp_flowno.length(), request->path.length());
            cout<<left_path<<endl;
            std::vector<std::string> one_pair;
            boost::split(one_pair,left_path , boost::is_any_of("/"));


            string company=one_pair[0];
            string type=one_pair[1];
            string way=one_pair[2];
            //UK,ZA,FR,IT,DE,TR,RU，这些先用新规则
            if(company.length()>3||type.length()>3)
            {
                string temp="path error";
                response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << temp.length()<< "\r\n\r\n" << temp;
                return;
            }
            if(way!="day"&&way!="month"&&way!="year")
            {
                string temp="flush way error";
                response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << temp.length()<< "\r\n\r\n" << temp;
                return;
            }
            //hincrby {scm_no} FR_PO_day_2017_03_09 1
            string id_name="{scm_no}";
            string dayormonthoryear;
            std::vector<std::string> hms;
            string which_day  =  to_iso_extended_string(second_clock::local_time().date());
            boost::split(hms,which_day , boost::is_any_of("-"));
            string year=hms[0];
            string month=hms[1];
            string day=hms[2];
            if(way=="day")
            {
                dayormonthoryear=which_day;
            }
            else if(way=="month")
            {
                dayormonthoryear=year+"-"+month;
            }
            else//year
            {
                dayormonthoryear=year;
            }
            string key=id_name+" "+company+"_"+type+"_"+way+"_"+dayormonthoryear;
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
        cout<<value<<":"<<__FILE__<<":"<<__LINE__<<endl;
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
void get_with_shipping_cost(HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request)
{
     try 
        {
            //BOOST_LOG_SEV(slg, notification)<<"request: "<<request->method<<" "<<request->path<<;
            //BOOST_LOG(test_lg::get())<<"request: "<<request->method<<" "<<request->path;initsink->flush();
            //cout<<request->path<<endl;
            cout<<__FILE__<<":"<<__LINE__<<endl;
            string temp_flowno="/ShippingCost/";
            string left_path=request->path.substr(temp_flowno.length(), request->path.length());
            cout<<left_path<<endl;
            std::vector<std::string> one_pair;
            boost::split(one_pair,left_path , boost::is_any_of("/"));


            string company=one_pair[0];
            string type=one_pair[1];
            //UK,ZA,FR,IT,DE,TR,RU，这些先用新规则
            // if((company=="UK")||(company=="ZA")||(company=="FR")||(company=="IT")||(company=="DE")||(company=="TR")||(company=="RU")||(company=="PA")||(company=="US")||(company=="CA")||(company=="MX")||(company=="BR")||(company=="JP")||(company=="TH"))
            // {
            //     type="OVERSEAS";
            // }
            // if(company!="JS")
            // {
            //     type="OVERSEAS";
            // }
            string id_name="{"+company+"_"+type+"_"+"ShippingCost}:id";
            //string incr_command="set "+id_name+" 1";
            string get_command="get "+id_name;
            cout<<id_name<<endl;
            //cout<<incr_command<<endl;
            cout<<get_command<<endl;
            
        //redisReply * incr=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, "{flow_number}:id", "incr {flow_number}:id"));
           // redisReply * incr=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, id_name.c_str(), incr_command.c_str()));
        //freeReplyObject(incr);
        //redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, "{flow_number}:id", "get {flow_number}:id"));
        cout<<__FILE__<<""<<__LINE__<<endl;
        redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, id_name.c_str(), get_command.c_str()));
        string value="0";
        //cout<<__LINE__<<endl;
        if(reply->str!=nullptr)
        {
            //cout<<reply->type<<endl;
          value=reply->str;
          //retJson.put<std::string>("flow_number",value);
        }

        freeReplyObject(reply);
        cout<<value<<":"<<__FILE__<<""<<__LINE__<<endl;
        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        //string temp="{\"flowNo\":\""+value+"\",\"replyTime\" : \""+now_str+"\"}";
        string temp="{\"ShippingCost-"+company+"-"+type+"\":"+value+"}";
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
void get_timezone(HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request)
{
     try 
        {
            cout<<__FILE__<<":"<<__LINE__<<endl;
            string temp_flowno="/timezone/";
            string left_path=request->path.substr(temp_flowno.length(), request->path.length());
            cout<<left_path<<":"<<__FILE__<<""<<__LINE__<<endl;
            
            string company=left_path;
            
            string id_name="{timezone}:"+company;
            //string incr_command="set "+id_name+" 1";
            string get_command="get "+id_name;
            cout<<id_name<<endl;
            //cout<<incr_command<<endl;
            cout<<get_command<<endl;
            
        
        cout<<__FILE__<<""<<__LINE__<<endl;
        redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, id_name.c_str(), get_command.c_str()));
        string value="0";
        //cout<<__LINE__<<endl;
        if(reply->str!=nullptr)
        {
            //cout<<reply->type<<endl;
          value=reply->str;
          //retJson.put<std::string>("flow_number",value);
        }

        freeReplyObject(reply);
        cout<<value<<":"<<__FILE__<<""<<__LINE__<<endl;
      
        string temp=value;
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
void post_with_shipping_cost(HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request)
{
     try 
        {
            //BOOST_LOG_SEV(slg, notification)<<"request: "<<request->method<<" "<<request->path<<;
            //BOOST_LOG(test_lg::get())<<"request: "<<request->method<<" "<<request->path;initsink->flush();
            //cout<<request->path<<endl;
            cout<<__FILE__<<":"<<__LINE__<<endl;
            string temp_flowno="/ShippingCost/";
            string left_path=request->path.substr(temp_flowno.length(), request->path.length());
            cout<<left_path<<":"<<__FILE__<<""<<__LINE__<<endl;
            std::vector<std::string> one_pair;
            boost::split(one_pair,left_path , boost::is_any_of("/"));


            string company=one_pair[0];
            string type=one_pair[1];
            //UK,ZA,FR,IT,DE,TR,RU，这些先用新规则
            // if((company=="UK")||(company=="ZA")||(company=="FR")||(company=="IT")||(company=="DE")||(company=="TR")||(company=="RU")||(company=="PA")||(company=="US")||(company=="CA")||(company=="MX")||(company=="BR")||(company=="JP")||(company=="TH"))
            // {
            //     type="OVERSEAS";
            // }
            // if(company!="JS")
            // {
            //     type="OVERSEAS";
            // }
            string id_name="{"+company+"_"+type+"_"+"ShippingCost}:id";
            //string incr_command="set "+id_name+" 1";
            string get_command="set "+id_name+" 1";
            cout<<id_name<<endl;
            //cout<<incr_command<<endl;
            cout<<get_command<<endl;
        redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, id_name.c_str(), get_command.c_str()));
        string value="0";
        //cout<<__LINE__<<endl;
        if(reply->str!=nullptr)
        {
            //cout<<reply->type<<endl;
          value=reply->str;
          //retJson.put<std::string>("flow_number",value);
        }

        freeReplyObject(reply);
        cout<<value<<":"<<__FILE__<<""<<__LINE__<<endl;
        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        //string temp="{\"flowNo\":\""+value+"\",\"replyTime\" : \""+now_str+"\"}";
        // string temp="{\"ShippingCost-"+company+"-"+type+"\":1"+value+"}";
        string temp="{\"errorCode\":\"200\"}";
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
void post_timezone(HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request)
{
    try 
    {
        cout<<__FILE__<<":"<<__LINE__<<endl;
        string temp_flowno="/timezone/";
        string left_path=request->path.substr(temp_flowno.length(), request->path.length());
        cout<<left_path<<":"<<__FILE__<<""<<__LINE__<<endl;
        std::vector<std::string> one_pair;
        boost::split(one_pair,left_path , boost::is_any_of("/"));


        string company=one_pair[0];
        string type=one_pair[1];
        
        string id_name="{timezone}:"+company;
        //string incr_command="set "+id_name+" 1";
        string get_command="set "+id_name+" "+type;
        cout<<id_name<<endl;
        //cout<<incr_command<<endl;
        cout<<get_command<<endl;
        redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, id_name.c_str(), get_command.c_str()));
        string value="0";
        //cout<<__LINE__<<endl;
        if(reply->str!=nullptr)
        {
            //cout<<reply->type<<endl;
          value=reply->str;
          //retJson.put<std::string>("flow_number",value);
        }
        freeReplyObject(reply);

        string temp="ok";
        cout<<temp<<":"<<__FILE__<<""<<__LINE__<<endl;
        
        response <<"HTTP/1.1 200 OK\r\nContent-Length: " << temp.length() << "\r\n\r\n" <<temp;
    }
    catch(json_parser_error& e) 
    {
        string temp="json error";
        response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << temp.length()<< "\r\n\r\n" << temp;
    }
    catch(exception& e) 
    {
        response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
    }
    catch(...) 
    {
        response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen("unknown error") << "\r\n\r\n" << "unknown error";
    }
}

int apollo(HttpServer& server,string url)
{
	try
	{
         server.resource["^/flowNo/*+$"]["GET"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) 
        {
            try 
            {
                cout<<request->path<<endl;
                ////cout<<__LINE__<<endl;
                string type="";
                string company="";
                string id_name="{"+type+"_"+company+"_"+"flow_number}:id";
                string incr_command="incr "+id_name;
                string get_command="get "+id_name;
                cout<<id_name<<endl;
                cout<<incr_command<<endl;
                cout<<get_command<<endl;
                //redisReply * incr=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, "{flow_number}:id", "incr {flow_number}:id"));
                redisReply * incr=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, id_name.c_str(), incr_command.c_str()));
                freeReplyObject(incr);
                //redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, "{flow_number}:id", "get {flow_number}:id"));
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

                ptime now = second_clock::local_time();  
                string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
                string temp="{\"flowNo\":"+value+",\"replyTime\" : \""+now_str+"\"}";
                // std::stringstream ss;
                // write_json(ss, retJson);
                // //在这里判断里面的children及childrens的值，如果为空，设置为空数组,用replace
                // string temp=ss.str();
                response <<"HTTP/1.1 200 OK\r\nContent-Length: " << temp.length() << "\r\n\r\n" <<temp;
            }
            catch(json_parser_error& e) 
            {
                string temp="json error";
                response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << temp.length()<< "\r\n\r\n" << temp;
                return -1;
            }
            catch(exception& e) {
                response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
                return -1;
            }
            catch(...) {
                response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen("unknown error") << "\r\n\r\n" << "unknown error";
                return -1;
            }
        };
        
        return 0;
    }
    catch(exception& e) 
    {
          BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();
          return -1;
    }
    catch(...) 
    {
          BOOST_LOG(test_lg::get())<<__LINE__<<": "<<"unknown error";
          return -1;
    }
}

void apollo_all(HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request)
{
    // cout<<"apollo_all:"<<__FILE__<<":"<<__LINE__<<endl;
    try {
        ptree pt;
        // cout<<"apollo_all:"<<request->content.rdbuf()<<":"<<__FILE__<<":"<<__LINE__<<endl;
        // boost::property_tree::wptree pt;
        
        // boost::property_tree::json_parser::read_json(jsonIStream,wptParse);

        read_json(request->content, pt);
        
        cout<<__LINE__<<endl;
        // string operation=pt.get<wstring>(L"operation");
        //string dataType=pt.get<string>("dataType");
        string operation=pt.get<string>("operation");
        // std::string text;
        // std::getline(request->content, text);
        // cout<<text<<endl;
        // const auto& j = nlohmann_map::json::parse(text);
 
        // const auto& operations = j["operation"];

        string retString;
        // string operation=operations;
        bool retBool;
        if((operation.compare("OVER_WRITE")==0))
        {
            // retString=OVER_WRITE_T_SYS_PARAMETER(pt);
        }
        else if((operation.compare("CREATE_SESSION")==0))
        {
            // retString=CREATE_SESSION_HTTP_SESSION(pt);
            cout<<__LINE__<<endl;
            retString=CREATE_SESSION_HTTP_SESSION2(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("QUERY_SESSION")==0))
        {
            // retString=CREATE_SESSION_HTTP_SESSION(pt);
            cout<<__LINE__<<endl;
            retString=QUERY_SESSION(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        // else if((operation.compare("BATCH_CREATE_AREAS")==0))
        // {
            
        //     retString=BATCH_CREATE_AREAS(pt);
        //     retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
        //     response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        // }
        
    }
    catch(json_parser_error& e) 
    {
        //cout<<e.what()<<endl;
        //{"errorCode":200,"message":"session read from cache[2] successfully","replyData":[{"sessionId":"01234567890123456789","value":{"userId":"01234567890123456789"}}],"replier":"pandora-cache","replyTime":"2015-05-25 08:00:00"}
        ptree retJson;
        retJson.put("errorCode",JSON_READ_OR_WRITE_ERROR);
        retJson.put("message","json parser error");
        retJson.put("replyData",e.what());
        retJson.put("replier","pandora-cache");

        ptime now = second_clock::local_time();  
        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
        ////cout<<now_str<<endl;
        retJson.put<std::string>("replyTime",now_str);
        std::stringstream ss;
        write_json(ss, retJson);
        ////cout<<ss.str();
        string retString=ss.str();
        retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
        response <<"HTTP/1.1 400 Bad Request\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        
    }
    catch(exception& e) {
        response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        
    }
    catch(...) {
        response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen("unknown error") << "\r\n\r\n" << "unknown error";
        
    }
    
}
void defaultindex(HttpServer& server)
{
    try
    {
        std::lock_guard<std::mutex> locker(lockRedis);
         server.default_resource["GET"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
        string filename="web";
        
        string path=request->path;
        cout<<path<<endl;
        string temp="/flowNo/";
        if(path.compare(0,temp.length(),temp) == 0)
        {
            deal_with_flow_number(response,request);
            return;
        }
        string temp0="/subFlowNo/";
        if(path.compare(0,temp0.length(),temp0) == 0)
        {
            deal_with_subflowno_number(response,request);
            return;
        }
        string temp2="/ShippingCost/";
        if(path.compare(0,temp2.length(),temp2) == 0)
        {
            cout<<__FILE__<<":"<<__LINE__<<endl;
            get_with_shipping_cost(response,request);
            return;
        }
        string temp3="/timezone/";
        if(path.compare(0,temp3.length(),temp3) == 0)
        {
            cout<<__FILE__<<":"<<__LINE__<<endl;
            get_timezone(response,request);
            return;
        }
        string temp4="/scm_flow_no/";
        if(path.compare(0,temp4.length(),temp4) == 0)
        {
            cout<<__FILE__<<":"<<__LINE__<<endl;
            get_scm_flow_no(response,request);
            return;
        }
        //Replace all ".." with "." (so we can't leave the web-directory)
        size_t pos;
        while((pos=path.find(".."))!=string::npos) {
            path.erase(pos, 1);
        }
        
        filename+=path;
        ifstream ifs;
        //A simple platform-independent file-or-directory check do not exist, but this works in most of the cases:
        if(filename.find('.')==string::npos) {
            if(filename[filename.length()-1]!='/')
                filename+='/';
            filename+="index.html";
        }
        ifs.open(filename, ifstream::in);
        
        if(ifs) {
            ifs.seekg(0, ios::end);
            size_t length=ifs.tellg();
            
            ifs.seekg(0, ios::beg);

            response << "HTTP/1.1 200 OK\r\nContent-Length: " << length << "\r\n\r\n";
            
            //read and send 128 KB at a time if file-size>buffer_size
            size_t buffer_size=131072;
            if(length>buffer_size) {
                vector<char> buffer(buffer_size);
                size_t read_length;
                while((read_length=ifs.read(&buffer[0], buffer_size).gcount())>0) {
                    response.stream.write(&buffer[0], read_length);
                    response << HttpServer::flush;
                }
            }
            else
                response << ifs.rdbuf();

            ifs.close();
        }
        else {
            string content="Could not open file "+filename;
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
        }
    };
        server.default_resource["POST"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) 
        {
            string filename="web";
            
            string path=request->path;
            // string temp="/flowNo/";
            // if(path.compare(0,temp.length(),temp) == 0)
            // {
            //     post_deal_with_flow_number(response,request);
            //     return;
            // }
            string temp2="/ShippingCost/";
            if(path.compare(0,temp2.length(),temp2) == 0)
            {
                post_with_shipping_cost(response,request);
                return;
            }  
            string temp3="/timezone/";
            if(path.compare(0,temp3.length(),temp3) == 0)
            {
                post_timezone(response,request);
                return;
            } 
            string temp4="/"+url;
            if(path.compare(0,temp4.length(),temp4) == 0)
            {
                apollo_all(response,request);
                return;
            } 
        };
    }
    catch(exception& e) 
    {
          BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();
    }
}
void serverRedisResource(HttpServer& server,string redisHost,string redisPort,string redisPassword,string url)
{
	try
	{
		//init redis connection pool

		 cluster_p = HiredisCommand<ThreadPoolCluster>::createCluster( redisHost.c_str(),boost::lexical_cast<int>(redisPort));

		//serverResource(server);
		// t_area(server);
		// //testget(server);
		// t_area_get(server);
		// t_function(server);
		// t_function_get(server);
		apollo(server,url);
		defaultindex(server);
	}
	catch(exception& e) 
	{
          BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();
	}
	catch(...) 
	{
         
	}
}

std::string&   replace_all(std::string&   str,const   std::string&   old_value,const   std::string&   new_value)     
{     
    while(true)   {     
        std::string::size_type   pos(0);     
        if(   (pos=str.find(old_value))!=std::string::npos   )     
            str.replace(pos,old_value.length(),new_value);     
        else   break;     
    }     
    return   str;     
}     
std::string&   replace_all_distinct(std::string&   str,const   std::string&   old_value,const   std::string&   new_value)     
{     
    for(std::string::size_type   pos(0);   pos!=std::string::npos;   pos+=new_value.length())   {     
        if(   (pos=str.find(old_value,pos))!=std::string::npos   )     
            str.replace(pos,old_value.length(),new_value);     
        else   break;     
    }     
    return   str;     
} 
#endif	