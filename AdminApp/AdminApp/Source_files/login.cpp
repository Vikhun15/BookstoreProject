#include "../Header_files/login.h"
#include "../UI_files/ui_login.h"
#include <QMessageBox>
#include <QKeyEvent>
#include "../Header_files/user.h"


Login::Login(bool firstTime, QList<User*> users, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    first = firstTime;
    ui->setupUi(this);
    Login::users = users;
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    connect(ui->loginBtn, SIGNAL(clicked()), this, SLOT(clickLogin()));
    connect(this,SIGNAL(destroyed()),this->parent(),SLOT(close()));
}

Login::~Login()
{
    delete ui;
}

void Login::clickLogin(){
    QMessageBox Msg(this);
    Msg.setWindowModality(Qt::NonModal);
    Msg.setDefaultButton(QMessageBox::Ok);


    if(checkCreds())
    {
        Msg.setText("Successful Login!");
        Msg.setWindowTitle("Success!");
        Msg.setStyleSheet("QLabel{padding:10px 50px;text-align:center;}");
        Msg.exec();
        this->close();
    }
    else
    {
        Msg.setText("Wrong username or password");
        Msg.setIcon(QMessageBox::Critical);
        Msg.setWindowTitle("Error!");
        Msg.exec();
    }


}
void Login::keyPressEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_Escape)
        return;

    QDialog::keyPressEvent(e);
}

void Login::closeEvent(QCloseEvent * event)
{
    if(checkCreds()){
        emit passUsername();
    }
    else if(first)
    {
        qApp->quit();
    }
}

bool Login::checkCreds()
{
    QString username = ui->username->text();
    QString password = ui->password->text();
    for(int i = 0; i < users.length(); i++){
        if(users[i]->username == username && users[i]->password == password){
            return true;
        }
        else if(users[i]->username == username && !(users[i]->password == password)){
            return false;
        }
    }
    return false;
}


QString Login::getUsername(){
    return ui->username->text();
}

