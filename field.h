#ifndef FIELD_H
#define FIELD_H
#include <QString>

class Field
{
public:
    Field(){}
    Field(QString name):name(name),type(0){}
    Field(QString name, int type):name(name),type(type){}

    int type;
    QString name;
    int size;
    static const int Type_STRING = 0;
    static const int Type_INT = 1;
    static const int Type_BOOL = 2;
    static const int Type_DATE = 3;
};

#endif // FIELD_H
