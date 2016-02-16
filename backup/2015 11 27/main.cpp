#include "dataobject.h"
#include "mainwindow.h"
#include "field.h"
#include "sourcegenerator.h"
#include <QApplication>
#include <QDebug>
#include <QString>
#include <string>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MainWindow w;
    //w.show();
    //    QString folder = "F:/Tutorials Centre/A CURRENT/C++/Qt/test";

    QString folder = "/mnt/B87E32217E31D938/program files/QT/projects/WebRAD";
    QList<Field*> fields;
    /*
    for(int i= 0; i<5; i++)
    {
        Field f1("name"+QString::number(i));
         fields<<f1;
    }
    for(int i= 0; i<5; i++)
    {
         qDebug("Name: "+fields[i].name.toLatin1());
    }
    //qDebug("size ");
    qDebug("size "+QString::number(fields.size()).toLatin1());
    return 0;
    */
//    model->setHeaderData(0,Qt::Horizontal,"Name");
//    model->setHeaderData(1,Qt::Horizontal,"Type");
//    model->setHeaderData(2,Qt::Horizontal,"Size");
//    model->setHeaderData(3,Qt::Horizontal,"Allow Null");
//    model->setHeaderData(4,Qt::Horizontal,"Is Pk");
//    model->setHeaderData(5,Qt::Horizontal,"Input Type");
//    model->setHeaderData(6,Qt::Horizontal,"Data Source");

    //TableMeta
//    Field *f0 = new Field("project_id");
//    Field *f1 = new Field("name");

    //ColMeta
    Field *f0 = new Field("table_id");
    Field *f1 = new Field("name");
    Field *f2 = new Field("_type");
    Field *f3 = new Field("_size");
    Field *f4 = new Field("allow_null");
    Field *f5 = new Field("is_pk");
    Field *f6 = new Field("input_type");
    Field *f7 = new Field("data_source");
    //Field *f8 = new Field("allow_null");
//    Field *f3 = new Field("web_name");
//    Field *f4 = new Field("web_url");
//    Field *f5 = new Field("db_name");
//     Field *f6 = new Field("db_type");
//      Field *f7 = new Field("db_user");
//      Field *f8 = new Field("db_password");
//    Field *f9 = new Field("db_host");
    //fields.append(f1);
    fields<<f0<<f1<<f2<<f3<<f4<<f5<<f6<<f7;//<<f8<<f9;
    DataObject student("ColMeta");
    student.folder = folder;
    student.fields = fields;
    student.create();

//    QFile *source = new QFile("C:/Users/Fixer/QT/projects/WebRAD/mainwindow.h");
//    QFile *dest = new QFile("C:/Users/Fixer/QT/projects/WebRAD/mainwindow.txt");
//    SourceGenerator sg(source,dest);
//    sg.generate();
    return a.exec();
}

/*
PROJECT
    Field *f1 = new Field("name");
    Field *f2 = new Field("folder");
    Field *f3 = new Field("web_name");
    Field *f4 = new Field("web_url");
    Field *f5 = new Field("db_name");
     Field *f6 = new Field("db_type");
      Field *f7 = new Field("db_user");
      Field *f8 = new Field("db_password");
    Field *f9 = new Field("db_host");
    //fields.append(f1);
    fields<<f1<<f2<<f3<<f4<<f5<<f6<<f7<<f8<<f9;
    DataObject student("Project");
    student.folder = folder;
    student.fields = fields;
    student.create();
*/
