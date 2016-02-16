#include "dataobject.h"
#include "field.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>


/*
    DataObject(QList fields);
    DataObject(QList fields, QString folder);
    bool create();
 */
DataObject::DataObject()
{

}
DataObject::DataObject(QString name):name(name)
{

}

DataObject::DataObject(QList<Field*> fields, QString folder):fields(fields),folder(folder)
{

}

DataObject::DataObject(QList<Field*> fields):fields(fields)
{

}
bool DataObject::create()
{
    QString text = createHeader();
    bool res = saveFile(folder+"/"+name.toLower()+".h",text);
    text = createClass();
    res = saveFile(folder+"/"+name.toLower()+".cpp",text);
    qDebug(res ? " Success!!":" Failed!! ");
    return true;
}

bool DataObject::saveFile( QString filename, QString text )
{
  QFile file( filename );
  if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
  {
    qDebug( "Failed to save file." );
    return false;
  }

  QTextStream stream( &file );
  stream << text;

  //filename = filename;
  //docWidget->document()->setModified( false );
  //setWindowTitle( tr("%1[*] - %2" ).arg(filename).arg(tr("SDI")) );

  return true;
}

//Init
QString DataObject::classInit()
{
     QString code = "";
     code +=  "bool "+name+"::init()";
     QString sql = "CREATE TABLE IF NOT EXISTS "+name.toLower()+" (_id INTEGER PRIMARY KEY";
     foreach (Field *field, fields) {
         QString type = "text";
         switch (field->type)
         {
         case (1):
        type = "int";
         break;
         case (2):
        type = "bool";
         break;
         case (3):
        type = "date";
         break;
         }
          sql += " ,"+field->name+" "+type;
     }
     sql +=" )";
     code +=
R"*(
{
     QSqlQuery qry;
     bool res = true;
     qry.prepare()*"+QString("\"")+sql+"\""+R"*( );
     if( !qry.exec() )
       {
         qFatal( "Failed to create table" );
         res = false;
     }
     else
     {
           qDebug( "Table created!" );
     }
     return res;
 }
             )*";
    return code;
}//!Init


//Update
QString DataObject::classUpdate()
{
     QString code = "";
      code += "\nbool "+name+"::update(int _id, QString field, QString value)";
     /*
       qry.prepare()*"+"\"UPDATE "+name.toLower()+" SET \"+field+\" = '\"+value+\"' WHERE _id =\"+_id+\"\""+R"*( );
      */
     code +=
 R"*(
{
  bool res = true;
  QSqlQuery qry;
 qry.prepare()*"+QString("\"UPDATE ")+name.toLower()+" SET \"+field+\" = '\"+value+\"' WHERE _id =\"+QString::number(_id)"+R"*( );
  if( !qry.exec() )
    {
      qDebug() << qry.lastError();
      res = false;
     }
     else
     {
       emit rowUpdated(_id);
       emit dataChanged();
     }
 // else
   // qDebug( "Updated!" );
  return res;
}
      )*"+"\n";
    return code;
}//!Update

//Delete
QString DataObject::classDelete()
{
     QString code = "";
      code +=  "bool "+name+"::deleteById(int _id)";
      code +=
   R"*(
   {
      bool res = true;
      QSqlQuery qry;
      qry.prepare( )*";
    code += "\"DELETE FROM "+name.toLower()+" WHERE _id =\"+QString::number(_id)"+ R"*( );
      if( !qry.exec() )
        {
          qDebug() << qry.lastError();
          res = false;
         }
        else
          {
            emit rowRemoved(_id);
            emit dataChanged();
          }
      return res;
   }
      )*"+"\n";

    return code;
}//!Delete

//Get
QString DataObject::classGet()
{
     QString code = "\n";
      code +=  name+" &"+name+"::get(int _id)";
      code +=
   R"*(
{
      this->_valid = false;
      QSqlQuery qry;
      )*";
     // code += name+" "+name.toLower()+";";
      code +=
   R"*(
      qry.prepare( )*";
    code += "\"SELECT * FROM "+name.toLower()+" WHERE _id =\"+QString::number(_id)"+ R"*( );
      if( !qry.exec() )
        {
          qDebug() << qry.lastError();
        }
        else
        {
   )*";
              //code += "           "+name +" *"+name.toLower()+" = new "+name +"();\n";
              code += "           if(qry.next())\n";
              code += "           {\n";
              code += "              this->_valid = true;\n";
              foreach(Field *f , fields)
              {
               //     code += "               "+name.toLower()+"."+f->name+" = qry.value(COL_"+f->name+").toString();\n";
                  code += "              this->"+f->name+" = qry.value(COL_"+f->name+").toString();\n";

              }
              code += "           }\n";
              //code += "            return "+name.toLower()+";";
              //code += "            return this;";
              code +=
  R"*(
          })*";
      //return 0;
        //code += "\n           return "+name.toLower()+";";
        code += "\n           return *this;";
         code +=
 R"*(
}
      )*";

    return code;
}//!Get

