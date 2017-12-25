#ifndef XML_H
#define XML_H
#include <QString>


class XmlClass
{
public:
    XmlClass();
    ~XmlClass();

    int read_xmll(QString filename);
    int write_xmll(QString filename);

    typedef struct {
       QString       Trans;
       QString       Comment;
       uint8_t       Timeout;
       uint8_t       Ccs;
       uint16_t      Index;
       uint8_t      SubIndex;
        union
        {
            uint32_t      DataInt;
            uint8_t       DataStr[100];
        };
        bool         IsChar;
       uint8_t       DataLenth;
    }XmlDataStruct;
    XmlDataStruct xmlData[300];//120
    int16_t XmlDataNum;
};

#endif // XML_H
