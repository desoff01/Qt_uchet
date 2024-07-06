#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>
#include <QPoint>

namespace Ui {
class ChangePassword;
}

class QMouseEvent;

class ChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePassword(QWidget *parent = nullptr);
    ~ChangePassword();

private slots:
    void pushButtonChangePasswd_clicked();

private:
    Ui::ChangePassword *ui;
    QPoint cursorPos;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // CHANGEPASSWORD_H
