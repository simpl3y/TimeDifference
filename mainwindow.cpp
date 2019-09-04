#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <boost/date_time.hpp>
#include <cmath>
#include <QMessageBox>

namespace bt = boost::posix_time;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->verticalLayout->addStretch();
    ui->verticalLayout_2->addStretch();
    ui->verticalLayout_3->addStretch();
    generateNewLine();
    on_lineEdit_returnPressed();
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_resetButton_clicked(){

    for(int i = 1; i < ui->verticalLayout->count()-1;){
        qdynamiclineedit *line = qobject_cast<qdynamiclineedit*>(ui->verticalLayout->itemAt(i)->widget());
        ui->verticalLayout->removeWidget(line);
        delete line;
        qdynamiclineedit *line2 = qobject_cast<qdynamiclineedit*>(ui->verticalLayout_2->itemAt(i)->widget());
        ui->verticalLayout->removeWidget(line2);
        delete line2;
        qdynamiclineedit *line3 = qobject_cast<qdynamiclineedit*>(ui->verticalLayout_3->itemAt(i)->widget());
        ui->verticalLayout->removeWidget(line3);
        delete line3;
    }
    qdynamiclineedit *line = qobject_cast<qdynamiclineedit*>(ui->verticalLayout->itemAt(0)->widget());
    line->clear();
    qdynamiclineedit *line2 = qobject_cast<qdynamiclineedit*>(ui->verticalLayout_2->itemAt(0)->widget());
    line2->clear();
    qdynamiclineedit *line3 = qobject_cast<qdynamiclineedit*>(ui->verticalLayout_3->itemAt(0)->widget());
    line3->clear();
}

void MainWindow::generateNewLine()
{
    updateTime();

    qdynamiclineedit *line = new qdynamiclineedit(this);
    ui->verticalLayout->insertWidget(ui->verticalLayout->count()-1,line);
    connect(line,SIGNAL(returnPressed()),SLOT(generateNewLine()));
    //line->setText(QString::number(line->getID()));
    //debug purpose^

    qdynamiclineedit *secondLine = new qdynamiclineedit(this);
    ui->verticalLayout_2->insertWidget(ui->verticalLayout_2->count()-1,secondLine);
    secondLine->setReadOnly(true);

    qdynamiclineedit *minuteLine = new qdynamiclineedit(this);
    ui->verticalLayout_3->insertWidget(ui->verticalLayout_3->count()-1,minuteLine);
    minuteLine->setReadOnly(true);


    line->setFocus();

}

bool MainWindow::check(std::string date){
    bt::ptime d1;
    std::istringstream t1(date);
    t1.imbue(mask);
    t1 >> d1;

    return d1 != bt::ptime();
}


int MainWindow::secondDifference(std::string date1, std::string date2){
    bt::ptime d1;
    bt::ptime d2;

    std::istringstream t1(date1);
    std::istringstream t2(date2);
    t1.imbue(mask);
    t2.imbue(mask);
    t1 >> d1;
    t2 >> d2;

    bt::time_duration diff = d1 - d2;
    return std::abs(diff.ticks()/bt::time_duration::rep_type::ticks_per_second);
}

std::string MainWindow::dateConvert(int seconds){
    int days = seconds / 86400;
    int hours = seconds / 60 / 60 % 24;
    int minutes = seconds / 60 % 60;

    char buffer [50];
    sprintf(buffer,"%d days %02d:%02d:%02d",days,hours,minutes,seconds % 60);
    return std::string(buffer);
}

void MainWindow::updateTime(){
    for(int i = 1; i < ui->verticalLayout->count()-1;i++){
        QString date1 = qobject_cast<qdynamiclineedit*>(ui->verticalLayout->itemAt(i-1)->widget())->text();
        QString date2 = qobject_cast<qdynamiclineedit*>(ui->verticalLayout->itemAt(i)->widget())->text();

        if(!check(date1.toStdString()) || !check(date2.toStdString())){
            qobject_cast<qdynamiclineedit*>(ui->verticalLayout_2->itemAt(i-1)->widget())->setText("Invalid Format!");
            qobject_cast<qdynamiclineedit*>(ui->verticalLayout_3->itemAt(i-1)->widget())->setText("Invalid Format!");
        }
        else{
            int seconds = secondDifference(date1.toStdString(),date2.toStdString());
            qobject_cast<qdynamiclineedit*>(ui->verticalLayout_2->itemAt(i-1)->widget())->setText(QString::number(seconds));
            qobject_cast<qdynamiclineedit*>(ui->verticalLayout_3->itemAt(i-1)->widget())->setText(QString::fromStdString((dateConvert(seconds))));
        }
    }
}



void MainWindow::on_calculateButton_clicked(){
    updateTime();
}


void MainWindow::on_lineEdit_returnPressed()
{
    std::string thing = ui->lineEdit->text().toStdString();
    mask = std::locale(std::locale::classic(),new bt::time_input_facet(thing));
}

void MainWindow::on_resetMask_clicked()
{
    ui->lineEdit->setText("%m/%d/%Y %H:%M:%S");
    on_lineEdit_returnPressed();
}

void MainWindow::on_apply_clicked()
{
    on_lineEdit_returnPressed();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(
        this,
        tr("About"),
        tr("A tool to quickly compare the difference in time between two dates\n\nWritten in C++ and uses QT for the gui\n\nMade by Alex Webster") );
}

void MainWindow::on_actionHelp_triggered()
{
    QMessageBox::information(
        this,
        tr("How to use"),
        tr("Paste a timestamp in the provided boxes to find the time difference from the timestamp above it\n\n"
           "Pressing enter will create a new timestamp box and will automatically press the calculate button\n\n"
           "If a timestamp does not follow the provided format the option to change it can be applied by using the format box"
           "\n\nFormatting Paramters\nYear: %Y\nMonth: %m\nDay: %d\nHour: %H\nMinute: %M\nSecond: %S") );
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
