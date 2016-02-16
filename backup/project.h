#ifndef PROJECT_H
#define PROJECT_H
#include <QString>
#include <QtSql>

class Project
{
public:
    Project();
    bool init();
    int add( Project project );
    bool update(QString id, QString field, QString value);
    bool deleteById(int id);
    QList<Project> getAll();
    QList<Project> scrollUp(int firstItem, int limit);
    QList<Project> scrollDown(int lastItem, int limit);
    ~Project();

    QString name;
    QString folder;
    QString web_name;
    QString web_url;
    QString db_name;
    QString db_type;
    QString db_user;
    QString db_password;
    QString db_host;

private:
    const int COL_id = 0;
    const int COL_name = 1;
    const int COL_folder = 2;
    const int COL_web_name = 3;
    const int COL_web_url = 4;
    const int COL_db_name = 5;
    const int COL_db_type = 6;
    const int COL_db_user = 7;
    const int COL_db_password = 8;
    const int COL_db_host = 9;

};

#endif //
