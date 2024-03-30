#ifndef REDISCONN_H
#define REDISCONN_H
#include <cstdio>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include <sw/redis++/command_options.h>
#include <sw/redis++/cxx_utils.h>
#include <sw/redis++/redis.h>
#include <sw/redis++/utils.h>
#include <utility>
#include <vector>
using namespace sw::redis;
class RedisConn{
public:
    RedisConn(){
        redis =new Redis("tcp://123456@127.0.0.1:6379");
        if(!redis){
            perror("redis init failed:");
            exit(1);
        }
        std::cout<<"redis connect success..."<<std::endl;
    }
    int set(std::string key,std::string val){
        redis->set(key,val);
        return 0;
    }
    int get(std::string key,std::string& val){
        auto pVal =redis->get(key);
        if(pVal){
            val = *pVal;
            return 0;
        }
        return -1;
    }
    bool del(std::string key){
       int res = redis->del(key);
       if(res>0){
            return true;
       }else{
        return false;
       }
    }
    int hmset(std::string key,std::initializer_list<std::pair<std::string, std::string>>argList){
        redis->hmset("11",argList);
        return 0;
    }
    int hset(std::string key,std::string field,std::string val){
        return redis->hset(key,field,val);
    }
    std::optional<std::string> hget(std::string key,std::string field){
        return redis->hget(key, field);
    }
    int lpush(std::string key,std::string val){
        return redis->lpush(key,val);
    }
    std::vector<std::string> lrange(std::string key,int l,int r){
        std::vector<std::string>res;
        redis->lrange(key,l,r,std::back_insert_iterator<std::vector<std::string>>(res));
        return res;
    }
    void zadd(std::string key,int score,std::string value){
        redis->zadd(key,{std::make_pair(value, score)});
    }
    std::vector<std::string> zrangebyscore(std::string key,int l,int r){
        std::vector<std::string>res;
        redis->lrange(key,l,r,std::back_insert_iterator<std::vector<std::string>>(res));
        redis->zrangebyscore("zset", BoundedInterval<double>(l, r, BoundType::OPEN),
std::back_inserter(res));
        return res;
    }
    ~RedisConn(){
        delete redis;
        redis = nullptr;
    }
public:
    Redis* redis;
};

#endif