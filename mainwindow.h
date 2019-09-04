#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <qdynamiclineedit.h>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool valid(QString date);
    int secondDifference(std::string date1, std::string date2);
    std::string dateConvert(int seconds);
    std::locale mask;
    bool check(std::string date);
    bool dateParser(std::string date,int* year, int* month, int* day, int* hour, int* minute, int* seconds);

private slots:
    void on_calculateButton_clicked();
    void on_resetButton_clicked();
    void generateNewLine();
    void updateTime();

    void on_lineEdit_returnPressed();
    void on_resetMask_clicked();
    void on_apply_clicked();
    void on_actionAbout_triggered();
    void on_actionHelp_triggered();
    void on_actionExit_triggered();
};
#endif // MAINWINDOW_H