//Add
QString DataObject::classAdd()
{
     QString code = "";
      code +=  "\nint "+name+"::add("+name+" "+name.toLower()+")";

     QString names = "";
     QString values = "";
     QString binding = "";
     QString sql = "";
     int i=0;
     foreach (Field *f, fields) {
         if(i!=0)
         {
             names += " ,";
             values += " ,";
             binding += "\n";
         }
         i++;
         names += f->name;
         values += ":"+f->name;
         binding += QString("   qry.bindValue(")+"\":"+f->name+"\","+name.toLower()+"."+f->name+");";
     }
      sql =  QString("\"INSERT INTO ")+name.toLower()+" ("+names+") VALUES ("+values+")\"";
              code +=
R"*(
{
  bool res = -1;
  QSqlQuery qry;
  qry.prepare( )*"+sql+" );\n"+binding+R"*(
  if( !qry.exec() )
    {
      qDebug() << qry.lastError();
      res = -1;
     }
    else
    {
        emit rowAdded(_id);
        emit dataChanged();
    }
  return res;
}
  )*";

    return code;
}//!Add

//Save
QString DataObject::classSave()
{
     QString code = "";
     //save
      code +=  "\nint "+name+"::save()";

     QString names = "";
     QString values = "";
     QString binding = "";
     QString sql = "";
     int i=0;
     foreach (Field *f, fields) {
         if(i!=0)
         {
             names += " ,";
             values += " ,";
             binding += "\n";
         }
         i++;
         names += f->name;
         values += ":"+f->name;
         binding += QString("   qry.bindValue(")+"\":"+f->name+"\","+f->name+");";
     }
      sql =  QString("\"INSERT INTO ")+name.toLower()+" ("+names+") VALUES ("+values+")\"";
              code +=
R"*(
{
  bool res = -1;
  QSqlQuery qry;
  qry.prepare( )*"+sql+" );\n"+binding+R"*(
  if( !qry.exec() )
    {
      qDebug() << qry.lastError();
      res = -1;
     }
    else
    {
        emit rowAdded(_id);
        emit dataChanged();
    }
  return res;
}
  )*";

    return code;
}//!Save

//GetAll
QString DataObject::classGetAll()
{
     QString code = "";

     //Get All

     code += "\nQList<Model*>* "+ name+"::getAll()";
     code +=
     R"*(
     {
         QList<Model*>* list = new QList<Model*>();
         QSqlQuery qry;
         qry.prepare( )*";
         code += "\"SELECT * FROM "+name.toLower()+" \"";
         code += R"*( );
         if( !qry.exec() )
         {
             qDebug() << qry.lastError();
             //list = null;
         }
         else
         {
         //QSqlRecord rec = qry.record();
         //int cols = rec.count();
         for( int r=0; qry.next(); r++ )
         {
     )*";
             code += "     "+name +" *"+name.toLower()+" = new "+name +"();\n";
             foreach(Field *f , fields)
             {
                 code += "     "+name.toLower()+"->"+f->name+" = qry.value(COL_"+f->name+").toString();\n";
             }
              code += "     *list<<"+name.toLower()+";";
     code += R"*(
         }
         }
         return list;
     }
     )*";

         /*
         SELECT title FROM tracks
          WHERE singer='Madonna'
            AND title<:firsttitle
          ORDER BY title DESC
          LIMIT 5;

     */
    return code;
}//!GetAll

//ScrollUp
QString DataObject::classScrollUp()
{
     QString code = "";
     //scrollUp

     code += "\nQList<"+name+"*>* "+ name+"::scrollUp(int firstItem, int limit)";
     code +=
     R"*(
 {
     QList<)*"+name+ R"*(*>* list = new QList<)*"+name+ R"*(*>();
     QSqlQuery qry;
     qry.prepare( )*"+"\"SELECT * FROM "+name.toLower()+" WHERE _id<\"+QString::number(firstItem)+\" ORDER BY _id ASC  LIMIT \"+QString::number(limit)+\"\""+R"*( );
     if( !qry.exec() )
     {
         qDebug() << qry.lastError();
         //list = null;
     }
     else
     {
     //QSqlRecord rec = qry.record();
     //int cols = rec.count();
     for( int r=0; qry.next(); r++ )
     {
 )*";
             code += "     "+name +" *"+name.toLower()+" = new "+name +"();\n";
             foreach(Field *f , fields)
             {
                 code += "     "+name.toLower()+"->"+f->name+" = qry.value(COL_"+f->name+").toString();\n";
             }
              code += "     *list<<"+name.toLower()+";";
     code += R"*(
     }
     }
     return list;
 }
     )*";

    return code;
}//!ScrollUp

