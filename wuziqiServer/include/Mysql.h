#ifndef _MYSQL_H
#define _MYSQL_H
#include "packdef.h"
#include <mysql/mysql.h>
#include<list>
#include<string>

using namespace  std;


class CMysql{
public:
    int ConnectMysql(const char *server, const char *user, const char *password, const char *database);
    int SelectMySql(char* szSql,int nColumn,list<string>& lst);
    int UpdateMySql(char *szsql);
    void DisConnect();
    void getAllUserData();
private:
    MYSQL *conn;

    pthread_mutex_t m_lock;
};




#endif
