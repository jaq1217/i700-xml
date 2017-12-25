#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDomDocument>
#include <QStandardItem>
#include "XmlClass.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //file is close or open
    bool fileIsOpen;
    //QStandardItem count pointer
    QStandardItem *standardItemData;
    //main dir
    QStandardItem* itemProject;
    XmlClass *xxml;
    //explicit MainWindow(QWidget *parent = 0);
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void dataItemChanged(QStandardItem *item);
    void on_writeButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel* model;
};

#endif // MAINWINDOW_H
