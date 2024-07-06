#ifndef EDITQUERIES_H
#define EDITQUERIES_H
#include <QSqlQuery>
class EditQueries
{
    QSqlQuery query;
public:
    EditQueries();

    bool editCompany(const QStringList& args);
    bool editCompany(const QString& company, const QString& surname,
                      const QString& fname, const QString& patronymic, const QString& id);

    bool editContact(const QStringList& args);
    bool editContact(const QString& phoneNumber, const QString& email, const QString& id);

    bool editInfoCompany(const QStringList& args);
    bool editInfoCompany(const QString& phoneNumber, const QString& company, const QString& id);

    bool editService(const QStringList& args);
    bool editService(const QString& service, const QString& id);

    bool editContract(const QStringList& args);
    bool editContract(const QString& phoneNumber, const QString& company,
                     const QString& service, const QString& conclusion,
                     const QString& deadline, const QString& id);
};

#endif // EDITQUERIES_H
