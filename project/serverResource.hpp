#ifndef SERVER_RESOURCE_HPP
#define	SERVER_RESOURCE_HPP

#include "serverResource_base.hpp"


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

			//********重新拼接json包并写日志和redis**********************8
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
void t_area_get(HttpServer& server)
{
	try
	{
	//get t_area:J4YVQ3SW2Y1KTJEWJWU7 
	//"{\"area_id\":\"J4YVQ3SW2Y1KTJEWJWU7\"}
	//return "{\"area_id\":\"J4YVQ3SW2Y1KTJEWJWU7\",\"area_code\":\"1\",\"parent_area_code\":\"\",\"full_name\":\"Africa\",\"short_name\":\"Africa\",\"dr\":0,\"data_version\":1}"
    server.resource["^/t_area_get$"]["POST"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request){
        try {
            ptree pt;
			read_json(request->content, pt);
			
            string area_id=pt.get<string>("area_id");
			
			
			/*std::ostringstream buf; 
			write_json(buf, pt,false);
			std::string json = buf.str();*/
			//cout<<json<<endl;
			// write to redis
			Connection conn(redisHost, redisPort, redisPassword);
			StringReply ret= conn.get("t_area:"+area_id);
			string retString;
			if(!ret.result().is_initialized())
			{
				throw std::runtime_error(std::string("error get info from redis"));
			}
			else
			{
				retString=(string)ret;
				cout<<retString<<endl;
			}
			//******************************************************

			response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" << retString;
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
void t_function(HttpServer& server)
{
	try
	{
	//set t_function:A1 "{\"function_id\":\"A1\",\"code\":\"a1\",\"name\":\"a1name\",\"description\":\"a1descrip\",\"up_level_function_id\":null,\"level\":1,\"type\":1,\"note\":\"Alibaba\",\"dr\":0,\"data_version\":1}"
    server.resource["^/t_function$"]["POST"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
        try {
            ptree pt;
			read_json(request->content, pt);
			
            string function_id=pt.get<string>("function_id");
			string code=pt.get<string>("code");
			string name=pt.get<string>("name");
			string description=pt.get<string>("description");
			string up_level_function_id=pt.get<string>("up_level_function_id");
			int level=pt.get<int>("level");
			int type=pt.get<int>("type");
			string note=pt.get<string>("note");
			int dr=pt.get<int>("dr");
			int data_version=pt.get<int>("data_version");
			//********重新拼接json包并写日志和redis**********************8
			//ptree pt;
			//pt.put ("foo", "bar");
			std::ostringstream buf; 
			write_json(buf, pt,false);
			std::string json = buf.str();
			//cout<<json<<endl;
			// write to redis
			Connection conn(redisHost, redisPort, redisPassword);
			if(!conn.set("t_function:"+function_id, json))
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
void t_function_get(HttpServer& server)
{
	try
	{
	//curl -X POST http://localhost:8080/t_function_get -d "{\"function_id\":\"A1\"}"
	//get t_function:A1 
	//"{\"function_id\":\"A1\",\"code\":\"a1\",\"name\":\"a1name\",\"description\":\"a1descrip\",\"up_level_function_id\":null,\"level\":\"1\",\"type\":\"1\",\"note\":\"Alibaba\",\"dr\":\"0\",\"data_version\":\"1\"}\n"
	//{"function_id":"A1","code":"a1","name":"a1name","description":"a1descrip","up_level_function_id":"null","level":"1","type":"1","note":"Alibaba","dr":"0","data_version":"1"}
    server.resource["^/t_function_get$"]["POST"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
        try {
            ptree pt;
			read_json(request->content, pt);
			
            string function_id=pt.get<string>("function_id");
			
			Connection conn(redisHost, redisPort, redisPassword);
			StringReply ret= conn.get("t_function:"+function_id);
			string retString;
			if(!ret.result().is_initialized())
			{
				throw std::runtime_error(std::string("error get info from redis"));
			}
			else
			{
				retString=(string)ret;
				cout<<retString<<endl;
			}
			//******************************************************

			response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" << retString;
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
        catch(exception& e) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        }
        catch(...) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen("unknown error") << "\r\n\r\n" << "unknown error";
        }
}



string OVER_WRITE_T_SYS_PARAMETER(ptree& pt)
{
	try
	{
	//在这里解析json并保存到redis里面，以dataType:parameter_id,表名:pk，实际为对象名:pk
						
	ptree pChild = pt.get_child("requestData");
	Connection conn(redisHost, redisPort, redisPassword);
	for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
	{
		//cout<<__LINE__<<endl;
		/*cout<<__LINE__<<it->first;*/
		/*cout<<it->second.get<string>("parameter_id")<<endl;
		cout<<it->second.get<string>("company_id")<<endl;
		cout<<it->second.get<string>("name")<<endl;
		cout<<it->second.get<string>("code")<<endl;
		cout<<it->second.get<int>("value")<<endl;
		cout<<it->second.get<string>("description")<<endl;
		cout<<it->second.get<int>("status")<<endl;
		cout<<it->second.get<string>("note")<<endl;
		cout<<it->second.get<string>("description")<<endl;
		cout<<it->second.get<int>("dr")<<endl;
		cout<<it->second.get<int>("data_version")<<endl;
		cout<<endl;*/

		/*std::ostringstream buf; 
		write_json(buf,it,false);
		std::string json = buf.str();
		cout<<json<<endl;
		if(!conn.set("T_SYS_PARAMETER:"+it->second.get<string>("parameter_id"), json))
		{
			throw std::runtime_error(std::string("error set to redis"));
		}*/


	}

	
	//	{
		//   "operation":"OVER_WRITE", /*覆盖写*/
		//   "dataType":"T_SYS_PARAMETER",
		//   "requestData":[{
		//      "parameter_id":"12345678901234567890",
		//   "company_id":"12345678901234567890",
		//   "name":"MAX_RETRY",
		//   "code":"MAX_RETRY",
		//   "value":3,
		//   "description":"最大重试次数",
		//   "status":0,
		//   "note":"及时生效",
		//   "dr":0,
		//   "data_version":1
		//},{
		//      "parameter_id":"09876543210987654321",
		//   "company_id":"12345678901234567890",
		//   "name":"CONNECTION_TIMEOUT",
		//   "code":"CONNECTION_TIMEOUT",
		//   "value":5,
		//   "description":"socket连接超时时长",
		//   "status":0,
		//   "note":"及时生效",
		//   "dr":0,
		//   "data_version":1
		//}],
		//"requestor":"apollo-employee-portal",
		//"requestTime":"2015-05-25 08:00:00"
		//}
	return "";
	}
	catch(exception& e) 
	{
          BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();
	}
}

//////about session
string CREATE_SESSION_HTTP_SESSION(const ptree& pt)
{
	try
	{	
		std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		string key="";
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			//cout<<it->second.get<string>("sessionId")<<endl;
			ptree pChildValue = it->second.get_child("value");

			std::ostringstream buf; 
			write_json(buf,(it->second),false);
			std::string json = buf.str();
			//cout<<json<<endl;
			key=it->second.get<string>("sessionId");

			string value="";
			if(!pChildValue.empty())
			{
				std::ostringstream bufValue; 
				write_json(bufValue,pChildValue,false);
				value = bufValue.str();			
			}
			string tempkey="{KV_SESSION}:"+key;
			//cout<<tempkey<<endl;
			
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			////cout<<"exists:"<<retint<<endl;
			if(retint)
			{
				basic_ptree<std::string, std::string> retJson;
				retJson.put<int>("errorCode",CREATE_SESSION_KEY_EXIST);
				retJson.put<std::string>("message","session key already exist");
				retJson.put<std::string>("replyData","");
				retJson.put<std::string>("replier","apollo-cache");

				ptime now = second_clock::local_time();  
				string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
				retJson.put<std::string>("replyTime",now_str);
				std::stringstream ss;
				write_json(ss, retJson);
				return ss.str();
			}
			if(!(bool)static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "set %s %s", tempkey.c_str(), value.c_str())))
			{
				throw std::runtime_error(std::string("error set to redis"));
			}
		}
		//return
		basic_ptree<std::string, std::string> retJson;
		
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message","session write to cache[KV_SESSION] successfully");
		retJson.put<std::string>("replyData",key);
		retJson.put<std::string>("replier","apollo-cache");
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
		retJson.put<std::string>("replier","apollo-cache");

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
		retJson.put<std::string>("replier","apollo-cache");

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
string ADD_USERID_UNDER_SESSION(const ptree& pt)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		string key="";
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			//cout<<it->second.get<string>("sessionId")<<endl;
			ptree pChildValue = it->second.get_child("value");

			std::ostringstream buf; 
			write_json(buf,(it->second),false);
			std::string json = buf.str();
			//cout<<json<<endl;
			key=it->second.get<string>("sessionId");
			//cout<<key<<endl;

			string value="";
			if(!pChildValue.empty())
			{
				std::ostringstream bufValue; 
				write_json(bufValue,pChildValue,false);
				value = bufValue.str();			
			}
			string tempkey="{KV_SESSION}:"+key;
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			if(retint)
			{
				HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"del %s", tempkey.c_str());
				//conn.del(key);
			}
			else
			{
				basic_ptree<std::string, std::string> retJson;
				retJson.put<int>("errorCode",ADD_USERID_KEY_NOT_EXIST);
				retJson.put<std::string>("message","key not exist");
				retJson.put<std::string>("replyData","");
				retJson.put<std::string>("replier","apollo-cache");

				ptime now = second_clock::local_time();  
				string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
				////cout<<now_str<<endl;
				retJson.put<std::string>("replyTime",now_str);
				
				std::stringstream ss;
				write_json(ss, retJson);
				return ss.str();
			}
			if(!(bool)static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "set %s %s", tempkey.c_str(), value.c_str())))
			//if(!conn.hset(key, "value", value))
			{
				throw std::runtime_error(std::string("error set to redis"));
			}
		}
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message","ADD_USERID to cache[KV_SESSION] successfully");
		retJson.put<std::string>("replyData",key);
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
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
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",ADD_USERID_UNDER_SESSION_UNKNOWN_ERROR);
		retJson.put<std::string>("message","ADD_USERID to cache[KV_SESSION] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}
string DELETE_SESSION(const ptree& pt)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		string key="";
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			key=it->second.get<string>("sessionId");
			
			string tempkey="{KV_SESSION}:"+key;
			//cout<<tempkey<<endl;
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			if(retint)
			{
				//conn.del(key);
				HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"del %s", tempkey.c_str());
				basic_ptree<std::string, std::string> retJson;
				retJson.put<int>("errorCode",200);
				retJson.put<std::string>("message","session remove from cache[KV_SESSION] successfully");
				retJson.put<std::string>("replyData",key);
				retJson.put<std::string>("replier","apollo-cache");

				ptime now = second_clock::local_time();  
				string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
				////cout<<now_str<<endl;
				retJson.put<std::string>("replyTime",now_str);
				std::stringstream ss;
				write_json(ss, retJson);
				////cout<<ss.str();
				return ss.str();
			}
			else
			{
				basic_ptree<std::string, std::string> retJson;
				retJson.put<int>("errorCode",DELETE_SESSION_KEY_NOT_EXIST);
				retJson.put<std::string>("message","key not exist");
				retJson.put<std::string>("replyData",key);
				retJson.put<std::string>("replier","apollo-cache");

				ptime now = second_clock::local_time();  
				string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
				////cout<<now_str<<endl;
				retJson.put<std::string>("replyTime",now_str);
				
				std::stringstream ss;
				write_json(ss, retJson);
				return ss.str();
			}
		}
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message","json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",DELETE_SESSION_UNKNOWN_ERROR);
		retJson.put<std::string>("message","session remove from cache[KV_SESSION] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}
string QUERY_SESSION(const ptree& pt)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		string key="";
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			key=it->second.get<string>("sessionId");
			////cout<<key<<endl;
			string tempkey="{KV_SESSION}:"+key;
			//cout<<tempkey<<endl;
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			if(retint)
			{
				ptree retJson;
				retJson.put("errorCode",200);
				retJson.put("message","session query from cache[KV_SESSION] successfully");
				ptree valuePtree;
				string value="";
				redisReply* valuekey=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"get %s", tempkey.c_str()));
				value=valuekey->str;//{"userId":"01234567890123456789"}
				freeReplyObject(valuekey);
				if(value.length()!=0)
				{
					value = value.substr(0, value.length()-1);
				}
				////cout<<__LINE__<<value<<endl;
				ptree childrenpt;
				childrenpt.put("sessionId", key);
				
				if(value.length()==0)
				{
					childrenpt.put("value", "");
				}
				else
				{
					istringstream valueStream(value);
					read_json(valueStream, valuePtree);
					childrenpt.add_child("value", valuePtree);
				}

				ptree vectorReplyData;
				vectorReplyData.push_back(std::make_pair("", childrenpt));
				retJson.add_child("replyData", vectorReplyData);
				retJson.put("replier","apollo-cache");

				ptime now = second_clock::local_time();  
				string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
				////cout<<now_str<<endl;
				retJson.put<std::string>("replyTime",now_str);
				std::stringstream ss;
				write_json(ss, retJson);
				////cout<<ss.str();
				return ss.str();
			}
			else
			{
				basic_ptree<std::string, std::string> retJson;
				retJson.put<int>("errorCode",QUERY_SESSION_KEY_NOT_EXIST);
				retJson.put<std::string>("message","session do not exsist in cache[KV_SESSION]");
				ptree childrenpt;
				childrenpt.put("sessionId", key);
				//childrenpt.add_child("value", valuePtree);

				ptree vectorReplyData;
				vectorReplyData.push_back(std::make_pair("", childrenpt));
				retJson.add_child("replyData", vectorReplyData);
				
				retJson.put<std::string>("replier","apollo-cache");

				ptime now = second_clock::local_time();  
				string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
				////cout<<now_str<<endl;
				retJson.put<std::string>("replyTime",now_str);
				
				std::stringstream ss;
				write_json(ss, retJson);
				return ss.str();
			}
		}
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message","json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",QUERY_SESSION_UNKNOWN_ERROR);
		retJson.put<std::string>("message","session query from cache[KV_SESSION] unknown error");
		ptree childrenpt;
		childrenpt.put("sessionId", "");
		//childrenpt.add_child("value", valuePtree);

		ptree vectorReplyData;
		vectorReplyData.push_back(std::make_pair("", childrenpt));
		retJson.add_child("replyData", vectorReplyData);
		
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}
string UPDATE_SESSION_DEADLINE(const ptree& pt)
{
	try
	{
		std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		string key="";
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			key=it->second.get<string>("sessionId");
			////cout<<key<<endl;
			string tempkey="{KV_SESSION}:"+key;
			//cout<<tempkey<<endl;
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			if(retint)
			{
				HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"del %s", tempkey.c_str());
				//conn.del(key);
				ptree pChildValue = it->second.get_child("value");
				string value="";
				if(!pChildValue.empty())
				{
					std::ostringstream bufValue; 
					write_json(bufValue,pChildValue,false);
					value = bufValue.str();			
				}
				
				if(!(bool)static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "set %s %s", tempkey.c_str(), value.c_str())))
			{
				throw std::runtime_error(std::string("error set to redis"));
				
			}
				ptree retJson;
				retJson.put("errorCode",200);
				retJson.put("message","deadline update to cache[KV_SESSION] successfully");
				retJson.put("replyData",key);
				retJson.put("replier","apollo-cache");

				ptime now = second_clock::local_time();  
				string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
				//////cout<<now_str<<endl;
				retJson.put<std::string>("replyTime",now_str);
				std::stringstream ss;
				write_json(ss, retJson);
				////cout<<ss.str();
				return ss.str();
			}
			else
			{
				basic_ptree<std::string, std::string> retJson;
				retJson.put<int>("errorCode",QUERY_SESSION_KEY_NOT_EXIST);
				retJson.put<std::string>("message","session do not exsist in cache[KV_SESSION]");
				retJson.put("replyData","");
				retJson.put<std::string>("replier","apollo-cache");

				ptime now = second_clock::local_time();  
				string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
				////cout<<now_str<<endl;
				retJson.put<std::string>("replyTime",now_str);
				
				std::stringstream ss;
				write_json(ss, retJson);
				return ss.str();
			}
		}
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message","json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UPDATE_SESSION_DEADLINE_UNKNOWN_ERROR);
		retJson.put<std::string>("message","deadline update to cache[KV_SESSION] unknown error");
		retJson.put("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}

////////about area
string BATCH_CREATE_AREAS(const ptree& pt)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		string key="",keyall;
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			std::ostringstream buf; 
			write_json(buf,(it->second),false);
			std::string json = buf.str();
			//cout<<json<<endl;
			key=it->second.get<string>("id");
			
			string tempkey="{KV_MF}:area:"+key;
			
			//cout<<__LINE__<<":"<<tempkey<<endl;
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			if(retint)
			{
				////cout<<"adfadgagdadgafdadfafda"<<endl;
				HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "del %s", tempkey.c_str());
				//conn.del(tempkey);
			}
			
			if(!(bool)static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "hset %s value %s", tempkey.c_str(), json.c_str()) ))
			{
				throw std::runtime_error(std::string("error set to redis"));
			}
			keyall+=tempkey+",";
		}
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message","BATCH_CREATE_AREAS to cache[KV_MF] successfully");
		retJson.put<std::string>("replyData",keyall);
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
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
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",BATCH_CREATE_AREAS_UNKNOWN_ERROR);
		retJson.put<std::string>("message","BATCH_CREATE_AREAS to cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}
string LIST_AREAS_BY_KEYS(const ptree& pt)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		string key="",keyall;
		basic_ptree<std::string, std::string> retJson,retchidren;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message","LIST_AREAS from cache[KV_MF] successfully");
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			std::ostringstream buf; 
			write_json(buf,(it->second),false);
			std::string json = buf.str();
			////cout<<json<<endl;
			key=it->second.get<string>("id");
			////cout<<key<<endl;
			string tempkey="{KV_MF}:area:"+key;
			////cout<<tempkey<<endl;
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			if(retint)
			{
				redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "hget %s value", tempkey.c_str()));
				string value="";				
				value=string(reply->str);				
				//////cout<<"value:"<<value<<endl;
				if(value.length()>0)
				{
					value = value.substr(0, value.length()-1);
				}
				ptree valuePtree;
				istringstream valueStream(value);
				read_json(valueStream, valuePtree);
				retchidren.push_back(std::make_pair("", valuePtree));
				
				freeReplyObject(reply);
			}	
		}
		retJson.add_child("replyData", retchidren);
		retJson.put<std::string>("replier","apollo-cache");
		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
		std::stringstream ss;
		write_json(ss, retJson);
		
		//在这里判断里面的children及childrens的值，如果为空，设置为空数组,用replace
		string temp=ss.str();
		temp=replace_all_distinct(temp,"\"children\": \"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\": \"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"children\":\"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\":\"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"dailyExchangeRateChildren\":\"\"","\"dailyExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"dailyExchangeRateChildren\": \"\"","\"dailyExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"periodAdjustmentExchangeRateChildren\":\"\"","\"periodAdjustmentExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"periodAdjustmentExchangeRateChildren\": \"\"","\"periodAdjustmentExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"taxFileChildren\":\"\"","\"taxFileChildren\":[]");
		temp=replace_all_distinct(temp,"\"taxFileChildren\": \"\"","\"taxFileChildren\":[]");
		temp=replace_all_distinct(temp,"\"replyData\":\"\"","\"replyData\":[]");
		temp=replace_all_distinct(temp,"\"replyData\": \"\"","\"replyData\":[]");
		return temp;
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message","json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message","LIST_AREAS from cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);

		return ss.str();
	}
}
string LIST_AREAS_BY_KEYWORDS(const ptree& pt)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		basic_ptree<std::string, std::string> retJson,retchidren;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message","LIST_AREAS all from cache[KV_MF] successfully");

		//获取所有key
		string tempkey="{KV_MF}:area:*";
		//cout<<tempkey<<endl;
		redisReply* reply;
		HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str());
		//执行此命令可以将node转向到含有此key的node
		
		reply = static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"keys %s", tempkey.c_str()));
		//std::string tempkey;
		/*cout<<__LINE__<<":"<<reply->type<<endl;
		cout<<__LINE__<<":"<<reply->elements<<endl;*/
		if(reply->type==REDIS_REPLY_ARRAY&&reply->elements>0)
		{
			redisReply** retkey=reply->element;
			for(int i=0;i<reply->elements;++i)
			{
				//cout<<retkey[i]->str<<endl;
		
				redisReply* tempreply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,retkey[i]->str,"hget %s value", retkey[i]->str));
				string value= tempreply->str;
				value = value.substr(0, value.length()-1);
				ptree valuePtree;
				istringstream valueStream(value);
				read_json(valueStream, valuePtree);
			
				retchidren.push_back(std::make_pair("", valuePtree));	
				freeReplyObject(tempreply);
			}
		}
		freeReplyObject(reply);
		retJson.add_child("replyData", retchidren);
		retJson.put<std::string>("replier","apollo-cache");
		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
		std::stringstream ss;
		write_json(ss, retJson);
		//在这里判断里面的children及childrens的值，如果为空，设置为空数组,用replace
		string temp=ss.str();
		//temp=temp.replace(temp.find("\"children\":\"\""), 1, "\"children\":[]");
		temp=replace_all_distinct(temp,"\"children\": \"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\": \"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"children\":\"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\":\"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"dailyExchangeRateChildren\":\"\"","\"dailyExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"dailyExchangeRateChildren\": \"\"","\"dailyExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"periodAdjustmentExchangeRateChildren\":\"\"","\"periodAdjustmentExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"periodAdjustmentExchangeRateChildren\": \"\"","\"periodAdjustmentExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"taxFileChildren\":\"\"","\"taxFileChildren\":[]");
		temp=replace_all_distinct(temp,"\"taxFileChildren\": \"\"","\"taxFileChildren\":[]");
		temp=replace_all_distinct(temp,"\"replyData\":\"\"","\"replyData\":[]");
		temp=replace_all_distinct(temp,"\"replyData\": \"\"","\"replyData\":[]");
		//cout<<__LINE__<<":"<<temp<<endl;
		return temp;
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message","json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message","LIST_AREAS all from cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}
string DELETE_AREAS_BY_KEYS(const ptree& pt)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		string key="",keyall="";
		basic_ptree<std::string, std::string> retJson,retchidren;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message","DELETE_AREAS from cache[KV_MF] successfully");
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			std::ostringstream buf; 
			write_json(buf,(it->second),false);
			std::string json = buf.str();
			//cout<<json<<endl;
			key=it->second.get<string>("id");
			//cout<<key<<endl;

			string tempkey="{KV_MF}:area:"+key;
			
			//cout<<__LINE__<<":"<<tempkey<<endl;
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			if(retint)
			{
				//cout<<"adfadgagdadgafdadfafda"<<endl;
				HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "del %s", tempkey.c_str());
				//conn.del(tempkey);
				keyall+=tempkey+",";
			}
		}
		if(keyall.length() == 0)
		{
			throw std::runtime_error(std::string("key does not exist"));
		}
		retJson.put<std::string>("replyData", keyall);
		retJson.put<std::string>("replier","apollo-cache");
		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
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
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message","DELETE_AREAS from cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}
string DELETE_AREAS_BY_KEYWORDS(const ptree& pt)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
	
		basic_ptree<std::string, std::string> retJson,retchidren;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message","DELETE_AREAS all from cache[KV_MF] successfully");

		std::string keyall="";
		//获取所有key
		string tempkey="{KV_MF}:area:*";
		//cout<<tempkey<<endl;
		redisReply* reply;
		HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str());
		//执行此命令可以将node转向到含有此key的node
		
		reply = static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"keys %s", tempkey.c_str()));
		//std::string tempkey;
		/*cout<<__LINE__<<":"<<reply->type<<endl;
		cout<<__LINE__<<":"<<reply->elements<<endl;*/
		if(reply->type==REDIS_REPLY_ARRAY&&reply->elements>0)
		{
			redisReply** retkey=reply->element;
			for(int i=0;i<reply->elements;++i)
			{
				//cout<<retkey[i]->str<<endl;
		
				redisReply* tempreply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,retkey[i]->str,"del %s", retkey[i]->str));
				
				freeReplyObject(tempreply);
				string temp(retkey[i]->str);
				keyall+=temp+",";
			}
		}
		if(keyall.length() == 0)
		{
			throw std::runtime_error(std::string("no keys deleted"));
		}
		retJson.put<std::string>("replyData", keyall);
		retJson.put<std::string>("replier","apollo-cache");
		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
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
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message","DELETE_AREAS all from cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}

