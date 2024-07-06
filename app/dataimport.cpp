#include "dataimport.h"
#include "ui_dataimport.h"
#include <QFileDialog>
#include <QTextStream>
#include <queries/addqueries.h>
#include <QMouseEvent>

DataImport::DataImport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataImport)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    cols = 4;
    ui->pushButtonAdd->hide();

    connect(ui->pushButtonOpenFile, &QPushButton::clicked, this, &DataImport::pushButtonOpenFile_clicked);
    connect(ui->pushButtonImport, &QPushButton::clicked, this, &DataImport::pushButtonImport_clicked);
    connect(ui->comboBoxSelectTable, &QComboBox::currentTextChanged, this, &DataImport::ComboBoxSelectTable_changed);
    connect(ui->pushButtonAdd, &QPushButton::clicked, this, &DataImport::pushButtonAdd_clicked);
    connect(ui->pushButtonMinimize, &QPushButton::clicked, this, &DataImport::showMinimized);
    connect(ui->pushButtonClose, &QPushButton::clicked, this, &DataImport::close);
}

DataImport::~DataImport()
{
    delete ui;
}

///
/// Selecting a file through Explorer
///

void DataImport::pushButtonOpenFile_clicked() {
    QString filters("CSV files (*.csv)");
    QString defaultFilter("CSV files (*.csv)");
    ui->lineEditOpenFile->setText(QFileDialog::getOpenFileName(0, "Open file",
            QCoreApplication::applicationDirPath(), filters, &defaultFilter));
}

///
/// Open file
///

void DataImport::pushButtonImport_clicked() {
    filename = ui->lineEditOpenFile->text();
    QFile file(filename);
    if (file.open(QFile::ReadOnly)) {
        QTextStream data(&file);
        QString str;

        str = data.readLine();
        strList += str.split(',');
        for (int i {0}; i < strList.size(); i++) {
            ui->listWidget->addItem(strList[i]);
            ui->listWidget->item(i)->setCheckState(Qt::Checked);
        }

        strList.clear();
        while (!data.atEnd()) {
            str = data.readLine();
            strList += str.split(',');
        }

        file.close();
    } else {
        ui->labelStatus->setText(tr("Файл не найден")); // File not found
        ui->labelStatus->setStyleSheet("color: #c71c1c");
    }

    ui->pushButtonAdd->show();
}

///
/// Add data in the database from file
///

void DataImport::pushButtonAdd_clicked() {
    int count {0};
    for (int i {0}; i < ui->listWidget->count(); i++) {
        if (ui->listWidget->item(i)->checkState() == Qt::Checked) {
            count++;
        }
    }
    if (count != cols) {
        ui->labelStatus->setText(tr("Выбрано неверное количество столбцов"));
        ui->labelStatus->setStyleSheet("color: #c71c1c");

        return;
    }

    QStringList sql {};
    auto size {strList.size() - cols};
    for (int i {0}; i <= size; i += cols+1) {
        for (int j {0}; j < ui->listWidget->count(); j++) {

            // import data only from checked columns
            if (ui->listWidget->item(j)->checkState() == Qt::Checked) {
                sql.append(strList[i+j]);
            }
        }
        if (!importTable(sql)) {
            ui->labelStatus->setText(tr("Данные не импортированы"));
            ui->labelStatus->setStyleSheet("color: #c71c1c");
            return;
        }
        sql.clear();
    }
    ui->labelStatus->setText(tr("Данные импортированы"));
    ui->labelStatus->setStyleSheet("color: #63c71c");
}

///
/// Add data to a specific table
/// \return result of adding data
///

bool DataImport::importTable(const QStringList& strList) const {
    AddQueries que;
    bool result {false};

    switch(ui->comboBoxSelectTable->currentIndex()) {
    case 0:
        result = que.addCompanies(strList);
        break;
    case 1:
        result = que.addContacts(strList);
        break;
    case 2:
        result = que.addInfoCompany(strList);
        break;
    case 3:
        result = que.addService(strList);
        break;
    case 4:
        result = que.addContract(strList);
        break;
    }

    return result;
}

///
/// change the number of columns required for the selected table
///

void DataImport::ComboBoxSelectTable_changed() {
    switch(ui->comboBoxSelectTable->currentIndex()) {
    case 0:
        cols = 4;
        break;
    case 1:
        cols = 2;
        break;
    case 2:
        cols = 2;
        break;
    case 3:
        cols = 1;
        break;
    case 4:
        cols = 6;
        break;
    }
}

void DataImport::mouseMoveEvent(QMouseEvent* event) {
    const QPoint delta {event->pos()-cursorPos};
    move(x() + delta.x(), y() + delta.y());
    event->accept();
}

void DataImport::mousePressEvent(QMouseEvent* event) {
    cursorPos = event->pos();
}
