#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include <QLoggingCategory>
#include <QMainWindow>

Q_DECLARE_LOGGING_CATEGORY(lcExample)

QT_BEGIN_NAMESPACE
namespace Ui {
class PDFViewer;
}

class QFileDialog;
class QLineEdit;
class QPdfDocument;
class QPdfPageSelector;
class QPdfSearchModel;
class QPdfView;
class QSpinBox;
QT_END_NAMESPACE

class ZoomSelector;

class PDFViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit PDFViewer(QWidget *parent = nullptr);
    ~PDFViewer();

public slots:
    void open(const QUrl &docLocation);

private slots:
    void bookmarkSelected(const QModelIndex &index);
    void pageSelected(int page);
    void searchResultSelected(const QModelIndex &current, const QModelIndex &previous);

    // action handlers
    void actionOpen_triggered();
    void actionQuit_triggered();
    void actionZoom_In_triggered();
    void actionZoom_Out_triggered();
    void actionPrevious_Page_triggered();
    void actionNext_Page_triggered();
    void thumbnailsView_activated(const QModelIndex &index);
    void actionContinuous_triggered();
    void actionBack_triggered();
    void actionForward_triggered();
    void actionFindNext_triggered();
    void actionFindPrevious_triggered();

private:
    Ui::PDFViewer *ui;
    ZoomSelector *zoomSelector;
    QPdfPageSelector *pageSelector;
    QPdfSearchModel *searchModel;
    QLineEdit *searchField;
    QFileDialog *fileDialog {nullptr};

    QPdfDocument *document;
};

#endif // PDFVIEWER_H
