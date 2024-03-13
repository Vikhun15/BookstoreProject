#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "user.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(bool firstTime,QList<User*> users, QWidget *parent = nullptr);
    QString getUsername();
    bool first;
    QList<User*> users;
    ~Login();
signals:
    void passUsername();


private:
    Ui::Login *ui;
    bool checkCreds();
    void keyPressEvent(QKeyEvent *e);
    void closeEvent(QCloseEvent * event);

private slots:
    void clickLogin();
};

#endif // LOGIN_H
