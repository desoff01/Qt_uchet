#include "dialogdeltables.h"
#include "ui_dialogdeltables.h"
#include "global.h"
#include "queries/delqueries.h"
#include <QMouseEvent>

DialogDelTables::DialogDelTables(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDelTables)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    connect(ui->pushButtonClose, &QPushButton::clicked, this, &DialogDelTables::close);
    connect(ui->pushButtonDel, &QPushButton::clicked, this, &DialogDelTables::pushButtonDel_clicked);
}

DialogDelTables::~DialogDelTables()
{
    delete ui;
}

void DialogDelTables::pushButtonDel_clicked() {
    bool success;
    DelQueries del;

    switch(st) {
    case SelectTables::COMPANIES:
        success = del.delCompany(ui->spinBox->text());
        break;
    case SelectTables::CONTACTS:
        success = del.delContact(ui->spinBox->text());
        break;
    case SelectTables::INFO:
        success = del.delInfoCompany(ui->spinBox->text());
        break;
    case SelectTables::SERVICES:
        success = del.delService(ui->spinBox->text());
        break;
    case SelectTables::CONTRACTS:
        success = del.delContract(ui->spinBox->text());
        break;
    }

    if (success) {
        ui->labelStatus->setText(tr("Запись удалена"));
        ui->labelStatus->setStyleSheet("color: #63c71c");
    } else {
        ui->labelStatus->setText(tr("Неверный id"));
        ui->labelStatus->setStyleSheet("color: #c71c1c");
    }
}

void DialogDelTables::mouseMoveEvent(QMouseEvent* event) {
    const QPoint delta {event->pos()-cursorPos};
    move(x() + delta.x(), y() + delta.y());
    event->accept();
}

void DialogDelTables::mousePressEvent(QMouseEvent* event) {
    cursorPos = event->pos();
}
