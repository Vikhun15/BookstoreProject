#include "../Header_files/user.h"
#include <QString>

User::User() {

}

User::User(int id, QString username, QString password){
    User::id = id;
    User::username = username;
    User::password = password;
}

