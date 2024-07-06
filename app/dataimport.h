#ifndef DATAIMPORT_H
#define DATAIMPORT_H

#include <QDialog>
#include <QPoint>

///
/// data import window class
///

namespace Ui {
class DataImport;
}

class QMouseEvent;

class DataImport : public QDialog
{
    Q_OBJECT

public:
    explicit DataImport(QWidget *parent = nullptr);
    ~DataImport();

private slots:
    void pushButtonOpenFile_clicked();

    void pushButtonImport_clicked();

    void ComboBoxSelectTable_changed();

    void pushButtonAdd_clicked();

private:
    Ui::DataImport *ui;
    QString filename;
    int cols;
    QStringList strList;
    QPoint cursorPos;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    bool importTable(const QStringList& strList) const;
};

#endif // DATAIMPORT_H
