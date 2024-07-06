#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLineEdit>
#include <fstream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;

    std::string lang {"english"};
    std::string fontSize {"13"};
    std::ifstream file("settings.ini");
    if (file.is_open()) {
        getline(file, lang);
        getline(file, fontSize);
    }
    file.close();
    if (lang == "english") {
        if (translator.load(":/i18n/Kursach_en_US.ts")) {
            a.installTranslator(&translator);
        }
    } else if (lang == "russian") {
        if (translator.load(":/i18n/Kursach_ru_RU.ts")) {
            a.installTranslator(&translator);
        }
    }
    a.setFont(QFont("Noto Sans", std::stoi(fontSize)));

    MainWindow w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();
    return a.exec();
}
