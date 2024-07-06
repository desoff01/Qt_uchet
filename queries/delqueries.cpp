#include "delqueries.h"
#include "app/global.h"

DelQueries::DelQueries() {
    query = QSqlQuery(QSqlDatabase::database());
}

bool DelQueries::delCompany(const QString& id) {
    QSqlDatabase::database().open();

    query.prepare("DELETE FROM Companies WHERE idCompanies = :id");
    query.bindValue(":id", id);

    return query.exec();
}

bool DelQueries::delContact(const QString& id) {
    QSqlDatabase::database().open();

    query.prepare("DELETE FROM Contacts WHERE idContacts = :id");
    query.bindValue(":id", id);

    return query.exec();
}

bool DelQueries::delInfoCompany(const QString& id) {
    QSqlDatabase::database().open();

    query.prepare("DELETE FROM InfoCompany WHERE idInfoCompany = :id");
    query.bindValue(":id", id);

    return query.exec();
}

bool DelQueries::delService(const QString& id) {
    QSqlDatabase::database().open();

    query.prepare("DELETE FROM Services WHERE idServices = :id");
    query.bindValue(":id", id);

    return query.exec();
}

bool DelQueries::delContract(const QString& id) {
    QSqlDatabase::database().open();

    query.prepare("DELETE FROM Contracts WHERE numOfContract = :id");
    query.bindValue(":id", id);

    return query.exec();
}