/////////about language
string BATCH_CREATE_LANGUAGE(const ptree& pt)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		string key="",keyall;
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			std::ostringstream buf; 
			write_json(buf,(it->second),false);
			std::string json = buf.str();
			//cout<<json<<endl;
			key=it->second.get<string>("id");
			//cout<<key<<endl;

			string tempkey="{KV_MF}:language:"+key;
			////cout<<__LINE__<<":"<<tempkey<<endl;
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			if(retint)
			{
				//cout<<"adfadgagdadgafdadfafda"<<endl;
				HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "del %s", tempkey.c_str());
				//conn.del(tempkey);
			}
			if(!(bool)static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "hset %s value %s", tempkey.c_str(), json.c_str()) ))
			//if(!conn.hset(tempkey, "value", json))
			{
				throw std::runtime_error(std::string("error set to redis"));
			}
			keyall+=tempkey+",";
		}
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message","BATCH_CREATE_LANGUAGE to cache[KV_MF] successfully");
		retJson.put<std::string>("replyData",keyall);
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
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
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message","BATCH_CREATE_LANGUAGE to cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}
string LIST_LANGUAGE_BY_KEYS(const ptree& pt)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		string key="",keyall;
		basic_ptree<std::string, std::string> retJson,retchidren;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message","LIST_LANGUAGE from cache[KV_MF] successfully");
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			std::ostringstream buf; 
			write_json(buf,(it->second),false);
			std::string json = buf.str();
			//cout<<json<<endl;
			key=it->second.get<string>("id");
			//cout<<key<<endl;

			string tempkey="{KV_MF}:language:"+key;
			
			//cout<<tempkey<<endl;
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			if(retint)
			{
				redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "hget %s value", tempkey.c_str()));
				string value="";
				if(reply->str!=nullptr)
				{
					string value(reply->str);
				
					//cout<<"value:"<<value<<endl;
					//freeReplyObject( reply );
					//string value=conn.hget(tempkey,"value");
					value = value.substr(0, value.length()-1);
				
					ptree valuePtree;
					istringstream valueStream(value);
					read_json(valueStream, valuePtree);
					retchidren.push_back(std::make_pair("", valuePtree));
				}
				freeReplyObject(reply);
			}
		}
		retJson.add_child("replyData", retchidren);
		retJson.put<std::string>("replier","apollo-cache");
		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
		std::stringstream ss;
		write_json(ss, retJson);
		//在这里判断里面的children及childrens的值，如果为空，设置为空数组,用replace
		string temp=ss.str();
		//temp=temp.replace(temp.find("\"children\":\"\""), 1, "\"children\":[]");
		temp=replace_all_distinct(temp,"\"children\": \"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\": \"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"children\":\"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\":\"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"replyData\":\"\"","\"replyData\":[]");
		temp=replace_all_distinct(temp,"\"replyData\": \"\"","\"replyData\":[]");
		////cout<<__LINE__<<":"<<temp<<endl;
		return temp;
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message","json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message","LIST_LANGUAGE from cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}
string LIST_LANGUAGE_BY_KEYWORDS(const ptree& pt)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		basic_ptree<std::string, std::string> retJson,retchidren;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message","LIST_LANGUAGE all from cache[KV_MF] successfully");

		//获取所有key
		string tempkey="{KV_MF}:language:*";
		//cout<<tempkey<<endl;
		redisReply* reply;
		HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str());
		//执行此命令可以将node转向到含有此key的node
		////cout<<__LINE__<<":"<<reply->type<<endl;
		////cout<<__LINE__<<":"<<reply->integer<<endl;

		reply = static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"keys %s", tempkey.c_str()));
		//std::string tempkey;
		/*//cout<<__LINE__<<":"<<reply->type<<endl;
		//cout<<__LINE__<<":"<<reply->elements<<endl;*/
		if(reply->type==REDIS_REPLY_ARRAY&&reply->elements>0)
		{
			redisReply** retkey=reply->element;
			for(int i=0;i<reply->elements;++i)
			{
				//cout<<retkey[i]->str<<endl;
		
				redisReply* tempreply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,retkey[i]->str,"hget %s value", retkey[i]->str));
				string value= tempreply->str;
				value = value.substr(0, value.length()-1);
				ptree valuePtree;
				istringstream valueStream(value);
				read_json(valueStream, valuePtree);
			
				retchidren.push_back(std::make_pair("", valuePtree));	
				freeReplyObject(tempreply);
			}
		}
		freeReplyObject(reply);
		retJson.add_child("replyData", retchidren);
		retJson.put<std::string>("replier","apollo-cache");
		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
		std::stringstream ss;
		write_json(ss, retJson);
		//在这里判断里面的children及childrens的值，如果为空，设置为空数组,用replace
		string temp=ss.str();
		//temp=temp.replace(temp.find("\"children\":\"\""), 1, "\"children\":[]");
		temp=replace_all_distinct(temp,"\"children\": \"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\": \"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"children\":\"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\":\"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"replyData\":\"\"","\"replyData\":[]");
		temp=replace_all_distinct(temp,"\"replyData\": \"\"","\"replyData\":[]");
		////cout<<__LINE__<<":"<<temp<<endl;
		return temp;
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message","json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message","LIST_LANGUAGE all from cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}

