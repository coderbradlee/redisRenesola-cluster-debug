#ifndef SERVER_RESOURCE_BASE_HPP
#define	SERVER_RESOURCE_BASE_HPP

void post_deal_with_flow_number(HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request)
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

            string company=one_pair[0];
            string type=one_pair[1];
            string num=one_pair[2];
            string sub_type=one_pair[3];
            //UK,ZA,FR,IT,DE,TR,RU，这些先用新规则
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

#endif	