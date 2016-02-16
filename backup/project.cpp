#include "project.h"

Project::Project()
{

}
bool Project::init()
{
     QSqlQuery qry;
     bool res = true;
     qry.prepare("CREATE TABLE IF NOT EXISTS project (id INTEGER PRIMARY KEY ,name text ,folder text ,web_name text ,web_url text ,db_name text ,db_type text ,db_user text ,db_password text ,db_host text )" );
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

bool Project::update(QString id, QString field, QString value)
{
  bool res = true;
  QSqlQuery qry;
 qry.prepare("UPDATE project SET "+field+" = '"+value+"' WHERE id ="+id );
  if( !qry.exec() )
    {
      qDebug() << qry.lastError();
      res = false;
  }
 // else
   // qDebug( "Updated!" );
  return res;
}

bool Project::deleteById(int id)
{
   bool res = true;
   QSqlQuery qry;
   qry.prepare( "DELETE FROM project WHERE id ="+QString::number(id) );
   if( !qry.exec() )
     {
       qDebug() << qry.lastError();
       res = false;
   }
  // else
    // qDebug( "Deleted!" );
   return res;
}

int Project::add(Project project)
{
   bool res = -1;
   QSqlQuery qry;
   qry.prepare( "INSERT INTO project (name ,folder ,web_name ,web_url ,db_name ,db_type ,db_user ,db_password ,db_host) VALUES (:name ,:folder ,:web_name ,:web_url ,:db_name ,:db_type ,:db_user ,:db_password ,:db_host)" );
   qry.bindValue(":name",project.name);
   qry.bindValue(":folder",project.folder);
   qry.bindValue(":web_name",project.web_name);
   qry.bindValue(":web_url",project.web_url);
   qry.bindValue(":db_name",project.db_name);
   qry.bindValue(":db_type",project.db_type);
   qry.bindValue(":db_user",project.db_user);
   qry.bindValue(":db_password",project.db_password);
   qry.bindValue(":db_host",project.db_host);
   if( !qry.exec() )
     {
       qDebug() << qry.lastError();
       res = -1;
   }
  // else
    // qDebug( "Added!" );
   return res;
}

QList<Project> Project::getAll()
{
    QList<Project> list;
    QSqlQuery qry;
    qry.prepare( "SELECT * FROM project " );
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
     Project project();
     project.name = qry.value(COL_name).toString();
     project.folder = qry.value(COL_folder).toString();
     project.web_name = qry.value(COL_web_name).toString();
     project.web_url = qry.value(COL_web_url).toString();
     project.db_name = qry.value(COL_db_name).toString();
     project.db_type = qry.value(COL_db_type).toString();
     project.db_user = qry.value(COL_db_user).toString();
     project.db_password = qry.value(COL_db_password).toString();
     project.db_host = qry.value(COL_db_host).toString();
     list<<project;
    }
    }
    return list;
}

QList<Project> Project::scrollUp(int firstItem, int limit)
{
    QList<Project> list;
    QSqlQuery qry;
    qry.prepare( "SELECT * FROM project WHERE id<"+QString::number(firstItem)+" ORDER BY id ASC  LIMIT "+QString::number(limit)+"" );
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
     Project project();
     project.name = qry.value(COL_name).toString();
     project.folder = qry.value(COL_folder).toString();
     project.web_name = qry.value(COL_web_name).toString();
     project.web_url = qry.value(COL_web_url).toString();
     project.db_name = qry.value(COL_db_name).toString();
     project.db_type = qry.value(COL_db_type).toString();
     project.db_user = qry.value(COL_db_user).toString();
     project.db_password = qry.value(COL_db_password).toString();
     project.db_host = qry.value(COL_db_host).toString();
     list<<project;
    }
    }
    return list;
}

QList<Project> Project::scrollDown(int lastItem, int limit)
{
    QList<Project> list;
    QSqlQuery qry;
    qry.prepare( "SELECT * FROM project WHERE id>"+QString::number(lastItem)+" ORDER BY id ASC  LIMIT "+QString::number(limit)+"" );
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
     Project project = new Project();
     project.name = qry.value(COL_name).toString();
     project.folder = qry.value(COL_folder).toString();
     project.web_name = qry.value(COL_web_name).toString();
     project.web_url = qry.value(COL_web_url).toString();
     project.db_name = qry.value(COL_db_name).toString();
     project.db_type = qry.value(COL_db_type).toString();
     project.db_user = qry.value(COL_db_user).toString();
     project.db_password = qry.value(COL_db_password).toString();
     project.db_host = qry.value(COL_db_host).toString();
     list<<project;
    }
    }
    return list;
}

Project::~Project()
{

}