//////about shipvia
string BATCH_CREATE_SHIPVIA(const ptree& pt)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		string key="",keyall;
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			std::ostringstream buf; 
			write_json(buf,(it->second),false);
			std::string json = buf.str();
			//cout<<json<<endl;
			key=it->second.get<string>("id");
			//cout<<key<<endl;

			string tempkey="{KV_MF}:ship:"+key;
			//cout<<__LINE__<<":"<<tempkey<<endl;
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			if(retint)
			{
				////cout<<"adfadgagdadgafdadfafda"<<endl;
				HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "del %s", tempkey.c_str());
				//conn.del(tempkey);
			}
			if(!(bool)static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "hset %s value %s", tempkey.c_str(), json.c_str()) ))
			{
				throw std::runtime_error(std::string("error set to redis"));
			}
			keyall+=tempkey+",";
		}
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message","BATCH_CREATE_SHIPVIA to cache[KV_MF] successfully");
		retJson.put<std::string>("replyData",keyall);
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
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
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message","BATCH_CREATE_SHIPVIA to cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}
string LIST_SHIPVIA_BY_KEYS(const ptree& pt)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		string key="",keyall;
		basic_ptree<std::string, std::string> retJson,retchidren;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message","LIST_SHIPVIA from cache[KV_MF] successfully");
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			std::ostringstream buf; 
			write_json(buf,(it->second),false);
			std::string json = buf.str();
			//cout<<json<<endl;
			key=it->second.get<string>("id");
			//cout<<key<<endl;

			string tempkey="{KV_MF}:ship:"+key;
			
			//cout<<tempkey<<endl;
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			if(retint)
			{
				redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "hget %s value", tempkey.c_str()));
				string value="";
				if(reply->str!=nullptr)
				{
					string value(reply->str);
				
					//cout<<"value:"<<value<<endl;
					//freeReplyObject( reply );
					//string value=conn.hget(tempkey,"value");
					value = value.substr(0, value.length()-1);
				
					ptree valuePtree;
					istringstream valueStream(value);
					read_json(valueStream, valuePtree);
					retchidren.push_back(std::make_pair("", valuePtree));
				}
				freeReplyObject(reply);
			}
		}
		retJson.add_child("replyData", retchidren);
		retJson.put<std::string>("replier","apollo-cache");
		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
		std::stringstream ss;
		write_json(ss, retJson);
		//在这里判断里面的children及childrens的值，如果为空，设置为空数组,用replace
		string temp=ss.str();
		//temp=temp.replace(temp.find("\"children\":\"\""), 1, "\"children\":[]");
		temp=replace_all_distinct(temp,"\"children\": \"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\": \"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"children\":\"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\":\"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"replyData\":\"\"","\"replyData\":[]");
		temp=replace_all_distinct(temp,"\"replyData\": \"\"","\"replyData\":[]");
		////cout<<__LINE__<<":"<<temp<<endl;
		return temp;
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message","json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message","LIST_SHIPVIA from cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}
string LIST_SHIPVIA_BY_KEYWORDS(const ptree& pt)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		basic_ptree<std::string, std::string> retJson,retchidren;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message","LIST_SHIPVIA all from cache[KV_MF] successfully");

		//获取所有key
		string tempkey="{KV_MF}:ship:*";
		//cout<<tempkey<<endl;
		redisReply* reply;
		HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str());
		//执行此命令可以将node转向到含有此key的node
		////cout<<__LINE__<<":"<<reply->type<<endl;
		////cout<<__LINE__<<":"<<reply->integer<<endl;

		reply = static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"keys %s", tempkey.c_str()));
		//std::string tempkey;
		/*//cout<<__LINE__<<":"<<reply->type<<endl;
		//cout<<__LINE__<<":"<<reply->elements<<endl;*/
		if(reply->type==REDIS_REPLY_ARRAY&&reply->elements>0)
		{
			redisReply** retkey=reply->element;
			for(int i=0;i<reply->elements;++i)
			{
				//cout<<retkey[i]->str<<endl;
		
				redisReply* tempreply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,retkey[i]->str,"hget %s value", retkey[i]->str));
				string value= tempreply->str;
				value = value.substr(0, value.length()-1);
				ptree valuePtree;
				istringstream valueStream(value);
				read_json(valueStream, valuePtree);
			
				retchidren.push_back(std::make_pair("", valuePtree));	
				freeReplyObject(tempreply);
			}
		}
		freeReplyObject(reply);
		retJson.add_child("replyData", retchidren);
		retJson.put<std::string>("replier","apollo-cache");
		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
		std::stringstream ss;
		write_json(ss, retJson);
		//在这里判断里面的children及childrens的值，如果为空，设置为空数组,用replace
		string temp=ss.str();
		//temp=temp.replace(temp.find("\"children\":\"\""), 1, "\"children\":[]");
		temp=replace_all_distinct(temp,"\"children\": \"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\": \"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"children\":\"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\":\"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"replyData\":\"\"","\"replyData\":[]");
		temp=replace_all_distinct(temp,"\"replyData\": \"\"","\"replyData\":[]");
		////cout<<__LINE__<<":"<<temp<<endl;
		return temp;
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message","json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message","LIST_SHIPVIA all from cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}

