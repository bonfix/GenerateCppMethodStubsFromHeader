#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QString>
#include <QList>
#include "field.h"
class DataObject
{
public:
    DataObject();
    DataObject(QList<Field*> fields);
    DataObject(QString name);
    DataObject(QList<Field*> fields, QString folder);
    bool create();
    QString createHeader();
    QString createClass();

    QString classConstructor();
    QString classDestructor();
    QString classCopyConstructor();
    QString classInit();
    QString classGet();
    QString classGetAll();
    QString classAdd();
    QString classUpdate();
    QString classDelete();
    QString classSave();
    QString classScrollUp();
    QString classScrollDown();
    QString classSignals();
    QString classToString();

    bool saveFile( QString filename, QString text );

    QList<Field*> fields;
    QString folder;
    QString name;
};

#endif // DATAOBJECT_H
