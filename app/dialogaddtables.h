#ifndef DIALOGADDTABLES_H
#define DIALOGADDTABLES_H

#include <QDialog>
#include <QPoint>

///
/// data add window class
///

namespace Ui {
class DialogAddTables;
}

class QMouseEvent;

class DialogAddTables : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddTables(QWidget *parent = nullptr);
    ~DialogAddTables();

private slots:
    void pushButtonAdd_clicked();

private:
    Ui::DialogAddTables *ui;
    QPoint cursorPos;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // DIALOGADDTABLES_H
