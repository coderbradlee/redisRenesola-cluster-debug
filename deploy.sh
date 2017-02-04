#172.29.1.5
su redis
taskset -c 0 redis-server /etc/redis/redis-6380.conf
taskset -c 1 redis-server /etc/redis/redis-6381.conf
taskset -c 2 redis-server /etc/redis/redis-7382.conf
cp apollo_cache.service /usr/lib/systemd/system/
service apollo_cache start
#172.29.1.3
#su redis
#taskset -c 0 redis-server /etc/redis/redis-6382.conf
#taskset -c 1 redis-server /etc/redis/redis-7380.conf
#taskset -c 2 redis-server /etc/redis/redis-7381.conf
