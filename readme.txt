2017.02.14
增加scm的表,来源于 t_supplier_basic
supplier_id supplier_no company_name_en status type=Group Supplier
{
	supplier_id:"",
	supplier_no:"",
	company_name_en:"",
	status:"",
	type="Group Supplier"
}
测试：
1、curl -X POST http://127.0.0.1:9088/scm -d '"{"supplier_id":"supplier_id1","supplier_no":"supplier_no1","company_name_en":"company_name_en1","status":"status1","type":"Group Supplier"}"'
2、curl -X GET http://127.0.0.1:9088/scm -d '"{supplier_id:"supplier_id1"}'

放弃此功能，改用data_exchange写mysql



2017.01.22
ShippingCost 部署到线上

2017.01.13
POST，RESTful
/ShippingCost/{companyCode}/{SO id}

在全局Cache中设置 如下 Key/Value 对 - 
key: "ShippingCost-{companyCode}-{SO id}"
value: 1 
------------------------------------------------------
操作：读取运费标志位
GET，RESTful
/ShippingCost/{companyCode}/{SO id}

如 key:value 已存在，返回：
{
   "ShippingCost-{companyCode}-{SO id}": 1 //已设置“运费”标志位
}

如 key:value 不存在，返回：
{
   "ShippingCost-{companyCode}-{SO id}": 0 //未设置“运费”标志位
}


curl -X GET http://127.0.0.1:8088/ShippingCost/PA/123

curl -X GET http://127.0.0.1:8088/ShippingCost/PA/123
curl -X POST http://127.0.0.1:8088/ShippingCost/PA/123
curl -X GET http://127.0.0.1:8088/ShippingCost/PA/123

curl -X GET http://127.0.0.1:8089/ShippingCost/PA/123

curl -X GET http://127.0.0.1:8089/ShippingCost/PA/123
curl -X POST http://127.0.0.1:8089/ShippingCost/PA/123
curl -X GET http://127.0.0.1:8089/ShippingCost/PA/123


2016.12.02
as更新新规则
set {JP_OVERSEAS_flow_number}:id 100
set {TH_OVERSEAS_flow_number}:id 100

curl -X GET http://127.0.0.1:8088/flowNo/JP/SO
curl -X GET http://127.0.0.1:8088/flowNo/JP/xx

curl -X GET http://127.0.0.1:8088/flowNo/TH/SO
curl -X GET http://127.0.0.1:8088/flowNo/TH/xx


2016.12.01
os更新新规则
PA	ReneSola Panama
US	ReneSola America
CA	ReneSola Canada
MX	ReneSola Mexico
BR
set {PA_OVERSEAS_flow_number}:id 20
set {US_OVERSEAS_flow_number}:id 20
set {CA_OVERSEAS_flow_number}:id 20
set {MX_OVERSEAS_flow_number}:id 20
set {BR_OVERSEAS_flow_number}:id 20
测试：
curl -X GET http://127.0.0.1:8089/flowNo/PA/SO
curl -X GET http://127.0.0.1:8089/flowNo/CA/SO
curl -X GET http://127.0.0.1:8089/flowNo/US/SO
curl -X GET http://127.0.0.1:8089/flowNo/MX/SO
curl -X GET http://127.0.0.1:8089/flowNo/BR/SO

curl -X GET http://127.0.0.1:8089/flowNo/US/PI
curl -X GET http://127.0.0.1:8089/flowNo/CA/PI

curl -X GET http://127.0.0.1:8088/flowNo/US/PI
curl -X GET http://127.0.0.1:8088/flowNo/CA/PI

2016.11.24
eu库的先用新规则，其他的还是老规则不变
即：
1、eu的几个公司，UK,ZA,FR,IT,DE,TR,RU，运用新规则
2、其他的用老规则

curl -X GET http://127.0.0.1:8089/flowNo/UK/SO
curl -X GET http://127.0.0.1:8089/flowNo/ZA/SO
curl -X GET http://127.0.0.1:8089/flowNo/FR/SO
curl -X GET http://127.0.0.1:8089/flowNo/IT/SO
curl -X GET http://127.0.0.1:8089/flowNo/DE/SO
curl -X GET http://127.0.0.1:8089/flowNo/TR/SO
curl -X GET http://127.0.0.1:8089/flowNo/RU/SO

curl -X GET http://127.0.0.1:8089/flowNo/UK/PI
curl -X GET http://127.0.0.1:8089/flowNo/ZA/PI
curl -X GET http://127.0.0.1:8089/flowNo/FR/PI
curl -X GET http://127.0.0.1:8089/flowNo/IT/PI
curl -X GET http://127.0.0.1:8089/flowNo/DE/PI
curl -X GET http://127.0.0.1:8089/flowNo/TR/PI
curl -X GET http://127.0.0.1:8089/flowNo/RU/PI

