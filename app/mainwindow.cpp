#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"
#include "otables.h"
#include <QSqlQuery>
#include <QIcon>
#include <QMouseEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditPasswd->setEchoMode(QLineEdit::Password);
    ui->pushButtonShowPass->setIcon(QIcon(":/img/images/free-icon-eye-158746.png"));
    ui->lineEditLogin->setCursorPosition(20);
    ui->labelLogin->setAlignment(Qt::AlignRight);
    ui->labelPasswd->setAlignment(Qt::AlignRight);

    setWindowFlags(Qt::FramelessWindowHint);

    // connection settings changed
    auth = QSqlDatabase::addDatabase("QMYSQL");
    auth.setHostName(hostname);
    auth.setPort(3306);
    auth.setUserName(username);
    auth.setPassword(password);
    auth.setDatabaseName(db);

    connect(ui->pushButtonSignIn, &QPushButton::clicked, this, &MainWindow::pushButtonSignIn_clicked);
    connect(ui->pushButtonMinimize, &QPushButton::clicked, this, &MainWindow::showMinimized);
    connect(ui->pushButtonClose, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->pushButtonShowPass, &QPushButton::clicked, this, &MainWindow::pushButtonShowPass_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushButtonSignIn_clicked() {
    if(auth.open()) {
        QSqlQuery q(auth);
        q.prepare("SELECT * FROM Users WHERE username = :username AND password = :password;");
        q.bindValue(":username", ui->lineEditLogin->text());
        q.bindValue(":password", getPasswordHash(ui->lineEditPasswd->text().toUtf8()).toHex());
        q.exec();

        // if user exist open the main window
        if(q.size() > 0) {
            savedLogin = ui->lineEditLogin->text();
            OTables *out {new OTables()};
            this->close();
            out->show();
        }
        else {
            ui->labelStatus->setText(tr("Неверное имя пользователя или пароль")); //Incorrect Username or password
        }
    } else {
        ui->labelStatus->setText(tr("Не удаётся подключиться к базе данных")); //Cannot connect to database
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
    const QPoint delta {event->pos()-cursorPos};
    move(x() + delta.x(), y() + delta.y());
    event->accept();
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    cursorPos = event->pos();
}

///
/// Change image if button was clicked
///
void MainWindow::pushButtonShowPass_clicked() {
    if(showPassClicked) {
        showPassClicked = false;
        ui->lineEditPasswd->setEchoMode(QLineEdit::Password);
        ui->pushButtonShowPass->setIcon(QIcon(":/img/images/free-icon-eye-158746.png"));
    } else {
        showPassClicked = true;
        ui->lineEditPasswd->setEchoMode(QLineEdit::Normal);
        ui->pushButtonShowPass->setIcon(QIcon(":/img/images/free-icon-hide-2767146.png"));
    }
}

