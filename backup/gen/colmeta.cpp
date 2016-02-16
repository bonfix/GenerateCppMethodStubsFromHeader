#include "colmeta.h"
#include <QtSql>

ColMeta::ColMeta(QObject *parent ) : Model("colmeta", parent )
{

}

ColMeta::~ColMeta()
{

}

bool ColMeta::init()
{
     QSqlQuery qry;
     bool res = true;
     qry.prepare("CREATE TABLE IF NOT EXISTS colmeta (_id INTEGER PRIMARY KEY ,table_id text ,name text ,_type text ,_size text ,allow_null text ,is_pk text ,input_type text ,data_source text )" );
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
             
ColMeta &ColMeta::get(int _id)
{
      QSqlQuery qry;
      qry.prepare( "SELECT * FROM colmeta WHERE _id ="+QString::number(_id) );
      if( !qry.exec() )
        {
          qDebug() << qry.lastError();
        }
        else
        {
              if(qry.next())
           {
             this->table_id = qry.value(COL_table_id).toString();
             this->name = qry.value(COL_name).toString();
             this->_type = qry.value(COL__type).toString();
             this->_size = qry.value(COL__size).toString();
             this->allow_null = qry.value(COL_allow_null).toString();
             this->is_pk = qry.value(COL_is_pk).toString();
             this->input_type = qry.value(COL_input_type).toString();
             this->data_source = qry.value(COL_data_source).toString();
           }
            return this;
          }
      return 0;
}
      
QList<ColMeta*>* ColMeta::getAll()
     {
         QList<ColMeta*>* list = new QList<ColMeta*>();
         QSqlQuery qry;
         qry.prepare( "SELECT * FROM colmeta " );
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
          ColMeta *colmeta = new ColMeta();
     colmeta->table_id = qry.value(COL_table_id).toString();
     colmeta->name = qry.value(COL_name).toString();
     colmeta->_type = qry.value(COL__type).toString();
     colmeta->_size = qry.value(COL__size).toString();
     colmeta->allow_null = qry.value(COL_allow_null).toString();
     colmeta->is_pk = qry.value(COL_is_pk).toString();
     colmeta->input_type = qry.value(COL_input_type).toString();
     colmeta->data_source = qry.value(COL_data_source).toString();
     *list<<colmeta;
         }
         }
         return list;
     }
     
int ColMeta::add(ColMeta colmeta)
{
  bool res = -1;
  QSqlQuery qry;
  qry.prepare( "INSERT INTO colmeta (table_id ,name ,_type ,_size ,allow_null ,is_pk ,input_type ,data_source) VALUES (:table_id ,:name ,:_type ,:_size ,:allow_null ,:is_pk ,:input_type ,:data_source)" );
   qry.bindValue(":table_id",colmeta.table_id);
   qry.bindValue(":name",colmeta.name);
   qry.bindValue(":_type",colmeta._type);
   qry.bindValue(":_size",colmeta._size);
   qry.bindValue(":allow_null",colmeta.allow_null);
   qry.bindValue(":is_pk",colmeta.is_pk);
   qry.bindValue(":input_type",colmeta.input_type);
   qry.bindValue(":data_source",colmeta.data_source);
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
  
int ColMeta::save()
{
  bool res = -1;
  QSqlQuery qry;
  qry.prepare( "INSERT INTO colmeta (table_id ,name ,_type ,_size ,allow_null ,is_pk ,input_type ,data_source) VALUES (:table_id ,:name ,:_type ,:_size ,:allow_null ,:is_pk ,:input_type ,:data_source)" );
   qry.bindValue(":table_id",table_id);
   qry.bindValue(":name",name);
   qry.bindValue(":_type",_type);
   qry.bindValue(":_size",_size);
   qry.bindValue(":allow_null",allow_null);
   qry.bindValue(":is_pk",is_pk);
   qry.bindValue(":input_type",input_type);
   qry.bindValue(":data_source",data_source);
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
  
QList<ColMeta*>* ColMeta::scrollUp(int firstItem, int limit)
 {
     QList<ColMeta*>* list = new QList<ColMeta*>();
     QSqlQuery qry;
     qry.prepare( "SELECT * FROM colmeta WHERE _id<"+QString::number(firstItem)+" ORDER BY _id ASC  LIMIT "+QString::number(limit)+"" );
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
      ColMeta *colmeta = new ColMeta();
     colmeta->table_id = qry.value(COL_table_id).toString();
     colmeta->name = qry.value(COL_name).toString();
     colmeta->_type = qry.value(COL__type).toString();
     colmeta->_size = qry.value(COL__size).toString();
     colmeta->allow_null = qry.value(COL_allow_null).toString();
     colmeta->is_pk = qry.value(COL_is_pk).toString();
     colmeta->input_type = qry.value(COL_input_type).toString();
     colmeta->data_source = qry.value(COL_data_source).toString();
     *list<<colmeta;
     }
     }
     return list;
 }
     
QList<ColMeta*>* ColMeta::scrollDown(int lastItem, int limit)
{
 QList<ColMeta*>* list = new QList<ColMeta*>();
 QSqlQuery qry;
 qry.prepare( "SELECT * FROM colmeta WHERE _id>"+QString::number(lastItem)+" ORDER BY _id ASC  LIMIT "+QString::number(limit)+"" );
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
     ColMeta *colmeta = new ColMeta();
     colmeta->table_id = qry.value(COL_table_id).toString();
     colmeta->name = qry.value(COL_name).toString();
     colmeta->_type = qry.value(COL__type).toString();
     colmeta->_size = qry.value(COL__size).toString();
     colmeta->allow_null = qry.value(COL_allow_null).toString();
     colmeta->is_pk = qry.value(COL_is_pk).toString();
     colmeta->input_type = qry.value(COL_input_type).toString();
     colmeta->data_source = qry.value(COL_data_source).toString();
     *list<<colmeta;
 }
 }
 return list;
}