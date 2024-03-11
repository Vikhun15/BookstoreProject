#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(bool firstTime, QWidget *parent = nullptr);
    QString getUsername();
    bool first;
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
