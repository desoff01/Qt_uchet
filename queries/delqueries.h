#ifndef DELQUERIES_H
#define DELQUERIES_H
#include <QSqlQuery>
class DelQueries
{
    QSqlQuery query;
public:
    DelQueries();

    bool delCompany(const QString& id);

    bool delContact(const QString& id);

    bool delInfoCompany(const QString& id);

    bool delService(const QString& id);

    bool delContract(const QString& id);
};

#endif // DELQUERIES_H
