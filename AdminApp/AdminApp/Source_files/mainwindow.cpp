#include "../Header_files/mainwindow.h"
#include "../UI_files/ui_mainwindow.h"
#include "../Header_files/login.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->syncBtn->setStyleSheet("background-color:blue;color:white;");

    login = new Login(true, this);
    login->setModal(true);

    connect(login, SIGNAL(passUsername()), this, SLOT(changeUsername()));

    connect(ui->logoutBtn, SIGNAL(clicked()), this, SLOT(logout_click()));
    connect(ui->modeChangeBtn, SIGNAL(clicked()), this, SLOT(mode_click()));

    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(add_click()));
    connect(ui->editBtn, SIGNAL(clicked()), this, SLOT(edit_click()));
    connect(ui->removeBtn, SIGNAL(clicked()), this, SLOT(remove_click()));
    connect(ui->stockBtn, SIGNAL(clicked()), this, SLOT(stock_click()));
    connect(ui->exportBtn, SIGNAL(clicked()), this, SLOT(export_click()));
    connect(ui->syncBtn, SIGNAL(clicked()), this, SLOT(sync_click()));


    login->open();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeUsername(){
    ui->username->setText(login->getUsername());
}

void MainWindow::logout_click(){
    login = new Login(false, this);
    login->setModal(true);

    connect(login, SIGNAL(passUsername()), this, SLOT(changeUsername()));

    login->open();
}

void MainWindow::mode_click(){
    //TODO
}

void MainWindow::add_click(){
    //TODO
}

void MainWindow::edit_click(){
    //TODO
}

void MainWindow::remove_click(){
    //TODO
}

void MainWindow::stock_click(){
    //TODO
}

void MainWindow::export_click(){
    //TODO
}

void MainWindow::sync_click(){
    //TODO
}
