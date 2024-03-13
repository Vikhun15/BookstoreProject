#include "../Header_files/addwindow.h"
#include "../UI_files/ui_addwindow.h"
#include "../Header_files/book.h"
#include <QTableWidgetItem>
#include <QBrush>
#include <stdlib.h>
#include <QMessageBox>
#include <QFileDialog>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>


AddWindow::AddWindow(QList<int> list,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddWindow)
{
    ui->setupUi(this);
    AddWindow::ui = ui;

    synced = false;
    ids = list;

    rowNum = 1;
    lastId = 0;

    ui->dataTable->setColumnCount(7);
    ui->dataTable->setHorizontalHeaderLabels(QStringList() << tr("Id")
                                                           << tr("Title")
                                                           << tr("Category")
                                                           << tr("Rating")
                                                           << tr("Price")
                                                           << tr("In Stock")
                                                           << tr("Quantity"));
    ui->dataTable->setRowCount(1);
    ui->dataTable->setItem(0, 0, new QTableWidgetItem);
    ui->dataTable->setItem(0, 1, new QTableWidgetItem);
    ui->dataTable->setItem(0, 2, new QTableWidgetItem);
    ui->dataTable->setItem(0, 3, new QTableWidgetItem);
    ui->dataTable->setItem(0, 4, new QTableWidgetItem);
    ui->dataTable->setItem(0, 5, new QTableWidgetItem);
    ui->dataTable->setItem(0, 6, new QTableWidgetItem);

    ui->dataTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(6, QHeaderView::ResizeToContents);


    this->setStyleSheet(""
                        "QPushButton#syncBtn {background-color:blue;color:white;}"
                        "QPushButton#syncBtn:pressed {background-color:rgb(0,120,255);}"
                        "QPushButton#syncBtn:hover:!pressed {background-color:darkblue;}"
                        "QPushButton#addBtn {background-color:rgb(0,200, 0);color:white;}"
                        "QPushButton#addBtn:pressed {background-color:darkgreen;}"
                        "QPushButton#addBtn:hover:!pressed {background-color:rgb(0,240,0);}"
                        "QPushButton#removeBtn {background-color:red;color:white;}"
                        "QPushButton#removeBtn:disabled {background-color:grey;color:white;}"
                        "QPushButton#removeBtn:pressed {background-color:rgb(120,0,0);}"
                        "QPushButton#removeBtn:hover:!pressed {background-color:rgb(255, 87, 51);}"
                        "");
    ui->removeBtn->setEnabled(false);

    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(AddRow()));
    connect(ui->removeBtn, SIGNAL(clicked()), this, SLOT(RemoveRow()));
    connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(Cancel()));
    connect(ui->syncBtn, SIGNAL(clicked()), this, SLOT(SyncData()));
    connect(ui->importcsvBtn, SIGNAL(clicked()), this, SLOT(ImportCSV()));
    connect(ui->dataTable, SIGNAL(itemSelectionChanged()), this, SLOT(selectedChanged()));

}

AddWindow::~AddWindow()
{
    delete ui;
}

void AddWindow::closeEvent(QCloseEvent * event)
{
    if(synced){
        emit closed();
    }
}

void AddWindow::AddRow(){
    rowNum++;
    ui->dataTable->insertRow(ui->dataTable->rowCount());
    ui->dataTable->setItem(rowNum-1, 0, new QTableWidgetItem);
    ui->dataTable->item(rowNum-1, 0)->setText(QString::number(FindId()));
    ui->dataTable->setItem(rowNum-1, 1, new QTableWidgetItem);
    ui->dataTable->setItem(rowNum-1, 2, new QTableWidgetItem);
    ui->dataTable->setItem(rowNum-1, 3, new QTableWidgetItem);
    ui->dataTable->setItem(rowNum-1, 4, new QTableWidgetItem);
    ui->dataTable->setItem(rowNum-1, 5, new QTableWidgetItem);
    ui->dataTable->setItem(rowNum-1, 6, new QTableWidgetItem);
}

void AddWindow::RemoveRow(){
    rowNum--;
    ids.removeAll(ui->dataTable->item(selectedRowNum,0)->text().toInt());
    for(int i = 0; i <books.length(); i++){
        if(books[i]->id == ui->dataTable->item(selectedRowNum,0)->text().toInt()){
            books.removeAt(i);
        }
    }
    ui->dataTable->removeRow(selectedRowNum);
}

void AddWindow::Cancel(){
    this->close();
}

bool AddWindow::CheckData(){
    bool correct = true;
    for (int i=0;i < ui->dataTable->rowCount();i++) {
        for (int j=0;j < ui->dataTable->columnCount();j++) {
            QTableWidgetItem *item =  ui->dataTable->item(i, j);
            if(item){
                if(item->text().isEmpty()){
                    item->setBackground(QBrush(Qt::red));
                    correct = false;
                }
                else{
                    item->setBackground(QBrush(Qt::white));
                }
                if(j == 0 || j == 3 || j == 4 || j == 6){
                    char *p;
                    bool isNumber = false;
                    if(item->text() == ""){
                        item->setBackground(QBrush(Qt::red));
                        correct = false;
                        continue;
                    }
                    else{
                        item->setBackground(QBrush(Qt::white));
                    }
                    item->text().toDouble(&isNumber);
                    if (!isNumber) {
                        item->setBackground(QBrush(Qt::red));
                        correct = false;
                    }
                    else{
                        item->setBackground(QBrush(Qt::white));
                    }
                }
                if(j == 5){
                    if(item->text().toLower() != "yes" && item->text().toLower() != "no"){
                        item->setBackground(QBrush(Qt::red));
                        correct = false;
                    }
                    else{
                        item->setBackground(QBrush(Qt::white));
                    }
                }
            }

        }
    }
    return correct;
}

