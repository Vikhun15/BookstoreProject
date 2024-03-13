#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
    User(int id, QString username, QString password);
    int id;
    QString username;
    QString password;
};

#endif // USER_H
