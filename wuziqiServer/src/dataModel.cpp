#include "dataModel.h"
#include <list>
#include <optional>
#include <string>
#include <sw/redis++/utils.h>
#include <sys/types.h>
#include <cstdlib>


dataModel::dataModel(CMysql* mysql,RedisConn* redis){
    this->mysql_ = mysql;
    this->redis_ = redis;
}

void dataModel::loadUserInfo(){
    redis_->del("userinfo");
    string sql = "select userId,userName,iconId,feeling,passwd from userinfo;";
	list<string>selectRes;
    query(sql, selectRes,5);
    for(auto ite = selectRes.begin();ite!=selectRes.end();){
        string id = *ite++;
        string content = *ite++ +":" + *ite++ + ":" + *ite++ +":"+*ite++;
        pair<string,string> p = {id,content};
        redis_->hset("userinfo", id, content);
    }
}

void dataModel::loadFriendId(){
    string sql = "select userId,friendId from friend;";
    list<string>selectRes;
    query(sql, selectRes,2);
    map<string,int>isDel;
    for(auto ite = selectRes.begin();ite!=selectRes.end();){
        if(!isDel.count(*ite)){
            redis_->del(*ite);
            isDel[*ite] = 1;
        }
        redis_->lpush(*ite++, *ite++);
    }
}

bool dataModel::query(string sql,list<string>& selectRes,int col){
    cout << sql << endl;
    int iResult = mysql_->SelectMySql((char*)sql.c_str(), col, selectRes);
    if (!iResult) {
		cout << sql+" select Failed" << endl;
		exit(0);
	}
    return iResult;
}

bool dataModel::insert(string sql){
    cout<<sql<<endl;
    int iResult = mysql_->UpdateMySql((char*)sql.c_str());
    return iResult;
}

optional<string> dataModel::getUserInfo(string userId){
    return redis_->hget("userinfo",userId);
}

vector<string> dataModel::getFriendIds(string userId){
    return redis_->lrange(userId, 0, -1);
}

bool dataModel::userIsExist(string userId){
    if (redis_->hget("userInfo",userId)!= nullopt) {
        return true;
    }
    return false;
}

void dataModel::loadFriendId(string id){
    cout<<"dataModel::loadFriendId(string id)"<<endl;
    string sql = "select friendId from friend where userId = \"" + id + "\";";
    list<string> selectRes;
    if(query(sql,selectRes,1)){
        redis_->del(id);
        for(auto ite = selectRes.begin();ite!=selectRes.end();){
            redis_->lpush(id, *ite++);
        }
    }
    cout<<sql<<endl;
}

void dataModel::loadWuziqiScore(){
    cout<<"dataModel::loadWuziqiScore()"<<endl;
    string sql ="select * from wuziqirank;";
    list<string> selectRes;
    if(query(sql,selectRes,2)){
        redis_->del("wuziqirank");
        for(auto ite = selectRes.begin();ite!=selectRes.end();){
            string id = *ite++;
            string score = *ite++;
            redis_->zadd("wuziqirank",atoi(score.c_str()),id);
        }
    }
    cout<<sql<<endl;
}

bool dataModel::newRegister(string id,string name,string passwd){
   string sql = "insert into userinfo(userId, userName, passwd) values(\"" + id + "\",\"" + name + "\",\"" + passwd + "\" ); ";
    bool res = insert(sql);
    if(!res){
        cout<<"dataModel::newRegister insert error"<<endl;
        return false;
    }else{
        list<string>selectRes;
        sql = "select userId,userName,iconId,feeling,passwd from userinfo where userId = \"" + id + "\";";
        if(query(sql, selectRes,4)){
            auto ite = selectRes.begin();
            string content = *ite++ +":" + *ite++ + ":" + *ite++ +":"+*ite++;
            pair<string,string> p = {id,content};
            if(!redis_->hset("userinfo", id, content)){
                cout<<"dataModel::newRegister redis->hset error"<<endl;
                return false;
            }
            loadFriendId(id);
            return true;
        }
    }
    return false;
}