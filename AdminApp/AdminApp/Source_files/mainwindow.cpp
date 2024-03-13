#include "../Header_files/mainwindow.h"
#include "../UI_files/ui_mainwindow.h"
#include "../Header_files/login.h"
#include "../Header_files/book.h"
#include "../Header_files/addwindow.h"
#include "../Header_files/editwindow.h"
#include "../Header_files/cashregisterwindow.h"
#include "../database.h"
#include "../Data/pgdatabase.h"
#include <QMessageBox>
#include <QFileDialog>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loggedIn = false;
    Setup();
}

MainWindow::MainWindow(bool loggedIn, QString username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::loggedIn = loggedIn;
    ui->username->setText(username);
    Setup();
}

void MainWindow::Setup(){

    this->setStyleSheet("QPushButton#syncBtn {background-color:blue; color:white;}QPushButton#syncBtn:pressed {background-color:rgb(0,120,255);}QPushButton#syncBtn:hover:!pressed {background-color:darkblue;}");

    pgdb = new PGDatabase();
    db = new DataBase();
    books = pgdb->GetBooks();

    window = new CashRegisterWindow(true,db, pgdb, books,this);
    window->hide();

    bool cRegister = (db->GetSetting() != "manage");

    if(cRegister){
        window = new CashRegisterWindow(db, pgdb, books, this);
        window->books = books;
        window->show();
        this->hide();
    }
    if(!loggedIn){
        login = new Login(!loggedIn, pgdb->GetUsers(), this);
        login->setModal(true);
    }
    //connect(window, SIGNAL(mode_clicked()), this, SLOT(refresh_table()));
    //connect(ui->modeChangeBtn, SIGNAL(clicked()), window, SLOT(mode_click()));

    ui->removeBtn->setEnabled(false);

    ui->stockBtn->setEnabled(false);
    ui->stockBtn->setText("Change Stock");

    ui->editBtn->setEnabled(false);

    connect(login, SIGNAL(passUsername()), this, SLOT(changeUsername()));

    connect(ui->logoutBtn, SIGNAL(clicked()), this, SLOT(logout_click()));
    connect(ui->modeChangeBtn, SIGNAL(clicked()), this, SLOT(mode_click()));

    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(add_click()));
    connect(ui->editBtn, SIGNAL(clicked()), this, SLOT(edit_click()));
    connect(ui->removeBtn, SIGNAL(clicked()), this, SLOT(remove_click()));
    connect(ui->stockBtn, SIGNAL(clicked()), this, SLOT(stock_click()));

    connect(ui->refreshBtn, SIGNAL(clicked()), this, SLOT(refresh_table()));

    dir = QString::fromStdString("/home");
    connect(ui->exportBtn, SIGNAL(clicked()), this, SLOT(export_click()));


    connect(ui->syncBtn, SIGNAL(clicked()), this, SLOT(sync_click()));
    connect(ui->dataTable, SIGNAL(itemSelectionChanged()), this, SLOT(selectedChanged()));

    connect(ui->searchBar, SIGNAL(textChanged(QString)), this, SLOT(searchChanged()));


    ui->dataTable->setColumnCount(7);
    ui->dataTable->setHorizontalHeaderLabels(QStringList() << tr("Id")
                                                           << tr("Title")
                                                           << tr("Category")
                                                           << tr("Rating")
                                                           << tr("Price")
                                                           << tr("In Stock")
                                                           << tr("Quantity"));
    ui->dataTable->setRowCount(1);


    books = pgdb->GetBooks();
    //books.append(new Book(1, "The Great Gatsby", "Fiction", 4.2, 22.50, true, 15));

    ui->dataTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(6, QHeaderView::ResizeToContents);



    /*
    for(int i = 0; i < books.length(); i++){
        ui->dataTable->setItem(i, 0, new QTableWidgetItem(QString::number(books[i]->id)));
        ui->dataTable->setItem(i, 1, new QTableWidgetItem(books[i]->title));
        ui->dataTable->setItem(i, 2, new QTableWidgetItem(books[i]->category));
        ui->dataTable->setItem(i, 3, new QTableWidgetItem(QString::number(books[i]->rating)));
        ui->dataTable->setItem(i, 4, new QTableWidgetItem(QString::number(books[i]->price)));

        QString stock = "";
        if(books[i]->inStock){
            stock = "Yes";
        }
        else{
            stock = "no";
        }
        ui->dataTable->setItem(i, 5, new QTableWidgetItem(stock));
        ui->dataTable->setItem(i, 6, new QTableWidgetItem(QString::number(books[i]->quantity)));
    }
*/
    SyncTable();
    SyncIds();
    if(!loggedIn && !cRegister){
        login->open();
    }


}

void MainWindow::SyncIds(){
    for(int i = 0; i < ui->dataTable->rowCount(); i++){
        ids.append(ui->dataTable->item(i, 0)->text().toInt());
    }
}

