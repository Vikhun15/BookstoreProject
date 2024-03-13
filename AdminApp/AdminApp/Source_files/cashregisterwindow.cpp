#include "../Header_files/cashregisterwindow.h"
#include "../UI_files/ui_cashregisterwindow.h"
#include "../Header_files/mainwindow.h"
#include <QTableWidget>
#include <QMessageBox>
#include <QDebug>

CashRegisterWindow::CashRegisterWindow(bool loggedIn, QString username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CashRegisterWindow)
{
    ui->setupUi(this);
    Setup();
    CashRegisterWindow::loggedIn = loggedIn;
    CashRegisterWindow::books = books;

}
CashRegisterWindow::CashRegisterWindow(bool loggedIn, DataBase* db, PGDatabase* pgdb , QList<Book*> books,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CashRegisterWindow)
{
    ui->setupUi(this);
    CashRegisterWindow::loggedIn = loggedIn;
    CashRegisterWindow::db = db;
    CashRegisterWindow::pgdb = pgdb;
    CashRegisterWindow::books = books;
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

CashRegisterWindow::CashRegisterWindow(DataBase *db, PGDatabase *pgdb , QList<Book*> books ,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CashRegisterWindow)
{
    ui->setupUi(this);
    loggedIn = false;
    CashRegisterWindow::db = db;
    CashRegisterWindow::pgdb = pgdb;
    CashRegisterWindow::books = books;
    Setup();

}

void CashRegisterWindow::Setup(){
    this->setStyleSheet("QPushButton#syncBtn {background-color:blue; color:white;}QPushButton#syncBtn:pressed {background-color:rgb(0,120,255);}QPushButton#syncBtn:hover:!pressed {background-color:darkblue;}");
    login = new Login(false, pgdb->GetUsers(), this);

    if(!loggedIn){
        login = new Login(!loggedIn, pgdb->GetUsers(), this);
        login->setModal(true);
    }

    connect(login, SIGNAL(passUsername()), this, SLOT(changeUsername()));

    connect(ui->logoutBtn, SIGNAL(clicked()), this, SLOT(logout_click()));
    connect(ui->modeChangeBtn, SIGNAL(clicked()), this, SLOT(mode_click()));

    connect(ui->refreshBtn, SIGNAL(clicked()), this, SLOT(refresh_table()));

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
    ui->itemsList->setColumnCount(3);
    ui->itemsList->setHorizontalHeaderLabels(QStringList() << tr("Title")
                                                           << tr("Price")
                                                           << tr("Quantity"));


    //books.append(new Book(1, "The Great Gatsby", "Fiction", 4.2, 22.50, true, 15));
    //ui->dataTable->setRowCount(1);

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
    login = new Login(!loggedIn, pgdb->GetUsers(), this);
    login->setModal(true);

    connect(login, SIGNAL(passUsername()), this, SLOT(changeUsername()));

    login->open();
}

void CashRegisterWindow::mode_click(){
    ((MainWindow*)parent())->ChangeData(loggedIn, ui->username->text());
    ((MainWindow*)parent())->show();
    ((MainWindow*)parent())->refresh_table();
    db->SetSetting("manage");
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
        selectedRows.clear();
        selectedItems.clear();
        if(ui->dataTable->selectionModel()->hasSelection()){
            ui->itemsList->clearSelection();
            selectedRowNum = ui->dataTable->selectionModel()->selectedRows().at(0).row();
            for(int i = 0; i < ui->dataTable->selectionModel()->selectedRows().length(); i++){
                selectedRows.append(ui->dataTable->selectionModel()->selectedRows().at(i).row());
            }
        }
        if(ui->itemsList->selectionModel()->hasSelection()){
            ui->dataTable->clearSelection();
            selectedListNum = ui->itemsList->selectionModel()->selectedRows().at(0).row();
            for(int i = 0; i < ui->itemsList->selectionModel()->selectedRows().length(); i++){
                selectedItems.append(ui->itemsList->selectionModel()->selectedRows().at(i).row());
            }
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
        if(selectedRows.length() <= 1){
            int num = ui->dataTable->item(selectedRowNum, 6)->text().toInt();
            QString title = ui->dataTable->item(selectedRowNum, 1)->text();
            int index = 0;
            for(int i = 0; i < books.length(); i++){
                if(books[i]->title == title){
                    index = i;
                    break;
                }
            }
            if(num != 0){
                if(num - 1 == 0){
                    ui->dataTable->item(selectedRowNum, 5)->setText("No");
                }
                ui->dataTable->item(selectedRowNum, 6)->setText(QString::number(num-1));
                books[index]->quantity--;
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
        else{
            for(int i = 0; i < selectedRows.length(); i++){
                int num = ui->dataTable->item(selectedRows[i], 6)->text().toInt();
                QString title = ui->dataTable->item(selectedRows[i], 1)->text();
                int index = 0;
                for(int j = 0; j < books.length(); j++){
                    if(books[j]->title == title){
                        index = j;
                        break;
                    }
                }
                if(num != 0){
                    if(num - 1 == 0){
                        ui->dataTable->item(selectedRows[i], 5)->setText("No");
                    }
                    ui->dataTable->item(selectedRows[i], 6)->setText(QString::number(num-1));
                    books[index]->quantity--;
                    bool found = false;
                    for(int j = 0; j < ui->itemsList->rowCount(); j++){
                        if(ui->itemsList->item(j, 0)->text() == title){
                            found = true;
                            ui->itemsList->item(j, 2)->setText(QString::number(ui->itemsList->item(j, 2)->text().toInt()+1));
                        }
                    }
                    if(!found){
                        ui->itemsList->insertRow(ui->itemsList->rowCount());
                        ui->itemsList->setItem(ui->itemsList->rowCount()-1, 0, new QTableWidgetItem(ui->dataTable->item(selectedRows[i], 1)->text()));
                        ui->itemsList->setItem(ui->itemsList->rowCount()-1, 1, new QTableWidgetItem(ui->dataTable->item(selectedRows[i], 4)->text()));
                        ui->itemsList->setItem(ui->itemsList->rowCount()-1, 2, new QTableWidgetItem("1"));
                    }
                }
            }
        }
    }
    if(ui->itemsList->selectionModel()->hasSelection()){
        if(selectedItems.length() <= 1){
            int row = 0;
            int num = 0;
            QString title = ui->itemsList->item(selectedListNum, 0)->text();
            int index = 0;
            for(int i = 0; i < books.length(); i++){
                if(books[i]->title == title){
                    index = i;
                    break;
                }
            }
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
                books[index]->quantity--;
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
        else{
            for(int i = 0; i < selectedItems.length(); i++){
                int row = 0;
                int num = 0;
                int index = 0;
                QString title = ui->itemsList->item(selectedItems[i], 0)->text();
                for(int j = 0; j < books.length(); j++){
                    if(books[j]->title == title){
                        index = j;
                        break;
                    }
                }
                for(int j = 0; j < ui->dataTable->rowCount(); j++){
                    if(ui->dataTable->item(j, 1)->text() == title){
                        num = ui->dataTable->item(j, 6)->text().toInt();
                        row = j;
                        break;
                    }
                }
                if(num != 0){
                    if(num - 1 == 0){
                        ui->dataTable->item(row, 5)->setText("No");
                    }
                    ui->dataTable->item(row, 6)->setText(QString::number(num-1));
                    books[index]->quantity--;
                    bool found = false;
                    for(int j = 0; j < ui->itemsList->rowCount(); j++){
                        if(ui->itemsList->item(j, 0)->text() == title){
                            found = true;
                            ui->itemsList->item(j, 2)->setText(QString::number(ui->itemsList->item(j, 2)->text().toInt()+1));
                            break;
                        }
                    }
                    if(!found){
                        ui->itemsList->insertRow(ui->itemsList->rowCount());
                        ui->itemsList->setItem(ui->itemsList->rowCount()-1, 0, new QTableWidgetItem(ui->dataTable->item(selectedItems[i], 1)->text()));
                        ui->itemsList->setItem(ui->itemsList->rowCount()-1, 1, new QTableWidgetItem(ui->dataTable->item(selectedItems[i], 4)->text()));
                        ui->itemsList->setItem(ui->itemsList->rowCount()-1, 2, new QTableWidgetItem("1"));
                    }
                }
            }
        }

    }
    calculatePrice();
    calculateTotal();
}

void CashRegisterWindow::remove_click(){
    if(ui->itemsList->selectionModel()->hasSelection()){
        if(selectedItems.length() <= 1){
            int num = ui->itemsList->item(selectedListNum, 2)->text().toInt();
            QString title = ui->itemsList->item(selectedListNum, 0)->text();
            int index = 0;
            for(int i = 0; i < books.length(); i++){
                if(books[i]->title == title){
                    index = i;
                    break;
                }
            }
            if(num - 1 == 0){
                ui->itemsList->removeRow(selectedListNum);
            }
            else{
                ui->itemsList->item(selectedListNum, 2)->setText(QString::number(num-1));
            }
            for(int i = 0; i < ui->dataTable->rowCount(); i++){
                if(ui->dataTable->item(i, 1)->text() == title){
                    if(ui->dataTable->item(i, 5)->text() == "No"){
                        ui->dataTable->item(i, 5)->setText("Yes");
                    }
                    ui->dataTable->item(i, 6)->setText(QString::number(ui->dataTable->item(i, 6)->text().toInt()+1));
                    books[index]->quantity--;
                }
            }
        }
        else{
            QList<int> rows;
            for(int i = 0; i < selectedItems.length(); i++){
                rows.append(selectedItems[i]);
                int num = ui->itemsList->item(selectedItems[i], 2)->text().toInt();
                QString title = ui->itemsList->item(selectedItems[i], 0)->text();
                int index = 0;
                for(int j = 0; j < books.length(); j++){
                    if(books[j]->title == title){
                        index = j;
                        break;
                    }
                }
                if(num - 1 > 0){
                    ui->itemsList->item(selectedItems[i], 2)->setText(QString::number(num-1));
                }
                for(int j = 0; j < ui->dataTable->rowCount(); j++){
                    if(ui->dataTable->item(j, 1)->text() == title){
                        if(ui->dataTable->item(j, 5)->text() == "No"){
                            ui->dataTable->item(j, 5)->setText("Yes");
                        }
                        ui->dataTable->item(j, 6)->setText(QString::number(ui->dataTable->item(j, 6)->text().toInt()+1));
                        books[index]->quantity--;
                    }
                }
            }
            for(int i = rows.length()-1; i >= 0; i--){
                if(ui->itemsList->item(rows[i], 2)->text().toInt() - 1 == 0){
                    ui->itemsList->removeRow(rows[i]);
                }
            }
        }
    }
    if(ui->dataTable->selectionModel()->hasSelection()){
        if(selectedRows.length() <= 1){
            if(ui->itemsList->rowCount() > 0){
                QString title = ui->dataTable->item(selectedRowNum, 1)->text();
                bool contains = false;

                for(int i = 0; i < ui->itemsList->rowCount(); i++){
                    if(ui->itemsList->item(i, 0)->text() == title){
                        contains = true;
                        break;
                    }
                }
                if(contains){
                    int row = 0;
                    int num = 0;
                    int index = 0;
                    for(int i = 0; i < books.length(); i++){
                        if(books[i]->title == title){
                            index = i;
                            break;
                        }
                    }
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
                        ui->itemsList->item(row, 2)->setText(QString::number(num-1));
                    }
                    for(int i = 0; i < ui->dataTable->rowCount(); i++){
                        bool found = false;
                        for(int j = 0; j < ui->itemsList->rowCount(); j++){
                            if(ui->itemsList->item(j, 0)->text() == title){
                                found = true;
                            }
                        }
                        if(ui->dataTable->item(i, 1)->text() == title && found){
                            if(ui->dataTable->item(i, 5)->text() == "No"){
                                ui->dataTable->item(i, 5)->setText("Yes");
                            }
                            ui->dataTable->item(i, 6)->setText(QString::number(ui->dataTable->item(i, 6)->text().toInt()+1));
                            books[index]->quantity++;
                        }
                    }
                }
            }
        }
        else{
                QList<int> rows;
                QList<bool> changed;
                for(int i = selectedRows.length()-1; i >= 0; i--){
                    bool contains = false;
                    for(int j = 0; j < ui->itemsList->rowCount(); j++){
                        if(ui->dataTable->item(selectedRows[i], 1)->text() == ui->itemsList->item(j, 0)->text()){
                            contains = true;
                            break;
                        }
                    }
                        if(contains){
                            if(ui->itemsList->rowCount() > 0){
                                QString title = ui->dataTable->item(selectedRows[i], 1)->text();
                                int row = 0;
                                int num = 0;
                                int index = 0;
                                for(int j = 0; j < books.length(); j++){
                                    if(books[j]->title == title){
                                        index = j;
                                        break;
                                    }
                                }
                                for(int j = 0;j < ui->itemsList->rowCount(); j++){
                                    if(ui->itemsList->item(j,0)->text() == title){
                                        num = ui->itemsList->item(j, 2)->text().toInt();
                                        row = j;
                                        rows.append(row);
                                        break;
                                    }
                                }
                                changed.append(num-1 > 0);
                                if(num-1 > 0){
                                    ui->itemsList->item(row, 2)->setText(QString::number(num-1));
                                }
                                else{
                                    ui->itemsList->removeRow(row);
                                }
                                for(int j = 0; j < ui->dataTable->rowCount(); j++){
                                    if(ui->dataTable->item(j, 1)->text() == title){
                                        if(ui->dataTable->item(j, 5)->text() == "No"){
                                            ui->dataTable->item(j, 5)->setText("Yes");
                                        }
                                        ui->dataTable->item(j, 6)->setText(QString::number(ui->dataTable->item(j, 6)->text().toInt()+1));
                                        books[index]->quantity++;
                                    }
                                }
                            }
                        }
                }

        }
    }
    calculatePrice();
    calculateTotal();
}

void CashRegisterWindow::list_click(){
    ui->dataTable->clearSelection();
    selectedRows.clear();
}

void CashRegisterWindow::table_click(){
    ui->itemsList->clearSelection();
    selectedItems.clear();
}

void CashRegisterWindow::sync_click(){
    QMessageBox msg;
    msg.setText("Are you sure you want to finalize the transaction?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::Yes);
    int result = msg.exec();
    if(result){
        pgdb->FillBooks(books);
        ui->itemsList->setRowCount(0);
        selectedListNum = 0;
        ui->priceTxt->setText("0$");
        ui->totalTxt->setText("0$");
    }
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

void CashRegisterWindow::refresh_table(){
    books = pgdb->GetBooks();
    SyncTable();
}

void CashRegisterWindow::closeEvent(QCloseEvent *event){
    qApp->exit();
}

CashRegisterWindow::~CashRegisterWindow()
{
    delete ui;
}

