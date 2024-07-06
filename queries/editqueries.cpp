#include "editqueries.h"
#include "app/global.h"

EditQueries::EditQueries() {
    query = QSqlQuery(QSqlDatabase::database());
}

bool EditQueries::editCompany(const QStringList& args) {
    if (args.size() < 5) return false;
    QSqlDatabase::database().open();
    query.prepare("UPDATE Companies SET `nameCompany` = :company,"
                  " `surnameDir` = :surname, `fnameDir` = :name, "
                  "`patronymicDir` = :patronymic"
                  " WHERE (`idCompanies` = :id)");
    query.bindValue(":company", args[0]);
    query.bindValue(":surname", args[1]);
    query.bindValue(":name", args[2]);
    query.bindValue(":patronymic", args[3]);
    query.bindValue(":id", args[4]);

    return query.exec();
}

bool EditQueries::editCompany(const QString& company, const QString& surname,
                    const QString& fname, const QString& patronymic, const QString& id) {
    QSqlDatabase::database().open();

    query.prepare("UPDATE Companies SET `nameCompany` = :company,"
                  " `surnameDir` = :surname, `fnameDir` = :name, "
                  "`patronymicDir` = :patronymic"
                  " WHERE (`idCompanies` = :id)");
    query.bindValue(":company", company);
    query.bindValue(":surname", surname);
    query.bindValue(":name", fname);
    query.bindValue(":patronymic", patronymic);
    query.bindValue(":id", id);

    return query.exec();
}

bool EditQueries::editContact(const QStringList& args) {
    if (args.size() < 3) return false;
    QSqlDatabase::database().open();

    query.prepare("UPDATE Contacts SET `phoneContacts` = :phone, "
                  "`emailContacts` = :email WHERE (`idContacts` = :id)");
    query.bindValue(":phone", args[0]);
    query.bindValue(":email", args[1]);
    query.bindValue(":id", args[2]);

    return query.exec();
}

bool EditQueries::editContact(const QString& phoneNumber,
                        const QString& email, const QString& id) {
    QSqlDatabase::database().open();

    query.prepare("UPDATE Contacts SET `phoneContacts` = :phone, "
                  "`emailContacts` = :email WHERE (`idContacts` = :id)");
    query.bindValue(":phone", phoneNumber);
    query.bindValue(":email", email);
    query.bindValue(":id", id);

    return query.exec();
}

bool EditQueries::editInfoCompany(const QStringList& args) {
    if (args.size() < 3) return false;
    QSqlDatabase::database().open();

    query.prepare("SELECT idContacts FROM Contacts "
                  "WHERE phoneContacts = :phone");
    query.bindValue(":phone", args[0]);
    query.exec();
    query.first();
    QString idContacts {query.value(0).toString()};

    query.prepare("SELECT idCompanies FROM Companies "
                  "WHERE nameCompany = :company");
    query.bindValue(":company", args[1]);
    query.exec();
    query.first();
    QString idCompanies {query.value(0).toString()};

    query.prepare("UPDATE InfoCompany SET `idCompaniesInfo` = :idCompanies, "
                  "`idContactsInfo` = :idContacts WHERE (`idInfoCompany` = :idInfo)");
    query.bindValue(":idContacts", idContacts);
    query.bindValue(":idCompanies", idCompanies);
    query.bindValue(":idInfo", args[2]);

    return query.exec();
}

bool EditQueries::editInfoCompany(const QString& phoneNumber,
                        const QString& company, const QString& id) {
    QSqlDatabase::database().open();

    query.prepare("SELECT idContacts FROM Contacts "
                  "WHERE phoneContacts = :phone");
    query.bindValue(":phone", phoneNumber);
    query.exec();
    query.first();
    QString idContacts {query.value(0).toString()};

    query.prepare("SELECT idCompanies FROM Companies "
                  "WHERE nameCompany = :company");
    query.bindValue(":company", company);
    query.exec();
    query.first();
    QString idCompanies {query.value(0).toString()};

    query.prepare("UPDATE InfoCompany SET `idCompaniesInfo` = :idCompanies, "
                  "`idContactsInfo` = :idContacts WHERE (`idInfoCompany` = :idInfo)");
    query.bindValue(":idContacts", idContacts);
    query.bindValue(":idCompanies", idCompanies);
    query.bindValue(":idInfo", id);

    return query.exec();
}

bool EditQueries::editService(const QStringList& args) {
    if (args.size() < 2) return false;
    QSqlDatabase::database().open();

    query.prepare("UPDATE Services SET `Service` = :service"
                  " WHERE (`idServices` = :id)");
    query.bindValue(":service", args[0]);
    query.bindValue(":id", args[1]);

    return query.exec();

}

bool EditQueries::editService(const QString& service, const QString& id) {
    QSqlDatabase::database().open();

    query.prepare("UPDATE Services SET `Service` = :service"
                  " WHERE (`idServices` = :id)");
    query.bindValue(":service", service);
    query.bindValue(":id", id);

    return query.exec();
}

bool EditQueries::editContract(const QStringList& args) {
    if (args.size() < 6) return false;
    QSqlDatabase::database().open();

    query.prepare("SELECT idContacts FROM Contacts WHERE phoneContacts = :phone");
    query.bindValue(":phone", args[0]);
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

    query.prepare("UPDATE Contracts SET `DateOfConclusion` = :conclusion,"
                  " `Deadline` = :deadline, `idInfoCompanyCon` = :idInfo, "
                  "`idServicesCon` = :idService WHERE (`numOfContract` = :id)");
    query.bindValue(":conclusion", args[3]);
    query.bindValue(":deadline", args[4]);
    query.bindValue(":idinfo", idInfoCompany);
    query.bindValue(":idservice", idService);
    query.bindValue(":id", args[5]);

    return query.exec();
}

bool EditQueries::editContract(const QString& phoneNumber, const QString& company,
                  const QString& service, const QString& conclusion,
                               const QString& deadline, const QString& id) {
    QSqlDatabase::database().open();

    query.prepare("SELECT idContacts FROM Contacts WHERE phoneContacts = :phone");
    query.bindValue(":phone", phoneNumber);
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

    query.prepare("UPDATE Contracts SET `DateOfConclusion` = :conclusion,"
                  " `Deadline` = :deadline, `idInfoCompanyCon` = :idInfo, "
                  "`idServicesCon` = :idService WHERE (`numOfContract` = :id)");
    query.bindValue(":conclusion", conclusion);
    query.bindValue(":deadline", deadline);
    query.bindValue(":idinfo", idInfoCompany);
    query.bindValue(":idservice", idService);
    query.bindValue(":id", id);

    return query.exec();
}
