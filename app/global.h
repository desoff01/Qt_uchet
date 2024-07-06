#ifndef GLOBAL_H
#define GLOBAL_H
#include <QSqlDatabase>
#include <QApplication>

///
/// class with global variables
///

extern QString savedLogin;
extern QByteArray getPasswordHash(QByteArray password);

enum struct SelectTables {COMPANIES,
                    CONTACTS,
                    INFO,
                    SERVICES,
                    CONTRACTS};

extern SelectTables st;

#endif // GLOBAL_H
