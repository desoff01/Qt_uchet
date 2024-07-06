#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QTranslator>
#include <QPoint>

namespace Ui {
class settings;
}

class QMouseEvent;

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = nullptr);
    ~settings();

private slots:
    void radioButtonRu_clicked();
    void radioButtonEn_clicked();
    void comboBoxFontSize_currentTextChanged();
    void pushButtonChangePasswd_clicked();

private:
    Ui::settings *ui;
    QPoint cursorPos;
    bool lang;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // SETTINGS_H