/////////general method 
string GENERAL_BATCH_CREATE(const ptree& pt,string keyTitle,string operation)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		string key="",keyall;
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			std::ostringstream buf; 
			write_json(buf,(it->second),false);
			std::string json = buf.str();
			//cout<<json<<endl;
			key=it->second.get<string>("id");
			////cout<<key<<endl;

			string tempkey=keyTitle+":"+key;
			//cout<<__LINE__<<":"<<tempkey<<endl;
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			if(retint)
			{
				////cout<<"adfadgagdadgafdadfafda"<<endl;
				HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "del %s", tempkey.c_str());
				//conn.del(tempkey);
			}
			
			
			if(!(bool)static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "hset %s value %s", tempkey.c_str(), json.c_str()) ))
			//if(!conn.hset(tempkey, "value", json))
			{
				throw std::runtime_error(std::string("error set to redis"));
			}
			keyall+=tempkey+",";
		}
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message",operation+" to cache[KV_MF] successfully");
		retJson.put<std::string>("replyData",keyall);
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message",operation+" to cache[KV_MF]:json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message",operation+" to cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}
string GENERAL_LIST_BY_KEYS(const ptree& pt,string keyTitle,string operation)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		string key="",keyall;
		basic_ptree<std::string, std::string> retJson,retchidren;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message",operation+" from cache[KV_MF] successfully");
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			std::ostringstream buf; 
			write_json(buf,(it->second),false);
			std::string json = buf.str();
			//cout<<json<<endl;
			key=it->second.get<string>("id");

			string tempkey=keyTitle+":"+key;
			//cout<<tempkey<<endl;
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			if(retint)
			{
				redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "hget %s value", tempkey.c_str()));
				string value="";
				if(reply->str!=nullptr)
				{
					string value(reply->str);
				
					//cout<<"value:"<<value<<endl;
					//freeReplyObject( reply );
					//string value=conn.hget(tempkey,"value");
					value = value.substr(0, value.length()-1);
				
					ptree valuePtree;
					istringstream valueStream(value);
					read_json(valueStream, valuePtree);
					retchidren.push_back(std::make_pair("", valuePtree));
				}
				freeReplyObject(reply);
			}	
		}
		retJson.add_child("replyData", retchidren);
		retJson.put<std::string>("replier","apollo-cache");
		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
		std::stringstream ss;
		write_json(ss, retJson);
		//在这里判断里面的children及childrens的值，如果为空，设置为空数组,用replace
		string temp=ss.str();
		//temp=temp.replace(temp.find("\"children\":\"\""), 1, "\"children\":[]");
		temp=replace_all_distinct(temp,"\"children\": \"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\": \"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"children\":\"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\":\"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"dailyExchangeRateChildren\":\"\"","\"dailyExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"dailyExchangeRateChildren\": \"\"","\"dailyExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"periodAdjustmentExchangeRateChildren\":\"\"","\"periodAdjustmentExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"periodAdjustmentExchangeRateChildren\": \"\"","\"periodAdjustmentExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"taxFileChildren\":\"\"","\"taxFileChildren\":[]");
		temp=replace_all_distinct(temp,"\"taxFileChildren\": \"\"","\"taxFileChildren\":[]");
		temp=replace_all_distinct(temp,"\"replyData\":\"\"","\"replyData\":[]");
		temp=replace_all_distinct(temp,"\"replyData\": \"\"","\"replyData\":[]");
		////cout<<__LINE__<<":"<<temp<<endl;
		return temp;
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message",operation+" from cache[KV_MF]:json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message",operation+" from cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}
string GENERAL_LIST_BY_KEYWORDS(const ptree& pt,string keyTitle,string operation)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		basic_ptree<std::string, std::string> retJson,retchidren;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message",operation+" all from cache[KV_MF] successfully");

		//获取所有key
		string tempkey=keyTitle+":*";
		//cout<<tempkey<<endl;
		redisReply* reply;
		HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str());
		//执行此命令可以将node转向到含有此key的node
		////cout<<__LINE__<<":"<<reply->type<<endl;
		////cout<<__LINE__<<":"<<reply->integer<<endl;

		reply = static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"keys %s", tempkey.c_str()));
		//std::string tempkey;
		/*//cout<<__LINE__<<":"<<reply->type<<endl;
		//cout<<__LINE__<<":"<<reply->elements<<endl;*/
		if(reply->type==REDIS_REPLY_ARRAY&&reply->elements>0)
		{
			redisReply** retkey=reply->element;
			for(int i=0;i<reply->elements;++i)
			{
				//cout<<retkey[i]->str<<endl;
		
				redisReply* tempreply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,retkey[i]->str,"hget %s value", retkey[i]->str));
				string value= tempreply->str;
				value = value.substr(0, value.length()-1);
				ptree valuePtree;
				istringstream valueStream(value);
				read_json(valueStream, valuePtree);
			
				retchidren.push_back(std::make_pair("", valuePtree));	
				freeReplyObject(tempreply);
			}
		}
		freeReplyObject(reply);
		retJson.add_child("replyData", retchidren);
		retJson.put<std::string>("replier","apollo-cache");
		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
		std::stringstream ss;
		write_json(ss, retJson);
		//在这里判断里面的children及childrens的值，如果为空，设置为空数组,用replace
		string temp=ss.str();
		//temp=temp.replace(temp.find("\"children\":\"\""), 1, "\"children\":[]");
		temp=replace_all_distinct(temp,"\"children\": \"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\": \"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"children\":\"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\":\"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"dailyExchangeRateChildren\":\"\"","\"dailyExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"dailyExchangeRateChildren\": \"\"","\"dailyExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"periodAdjustmentExchangeRateChildren\":\"\"","\"periodAdjustmentExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"periodAdjustmentExchangeRateChildren\": \"\"","\"periodAdjustmentExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"taxFileChildren\":\"\"","\"taxFileChildren\":[]");
		temp=replace_all_distinct(temp,"\"taxFileChildren\": \"\"","\"taxFileChildren\":[]");
		temp=replace_all_distinct(temp,"\"replyData\":\"\"","\"replyData\":[]");
		temp=replace_all_distinct(temp,"\"replyData\": \"\"","\"replyData\":[]");
		////cout<<__LINE__<<":"<<temp<<endl;
		return temp;
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message",operation+" all from cache[KV_MF]:json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message",operation+" all from cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		//cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}

