#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "distances.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
int cantidad=1;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_manhatan_clicked(){
    ui->listResultados->clear();
    string user = ui->dato1->text().toStdString();
    string user2 = ui->dato2->text().toStdString();
    string db= ui->dataBase->currentText().toStdString();
    unsigned t0, t1;
    t0=clock();
    double resultado=manhatan(db,user,user2);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    ui->listResultados->addItem(QString::number(resultado));
    ui->listResultados->addItem(QString::number(time)+"s");

}

void MainWindow::on_euclidiana_clicked(){
    ui->listResultados->clear();
    string user = ui->dato1->text().toStdString();
    string user2 = ui->dato2->text().toStdString();
    string db= ui->dataBase->currentText().toStdString();
    unsigned t0, t1;
    t0=clock();
    double resultado=euclidiana(db,user,user2);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    ui->listResultados->addItem(QString::number(resultado));
    ui->listResultados->addItem(QString::number(time)+"s");

}

void MainWindow::on_minkowsky_clicked(){
    ui->listResultados->clear();
    string user = ui->dato1->text().toStdString();
    string user2 = ui->dato2->text().toStdString();
    string db= ui->dataBase->currentText().toStdString();
    unsigned t0, t1;
    t0=clock();
    double resultado=minkowsky(db,user,user2);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    ui->listResultados->addItem(QString::number(resultado));
    ui->listResultados->addItem(QString::number(time)+"s");
}

void MainWindow::on_pearson_clicked(){
    ui->listResultados->clear();
    string user = ui->dato1->text().toStdString();
    string user2 = ui->dato2->text().toStdString();
    string db= ui->dataBase->currentText().toStdString();
    unsigned t0, t1;
    t0=clock();
    double resultado=pearson(db,user,user2);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    ui->listResultados->addItem(QString::number(resultado));
    ui->listResultados->addItem(QString::number(time)+"s");
}

void MainWindow::on_coseno_clicked(){
    ui->listResultados->clear();
    string user = ui->dato1->text().toStdString();
    string user2 = ui->dato2->text().toStdString();
    string db= ui->dataBase->currentText().toStdString();
    unsigned t0, t1;
    t0=clock();
    double resultado=coseno(db,user,user2);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    ui->listResultados->addItem(QString::number(resultado));
    ui->listResultados->addItem(QString::number(time)+"s");

}

void MainWindow::on_jaccard_clicked(){
    ui->listResultados->clear();
    string user = ui->dato1->text().toStdString();
    string user2 = ui->dato2->text().toStdString();
    string db= ui->dataBase->currentText().toStdString();
    unsigned t0, t1;
    t0=clock();
    double resultado=jaccard(db,user,user2);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    ui->listResultados->addItem(QString::number(resultado));
    ui->listResultados->addItem(QString::number(time)+"s");

}

void MainWindow::on_cosenoAjustado_clicked(){
    ui->listResultados->clear();
    string user = ui->dato1->text().toStdString();
    string item = ui->dato2->text().toStdString();
    string db= ui->dataBase->currentText().toStdString();

    unsigned t0, t1;
    t0=clock();
    double cosenoA=cosenoAjustado(db,user,item);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    ui->listResultados->addItem(QString::number(cosenoA));
    ui->listResultados->addItem(QString::number(time)+"s");

}

void MainWindow::on_Matriz_clicked(){
    string db= ui->dataBase->currentText().toStdString();
    int n=0;
    bool ok;
    n = ui->sizeMatriz->text().toInt(&ok);
    ui->tableWidget->setRowCount(n);
    ui->tableWidget->setColumnCount(n-1);
    QStringList moviesHorizontal;
    QStringList moviesVertical;
    ifstream headeritems;
    string strdb="E:/Proyectos/QT/TBD2/"+db+"/indexitem.csv";
    string stritem,stritemant;
    char cadena[40];
    headeritems.open(strdb);
    headeritems>>cadena;
    string itemslist[100];
    stritem=cadena;
    for(int i=0;i<n;i++){
        moviesVertical<<QString::fromStdString(stritem);
        itemslist[i]=stritem;
        stritemant=stritem;
        headeritems>>cadena;
        stritem=cadena;
        if(i!=n-1){
            moviesHorizontal<<QString::fromStdString(stritem);
        }
    }
    ui->tableWidget->setHorizontalHeaderLabels(moviesHorizontal);
    ui->tableWidget->setVerticalHeaderLabels(moviesVertical);


    Tlista item1=NULL;
    Tlista item2=NULL;
    double result=0;
    for(int i=0;i<n-1;i++){
        for(int k=i+1;k<n;k++){
            fillList(item1,itemslist[i],db,"item");
            fillList(item2,itemslist[k],db,"item");
            result=cosAjus(item1,item2,db);
            ui->tableWidget->setItem(i,k-1,new QTableWidgetItem(QString::number(result)));
            destruc(item1);
            destruc(item2);
        }
    }
}


void MainWindow::on_slopeOne_clicked(){
    ui->listResultados->clear();
    string user = ui->dato1->text().toStdString();
    string item = ui->dato2->text().toStdString();
    string db= ui->dataBase->currentText().toStdString();

    unsigned t0, t1;
    t0=clock();
    double slop=slopOne(db,user,item);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    ui->listResultados->addItem(QString::number(slop));
    ui->listResultados->addItem(QString::number(time)+"s");

}


void MainWindow::on_Agregar_clicked()
{
    string user = ui->dato1->text().toStdString();
    string item = ui->dato2->text().toStdString();
    string db= ui->dataBase->currentText().toStdString();
    double n=0;
    n = ui->rating->text().toDouble();
    string struser,stritem,strhu,strhi;
    ifstream huser,hitem;
    fstream dbuser,dbitem, headeruser,headeritem;
    strhu="E:/Proyectos/QT/TBD2/"+db+"/indexuser.csv";
    strhi="E:/Proyectos/QT/TBD2/"+db+"/indexitem.csv";
    huser.open(strhu);
    hitem.open(strhi);
    char cadena[40];
    bool agregaruser=true, agregaritem=true;
    while(!huser.eof()){
        huser>>cadena;
        struser=cadena;
        if(user==struser){
            agregaruser=false;
        }
    }
    while(!hitem.eof()){
        hitem>>cadena;
        stritem=cadena;
        if(item==stritem){
            agregaritem=false;
        }
    }
    if(agregaruser){
        headeruser.open(strhu,ios::app);
        headeruser<<endl<<user;
    }
    if(agregaritem){
        headeritem.open(strhi,ios::app);
        headeritem<<endl<<item;
    }

    struser="E:/Proyectos/QT/TBD2/"+db+"/user/"+user+".csv";
    stritem="E:/Proyectos/QT/TBD2/"+db+"/item/"+item+".csv";

    dbuser.open(struser,ios::app);
    dbuser<<item<<" "<<n<<" "<<endl;
    dbuser.close();

    dbitem.open(stritem,ios::app);
    dbitem<<user<<" "<<n<<" "<<endl;
    dbitem.close();

    ui->listResultados->addItem(QString::number(cantidad)+" "+"Agregado: "+QString::fromStdString(user)+" "+QString::fromStdString(item)+" "+QString::number(n));
    cantidad++;
}