void AddWindow::SyncData(){
    if(CheckData()){
        QMessageBox msg;
        msg.setText("Successful sync!");;
        msg.exec();

        books.clear();

        for(int i = 0; i < ui->dataTable->rowCount(); i++){
            int id = ui->dataTable->item(i, 0)->text().toInt();
            lastId = id;
            QString title = ui->dataTable->item(i, 1)->text();
            QString category = ui->dataTable->item(i, 2)->text();
            double rating = ui->dataTable->item(i, 3)->text().toDouble();
            double price = ui->dataTable->item(i, 4)->text().toDouble();
            bool stock = ui->dataTable->item(i, 5)->text().toLower() == "yes";
            int quantity = ui->dataTable->item(i, 6)->text().toInt();
            books.append(new Book(id, title, category, rating, price, stock, quantity));
        }
        synced = true;
        this->close();
    }
}

void AddWindow::selectedChanged(){
    if(ui->dataTable->selectionModel()->hasSelection()){
        selectedRowNum = ui->dataTable->selectionModel()->selectedRows().at(0).row();
        ui->removeBtn->setEnabled(true);
    }
    else{
        ui->removeBtn->setEnabled(false);
    }
}

void AddWindow::ReadCSV(QString path){
    std::ifstream file(path.toStdString());

    std::string line;
    if(file.good())
    {
        std::getline(file, line);

    }

    while(std::getline(file, line))
    {
        QList<std::string> lineSplit;

        size_t pos = 0;
        std::string token;
        std::string delimiter = ",";

        int countT = 0;

        for (int i = 0; i < line.size(); i++)
            if (line[i] == delimiter[0]) countT++;
        int count = countT-5;
        if(count > 0){
            std::string titleTemp = "";
            count++;
            while ((pos = line.find(delimiter)) != std::string::npos && count > 0) {
                token = line.substr(0, pos);
                titleTemp = titleTemp + "," + token;
                line.erase(0, pos + delimiter.length());
                count--;
            }
            if(titleTemp[0] == ','){
                titleTemp.erase(0,1);
            }

            lineSplit.append(titleTemp);
        }

        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            lineSplit.append(token);
            line.erase(0, pos + delimiter.length());
        }
        lineSplit.append(line);
        double rating = 0;
        if(lineSplit[2] == "One"){
            rating = 1;
        }
        if(lineSplit[2] == "Two"){
            rating = 2;
        }
        if(lineSplit[2] == "Three"){
            rating = 3;
        }
        if(lineSplit[2] == "Four"){
            rating = 4;
        }
        if(lineSplit[2] == "Five"){
            rating = 5;
        }
        lastId = FindId();
        QString title = QString::fromStdString(lineSplit[0]);
        QString category = QString::fromStdString(lineSplit[1]);
        double price = QString::fromStdString(lineSplit[3]).toDouble();
        bool stock = (lineSplit[4] == "In stock");
        int quantity = QString::fromStdString(lineSplit[5]).toInt();
        Book* book = new Book(lastId,title,category,rating,price,stock,quantity);
        books.append(book);

    }
    rowNum = 0;
    ui->dataTable->setRowCount(0);
    for(int i = 0; i < books.length(); i++){
        ui->dataTable->insertRow(ui->dataTable->rowCount());
        rowNum++;
        ui->dataTable->setItem(ui->dataTable->rowCount()-1, 0, new QTableWidgetItem(QString::number(books[i]->id)));
        ui->dataTable->setItem(ui->dataTable->rowCount()-1, 1, new QTableWidgetItem(books[i]->title));
        ui->dataTable->setItem(ui->dataTable->rowCount()-1, 2, new QTableWidgetItem(books[i]->category));
        ui->dataTable->setItem(ui->dataTable->rowCount()-1, 3, new QTableWidgetItem(QString::number(books[i]->rating)));
        ui->dataTable->setItem(ui->dataTable->rowCount()-1, 4, new QTableWidgetItem(QString::number(books[i]->price)));
        ui->dataTable->setItem(ui->dataTable->rowCount()-1, 5, new QTableWidgetItem(books[i]->inStock ? "Yes" : "No"));
        ui->dataTable->setItem(ui->dataTable->rowCount()-1, 6, new QTableWidgetItem(QString::number(books[i]->quantity)));
    }

    file.close();
}

int AddWindow::FindId(){
    int count = 1;
    while(ids.indexOf(count) >= 0){
        count++;
    }
    ids.append(count);
    return count;
}

void AddWindow::ImportCSV(){
    QFileDialog fileDialog;
    fileDialog.setNameFilter(tr("CSV files (*.CSV *.csv)"));

    if(fileDialog.exec() == 1){
        for(int i = 0; i < fileDialog.selectedFiles().length(); i++){
            QString path = fileDialog.selectedFiles().at(i);
            ReadCSV(path);
        }
    }
}
