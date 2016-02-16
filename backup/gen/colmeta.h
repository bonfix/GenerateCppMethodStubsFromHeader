
#ifndef COLMETA_H
#define COLMETA_H
#include <QString>
#include "model.h"

class ColMeta : public Model
{
 //   Q_OBJECT
public:
    ColMeta(QObject *parent = 0);
    bool init();
    int add( ColMeta colmeta );
    int save();
    //bool update(int _id, QString field, QString value);
    //bool deleteById(int _id);
    virtual ColMeta* get(int _id) Q_DECL_OVERRIDE;
    virtual QList<ColMeta*>* getAll() Q_DECL_OVERRIDE;
    QList<ColMeta*>* scrollUp(int firstItem, int limit);
    QList<ColMeta*>* scrollDown(int lastItem, int limit);
    ~ColMeta();
    /*NB: change to appropriate var <name>*/
    virtual QString toString() Q_DECL_OVERRIDE {return name;}
    
    QString table_id;
    QString name;
    QString _type;
    QString _size;
    QString allow_null;
    QString is_pk;
    QString input_type;
    QString data_source;

public:
    //static const int COL__id = 0;
    static const int COL_table_id = 1;
    static const int COL_name = 2;
    static const int COL__type = 3;
    static const int COL__size = 4;
    static const int COL_allow_null = 5;
    static const int COL_is_pk = 6;
    static const int COL_input_type = 7;
    static const int COL_data_source = 8;

//signals:
//    void dataChanged();
//    void rowAdded(int _id);
//    void rowRemoved(int _id);
//    void rowUpdated(int _id);
};

#endif //

