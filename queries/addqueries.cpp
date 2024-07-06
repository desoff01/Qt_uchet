#include "addqueries.h"
#include <QStringList>
#include "app/global.h"
#include <QVariant>

AddQueries::AddQueries() {
    query = QSqlQuery(QSqlDatabase::database());
}

bool AddQueries::addCompanies(const QStringList& args) {
    if (args.size() < 4) return false;
    QSqlDatabase::database().open();

    query.prepare("INSERT INTO Companies (`nameCompany`, `surnameDir`, `fnameDir`, `patronymicDir`)"
                  " VALUES (:company, :surname, :name, :patronymic)");
    query.bindValue(":company", args[0]);
    query.bindValue(":surname", args[1]);
    query.bindValue(":name", args[2]);
    query.bindValue(":patronymic", args[3]);

    return query.exec();
}
bool AddQueries::addCompanies(const QString& company, const QString& surname,
                            const QString& fname, const QString& patronymic) {
    QSqlDatabase::database().open();

    query.prepare("INSERT INTO Companies (`nameCompany`, `surnameDir`, `fnameDir`, `patronymicDir`)"
                  " VALUES (:company, :surname, :name, :patronymic)");
    query.bindValue(":company", company);
    query.bindValue(":surname", surname);
    query.bindValue(":name", fname);
    query.bindValue(":patronymic", patronymic);

    return query.exec();
}

bool AddQueries::addContacts(const QStringList& args) {
    if (args.size() < 2) return false;
    QSqlDatabase::database().open();

    query.prepare("INSERT INTO Contacts (`phoneContacts`, `emailContacts`)"
                  " VALUES (:phoneNumber, :email)");
    query.bindValue(":phoneNumber", args[0]);
    query.bindValue(":email", args[1]);

    return query.exec();
}
bool AddQueries::addContacts(const QString& phoneNumber, const QString& email) {
    QSqlDatabase::database().open();

    query.prepare("INSERT INTO Contacts (`phoneContacts`, `emailContacts`)"
                  " VALUES (:phoneNumber, :email)");
    query.bindValue(":phoneNumber", phoneNumber);
    query.bindValue(":email", email);

    return query.exec();
}

bool AddQueries::addInfoCompany(const QStringList& args) {
    if (args.size() < 2) return false;
    QSqlDatabase::database().open();

    query.prepare("SELECT idContacts FROM Contacts WHERE phoneContacts = :phoneNumber");
    query.bindValue(":phoneNumber", args[0]);
    query.exec();
    query.first();
    QString idContacts {query.value(0).toString()};

    query.prepare("SELECT idCompanies FROM Companies WHERE nameCompany = :company");
    query.bindValue(":company", args[1]);
    query.exec();
    query.first();
    QString idCompanies {query.value(0).toString()};

    query.prepare("INSERT INTO InfoCompany (`idCompaniesInfo`, `idContactsInfo`)"
                  " VALUES (:contacts, :companies)");
    query.bindValue(":contacts", idContacts);
    query.bindValue(":companies", idCompanies);
    return query.exec();
}
bool AddQueries::addInfoCompany(const QString& phoneNumber, const QString& company) {
    QSqlDatabase::database().open();

    query.prepare("SELECT idContacts FROM Contacts WHERE phoneContacts = :phoneNumber");
    query.bindValue(":phoneNumber", phoneNumber);
    query.exec();
    query.first();
    QString idContacts {query.value(0).toString()};

    query.prepare("SELECT idCompanies FROM Companies WHERE nameCompany = :company");
    query.bindValue(":company", company);
    query.exec();
    query.first();
    QString idCompanies {query.value(0).toString()};

    query.prepare("INSERT INTO InfoCompany (`idCompaniesInfo`, `idContactsInfo`)"
                  " VALUES (:contacts, :companies)");
    query.bindValue(":contacts", idContacts);
    query.bindValue(":companies", idCompanies);
    return query.exec();
}

bool AddQueries::addService(const QStringList& args) {
    if (args.size() < 1) return false;
    QSqlDatabase::database().open();

    query.prepare("INSERT INTO Services (`Service`) VALUES (:service)");
    query.bindValue(":service", args[0]);
    return query.exec();

}
bool AddQueries::addService(const QString &service) {
    QSqlDatabase::database().open();

    query.prepare("INSERT INTO Services (`Service`) VALUES (:service)");
    query.bindValue(":service", service);
    return query.exec();
}

bool AddQueries::addContract(const QStringList& args) {
    if (args.size() < 5) return false;
    QSqlDatabase::database().open();

    query.prepare("SELECT idContacts FROM Contacts WHERE phoneContacts = :phoneNumber");
    query.bindValue(":phoneNumber", args[0]);
    query.exec();
    query.first();
    QString idContacts {query.value(0).toString()};

    query.prepare("SELECT idCompanies FROM Companies WHERE nameCompany = :company");
    query.bindValue(":company", args[1]);
    query.exec();
    query.first();
    QString idCompanies {query.value(0).toString()};

    query.prepare("SELECT idInfoCompany FROM InfoCompany WHERE"
                  " idCompaniesInfo = :idcompany AND idContactsInfo = :idcontact");
    query.bindValue(":idcompany", idCompanies);
    query.bindValue(":idcontact", idContacts);
    query.exec();
    query.first();
    QString idInfoCompany {query.value(0).toString()};

    query.prepare("SELECT idServices FROM Services WHERE Service = :service");
    query.bindValue(":service", args[2]);
    query.exec();
    query.first();
    QString idService {query.value(0).toString()};

    query.prepare("INSERT INTO Contracts (`DateOfConclusion`, `Deadline`,"
                  " `idInfoCompanyCon`, `idServicesCon`)"
                  " VALUES (:conclusion, :deadline, :idinfo, :idservice)");
    query.bindValue(":conclusion", args[3]);
    query.bindValue(":deadline", args[4]);
    query.bindValue(":idinfo", idInfoCompany);
    query.bindValue(":idservice", idService);
    return query.exec();
}
bool AddQueries::addContract(const QString& phoneNumber, const QString& company,
            const QString& service, const QString& conclusion, const QString& deadline) {
    QSqlDatabase::database().open();

    query.prepare("SELECT idContacts FROM Contacts WHERE phoneContacts = :phoneNumber");
    query.bindValue(":phoneNumber", phoneNumber);
    query.exec();
    query.first();
    QString idContacts {query.value(0).toString()};

    query.prepare("SELECT idCompanies FROM Companies WHERE nameCompany = :company");
    query.bindValue(":company", company);
    query.exec();
    query.first();
    QString idCompanies {query.value(0).toString()};

    query.prepare("SELECT idInfoCompany FROM InfoCompany WHERE"
                  " idCompaniesInfo = :idcompany AND idContactsInfo = :idcontact");
    query.bindValue(":idcompany", idCompanies);
    query.bindValue(":idcontact", idContacts);
    query.exec();
    query.first();
    QString idInfoCompany {query.value(0).toString()};

    query.prepare("SELECT idServices FROM Services WHERE Service = :service");
    query.bindValue(":service", service);
    query.exec();
    query.first();
    QString idService {query.value(0).toString()};

    query.prepare("INSERT INTO Contracts (`DateOfConclusion`, `Deadline`,"
                  " `idInfoCompanyCon`, `idServicesCon`)"
                  " VALUES (:conclusion, :deadline, :idinfo, :idservice)");
    query.bindValue(":conclusion", conclusion);
    query.bindValue(":deadline", deadline);
    query.bindValue(":idinfo", idInfoCompany);
    query.bindValue(":idservice", idService);

    return query.exec();
}
