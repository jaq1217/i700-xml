#include "XmlClass.h"
#include "qfile.h"
#include "qdebug.h"
#include <QDomDocument>
#include "qtextcodec.h"
using namespace std;
XmlClass::XmlClass()
{

    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));

    QFile *file;
    QString  filename = "single-jq.xml";
}

XmlClass::~XmlClass()
{

}

int XmlClass::read_xmll(QString filename)
{
   QString QStrTemp;
   XmlDataNum = 0;
   QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        return 0;
    }
    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument doc;
    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
        return 0;
        file.close();
    }
    file.close();
    //////////////////////////
    QDomElement root = doc.documentElement();
    if (root.tagName() != "EtherCATMailbox") {
       qDebug()<<"root.tagname != EtherCATMailbox..." ;
    }
    QDomNode CoEroot = root.firstChild();
    while (!CoEroot.isNull())
    {
        if(CoEroot.isElement())
        {
           QDomNode cmdroot = CoEroot.firstChild();
           while(!cmdroot.isNull())
           {
               if(cmdroot.isElement())
               {
                   QDomNode node = cmdroot.firstChild();
                   while(!node.isNull())
                   {
                       if(node.isElement())
                       {
                           QDomElement element = node.toElement();
                           QDomNodeList Llist = element.childNodes();

                           for(int tempi = 0;tempi < Llist.count(); tempi ++)
                           {
                               QDomNode nodechild = Llist.at(tempi);
                               if(nodechild.isElement())
                               {
                                   if(nodechild.toElement().tagName() == "Transition")
                                   {
                                       xmlData[XmlDataNum].Trans = nodechild.toElement().text();

                                   }
                                   if(nodechild.toElement().tagName() == "Comment")
                                   {
                                       xmlData[XmlDataNum].Comment = nodechild.toElement().text();
                                   }
                                   if(nodechild.toElement().tagName() == "Timeout")
                                   {
                                       QStrTemp = nodechild.toElement().text();
                                       xmlData[XmlDataNum].Timeout = QStrTemp.toInt(0,16);
                                   }
                                   if(nodechild.toElement().tagName() == "Ccs")
                                   {
                                       QStrTemp = nodechild.toElement().text();
                                       xmlData[XmlDataNum].Ccs = QStrTemp.toInt();
                                   }
                                   if(nodechild.toElement().tagName() == "Index")
                                   {
                                       QStrTemp = nodechild.toElement().text();
                                       xmlData[XmlDataNum].Index = QStrTemp.toInt(0,10);
                                   }
                                   if(nodechild.toElement().tagName() == "SubIndex")
                                   {
                                       QStrTemp = nodechild.toElement().text();
                                       xmlData[XmlDataNum].SubIndex = QStrTemp.toInt(0,10);
                                   }
                                   if(nodechild.toElement().tagName() == "Data")
                                   {
                                       int8_t DataStrLen = 0;
                                       QStrTemp = nodechild.toElement().text();
                                       if(xmlData[XmlDataNum].Index == 8193 | (xmlData[XmlDataNum].Index == 11265 & xmlData[XmlDataNum].SubIndex == 10) | xmlData[XmlDataNum].Index == 25604)
                                       {
                                           QStrTemp = nodechild.toElement().text();
                                           for(int tempi = 0;tempi < QStrTemp.length()/2;tempi ++)
                                           {
                                               xmlData[XmlDataNum].DataStr[tempi] = QStrTemp.mid(2*tempi,2).toInt(0,16);
                                               DataStrLen++;
                                               //qDebug()<<"first" <<QString::number(xmlData[XmlDataNum].DataStr[tempi],16);
                                           }
                                           xmlData[XmlDataNum].DataLenth = DataStrLen;
                                           xmlData[XmlDataNum].IsChar = true;
                                           //qDebug()<< XmlDataNum <<QStrTemp.length() << QStrTemp;
                                       }
                                       else
                                       {
                                           QStrTemp = nodechild.toElement().text();
                                           xmlData[XmlDataNum].DataInt = QStrTemp.toUInt(0,16);
                                           xmlData[XmlDataNum].IsChar = false;
                                           xmlData[XmlDataNum].DataLenth = QStrTemp.length() / 2;//bype of number
//                                           if(xmlData[XmlDataNum].Index == 24677)
//                                           {
//                                               qDebug()<<"QStrTemp"<<QStrTemp;
//                                               qDebug()<<xmlData[XmlDataNum].DataInt.;
//                                           }
                                       }
                                   }

                               }
                           }

                           XmlDataNum++;
                       }
                       node = node.nextSibling();
                   }




               }
               cmdroot = cmdroot.nextSibling();
           }

        }
        CoEroot = CoEroot.nextSibling();
    }
    return 1;
}
