#ifndef DIALOGEDITTABLES_H
#define DIALOGEDITTABLES_H

#include <QDialog>
#include <QPoint>

///
/// data change window class
///

namespace Ui {
class DialogEditTables;
}

class QMouseEvent;

class DialogEditTables : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditTables(QWidget *parent = nullptr);
    ~DialogEditTables();

private slots:
    void pushButtonEdit_clicked();

private:
    Ui::DialogEditTables *ui;
    QPoint cursorPos;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // DIALOGEDITTABLES_H
