#include "../Header_files/editwindow.h"
#include "../UI_files/ui_editwindow.h"

EditWindow::EditWindow(Book* book, QList<int> id, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditWindow)
{
    ui->setupUi(this);

    ids = id;
    EditWindow::book = book;

    ui->idTxt->setText(QString::number(book->id));
    ui->titleTxt->setText(book->title);
    ui->categoryTxt->setText(book->category);
    ui->ratingTxt->setText(QString::number(book->rating));
    ui->priceTxt->setText(QString::number(book->price));
    ui->quantityTxt->setText(QString::number(book->quantity));
    ui->stockCheck->setChecked(book->inStock);

}

void EditWindow::accept(){
    if(CheckData()){
        book->id = ui->idTxt->text().toInt();
        book->title = ui->titleTxt->text();
        book->category = ui->categoryTxt->text();
        book->rating = ui->ratingTxt->text().toDouble();
        book->price = ui->priceTxt->text().toDouble();
        book->quantity = ui->quantityTxt->text().toInt();
        book->inStock = ui->stockCheck->isChecked();
        this->done(1);
    }
}

bool EditWindow::CheckData(){
    bool correct = true;
    bool isNumber = false;
    int id = ui->idTxt->text().toInt(&isNumber);
    if(!isNumber || (ids.indexOf(id) >= 0 && id != book->id)){
        ui->idTxt->setStyleSheet("background-color:red;color:white;");
        correct = false;
    }
    else{
        ui->idTxt->setStyleSheet("background-color:white;color:black;");
    }
    ui->ratingTxt->text().toDouble(&isNumber);
    if(!isNumber){
        ui->ratingTxt->setStyleSheet("background-color:red;color:white;");
        correct = false;
    }
    else{
        ui->ratingTxt->setStyleSheet("background-color:white;color:black;");
    }
    ui->priceTxt->text().toDouble(&isNumber);
    if(!isNumber){
        ui->priceTxt->setStyleSheet("background-color:red;color:white;");
        correct = false;
    }
    else{
        ui->priceTxt->setStyleSheet("background-color:white;color:black;");
    }
    ui->quantityTxt->text().toInt(&isNumber);
    if(!isNumber){
        ui->quantityTxt->setStyleSheet("background-color:red;color:white;");
        correct = false;
    }
    else{
        ui->quantityTxt->setStyleSheet("background-color:white;color:black;");
    }
    if(ui->titleTxt->text().count(' ') == ui->titleTxt->text().length() || ui->titleTxt->text() == ""){
        ui->titleTxt->setStyleSheet("background-color:red;color:white;");
        correct = false;
    }
    else{
        ui->titleTxt->setStyleSheet("background-color:white;color:black;");
    }
    if(ui->categoryTxt->text().count(' ') == ui->categoryTxt->text().length() || ui->categoryTxt->text() == ""){
        ui->categoryTxt->setStyleSheet("background-color:red;color:white;");
        correct = false;
    }
    else{
        ui->categoryTxt->setStyleSheet("background-color:white;color:black;");
    }
    return correct;
}

EditWindow::~EditWindow()
{
    delete ui;
}