////////about role
string SET_USER_ROLE(const ptree& pt,string keyTitle,string operation)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		string key="",keyall;
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			std::ostringstream buf; 
			write_json(buf,(it->second),false);
			std::string json = buf.str();
			//cout<<json<<endl;
			key=it->second.get<string>("systemAccountId");
			
			string tempkey=keyTitle+":"+key;
			//cout<<tempkey<<endl;
			
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			////cout<<"exists:"<<retint<<endl;
			if(retint)
			{
				HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "del %s", tempkey.c_str());
			}
			if(!(bool)static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "hset %s value %s", tempkey.c_str(), json.c_str()) ))
			{
				throw std::runtime_error(std::string("error set to redis"));
			}
			keyall+=tempkey+",";
		}
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message",operation+" to cache[KV_MF] successfully");
		retJson.put<std::string>("replyData",keyall);
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message",operation+" to cache[KV_MF]:json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message",operation+" to cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}
string GET_USER_ROLE(const ptree& pt,string keyTitle,string operation)
{
	try
	{	std::lock_guard<std::mutex> locker(lockRedis);
		ptree pChild = pt.get_child("requestData");
		
		string key="",keyall;
		basic_ptree<std::string, std::string> retJson,retchidren;
		retJson.put<int>("errorCode",200);
		retJson.put<std::string>("message",operation+" from cache[KV_MF] successfully");
		for (ptree::iterator it = pChild.begin(); it != pChild.end(); ++it)
		{
			std::ostringstream buf; 
			write_json(buf,(it->second),false);
			std::string json = buf.str();
			//cout<<json<<endl;
			key=it->second.get<string>("systemAccountId");
			//cout<<key<<endl;

			string tempkey=keyTitle+":"+key;
			
			//cout<<tempkey<<endl;
			redisReply* exists=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p,tempkey.c_str(),"exists %s", tempkey.c_str()));
			int retint=exists->integer;
			freeReplyObject(exists);
			if(retint)
			{

				redisReply * reply=static_cast<redisReply*>( HiredisCommand<ThreadPoolCluster>::Command( cluster_p, tempkey.c_str(), "hget %s value", tempkey.c_str()));
				string value="";
				//cout<<__LINE__<<endl;
				if(reply->str!=nullptr)
				{
					//cout<<reply->type<<endl;
					string value(reply->str);
				    //cout<<reply->str<<endl;
					//cout<<"value:"<<value<<endl;
					//freeReplyObject( reply );
					//string value=conn.hget(tempkey,"value");
					value = value.substr(0, value.length()-1);
				
					ptree valuePtree;
					istringstream valueStream(value);
					read_json(valueStream, valuePtree);
					retchidren.push_back(std::make_pair("", valuePtree));
				}
				freeReplyObject(reply);
			}
		}
		retJson.add_child("replyData", retchidren);
		retJson.put<std::string>("replier","apollo-cache");
		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
		std::stringstream ss;
		write_json(ss, retJson);
		//在这里判断里面的children及childrens的值，如果为空，设置为空数组,用replace
		string temp=ss.str();
		//temp=temp.replace(temp.find("\"children\":\"\""), 1, "\"children\":[]");
		temp=replace_all_distinct(temp,"\"children\": \"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\": \"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"children\":\"\"","\"children\":[]");
		temp=replace_all_distinct(temp,"\"childrens\":\"\"","\"childrens\":[]");
		temp=replace_all_distinct(temp,"\"dailyExchangeRateChildren\":\"\"","\"dailyExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"dailyExchangeRateChildren\": \"\"","\"dailyExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"periodAdjustmentExchangeRateChildren\":\"\"","\"periodAdjustmentExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"periodAdjustmentExchangeRateChildren\": \"\"","\"periodAdjustmentExchangeRateChildren\":[]");
		temp=replace_all_distinct(temp,"\"taxFileChildren\":\"\"","\"taxFileChildren\":[]");
		temp=replace_all_distinct(temp,"\"taxFileChildren\": \"\"","\"taxFileChildren\":[]");
		temp=replace_all_distinct(temp,"\"replyData\":\"\"","\"replyData\":[]");
		temp=replace_all_distinct(temp,"\"replyData\": \"\"","\"replyData\":[]");
		////cout<<__LINE__<<":"<<temp<<endl;
		return temp;
	}
	catch(json_parser_error& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",JSON_READ_OR_WRITE_ERROR);
		retJson.put<std::string>("message",operation+" from cache[KV_MF]:json read or write error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
	catch(exception& e) 
	{
		basic_ptree<std::string, std::string> retJson;
		retJson.put<int>("errorCode",UNKNOWN_ERROR);
		retJson.put<std::string>("message",operation+" from cache[KV_MF] unknown error");
		retJson.put<std::string>("replyData",e.what());
		retJson.put<std::string>("replier","apollo-cache");

		ptime now = second_clock::local_time();  
		string now_str  =  to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());  
		////cout<<now_str<<endl;
		retJson.put<std::string>("replyTime",now_str);
        BOOST_LOG(test_lg::get())<<__LINE__<<": "<<e.what();

		std::stringstream ss;
		write_json(ss, retJson);
		return ss.str();
	}
}

