#include "../Header_files/cashregisterwindow.h"
#include "../UI_files/ui_cashregisterwindow.h"
#include "../Header_files/mainwindow.h"
#include <QTableWidget>

CashRegisterWindow::CashRegisterWindow(bool loggedIn, QString username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CashRegisterWindow)
{
    ui->setupUi(this);
    Setup();
    CashRegisterWindow::loggedIn = loggedIn;

}
CashRegisterWindow::CashRegisterWindow(bool loggedIn, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CashRegisterWindow)
{
    ui->setupUi(this);
    CashRegisterWindow::loggedIn = loggedIn;
    Setup();

}
CashRegisterWindow::CashRegisterWindow(bool loggedIn, QString username, QList<Book*> books, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CashRegisterWindow)
{
    ui->setupUi(this);
    CashRegisterWindow::loggedIn = loggedIn;
    ui->username->setText(username);
    CashRegisterWindow::books = books;
    Setup();

}

CashRegisterWindow::CashRegisterWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CashRegisterWindow)
{
    ui->setupUi(this);
    loggedIn = false;
    Setup();

}

void CashRegisterWindow::Setup(){
    this->setStyleSheet("QPushButton#syncBtn {background-color:blue; color:white;}QPushButton#syncBtn:pressed {background-color:rgb(0,120,255);}QPushButton#syncBtn:hover:!pressed {background-color:darkblue;}");

    if(!loggedIn){
        login = new Login(!loggedIn, this);
        login->setModal(true);
    }

    connect(login, SIGNAL(passUsername()), this, SLOT(changeUsername()));

    connect(ui->logoutBtn, SIGNAL(clicked()), this, SLOT(logout_click()));
    connect(ui->modeChangeBtn, SIGNAL(clicked()), this, SLOT(mode_click()));

    connect(ui->syncBtn, SIGNAL(clicked()), this, SLOT(sync_click()));
    connect(ui->dataTable, SIGNAL(itemSelectionChanged()), this, SLOT(selectedChanged()));
    connect(ui->itemsList, SIGNAL(itemSelectionChanged()), this, SLOT(selectedChanged()));

    connect(ui->dataTable, SIGNAL(clicked(QModelIndex)), this, SLOT(table_click()));
    connect(ui->itemsList, SIGNAL(clicked(QModelIndex)), this, SLOT(list_click()));

    connect(ui->searchBar, SIGNAL(textChanged(QString)), this, SLOT(searchChanged()));
    connect(ui->discountTxt, SIGNAL(textChanged(QString)), this, SLOT(change_discount()));

    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(add_click()));
    connect(ui->removeBtn, SIGNAL(clicked()), this, SLOT(remove_click()));

    ui->dataTable->setColumnCount(7);
    ui->dataTable->setHorizontalHeaderLabels(QStringList() << tr("Id")
                                                           << tr("Title")
                                                           << tr("Category")
                                                           << tr("Rating")
                                                           << tr("Price")
                                                           << tr("In Stock")
                                                           << tr("Quantity"));
    ui->dataTable->setRowCount(1);
    ui->itemsList->setColumnCount(3);
    ui->itemsList->setHorizontalHeaderLabels(QStringList() << tr("Title")
                                                           << tr("Price")
                                                           << tr("Quantity"));


    books.append(new Book(1, "The Great Gatsby", "Fiction", 4.2, 22.50, true, 15));

    ui->dataTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(6, QHeaderView::ResizeToContents);

    ui->itemsList->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->itemsList->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->itemsList->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);


    SyncTable();
    if(!loggedIn){
        login->open();
    }
}


void CashRegisterWindow::SyncTable(){
    ui->dataTable->setRowCount(0);
    for(int i = 0; i <books.length(); i++){
        ui->dataTable->insertRow(ui->dataTable->rowCount());
        ui->dataTable->setItem(ui->dataTable->rowCount()-1, 0, new QTableWidgetItem(QString::number(books[i]->id)));
        ui->dataTable->setItem(ui->dataTable->rowCount()-1, 1, new QTableWidgetItem(books[i]->title));
        ui->dataTable->setItem(ui->dataTable->rowCount()-1, 2, new QTableWidgetItem(books[i]->category));
        ui->dataTable->setItem(ui->dataTable->rowCount()-1, 3, new QTableWidgetItem(QString::number(books[i]->rating)));
        ui->dataTable->setItem(ui->dataTable->rowCount()-1, 4, new QTableWidgetItem(QString::number(books[i]->price)));
        ui->dataTable->setItem(ui->dataTable->rowCount()-1, 5, new QTableWidgetItem(books[i]->inStock ? "Yes" : "No"));
        ui->dataTable->setItem(ui->dataTable->rowCount()-1, 6, new QTableWidgetItem(QString::number(books[i]->quantity)));
    }
}


