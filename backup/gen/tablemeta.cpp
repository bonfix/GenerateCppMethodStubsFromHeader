#include "tablemeta.h"
#include <QtSql>

TableMeta::TableMeta(QObject *parent ) : Model("tablemeta", parent )
{

}

TableMeta::~TableMeta()
{

}

bool TableMeta::init()
{
     QSqlQuery qry;
     bool res = true;
     qry.prepare("CREATE TABLE IF NOT EXISTS tablemeta (_id INTEGER PRIMARY KEY ,project_id text ,name text )" );
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
             
TableMeta &TableMeta::get(int _id)
{
      QSqlQuery qry;
      qry.prepare( "SELECT * FROM tablemeta WHERE _id ="+QString::number(_id) );
      if( !qry.exec() )
        {
          qDebug() << qry.lastError();
        }
        else
        {
              if(qry.next())
           {
             this->project_id = qry.value(COL_project_id).toString();
             this->name = qry.value(COL_name).toString();
           }
            return *this;
          }
      return NULL;
}
      
QList<TableMeta*>* TableMeta::getAll()
     {
         QList<TableMeta*>* list = new QList<TableMeta*>();
         QSqlQuery qry;
         qry.prepare( "SELECT * FROM tablemeta " );
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
          TableMeta *tablemeta = new TableMeta();
     tablemeta->project_id = qry.value(COL_project_id).toString();
     tablemeta->name = qry.value(COL_name).toString();
     *list<<tablemeta;
         }
         }
         return list;
     }
     
int TableMeta::add(TableMeta tablemeta)
{
  bool res = -1;
  QSqlQuery qry;
  qry.prepare( "INSERT INTO tablemeta (project_id ,name) VALUES (:project_id ,:name)" );
   qry.bindValue(":project_id",tablemeta.project_id);
   qry.bindValue(":name",tablemeta.name);
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
  
int TableMeta::save()
{
  bool res = -1;
  QSqlQuery qry;
  qry.prepare( "INSERT INTO tablemeta (project_id ,name) VALUES (:project_id ,:name)" );
   qry.bindValue(":project_id",project_id);
   qry.bindValue(":name",name);
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
  
QList<TableMeta*>* TableMeta::scrollUp(int firstItem, int limit)
 {
     QList<TableMeta*>* list = new QList<TableMeta*>();
     QSqlQuery qry;
     qry.prepare( "SELECT * FROM tablemeta WHERE _id<"+QString::number(firstItem)+" ORDER BY _id ASC  LIMIT "+QString::number(limit)+"" );
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
      TableMeta *tablemeta = new TableMeta();
     tablemeta->project_id = qry.value(COL_project_id).toString();
     tablemeta->name = qry.value(COL_name).toString();
     *list<<tablemeta;
     }
     }
     return list;
 }
     
QList<TableMeta*>* TableMeta::scrollDown(int lastItem, int limit)
{
 QList<TableMeta*>* list = new QList<TableMeta*>();
 QSqlQuery qry;
 qry.prepare( "SELECT * FROM tablemeta WHERE _id>"+QString::number(lastItem)+" ORDER BY _id ASC  LIMIT "+QString::number(limit)+"" );
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
     TableMeta *tablemeta = new TableMeta();
     tablemeta->project_id = qry.value(COL_project_id).toString();
     tablemeta->name = qry.value(COL_name).toString();
     *list<<tablemeta;
 }
 }
 return list;
}
