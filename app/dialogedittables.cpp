#include "dialogedittables.h"
#include "ui_dialogedittables.h"
#include "global.h"
#include "queries/editqueries.h"
#include <QMouseEvent>

DialogEditTables::DialogEditTables(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditTables)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    connect(ui->pushButtonClose, &QPushButton::clicked, this, &DialogEditTables::close);
    connect(ui->pushButtonEdit, &QPushButton::clicked, this, &DialogEditTables::pushButtonEdit_clicked);

    switch (st) {
    case SelectTables::COMPANIES:
        ui->lineEdit_2->show();
        ui->lineEdit_3->show();
        ui->lineEdit_4->show();
        ui->lineEdit_5->hide();

        ui->label_2->show();
        ui->label_3->show();
        ui->label_4->show();
        ui->label_5->hide();

        ui->label->setText(tr("Компания:"));
        ui->label_2->setText(tr("Фамилия:"));
        ui->label_3->setText(tr("Имя:"));
        ui->label_4->setText(tr("Отчество:"));
        break;

    case SelectTables::CONTACTS:
        ui->lineEdit_2->show();
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();
        ui->lineEdit_5->hide();

        ui->label_2->show();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();

        ui->label->setText(tr("Номер телефона:"));
        ui->label_2->setText(tr("Почта:"));
        break;

    case SelectTables::INFO:
        ui->lineEdit_2->show();
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();
        ui->lineEdit_5->hide();

        ui->label_2->show();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();

        ui->label->setText(tr("Номер телефона:"));
        ui->label_2->setText(tr("Компания:"));
        break;

    case SelectTables::SERVICES:
        ui->lineEdit_2->hide();
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();
        ui->lineEdit_5->hide();

        ui->label_2->hide();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();

        ui->label->setText(tr("Услуга:"));
        break;

    case SelectTables::CONTRACTS:
        ui->lineEdit_2->show();
        ui->lineEdit_3->show();
        ui->lineEdit_4->show();
        ui->lineEdit_5->show();

        ui->label_2->show();
        ui->label_3->show();
        ui->label_4->show();
        ui->label_5->show();

        ui->label->setText(tr("Компания:"));
        ui->label_2->setText(tr("Номер телефона:"));
        ui->label_3->setText(tr("Дата заключения:"));
        ui->label_4->setText(tr("Дедлайн:"));
        ui->label_5->setText(tr("Услуга:"));
        break;
    }
}

DialogEditTables::~DialogEditTables()
{
    delete ui;
}

void DialogEditTables::pushButtonEdit_clicked() {
    bool success;
    EditQueries edit;

    switch(st) {
    case SelectTables::COMPANIES:
        success = edit.editCompany(ui->lineEdit->text(), ui->lineEdit_2->text(),
                ui->lineEdit_3->text(), ui->lineEdit_4->text(), ui->spinBox->text());
        break;

    case SelectTables::CONTACTS:
        success = edit.editContact(ui->lineEdit->text(), ui->lineEdit_2->text(),
                                   ui->spinBox->text());
        break;

    case SelectTables::INFO:
    {
        success = edit.editInfoCompany(ui->lineEdit->text(), ui->lineEdit_2->text(),
                                       ui->spinBox->text());
        break;
    }

    case SelectTables::SERVICES:
        success = edit.editService(ui->lineEdit->text(), ui->spinBox->text());
        break;

    case SelectTables::CONTRACTS:
    {
        success = edit.editContract(ui->lineEdit_2->text(), ui->lineEdit->text(), ui->lineEdit_5->text(),
                                    ui->lineEdit_3->text(), ui->lineEdit_4->text(), ui->spinBox->text());
        break;
    }
    }

    if (success) {
        ui->labelStatus->setText(tr("Запись изменена"));
        ui->labelStatus->setStyleSheet("color: #63c71c");
    } else {
        ui->labelStatus->setText(tr("Запись не изменена"));
        ui->labelStatus->setStyleSheet("color: #c71c1c");
    }
}

void DialogEditTables::mouseMoveEvent(QMouseEvent* event) {
    const QPoint delta {event->pos()-cursorPos};
    move(x() + delta.x(), y() + delta.y());
    event->accept();
}

void DialogEditTables::mousePressEvent(QMouseEvent* event) {
    cursorPos = event->pos();
}