//scrollDown
QString DataObject::classScrollDown()
{
     QString code = "";
     //scrollDown
     code += "\nQList<"+name+"*>* "+ name+"::scrollDown(int lastItem, int limit)";
     code +=
     R"*(
{
 QList<)*"+name+ R"*(*>* list = new QList<)*"+name+ R"*(*>();
 QSqlQuery qry;
 qry.prepare( )*"+"\"SELECT * FROM "+name.toLower()+" WHERE _id>\"+QString::number(lastItem)+\" ORDER BY _id ASC  LIMIT \"+QString::number(limit)+\"\""+R"*( );
 if( !qry.exec() )
 {
     qDebug() << qry.lastError();
     //list = null;
 }
 else
 {
 //QSqlRecord rec = qry.record();
 //int cols = rec.count();
 for( int r=0; qry.next(); r++ )
 {
)*";
             code += "     "+name +" *"+name.toLower()+" = new "+name +"();\n";
             foreach(Field *f , fields)
             {
                 code += "     "+name.toLower()+"->"+f->name+" = qry.value(COL_"+f->name+").toString();\n";
             }
              code += "     *list<<"+name.toLower()+";";
     code += R"*(
 }
 }
 return list;
})*";
    return code;
}//!scrollDown

//Signals
QString DataObject::classSignals()
{
     QString code = "";
     //SIGNALS
     //dataChanged
     code += "\nvoid "+name+"::"+"dataChanged()\n{\n\n}\n";
     //rowAdded
     code +=  "\nvoid "+name+"::"+"rowAdded(int _id)\n{\n\n}";
     //rowRemoved
     code +=  "\nvoid "+name+"::"+"rowRemoved(int _id)\n{\n\n}";
     //rowUpdated
     code +=  "\nvoid "+name+"::"+"rowUpdated(int _id)\n{\n\n}";
    return code;
}//!Signals

//destructor
QString DataObject::classDestructor()
{
     QString code = "";
     //destructor
     code += "\n"+name+"::"+"~"+ name+"()\n{\n\n}\n\n";
    return code;
}//!destructor

 //Constructor
QString DataObject::classConstructor()
{
     QString code = "";
     //Constructor
      code +=  name+"::"+name+"(QObject *parent ) : Model(\""+name.toLower()+"\", parent )\n";
      code += "{\n\n}\n";
    return code;
}//!Constructor

QString DataObject::classCopyConstructor()
{
    QString code = "";
    //)*"+name+"("+name+" &"+name.toLower()+")"+ R"*(;
     code +=  name+"::"+name+"("+name+" &"+name.toLower()+") : Model(\""+name.toLower()+"\", 0 )\n";
     code += "{\n";
     code += "    _id = "+name.toLower()+"._id;\n";
     foreach (Field *field, fields)
     {
         code += "    "+field->name+" = "+name.toLower()+"."+ field->name+";\n";
     }
     code += "\n}\n";
   return code;
}
//Init
//QString DataObject::classInit()
//{
//    QString code = "";

//   return code;
//}//!Init
QString DataObject::createClass()
{
    QString code =  "#include \""+name.toLower()+".h\"\n#include <QtSql>\n\n";
    code += classConstructor();
    code += classCopyConstructor();
    code += classDestructor();
    code += classInit();
    code += classGet();
    code += classGetAll();
    code += classAdd();
   // code += classUpdate();
   // code += classDelete();
    code += classSave();
    code += classScrollUp();
    code += classScrollDown();
    //code += classSignals();
return code;
}
QString DataObject::classToString()
{
    return "virtual QString toString() Q_DECL_OVERRIDE{return name;}";
}

QString DataObject::createHeader()
{
//bool res = true;
QString code = R"*(
#ifndef )*"+name.toUpper()+"_H"+ R"*(
#define )*"+name.toUpper()+"_H"+ R"*(

#include "model.h"

QT_BEGIN_NAMESPACE

class QString;

QT_END_NAMESPACE

class )*"+name+ R"*( : public Model
{
 //   Q_OBJECT
public:
    )*"+name+ R"*((QObject *parent = 0);
    )*"+name+"("+name+" &"+name.toLower()+")"+ R"*(;
    bool init();
    int add( )*"+name+" "+name.toLower()+R"*( );
    int save();
    //bool update(int _id, QString field, QString value);
    //bool deleteById(int _id);
    virtual )*"+name+ R"*( &get(int _id) Q_DECL_OVERRIDE;
    virtual QList<)*"+"Model"+ R"*(*>* getAll() Q_DECL_OVERRIDE;
    QList<)*"+name+ R"*(*>* scrollUp(int firstItem, int limit);
    QList<)*"+name+ R"*(*>* scrollDown(int lastItem, int limit);
    ~)*"+name+ R"*(();
    /*NB: change to appropriate var <name>*/
    virtual QString toString() Q_DECL_OVERRIDE {return name;}
    )*";
            //code += "\n    int _id;";
            foreach(Field *field , fields)
                {
                    QString type = "QString";
                    switch (field->type)
                    {
                    case (1):
                   type = "int";
                    break;
                    case (2):
                   type = "bool";
                    break;
                    case (3):
                   type = "date";
                    break;

}
                    code += "\n    "+type+" "+field->name+";";
                }
            code += R"*(

public:
    //static const int COL__id = 0;
)*";
        int i = 0;
        foreach(Field *field , fields)
            {
            i++;
                code += "    static const int COL_"+field->name+" = "+QString::number(i)+";\n";

            }
        code += R"*(
//signals:
//    void dataChanged();
//    void rowAdded(int _id);
//    void rowRemoved(int _id);
//    void rowUpdated(int _id);
};

#endif //

)*";


return code;
}

