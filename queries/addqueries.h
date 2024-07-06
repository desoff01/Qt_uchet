#ifndef QUERIES_H
#define QUERIES_H
#include <QSqlQuery>
///
/// In the AddQueries class implemented add queries
///

class AddQueries
{
    QSqlQuery query;
public:
    AddQueries();

    bool addCompanies(const QStringList& args);
    bool addCompanies(const QString& company, const QString& surname,
            const QString& fname, const QString& patronymic);

    bool addContacts(const QStringList& args);
    bool addContacts(const QString& phoneNumber, const QString& email);

    bool addInfoCompany(const QStringList& args);
    bool addInfoCompany(const QString& phoneNumber, const QString& company);

    bool addService(const QStringList& args);
    bool addService(const QString& service);

    bool addContract(const QStringList& args);
    bool addContract(const QString& phoneNumber, const QString& company,
            const QString& service, const QString& conclusion,
            const QString& deadline);
};

#endif // QUERIES_H