void MainWindow::SyncTable(){
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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeUsername(){
    ui->username->setText(login->getUsername());
    loggedIn = true;
}

void MainWindow::logout_click(){
    login = new Login(!loggedIn, pgdb->GetUsers(), this);
    login->setModal(true);

    connect(login, SIGNAL(passUsername()), this, SLOT(changeUsername()));

    login->open();
}

void MainWindow::mode_click(){
    window->ChangeData(loggedIn, ui->username->text(), books);
    db->SetSetting("register");
    window->show();
    window->refresh_table();
    this->hide();
}

void MainWindow::ChangeData(bool loggedIn, QString username){
    MainWindow::loggedIn = loggedIn;
    ui->username->setText(username);
}

void MainWindow::add_click(){
    addWindow = new AddWindow(ids,this);
    addWindow->setModal(true);
    connect(addWindow, SIGNAL(closed()), this, SLOT(add_to_table()));
    addWindow->exec();
}

void MainWindow::add_to_table(){
    for(int i = 0; i < addWindow->books.length(); i++){
        if(ids.indexOf(addWindow->books[i]->id) == -1){
            books.append(addWindow->books[i]);
        }
    }
    SyncIds();
    SyncTable();
}

void MainWindow::edit_click(){

    Book* book;

    for(int i = 0; i < books.length(); i++){
        if(ui->dataTable->item(selectedRowNum, 0)->text().toInt() == books[i]->id){
            book = books[i];
            break;
        }
    }

    EditWindow edit(book, ids, this);
    int result = edit.exec();

    if(result == 1){
        books[selectedRowNum] = edit.book;
        ui->dataTable->setItem(selectedRowNum, 0, new QTableWidgetItem(QString::number(books[selectedRowNum]->id)));
        ui->dataTable->setItem(selectedRowNum, 1, new QTableWidgetItem(books[selectedRowNum]->title));
        ui->dataTable->setItem(selectedRowNum, 2, new QTableWidgetItem(books[selectedRowNum]->category));
        ui->dataTable->setItem(selectedRowNum, 3, new QTableWidgetItem(QString::number(books[selectedRowNum]->rating)));
        ui->dataTable->setItem(selectedRowNum, 4, new QTableWidgetItem(QString::number(books[selectedRowNum]->price)));
        ui->dataTable->setItem(selectedRowNum, 5, new QTableWidgetItem(books[selectedRowNum]->inStock ? "Yes" : "No"));
        ui->dataTable->setItem(selectedRowNum, 6, new QTableWidgetItem(QString::number(books[selectedRowNum]->quantity)));
    }

}

void MainWindow::remove_click(){
    ids.removeAll(ui->dataTable->item(selectedRowNum,0)->text().toInt());
    for(int i = 0; i <books.length(); i++){
        if(books[i]->id == ui->dataTable->item(selectedRowNum,0)->text().toInt()){
            books.removeAt(i);
        }
    }
    ui->dataTable->removeRow(selectedRowNum);
}

void MainWindow::selectedChanged(){
    if(ui->dataTable->selectionModel()->hasSelection()){
        selectedRowNum = ui->dataTable->selectionModel()->selectedRows().at(0).row();
        ui->removeBtn->setEnabled(true);
        ui->stockBtn->setEnabled(true);
        ui->stockBtn->setText(books[selectedRowNum]->inStock ? "In stock" : "Out of stock");
        ui->editBtn->setEnabled(true);
    }
    else{
        ui->removeBtn->setEnabled(false);
        ui->stockBtn->setEnabled(false);
        ui->stockBtn->setText("Change stock");
        ui->editBtn->setEnabled(false);
    }
}

void MainWindow::stock_click(){

    bool result = false;
    if(ui->stockBtn->text() == "Out of stock"){
        result = true;
        ui->stockBtn->setText("In stock");
    }
    else{
        result = false;
        ui->stockBtn->setText("Out of stock");
    }

    for(int i = 0; i < books.length(); i++){
        if(books[i]->id == ui->dataTable->item(selectedRowNum,0)->text().toInt()){
            books[i]->inStock = result;
        }
    }
    ui->dataTable->item(selectedRowNum, 5)->setText(result ? "Yes" : "No");
    ui->dataTable->selectRow(selectedRowNum);
}

void MainWindow::export_click(){
        QString prevDir = dir;
        QString temp = QFileDialog::getExistingDirectory(this, tr("Choose export location"),
                                                prevDir,
                                                QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
        if(!temp.isNull()){
            dir = temp;
            WriteCSV(dir.toStdString());

            QMessageBox msg;
            msg.setText("Successfully exported to " + dir + "/output.csv");
            msg.exec();
        }

}

void MainWindow::WriteCSV(std::string path){
    std::fstream fout;

    fout.open(path + "/output.csv", std::ios::out | std::ios::trunc);

    for (int i = 0; i < books.length(); i++) {

        fout << std::to_string(books[i]->id) << ", "
             << books[i]->title.toStdString() << ", "
             << books[i]->category.toStdString() << ", "
             << std::to_string(books[i]->rating) << ", "
             << std::to_string(books[i]->price) << ", "
             << (books[i]->inStock ? "Yes" : "No") << ", "
             << std::to_string(books[i]->quantity)
             << "\n";
    }
    fout.close();
}

void MainWindow::sync_click(){
    QMessageBox msg;
    msg.setText("Are you sure you want to sync to the database?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::Yes);
    int result = msg.exec();
    if(result){
        pgdb->FillBooks(books);
    }
}


void MainWindow::refresh_table(){
    books = pgdb->GetBooks();
    SyncTable();
}

void MainWindow::searchChanged(){
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
