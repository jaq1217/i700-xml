#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItem>
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    xxml = new XmlClass;
    QStandardItemModel* model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Tag")<<QStringLiteral("Index")<<QStringLiteral("SubIndex")<<QStringLiteral("Data")<<QStringLiteral("Comment")<<QStringLiteral("Lenth"));
    ui->treeView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete xxml;
}

void MainWindow::on_pushButton_clicked()
{
    QString QStr = "";
    if(xxml->read_xmll("single-jq.xml"))
    {
        QStandardItemModel* model = new QStandardItemModel(ui->treeView);
        model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Tag")<<QStringLiteral("Index")<<QStringLiteral("SubIndex")<<QStringLiteral("Data")<<QStringLiteral("Comment")<<QStringLiteral("Lenth"));
        ui->treeView->setModel(model);


        QStandardItem* itemProject = new QStandardItem(QStringLiteral("InitCmds"));
        model->appendRow(itemProject);
        for(int tempi = 0; tempi < xxml->XmlDataNum; tempi++)
        {
            QStandardItem* itemChild = new QStandardItem(QStringLiteral(" "));
            itemProject->appendRow(itemChild);

            itemProject->setChild(tempi,1,new QStandardItem(QString::number(xxml->xmlData[tempi].Index,10)));
            itemProject->setChild(tempi,2,new QStandardItem(QString::number(xxml->xmlData[tempi].SubIndex,10)));

            if(xxml->xmlData[tempi].IsChar)
            {
                QStr = "";

                //qDebug()<< xxml->xmlData[tempi].DataLenth;
                for(uint8_t intj = 0; intj < xxml->xmlData[tempi].DataLenth;intj++)
                {
                    QStr+=xxml->xmlData[tempi].DataStr[intj];
                    //QStr+=QString::number(xxml->xmlData[tempi].DataStr[intj],16);
                    //qDebug()<<QString::number(xxml->xmlData[tempi].DataStr[intj],16);
                }
                itemProject->setChild(tempi,3,new QStandardItem(QStr));
                //qDebug()<<QStr;
            }
            else
            {
                if(xxml->xmlData[tempi].Index == 24677)
                {
                    qDebug()<<"first"<<xxml->xmlData[tempi].DataInt;
                }
                //itemProject->setChild(tempi,3,new QStandardItem(QString::number(xxml->xmlData[tempi].DataInt,16)));
                itemProject->setChild(tempi,3,new QStandardItem(QString("%1").arg(xxml->xmlData[tempi].DataInt,xxml->xmlData[tempi].DataLenth * 2,16,QChar('0'))));
            }
            itemProject->setChild(tempi,4,new QStandardItem(xxml->xmlData[tempi].Comment));
            itemProject->setChild(tempi,5,new QStandardItem(QString::number(xxml->xmlData[tempi].DataLenth,10)));
        }
    }
}