int apollo(HttpServer& server,string url)
{
	try
	{
         server.resource["^/flowNo/*+$"]["GET"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
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
    cout<<"apollo_all:"<<__FILE__<<":"<<__LINE__<<endl;
    try {
        ptree pt;
        cout<<url<<__FILE__<<__LINE__<<endl;
        read_json(request->content, pt);
        
        ////cout<<__LINE__<<endl;
        string operation=pt.get<string>("operation");
        //string dataType=pt.get<string>("dataType");
        string retString;
        bool retBool;
        if((operation.compare("OVER_WRITE")==0))
        {
            retString=OVER_WRITE_T_SYS_PARAMETER(pt);
        }
        else if((operation.compare("CREATE_SESSION")==0))
        {
            // retString=CREATE_SESSION_HTTP_SESSION(pt);
            retString=CREATE_SESSION_HTTP_SESSION2(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("ADD_USERID_UNDER_SESSION")==0))
        {
            retString=ADD_USERID_UNDER_SESSION(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("DELETE_SESSION")==0))
        {
            retString=DELETE_SESSION(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("QUERY_SESSION")==0))
        {
            retString=QUERY_SESSION(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("UPDATE_SESSION_DEADLINE")==0))
        {
            
            retString=UPDATE_SESSION_DEADLINE(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("BATCH_CREATE_AREAS")==0))
        {
            
            retString=BATCH_CREATE_AREAS(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_AREAS_BY_KEYS")==0))
        {
            
            retString=LIST_AREAS_BY_KEYS(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_AREAS_BY_KEYWORDS")==0))
        {
            
            retString=LIST_AREAS_BY_KEYWORDS(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("DELETE_AREAS_BY_KEYS")==0))
        {
            
            retString=DELETE_AREAS_BY_KEYS(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("DELETE_AREAS_BY_KEYWORDS")==0))
        {
            
            retString=DELETE_AREAS_BY_KEYWORDS(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("BATCH_CREATE_LANGUAGE")==0))
        {
            
            retString=BATCH_CREATE_LANGUAGE(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_LANGUAGE_BY_KEYS")==0))
        {
            
            retString=LIST_LANGUAGE_BY_KEYS(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_LANGUAGE_BY_KEYWORDS")==0))
        {
            
            retString=LIST_LANGUAGE_BY_KEYWORDS(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("BATCH_CREATE_SHIPVIA")==0))
        {
            
            retString=BATCH_CREATE_SHIPVIA(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_SHIPVIA_BY_KEYS")==0))
        {
            
            retString=LIST_SHIPVIA_BY_KEYS(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_SHIPVIA_BY_KEYWORDS")==0))
        {
            
            retString=LIST_SHIPVIA_BY_KEYWORDS(pt);
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("BATCH_CREATE_TRADETERM")==0))
        {
            
            retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:trade","BATCH_CREATE_TRADETERM");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_TRADETERM_BY_KEYS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:trade","LIST_TRADETERM_BY_KEYS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_TRADETERM_BY_KEYWORDS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:trade","LIST_TRADETERM_BY_KEYWORDS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("BATCH_CREATE_WEBSITE")==0))
        {
            
            retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:website","BATCH_CREATE_WEBSITE");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_WEBSITE_BY_KEYS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:website","LIST_WEBSITE_BY_KEYS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_WEBSITE_BY_KEYWORDS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:website","LIST_WEBSITE_BY_KEYWORDS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("BATCH_CREATE_SEAPORT")==0))
        {
            
            retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:seaport","BATCH_CREATE_SEAPORT");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_SEAPORT_BY_KEYS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:seaport","LIST_SEAPORT_BY_KEYS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_SEAPORT_BY_KEYWORDS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:seaport","LIST_SEAPORT_BY_KEYWORDS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("BATCH_CREATE_WAREHOUSE")==0))
        {
            
            retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:warehouse","BATCH_CREATE_WAREHOUSE");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_WAREHOUSE_BY_KEYS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:warehouse","LIST_WAREHOUSE_BY_KEYS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_WAREHOUSE_BY_KEYWORDS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:warehouse","LIST_WAREHOUSE_BY_KEYWORDS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        /////////////////////////////////////////////////////
        else if((operation.compare("BATCH_CREATE_AIRPORT")==0))
        {
            
            retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:airport","BATCH_CREATE_AIRPORT");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_AIRPORT_BY_KEYS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:airport","LIST_AIRPORT_BY_KEYS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_AIRPORT_BY_KEYWORDS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:airport","LIST_AIRPORT_BY_KEYWORDS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        //////////////////////////////////////////////////
        else if((operation.compare("BATCH_CREATE_CURRENCY")==0))
        {
            
            retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:currency","BATCH_CREATE_CURRENCY");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_CURRENCY_BY_KEYS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:currency","LIST_CURRENCY_BY_KEYS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_CURRENCY_BY_KEYWORDS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:currency","LIST_CURRENCY_BY_KEYWORDS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        ////////////////////////////////////////////////
        else if((operation.compare("BATCH_CREATE_COUNTRY")==0))
        {
            
            retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:country","BATCH_CREATE_COUNTRY");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_COUNTRY_BY_KEYS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:country","LIST_COUNTRY_BY_KEYS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_COUNTRY_BY_KEYWORDS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:country","LIST_COUNTRY_BY_KEYWORDS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        ////////////////////////////////////////////////
        else if((operation.compare("BATCH_CREATE_REGION")==0))
        {
            
            retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:region","BATCH_CREATE_REGION");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_REGION_BY_KEYS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:region","LIST_REGION_BY_KEYS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_REGION_BY_KEYWORDS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:region","LIST_REGION_BY_KEYWORDS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        ////////////////////////////////////////////////
        else if((operation.compare("BATCH_CREATE_STATE")==0))
        {
            
            retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:state","BATCH_CREATE_STATE");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_STATE_BY_KEYS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:state","LIST_STATE_BY_KEYS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_STATE_BY_KEYWORDS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:state","LIST_STATE_BY_KEYWORDS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        ////////////////////////////////////////////////
        else if((operation.compare("BATCH_CREATE_CITY")==0))
        {
            
            retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:city","BATCH_CREATE_CITY");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_CITY_BY_KEYS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:city","LIST_CITY_BY_KEYS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_CITY_BY_KEYWORDS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:city","LIST_CITY_BY_KEYWORDS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        ////////////////////////////////////////////////
        else if((operation.compare("BATCH_CREATE_UOM")==0))
        {
            
            retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:uom","BATCH_CREATE_UOM");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_UOM_BY_KEYS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:uom","LIST_UOM_BY_KEYS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_UOM_BY_KEYWORDS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:uom","LIST_UOM_BY_KEYWORDS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        ////////////////////////////////////////////////
        else if((operation.compare("BATCH_CREATE_EXCHANGE_RATES")==0))
        {
            
            retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:exchange","BATCH_CREATE_EXCHANGE_RATES");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_EXCHANGE_RATES_BY_KEYS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:exchange","LIST_EXCHANGE_RATES_BY_KEYS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_EXCHANGE_RATES_BY_KEYWORDS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:exchange","LIST_EXCHANGE_RATES_BY_KEYWORDS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        ////////////////////////////////////////////////
        else if((operation.compare("BATCH_CREATE_TAX_SCHEDULES")==0))
        {
            
            retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:tax","BATCH_CREATE_TAX_SCHEDULES");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_TAX_SCHEDULES_BY_KEYS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:tax","LIST_TAX_SCHEDULES_BY_KEYS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_TAX_SCHEDULES_BY_KEYWORDS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:tax","LIST_TAX_SCHEDULES_BY_KEYWORDS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        ////////////////////////////////////////////////
        else if((operation.compare("BATCH_CREATE_TAX_FILES")==0))
        {
            
            retString=GENERAL_BATCH_CREATE(pt,"{KV_MF}:taxfile","BATCH_CREATE_TAX_FILES");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_TAX_FILES_BY_KEYS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYS(pt,"{KV_MF}:taxfile","LIST_TAX_FILES_BY_KEYS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("LIST_TAX_FILES_BY_KEYWORDS")==0))
        {
            
            retString=GENERAL_LIST_BY_KEYWORDS(pt,"{KV_MF}:taxfile","LIST_TAX_FILES_BY_KEYWORDS");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("SET_USER_ROLE")==0))
        {
            
            retString=SET_USER_ROLE(pt,"{KV_MF}:role","SET_USER_ROLE");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
        else if((operation.compare("GET_USER_ROLE")==0))
        {
            
            retString=GET_USER_ROLE(pt,"{KV_MF}:role","GET_USER_ROLE");
            retString.erase(remove(retString.begin(), retString.end(), '\n'), retString.end());
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << retString.length() << "\r\n\r\n" <<retString;
        }
    }
    catch(json_parser_error& e) 
    {
        //cout<<e.what()<<endl;
        //{"errorCode":200,"message":"session read from cache[2] successfully","replyData":[{"sessionId":"01234567890123456789","value":{"userId":"01234567890123456789"}}],"replier":"apollo-cache","replyTime":"2015-05-25 08:00:00"}
        ptree retJson;
        retJson.put("errorCode",JSON_READ_OR_WRITE_ERROR);
        retJson.put("message","json parser error");
        retJson.put("replyData",e.what());
        retJson.put("replier","apollo-cache");

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
		t_area(server);
		//testget(server);
		t_area_get(server);
		t_function(server);
		t_function_get(server);
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







void testhash(Connection &conn)
{
    conn.del("hello");
    cout<<((bool)conn.hset("hello", "world", "one"))<<std::endl;
    cout<<((bool)conn.hset("hello", "mars", "two"))<<std::endl;
    cout<<((std::string)conn.hget("hello", "world") == "one")<<std::endl;
    cout<<(!conn.hsetNX("hello", "mars", "two"))<<std::endl;
    cout<<((bool)conn.hsetNX("hello", "venus", "1"))<<std::endl;
    cout<<(conn.hincrBy("hello", "venus", 3) == 4)<<std::endl;
    cout<<((bool)conn.hexists("hello", "venus"))<<std::endl;
    cout<<((bool)conn.hdel("hello", "venus"))<<std::endl;
    cout<<(!conn.hexists("hello", "venus"))<<std::endl;
    cout<<(conn.hlen("hello") == 2)<<std::endl;
    MultiBulkEnumerator result = conn.hkeys("hello");
    std::string str1;
    std::string str2;
    cout<<(result.next(&str1))<<std::endl;
    cout<<(result.next(&str2))<<std::endl;
    cout<<((str1 == "world" && str2 == "mars") || (str2 == "world" && str1 == "mars"))<<std::endl;
    result = conn.hvals("hello");
    cout<<(result.next(&str1))<<std::endl;
    cout<<(result.next(&str2))<<std::endl;
    cout<<((str1 == "one" && str2 == "two") || (str2 == "one" && str1 == "two"))<<std::endl;
    result = conn.hgetAll("hello");
    std::string str3;
    std::string str4;
    cout<<(result.next(&str1))<<std::endl;
    cout<<(result.next(&str2))<<std::endl;
    cout<<(result.next(&str3))<<std::endl;
    cout<<(result.next(&str4))<<std::endl;
    cout<<(
                    (str1 == "world" && str2 == "one" && str3 == "mars" && str4 == "two")
                    ||
                    (str1 == "mars" && str2 == "two" && str3 == "world" && str4 == "one")
                )<<std::endl;
}

void testset(Connection &conn)
{
	conn.del("hello");
	cout<<((bool)conn.sadd("hello", "world"))<<std::endl;
    cout<<((bool)conn.sisMember("hello", "world"))<<std::endl;
    cout<<(!conn.sisMember("hello", "mars"))<<std::endl;
    cout<<(conn.scard("hello") == 1)<<std::endl;
    cout<<((bool)conn.sadd("hello", "mars"))<<std::endl;
    cout<<(conn.scard("hello") == 2)<<std::endl;
    MultiBulkEnumerator result = conn.smembers("hello");
    std::string str1;
    std::string str2;
    cout<<(result.next(&str1))<<std::endl;
    cout<<(result.next(&str2))<<std::endl;
    cout<<((str1 == "world" && str2 == "mars") || (str2 == "world" && str1 == "mars"))<<std::endl;
    std::string randomMember = conn.srandMember("hello");
    cout<<(randomMember == "world" || randomMember == "mars")<<std::endl;
    cout<<((bool)conn.srem("hello", "mars"))<<std::endl;
    cout<<(conn.scard("hello") == 1)<<std::endl;
    cout<<((std::string)conn.spop("hello") == "world")<<std::endl;
    cout<<(conn.scard("hello") == 0)<<std::endl;
    conn.del("hello1");
    cout<<((bool)conn.sadd("hello", "world"))<<std::endl;
    cout<<(conn.scard("hello") == 1)<<std::endl;
    cout<<((bool)conn.smove("hello", "hello1", "world"))<<std::endl;
    cout<<(conn.scard("hello") == 0)<<std::endl;
    cout<<(conn.scard("hello1") == 1)<<std::endl;
}
void testlist(Connection &conn)
{
	conn.del("hello");
	cout<<(conn.lpush("hello", "c") == 1)<<std::endl;
    cout<<(conn.lpush("hello", "d") == 2)<<std::endl;
    cout<<(conn.rpush("hello", "b") == 3)<<std::endl;
    cout<<(conn.rpush("hello", "a") == 4)<<std::endl;
    cout<<(conn.llen("hello") == 4)<<std::endl;
    MultiBulkEnumerator result = conn.lrange("hello", 1, 3);
    std::string str;
    cout<<(result.next(&str))<<std::endl;
    cout<<(str == "c")<<std::endl;
    cout<<(result.next(&str))<<std::endl;
    cout<<(str == "b")<<std::endl;
    cout<<(result.next(&str))<<std::endl;
    cout<<(str == "a")<<std::endl;
    cout<<conn.ltrim("hello", 0, 1)<<std::endl;
    result = conn.lrange("hello", 0, 10);
    cout<<(result.next(&str))<<std::endl;
    cout<<(str == "d")<<std::endl;
    cout<<(result.next(&str))<<std::endl;
    cout<<(str == "c")<<std::endl;
    cout<<((std::string)conn.lindex("hello", 0) == "d")<<std::endl;
    cout<<((std::string)conn.lindex("hello", 1) == "c")<<std::endl;
    cout<<conn.lset("hello", 1, "f")<<std::endl;
    cout<<((std::string)conn.lindex("hello", 1) == "f")<<std::endl;
    conn.lpush("hello", "f");
    conn.lpush("hello", "f");
    conn.lpush("hello", "f");
	cout<<"................"<<std::endl;
    cout<<(conn.lrem("hello", 2, "f") == 2)<<std::endl;
    cout<<(conn.llen("hello") == 3)<<std::endl;
    cout<<((std::string)conn.lpop("hello") == "f")<<std::endl;
    cout<<(conn.llen("hello") == 2)<<std::endl;
    conn.rpush("hello", "x");
    cout<<((std::string)conn.rpop("hello") == "x")<<std::endl;
    conn.rpush("hello", "z");
    cout<<((std::string)conn.rpopLpush("hello", "hello") == "z")<<std::endl;


}

void run(string host="localhost",string arg="6379",string password="renesola")
{
	try
    {
	cout<<"redis"<<std::endl;
	//cout<<"redis1"<<std::endl;
    Connection conn(host, arg, password);
	conn.select(0);
	conn.set("hello", "world");
    StringReply stringReply = conn.get("hello");
	
    cout<<stringReply.result().is_initialized()<<std::endl;
	
    cout<<(std::string)conn.get("hello")<<std::endl;
	
    cout<<((bool)conn.exists("hello"))<<std::endl;
    cout<<((bool)conn.del("hello"))<<std::endl;
    cout<<(!conn.exists("hello"))<<std::endl;
    cout<<(!conn.del("hello"))<<std::endl;
	cout<<(conn.type("hello") == String)<<std::endl;
	
	cout<<"///////////////////////////////////////"<<std::endl;

	testlist(conn);
	cout<<"///////////////////////////////////////"<<std::endl;
	testset(conn);
	cout<<"///////////////////////////////////////"<<std::endl;
	testhash(conn);
	cout<<"///////////////////////////////////////"<<std::endl;
	/*testzset(conn);*/
	 }
    catch (std::exception& e)
    {
        std::cout << "FAILURE: " << e.what() << std::endl;
       // cout <<GetStackTrace()<< std::endl;
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