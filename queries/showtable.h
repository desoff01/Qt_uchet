#ifndef SHOWTABLE_H
#define SHOWTABLE_H
#include <QTableView>
#include <QSqlQueryModel>
///
/// The ShowTables class display data in the table
///

class ShowTables
{
public:
    ShowTables(QSqlQueryModel* model, QTableView* tableView);
    ShowTables(QTableView* tableView);
    ~ShowTables();

    void showCompanies() const;

    void showContacts() const;

    void showInfo() const;

    void showServices() const;

    void showContracts() const;

private:
    QTableView* tableView;
    QSqlQueryModel* model;
};

#endif // SHOWTABLE_H