void CashRegisterWindow::changeUsername(){
    ui->username->setText(login->getUsername());
    loggedIn = true;
}


void CashRegisterWindow::logout_click(){
    login = new Login(!loggedIn, this);
    login->setModal(true);

    connect(login, SIGNAL(passUsername()), this, SLOT(changeUsername()));

    login->open();
}

void CashRegisterWindow::mode_click(){
    ((MainWindow*)parent())->ChangeData(loggedIn, ui->username->text());
    ((MainWindow*)parent())->show();
    this->hide();
}


void CashRegisterWindow::ChangeData(bool loggedIn, QString username, QList<Book*> books){
    CashRegisterWindow::loggedIn = loggedIn;
    ui->username->setText(username);
    CashRegisterWindow::books = books;
    SyncTable();
}

void CashRegisterWindow::calculatePrice(){
    double sum = 0;
    for(int i = 0; i < ui->itemsList->rowCount(); i++){
        sum += (ui->itemsList->item(i, 1)->text().toDouble() * ui->itemsList->item(i, 2)->text().toDouble());
    }
    ui->priceTxt->setText(QString::number(sum) + "$");
}

bool CashRegisterWindow::checkDiscount(){
    bool result = true;


    ui->discountTxt->text().toDouble(&result);
    if(ui->discountTxt->text().isEmpty()){
        result = true;
    }
    if(!result){
        ui->discountTxt->setStyleSheet("background-color:red;color:white;");
    }
    else{
        ui->discountTxt->setStyleSheet("background-color:white;color:black;");
    }

    return result;
}

void CashRegisterWindow::change_discount(){
    calculateTotal();
}

void CashRegisterWindow::calculateTotal(){
    if(checkDiscount()){
        double price = ui->priceTxt->text().removeLast().toDouble();
        double discount = 0;
        if(!ui->discountTxt->text().isEmpty()){
            discount = ui->discountTxt->text().toDouble() / 100;
        }
        ui->totalTxt->setText(QString::number(price -  price * discount) + "$");
    }
    else{
        ui->totalTxt->setText(ui->priceTxt->text().removeLast() + "$");
    }
}

void CashRegisterWindow::selectedChanged(){
    if(ui->dataTable->selectionModel()->hasSelection() || ui->itemsList->selectionModel()->hasSelection()){
        if(ui->dataTable->selectionModel()->hasSelection()){
            selectedRowNum = ui->dataTable->selectionModel()->selectedRows().at(0).row();
        }
        if(ui->itemsList->selectionModel()->hasSelection()){
            selectedListNum = ui->itemsList->selectionModel()->selectedRows().at(0).row();
        }
        ui->removeBtn->setEnabled(true);
        ui->addBtn->setEnabled(true);
    }
    else{
        ui->removeBtn->setEnabled(false);
        ui->addBtn->setEnabled(false);
    }
}

void CashRegisterWindow::add_click(){
    if(ui->dataTable->selectionModel()->hasSelection()){
        int num = ui->dataTable->item(selectedRowNum, 6)->text().toInt();
        QString title = ui->dataTable->item(selectedRowNum, 1)->text();
        if(num != 0){
            if(num - 1 == 0){
                ui->dataTable->item(selectedRowNum, 5)->setText("No");
            }
            ui->dataTable->item(selectedRowNum, 6)->setText(QString::number(num-1));
            bool found = false;
            for(int i = 0; i < ui->itemsList->rowCount(); i++){
                if(ui->itemsList->item(i, 0)->text() == title){
                    found = true;
                    ui->itemsList->item(i, 2)->setText(QString::number(ui->itemsList->item(i, 2)->text().toInt()+1));
                }
            }
            if(!found){
                ui->itemsList->insertRow(ui->itemsList->rowCount());
                ui->itemsList->setItem(ui->itemsList->rowCount()-1, 0, new QTableWidgetItem(ui->dataTable->item(selectedRowNum, 1)->text()));
                ui->itemsList->setItem(ui->itemsList->rowCount()-1, 1, new QTableWidgetItem(ui->dataTable->item(selectedRowNum, 4)->text()));
                ui->itemsList->setItem(ui->itemsList->rowCount()-1, 2, new QTableWidgetItem("1"));
            }
        }
    }
    if(ui->itemsList->selectionModel()->hasSelection()){
        int row = 0;
        int num = 0;
        QString title = ui->itemsList->item(selectedListNum, 0)->text();
        for(int i = 0; i < ui->dataTable->rowCount(); i++){
            if(ui->dataTable->item(i, 1)->text() == title){
                num = ui->dataTable->item(i, 6)->text().toInt();
                row = i;
                break;
            }
        }
        if(num != 0){
            if(num - 1 == 0){
                ui->dataTable->item(row, 5)->setText("No");
            }
            ui->dataTable->item(row, 6)->setText(QString::number(num-1));
            bool found = false;
            for(int i = 0; i < ui->itemsList->rowCount(); i++){
                if(ui->itemsList->item(i, 0)->text() == title){
                    found = true;
                    ui->itemsList->item(i, 2)->setText(QString::number(ui->itemsList->item(i, 2)->text().toInt()+1));
                }
            }
            if(!found){
                ui->itemsList->insertRow(ui->itemsList->rowCount());
                ui->itemsList->setItem(ui->itemsList->rowCount()-1, 0, new QTableWidgetItem(ui->dataTable->item(selectedRowNum, 1)->text()));
                ui->itemsList->setItem(ui->itemsList->rowCount()-1, 1, new QTableWidgetItem(ui->dataTable->item(selectedRowNum, 4)->text()));
                ui->itemsList->setItem(ui->itemsList->rowCount()-1, 2, new QTableWidgetItem("1"));
            }
        }
    }
    calculatePrice();
    calculateTotal();
}

