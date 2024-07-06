#ifndef DIALOGDELTABLES_H
#define DIALOGDELTABLES_H

#include <QDialog>
#include <QPoint>

///
/// data delete window class
///

namespace Ui {
class DialogDelTables;
}

class QMouseEvent;

class DialogDelTables : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDelTables(QWidget *parent = nullptr);
    ~DialogDelTables();

private slots:
    void pushButtonDel_clicked();

private:
    Ui::DialogDelTables *ui;
    QPoint cursorPos;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // DIALOGDELTABLES_H
