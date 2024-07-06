#include "global.h"
#include <QCryptographicHash>

SelectTables st;
QString savedLogin = "user";
QByteArray getPasswordHash(QByteArray password) {
    std::array<int, 3> xorArr {0x10, 0x20, 0x30};
    for (qsizetype i {}; i < password.length(); i++) {
        password[i] ^= xorArr[i % 3] + 3;
    }
    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(password);
    hash.addData("PT_h4ckDa9s");

    return hash.result();
}
