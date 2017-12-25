#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //file is open flag
    fileIsOpen=false;
    //init xxml
    xxml = new XmlClass;
    //set model
    model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Tag")<<QStringLiteral("Index")<<QStringLiteral("SubIndex")<<QStringLiteral("Data")<<QStringLiteral("Comment")<<QStringLiteral("Lenth"));
    ui->treeView->setModel(model);

    QObject::connect(model, SIGNAL(itemChanged(QStandardItem *)), this, SLOT(dataItemChanged(QStandardItem *)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete []standardItemData;
    delete xxml;
}

void MainWindow::on_pushButton_clicked()
{
    QString QStr = "";
    if(fileIsOpen)
    {
//        model->takeItem(1,0);
//        model->takeItem(0,0);
//        model->takeItem(0,1);
//        model->takeItem(0,2);
//        model->takeItem(0,3);
//        model->takeItem(0,4);
//        model->takeItem(0,5);

//       int row = model->rowCount();
//        qDebug()<<row;
//        row=itemProject->rowCount();
//        qDebug()<<row;
//        for (int i=row-1; i>=0; i--)
//        {
//           itemProject->c;
//        }
//      itemProject->textAlignment();
//      m_itemmodel->removeRow(0, m_itemmodel->rowCount());
//      model->takeItem(0,0);
//      fileIsOpen=false;
//      delete itemProject;
//      delete []standardItemData;
    }
    if(xxml->read_xmll("single-jq.xml")&&!fileIsOpen)
    {
//      qDebug()<<"124";
//      qDebug()<<QString("%1").arg("12345");
//      QStandardItemModel* model = new QStandardItemModel(ui->treeView);
//      model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Tag")<<QStringLiteral("Index")<<QStringLiteral("SubIndex")<<QStringLiteral("Data")<<QStringLiteral("Comment")<<QStringLiteral("Lenth"));
//      ui->treeView->setModel(model);


//      QStandardItem* itemProject = new QStandardItem(QStringLiteral("InitCmds"));
        itemProject = new QStandardItem(QStringLiteral("InitCmds"));
        model->appendRow(itemProject);
        standardItemData = new QStandardItem[xxml->XmlDataNum*6];
        for(int tempi = 0; tempi < xxml->XmlDataNum; tempi++)
        {
//          QStandardItem* itemChild = new QStandardItem(QStringLiteral(" "));
//          itemProject->appendRow(itemChild);
            standardItemData[tempi*6+0].setText(QStringLiteral(" "));
            itemProject->appendRow(&standardItemData[tempi*6+0]);

//          itemProject->setChild(tempi,1,new QStandardItem(QString::number(xxml->xmlData[tempi].Index,10)));
//          itemProject->setChild(tempi,2,new QStandardItem(QString::number(xxml->xmlData[tempi].SubIndex,10)));
            standardItemData[tempi*6+1].setText(QString::number(xxml->xmlData[tempi].Index,10));
//            qDebug()<< xxml->xmlData[tempi].Index;
            itemProject->setChild(tempi,1,&standardItemData[tempi*6+1]);
            standardItemData[tempi*6+2].setText(QString::number(xxml->xmlData[tempi].SubIndex,10));
            itemProject->setChild(tempi,2,&standardItemData[tempi*6+2]);

            if(xxml->xmlData[tempi].IsChar)
            {
                QStr = "";
                //qDebug()<< xxml->xmlData[tempi].DataLenth;
                for(uint8_t intj = 0; intj < xxml->xmlData[tempi].DataLenth;intj++)
                {
                    QStr+=xxml->xmlData[tempi].DataStr[intj];
                    //qDebug()<<xxml->xmlData[tempi].DataStr[intj];
                    //QStr+=QString::number(xxml->xmlData[tempi].DataStr[intj],16);
                    //qDebug()<<QString::number(xxml->xmlData[tempi].DataStr[intj],16);
                }
                //qDebug()<<xxml->xmlData[tempi].DataLenth<<QStr;
//              //itemProject->setChild(tempi,3,new QStandardItem(QStr));
                standardItemData[tempi*6+3].setText(QStr);
                itemProject->setChild(tempi,3,&standardItemData[tempi*6+3]);
                //qDebug()<<QStr;
            }
            else
            {
                if(xxml->xmlData[tempi].Index == 24677)
                {
                    //qDebug()<<"first"<<xxml->xmlData[tempi].DataInt;
                }
                //itemProject->setChild(tempi,3,new QStandardItem(QString::number(xxml->xmlData[tempi].DataInt,16)));
                //itemProject->setChild(tempi,3,new QStandardItem(QString("%1").arg(xxml->xmlData[tempi].DataInt,xxml->xmlData[tempi].DataLenth * 2,16,QChar('0'))));
                standardItemData[tempi*6+3].setText(QString("%1").arg(xxml->xmlData[tempi].DataInt,xxml->xmlData[tempi].DataLenth * 2,16,QChar('0')));
                //qDebug()<<QString("%1").arg(xxml->xmlData[tempi].DataInt,0,16,QChar('0'));
                //qDebug()<<QString("%1").arg(xxml->xmlData[tempi].DataInt,0,16,QChar('0'))<<" "<<xxml->xmlData[tempi].DataInt<<"  "<<xxml->xmlData[tempi].DataLenth;
                itemProject->setChild(tempi,3,&standardItemData[tempi*6+3]);
            }
            //itemProject->setChild(tempi,4,new QStandardItem(xxml->xmlData[tempi].Comment));
            //itemProject->setChild(tempi,5,new QStandardItem(QString::number(xxml->xmlData[tempi].DataLenth,10)));
            standardItemData[tempi*6+4].setText(xxml->xmlData[tempi].Comment);
            itemProject->setChild(tempi,4,&standardItemData[tempi*6+4]);
            standardItemData[tempi*6+5].setText(QString::number(xxml->xmlData[tempi].DataLenth,10));
            itemProject->setChild(tempi,5,&standardItemData[tempi*6+5]);
        }
        fileIsOpen=true;
    }
}


 void MainWindow::dataItemChanged(QStandardItem *item)
 {
    int row;
    int column;
    if(fileIsOpen)
    {
       row=item->row();
       column=item->column();
       qDebug()<<row<<" "<<column;
       switch(column)
       {
            case 1:
                  {
                     xxml->xmlData[row].Index=standardItemData[row*6+column].text().toInt();
//                     qDebug()<<standardItemData[row*6+column].text().toInt();
                     break;
                  }
            case 2:
                   {
                      xxml->xmlData[row].SubIndex=standardItemData[row*6+column].text().toInt();
//                      qDebug()<<standardItemData[row*6+column].text().toInt();
                      break;
                   }
            case 3:
                   {
                      if(!xxml->xmlData[row].IsChar)
                      {
                          unsigned int tempInt=(unsigned int)standardItemData[row*6+column].text().toInt(NULL,16);
                          xxml->xmlData[row].DataInt=tempInt;
                      }
                      break;
                   }
            case 4:
                   {
                      xxml->xmlData[row].Comment=standardItemData[row*6+column].text();
//                    qDebug()<<standardItemData[row*6+column].text();
                      break;
                   }
            case 5:
                   {
//                      xxml->xmlData[row].DataLenth=standardItemData[row*6+column].text().toInt();
//                      qDebug()<<standardItemData[row*6+column].text().toInt();
                      break;
                   }
            default:break;
       }
    }
 }



void MainWindow::on_writeButton_clicked()
{
    if(fileIsOpen)
    {
        xxml->write_xmll("single-jq.xml");
    }
}
