#include "Mysql.h"
#include "redisConn.h"
#include <optional>
#include <string>
#include <sw/redis++/utils.h>
#include <vector>
class dataModel{
public:
    dataModel(CMysql* mysql,RedisConn* redis);
    void loadUserInfo();
    void loadFriendId();
    void loadFriendId(string id);
    void loadWuziqiScore();
    bool query(string sql,list<string>&str,int col);
    bool insert(string sql);
public:
    optional<string> getUserInfo(string userId);
    bool userIsExist(string userId);
    vector<string> getFriendIds(string userId);
public:
    bool newRegister(string id,string name,string passwd);
private:
    CMysql* mysql_;
    RedisConn* redis_;
};

