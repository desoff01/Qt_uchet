#include "changepassword.h"
#include "ui_changepassword.h"
#include "global.h"
#include <QSqlQuery>
#include <QString>
#include <QSqlDatabase>
#include <QMouseEvent>

ChangePassword::ChangePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    ui->lineEditCurrPasswd->setEchoMode(QLineEdit::Password);
    ui->lineEditNewPasswd->setEchoMode(QLineEdit::Password);
    ui->lineEditRepNewPasswd->setEchoMode(QLineEdit::Password);

    connect(ui->pushButtonClose, &QPushButton::clicked, this, &ChangePassword::close);
    connect(ui->pushButtonMinimize, &QPushButton::clicked, this, &ChangePassword::showMinimized);
    connect(ui->pushButtonChangePasswd, &QPushButton::clicked,
            this, &ChangePassword::pushButtonChangePasswd_clicked);
}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::pushButtonChangePasswd_clicked() {
    if(QSqlDatabase::database().open()) {

        QSqlQuery q(QSqlDatabase::database());
        q.prepare("SELECT idUsers FROM Users WHERE username = :username AND password = :password;");
        q.bindValue(":username", savedLogin);
        q.bindValue(":password", getPasswordHash(ui->lineEditCurrPasswd->text().toUtf8()).toHex());
        q.exec();

        if(q.size() > 0) {
            if (ui->lineEditNewPasswd->text() == ui->lineEditRepNewPasswd->text()) {
                q.first();
                int idUsers {q.value(0).toInt()};
                q.clear();

                q.prepare("UPDATE Users SET `password` = :newPass WHERE (`idUsers` = :id);");
                q.bindValue(":id", idUsers);
                q.bindValue(":newPass", getPasswordHash(ui->lineEditNewPasswd->text().toUtf8()).toHex());
                q.exec();

                ui->labelStatus->setText(tr("Пароль изменён"));
                ui->labelStatus->setStyleSheet("color: #63c71c");
            } else {
                ui->labelStatus->setText(tr("Пароли не совпадают"));
                ui->labelStatus->setStyleSheet("color: #c71c1c");
            }
        } else {
            ui->labelStatus->setText(tr("Неверный текущий пароль"));
            ui->labelStatus->setStyleSheet("color: #c71c1c");
        }
    } else {
        ui->labelStatus->setText(tr("Нет соединения с БД")); // Cannot connect to database
        ui->labelStatus->setStyleSheet("color: #c71c1c");
    }
}

void ChangePassword::mouseMoveEvent(QMouseEvent* event) {
    const QPoint delta {event->pos()-cursorPos};
    move(x() + delta.x(), y() + delta.y());
    event->accept();
}

void ChangePassword::mousePressEvent(QMouseEvent* event) {
    cursorPos = event->pos();
}
