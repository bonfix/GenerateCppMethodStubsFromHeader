
#ifndef TABLEMETA_H
#define TABLEMETA_H
#include <QString>
#include "model.h"

class TableMeta : public Model
{
 //   Q_OBJECT
public:
    TableMeta(QObject *parent = 0);
    bool init();
    int add( TableMeta tablemeta );
    int save();
    //bool update(int _id, QString field, QString value);
    //bool deleteById(int _id);
    virtual TableMeta &get(int _id) Q_DECL_OVERRIDE;
    virtual QList<Model*>* getAll() Q_DECL_OVERRIDE;
    QList<TableMeta*>* scrollUp(int firstItem, int limit);
    QList<TableMeta*>* scrollDown(int lastItem, int limit);
    ~TableMeta();
    /*NB: change to appropriate var <name>*/
    virtual QString toString() Q_DECL_OVERRIDE {return name;}
    
    QString project_id;
    QString name;

public:
    //static const int COL__id = 0;
    static const int COL_project_id = 1;
    static const int COL_name = 2;

//signals:
//    void dataChanged();
//    void rowAdded(int _id);
//    void rowRemoved(int _id);
//    void rowUpdated(int _id);
};

#endif //