2016.11.11
flow 分支保存有log和redis的data数据
curl -X GET http://172.18.100.85:8088/flowNo/us/so
更改规则：当company是JS时不变，当company不是JS时设置type为定值


  {"flowNo":"7","replyTime" : "2016-07-18 18:01:14"}
curl -X GET http://127.0.0.1:8088/flowNo/JS/test1
curl -X GET http://127.0.0.1:8088/flowNo/JS/test2
curl -X GET http://127.0.0.1:8088/flowNo/US/SO
curl -X GET http://127.0.0.1:8088/flowNo/US/PI
curl -X GET http://127.0.0.1:8088/flowNo/JP/SO
curl -X GET http://127.0.0.1:8088/flowNo/JP/PI

线上部署服务目录及端口更改了下
curl -X POST http://127.0.0.1:8088/apollo -d "{\"operation\":\"QUERY_SESSION\",\"requestData\":[{\"sessionId\":\"J57B5D55ERJHZXDPL1R2\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}"

curl -X GET http://127.0.0.1:8089/flowNo/us/so 

curl -X POST http://172.18.100.85:8088/apollo -d "{\"operation\":\"QUERY_SESSION\",\"requestData\":[{\"sessionId\":\"J57B5D55ERJHZXDPL1R2\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}"

curl -X POST http://172.18.100.87:8088/apollo -d "{\"operation\":\"QUERY_SESSION\",\"requestData\":[{\"sessionId\":\"J57B5D55ERJHZXDPL1R2\"}],\"requestor\":\"apollo-employee-portal\",\"requestTime\":\"2015-05-25 08:00:00\"}"

curl -X GET http://172.18.100.85:8088/flowNo/us/so 
curl -X GET http://172.18.100.87:8088/flowNo/us/so 
{"flowNo":"7","replyTime" : "2016-07-18 18:01:14"}
curl -X GET http://172.18.100.87:8088/flowNo/US/SO

$cd lib_acl; make
$cd lib_protocol; make
$cd lib_acl_cpp; make

example:

CFLAGS = -c -g -W -O3 -Wall -Werror -Wshadow \
-Wno-long-long -Wpointer-arith -D_REENTRANT \
-D_POSIX_PTHREAD_SEMANTICS -DLINUX2 \
-I ./lib_acl_cpp/include
BASE_PATH=./acl
LDFLAGS = -L$(BASE_PATH)/lib_acl_cpp/lib -l_acl_cpp \
    -L$(BASE_PATH)/lib_protocol/lib -l_protocol \
    -L$(BASE_PATH)/lib_acl/lib -l_acl \
    -lpthread
test: main.o
    gcc -o main.o $(LDFLAGS)
main.o: main.cpp
    gcc $(CFLAGS) main.cpp -o main.o



记得free掉reply
如何将单机的redis数据导入到redis cluster



bug修复
1、修复query_session时value为空的情况
2、去除response的json的\n
3、修复children等子树为空时返回[]


1、定义宏确定是否开启Daemon模式 ok
2、添加默认页 ok
3、make install
4、动态添加模块 boost plugin
5、日志删除能否自建 目前为循环日志，大小16m 达到一定大小后放到logs目录下面去
6、日志开关 
7、增加日志等级

1、主备
2、主发送数据给备机,备机保存aof文件per sec

策略：
两台机器做redis cluster，一个机器是两master实例，一个slave实例；另一个机器是两个slave实例，一个master实例，配置aof持久化文件，每秒钟持久化一次。

需要redis版本3.0以上，目前已经在自己电脑实验部署好cluster，后面需要：
1、升级测试用机器的redis版本，另一台新装机器需要部署环境
2、redis cluster部署完后，需要改写代码，将原来的写一个redis实例的代码更改为写redis cluster




reponse log ok
request log post ok
request log get 未取到数据，待查


#主库配置
url_master=jdbc:mysql://172.18.22.202:3306/apollo?Unicode=true&amp;characterEncoding=UTF-8
username_master=renesola
password_master=renesola

#从库配置
url_slave=jdbc:mysql://172.18.22.203:3306/apollo?Unicode=true&amp;characterEncoding=UTF-8
username_slave=renesola
password_slave=renesola



1、redis 主从设置
2、request get时request不能写日志，只有请求全部为post即可
3、redis设置过期时间问题（用于session）
4、redis数据持久化问题
save 900 1

save 300 10

save 60 10000

#   after 900 sec (15 min) if at least 1 key changed

#   after 300 sec (5 min) if at least 10 keys changed

#   after 60 sec if at least 10000 keys changed
可能会有数据丢失


5、本程序主从
考虑可以一台主redis，N台read-only的slave，每台上面都部署程序
或者一主一备，二主二备皆可，每台都提供程序

6、数据存放是否需要不同的redis数据库，默认是select 0



