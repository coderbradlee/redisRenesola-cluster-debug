#ifndef SCM_RESOURCE_HPP
#define SCM_RESOURCE_HPP
#include "common.hpp"
void scm_supplier(HttpServer& server)
{
	try
	{
	//{
	// supplier_id:"",
	// supplier_no:"",
	// company_name_en:"",
	// status:"",
	// type="Group Supplier"
	// }
    server.resource["^/scm$"]["POST"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) 
    {
        try 
        {
            ptree pt;
			read_json(request->content, pt);
			
            string supplier_id=pt.get<string>("supplier_id");
            std::cout<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
			string supplier_no=pt.get<string>("supplier_no");
			std::cout<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
			string company_name_en=pt.get<string>("company_name_en");
			std::cout<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
			string status=pt.get<string>("status");
			std::cout<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
			string type=pt.get<string>("type");
			std::cout<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
			string keys="{scm_supplier}"+supplier_id;
			string hmset_command="hmset "+keys+" supplier_no "+supplier_no+" company_name_en "+company_name_en+" status "+status+" type "+type;
			redisReply * incr=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, keys.c_str(), hmset_command.c_str()));
        
        	freeReplyObject(incr);
	        ptime now = second_clock::local_time();  
	        string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
	        string temp="{\"status\":ok\",\"replyTime\" : \""+now_str+"\"}";
	        response <<"HTTP/1.1 200 OK\r\nContent-Length: " << temp.length() << "\r\n\r\n" <<temp;
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