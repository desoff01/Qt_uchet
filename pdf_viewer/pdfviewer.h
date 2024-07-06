#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include <QMainWindow>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(lcExample)

QT_BEGIN_NAMESPACE
namespace Ui {
class PDFViewer;
}

class QPdfDocument;
class QPdfView;
QT_END_NAMESPACE

class PageSelector;
class ZoomSelector;
class QTreeView;
class QSplitter;
class QPdfBookmarkModel;

class PDFViewer : public QMainWindow
{
    Q_OBJECT

public slots:
    void open(const QUrl &docLocation);

private slots:
    void bookmarkSelected(const QModelIndex &index);

    // action handlers
    void on_actionOpen_triggered();
    void on_actionQuit_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionPrevious_Page_triggered();
    void on_actionNext_Page_triggered();
    void on_actionContinuous_triggered();

public:
    explicit PDFViewer(QWidget *parent = nullptr);
    ~PDFViewer();

private:
    Ui::PDFViewer *ui;
    ZoomSelector *m_zoomSelector;
    PageSelector *m_pageSelector;

    QPdfDocument *m_document;

    QPdfView* pdfView;
    QPdfBookmarkModel *bookmarkModel;
};

#endif // PDFVIEWER_H
