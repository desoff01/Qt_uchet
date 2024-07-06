#include "showtable.h"
#include "app/global.h"
#include <QMessageBox>

ShowTables::ShowTables(QSqlQueryModel* model, QTableView* tableView) {
    this->tableView = tableView;
    this->model = model;
}

ShowTables::ShowTables(QTableView* tableView) {
    this->tableView = tableView;
    model = new QSqlQueryModel;
    tableView->setModel(model);
}

ShowTables::~ShowTables() {
    delete tableView;
    delete model;
}

void ShowTables::showCompanies() const {
    if (QSqlDatabase::database().open()) {
        model->clear();

        model->setQuery("SELECT * FROM Companies;", QSqlDatabase::database());

        model->setHeaderData(0, Qt::Horizontal, "id");
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Компания"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Фамилия"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Имя"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Отчество"));

        tableView->resizeColumnsToContents();
    }
}

void ShowTables::showContacts() const {
    if (QSqlDatabase::database().open()) {
        model->clear();
        model->setQuery("SELECT * FROM Contacts;", QSqlDatabase::database());

        model->setHeaderData(0, Qt::Horizontal, "id");
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Номер телефона"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Почта"));

        tableView->resizeColumnsToContents();
    }
}

void ShowTables::showInfo() const {
    if (QSqlDatabase::database().open()) {
        model->clear();
        model->setQuery("SELECT idInfoCompany, nameCompany, phoneContacts, emailContacts FROM InfoCompany "
                        "INNER JOIN Companies ON idCompaniesInfo = idCompanies "
                        "INNER JOIN Contacts ON idContactsInfo = idContacts;", QSqlDatabase::database());

        model->setHeaderData(0, Qt::Horizontal, "id");
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Компания"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Номер телефона"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Почта"));

        tableView->resizeColumnsToContents();
    }
}

void ShowTables::showServices() const {
    if (QSqlDatabase::database().open()) {
        model->clear();
        model->setQuery("SELECT * FROM Services;", QSqlDatabase::database());

        model->setHeaderData(0, Qt::Horizontal, "id");
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Услуга"));

        tableView->resizeColumnsToContents();
    }
}

void ShowTables::showContracts() const {
    if (QSqlDatabase::database().open()) {
        model->clear();
        model->setQuery("SELECT numOfContract, DateOfConclusion, Deadline, nameCompany, "
                        "phoneContacts, emailContacts, Service FROM Contracts "
                        "INNER JOIN Services ON idServicesCon = idServices "
                        "INNER JOIN InfoCompany ON idInfoCompanyCon = idInfoCompany "
                        "INNER JOIN Companies ON idCompaniesInfo = idCompanies "
                        "INNER JOIN Contacts ON idContactsInfo = idContacts;", QSqlDatabase::database());

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("номер контракта"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Дата заключения контракта"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Дедлайн"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Компания"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Номер телефона"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Почта"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Услуга"));

        tableView->resizeColumnsToContents();
    }
}
