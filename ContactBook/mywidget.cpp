#include "mywidget.h"
#include "ui_mywidget.h"

#include <QFile>
#include <QDebug>
#include <QFileDialog>



QString mFilename = "C:/Users/jarie/OneDrive/桌面/ContactBook/ContactBook.txt";

void Write(QString Filename,QString str){
    QFile mFile(Filename);
    if(!mFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug()<<"could not open file for write";
        return;
    }
    QTextStream out(&mFile);
    out<<str;
    mFile.flush();
    mFile.close();
}

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    QStringList ColTotle;
    ui->tableWidget->horizontalHeader()->setSectionsMovable(false);
    ui->tableWidget->horizontalHeader()->setDragEnabled(false);
    ui->tableWidget->horizontalHeader()->setDragDropMode(QAbstractItemView::NoDragDrop);

    ui->tableWidget->setColumnCount(4);
    ColTotle<<QStringLiteral("學號")<<QStringLiteral("班級")<<QStringLiteral("姓名")<<QStringLiteral("電話");
    ui->tableWidget->setHorizontalHeaderLabels(ColTotle);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    QTableWidgetItem *inputRow1,*inputRow2,*inputRow3,*inputRow4;

    inputRow1= new QTableWidgetItem(QString(ui->lineEdit->text()));
    inputRow2= new QTableWidgetItem(QString(ui->lineEdit_2->text()));
    inputRow3= new QTableWidgetItem(QString(ui->lineEdit_3->text()));
    inputRow4= new QTableWidgetItem(QString(ui->lineEdit_4->text()));

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,inputRow1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,inputRow2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,inputRow3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,inputRow4);


}


void MyWidget::on_pushButton_2_clicked()
{
    QString saveFile="";
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        for(int j=0;j<ui->tableWidget->columnCount();j++){
            saveFile+=ui->tableWidget->item(i,j)->text()+",";
        }
        saveFile+="\n";
    }
    Write(mFilename,saveFile);
}


void MyWidget::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "選擇資料檔案",
        "",
        "CSV Files (*.csv);;Text Files (*.txt);;All Files (*)");

    if (fileName.isEmpty()) return;

    QFile mFile(fileName);
    if (!mFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "File read error:" << mFile.errorString();
        return;
    }

    ui->tableWidget->setRowCount(0);

    QTextStream in(&mFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;

        QStringList parts = line.split(",");

        if (parts.size() >= 4) {
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);

            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(parts[0]));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(parts[1]));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(parts[2]));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(parts[3]));
        }
    }

    mFile.close();
}



void MyWidget::on_pushButton_3_clicked()
{
    close();
}



