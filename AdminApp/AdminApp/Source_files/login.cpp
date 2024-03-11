#include "../Header_files/login.h"
#include "../UI_files/ui_login.h"
#include <QMessageBox>
#include <QKeyEvent>


Login::Login(bool firstTime, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    first = firstTime;
    ui->setupUi(this);
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
    QString username = "user";
    QString password = "pass";

    return (ui->username->text() == username && ui->password->text() == password);
}


QString Login::getUsername(){
    return ui->username->text();
}