void CashRegisterWindow::remove_click(){
    if(ui->itemsList->selectionModel()->hasSelection()){
        int num = ui->itemsList->item(selectedListNum, 2)->text().toInt();
        QString title = ui->itemsList->item(selectedListNum, 0)->text();
        if(num - 1 == 0){
            ui->itemsList->removeRow(selectedListNum);
        }
        else{
            ui->itemsList->item(selectedRowNum, 2)->setText(QString::number(num-1));
        }
        for(int i = 0; i < ui->dataTable->rowCount(); i++){
            if(ui->dataTable->item(i, 1)->text() == title){
                if(ui->dataTable->item(i, 5)->text() == "No"){
                    ui->dataTable->item(i, 5)->setText("Yes");
                }
                ui->dataTable->item(i, 6)->setText(QString::number(ui->dataTable->item(i, 6)->text().toInt()+1));
            }
        }
    }
    if(ui->dataTable->selectionModel()->hasSelection()){
        if(ui->itemsList->rowCount() > 0){
            QString title = ui->dataTable->item(selectedRowNum, 1)->text();
            int row = 0;
            int num = 0;
            for(int i = 0;i < ui->itemsList->rowCount(); i++){
                if(ui->itemsList->item(i,0)->text() == title){
                    num = ui->itemsList->item(i, 2)->text().toInt();
                    row = i;
                    break;
                }
            }
            if(num - 1 == 0){
                ui->itemsList->removeRow(row);
            }
            else{
                ui->itemsList->item(selectedRowNum, 2)->setText(QString::number(num-1));
            }
            for(int i = 0; i < ui->dataTable->rowCount(); i++){
                if(ui->dataTable->item(i, 1)->text() == title){
                    if(ui->dataTable->item(i, 5)->text() == "No"){
                        ui->dataTable->item(i, 5)->setText("Yes");
                    }
                    ui->dataTable->item(i, 6)->setText(QString::number(ui->dataTable->item(i, 6)->text().toInt()+1));
                }
            }
        }
    }
    calculatePrice();
    calculateTotal();
}

void CashRegisterWindow::list_click(){
    ui->dataTable->selectionModel()->clearSelection();
}

void CashRegisterWindow::table_click(){
    ui->itemsList->selectionModel()->clearSelection();
}

void CashRegisterWindow::sync_click(){
    //TODO
}

void CashRegisterWindow::searchChanged(){
    if(ui->searchBar->text() != ""){
        for(int i = 0; i < ui->dataTable->rowCount(); i++){
            if(ui->dataTable->item(i, 1)->text().toLower().contains(ui->searchBar->text().toLower()) || ui->dataTable->item(i, 2)->text().toLower().contains(ui->searchBar->text().toLower())){
                ui->dataTable->showRow(i);
            }
            else{
                ui->dataTable->hideRow(i);
            }
        }
    }
    else{
        for(int i = 0; i < ui->dataTable->rowCount(); i++){
            ui->dataTable->showRow(i);
        }
    }
}

void CashRegisterWindow::closeEvent(QCloseEvent *event){
    qApp->exit();
}

CashRegisterWindow::~CashRegisterWindow()
{
    delete ui;
}

