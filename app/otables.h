#ifndef OTABLES_H
#define OTABLES_H

#include <QMainWindow>
#include "queries/showtable.h"
#ifdef __linux__
#include "pdf_viewer/pdfviewer.h"
#elif _WIN32
#include "pdf_viewer/pdfviewer_win.h"
#endif
///
/// main window class
///

namespace Ui {
class OTables;
}

class OTables : public QMainWindow
{
    Q_OBJECT

public:
    explicit OTables(QWidget *parent = nullptr);
    ~OTables();

private slots:

    void pushButtonCompanies_clicked();

    void pushButtonContacts_clicked();

    void pushButtonInfo_clicked();

    void pushButtonServices_clicked();

    void pushButtonContracts_clicked();

    void AddEntry_triggered();

    void EditEntry_triggered();

    void DelEntry_triggered();

    void ImportTable_triggered();

    void ExportTable_triggered();

    void menuSettings_triggered();

    void menuOpenPDF_triggered();

    void menuExit_triggered();

    void lineEditSearch_textChanged(const QString &arg1);

private:
    Ui::OTables *ui;
    ShowTables* showTables;
    QAction* menuSettings;
    QAction* menuOpenPDF;
    QAction* menuExit;
    QSqlQueryModel* model;

    std::unique_ptr<PDFViewer> pdfViewer {std::make_unique<PDFViewer>()};

    void updateTable() const;
};

#endif // OTABLES_H
