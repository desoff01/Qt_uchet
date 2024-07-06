#include "settings.h"
#include "ui_settings.h"
#include <fstream>
#include "changepassword.h"
#include <QMouseEvent>

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    std::string lang;
    std::string fontSize {"13"};
    std::ifstream file("settings.ini");
    if (file.is_open()) {
        getline(file, lang);
        getline(file, fontSize);
    }
    file.close();

    if (lang == "english") {
        ui->radioButtonEn->setChecked(true);
        lang = false;
    } else if (lang == "russian") {
        ui->radioButtonRu->setChecked(true);
        lang = true;
    }

    int iFontSize {std::stoi(fontSize)};
    switch(iFontSize) {
    case 10:
        ui->comboBoxFontSize->setCurrentIndex(0);
        break;
    case 11:
        ui->comboBoxFontSize->setCurrentIndex(1);
        break;
    case 12:
        ui->comboBoxFontSize->setCurrentIndex(2);
        break;
    case 13:
        ui->comboBoxFontSize->setCurrentIndex(3);
        break;
    case 14:
        ui->comboBoxFontSize->setCurrentIndex(4);
        break;
    case 15:
        ui->comboBoxFontSize->setCurrentIndex(5);
        break;
    case 16:
        ui->comboBoxFontSize->setCurrentIndex(6);
        break;
    }

    connect(ui->pushButtonClose, &QPushButton::clicked, this, &settings::close);
    connect(ui->pushButtonMinimize, &QPushButton::clicked, this, &settings::showMinimized);
    connect(ui->radioButtonRu, &QRadioButton::clicked, this, &settings::radioButtonRu_clicked);
    connect(ui->radioButtonEn, &QRadioButton::clicked, this, &settings::radioButtonEn_clicked);
    connect(ui->comboBoxFontSize, &QComboBox::currentTextChanged,
            this, &settings::comboBoxFontSize_currentTextChanged);
    connect(ui->pushButtonChangePasswd, &QPushButton::clicked,
            this, &settings::pushButtonChangePasswd_clicked);
}

settings::~settings()
{
    delete ui;
}

void settings::radioButtonRu_clicked() {
    std::ofstream file("settings.ini");
    if (file.is_open()) {
        file << "russian\n" << ui->comboBoxFontSize->currentText().toUtf8().constData() << '\n';
    }
    file.close();

    lang = true;
    ui->labelStatus->setText(tr("Изменения вступят в силу\nпри следующем запуске"));
}

void settings::radioButtonEn_clicked() {
    std::ofstream file("settings.ini");
    if (file.is_open()) {
        file << "english\n" << ui->comboBoxFontSize->currentText().toUtf8().constData() << '\n';
    }
    file.close();

    lang = false;
    ui->labelStatus->setText(tr("Изменения вступят в силу\nпри следующем запуске"));
}

void settings::comboBoxFontSize_currentTextChanged() {
    if (lang) {
        radioButtonRu_clicked();
    } else {
        radioButtonEn_clicked();
    }
}

void settings::pushButtonChangePasswd_clicked() {
    auto chPass {std::make_unique<ChangePassword>()};
    chPass->exec();
}

void settings::mouseMoveEvent(QMouseEvent* event) {
    const QPoint delta {event->pos()-cursorPos};
    move(x() + delta.x(), y() + delta.y());
    event->accept();
}

void settings::mousePressEvent(QMouseEvent* event) {
    cursorPos = event->pos();
}
