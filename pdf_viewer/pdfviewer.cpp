#include "pdfviewer.h"
#include "ui_pdfviewer.h"
#include "pageselector.h"
#include "zoomselector.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPdfBookmarkModel>
#include <QPdfDocument>
#include <QPdfPageNavigation>
#include <QHBoxLayout>
#include <QSplitter>
#include <QTreeView>
#include <memory>
#include <QtMath>

const qreal zoomMultiplier = qSqrt(2.0);

Q_LOGGING_CATEGORY(lcExample, "qt.examples.pdfviewer")

PDFViewer::PDFViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PDFViewer),
    m_zoomSelector(new ZoomSelector(this)),
    m_pageSelector(new PageSelector(this)),
    m_document(new QPdfDocument(this))
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/img/images/varnoff1.png"));

    pdfView = new QPdfView();
    ui->bookmarkView->setHeaderHidden(true);
    ui->horizontalLayout->addWidget(pdfView);

    m_zoomSelector->setMaximumWidth(150);
    ui->toolBar->insertWidget(ui->actionZoom_In, m_zoomSelector);

    m_pageSelector->setMaximumWidth(210);
    ui->toolBar->addWidget(m_pageSelector);

    m_pageSelector->setPageNavigation(pdfView->pageNavigation());

    connect(m_zoomSelector, &ZoomSelector::zoomModeChanged, pdfView, &QPdfView::setZoomMode);
    connect(m_zoomSelector, &ZoomSelector::zoomFactorChanged, pdfView, &QPdfView::setZoomFactor);
    m_zoomSelector->reset();

    bookmarkModel = new QPdfBookmarkModel(this);
    bookmarkModel->setDocument(m_document);

    ui->bookmarkView->setModel(bookmarkModel);
    connect(ui->bookmarkView, SIGNAL(activated(QModelIndex)), this, SLOT(bookmarkSelected(QModelIndex)));

    pdfView->setDocument(m_document);

    connect(pdfView, &QPdfView::zoomFactorChanged,
            m_zoomSelector, &ZoomSelector::setZoomFactor);
}

PDFViewer::~PDFViewer()
{   
    delete m_zoomSelector;
    delete m_pageSelector;
    delete m_document;
    delete bookmarkModel;
    delete pdfView;
    delete ui;
}

void PDFViewer::open(const QUrl &docLocation)
{
    if (docLocation.isLocalFile()) {
        m_document->load(docLocation.toLocalFile());
        const auto documentTitle = m_document->metaData(QPdfDocument::Title).toString();
        setWindowTitle(!documentTitle.isEmpty() ? documentTitle : QStringLiteral("PDF Viewer"));
    } else {
        qCDebug(lcExample) << docLocation << "is not a valid local file";
        QMessageBox::critical(this, tr("Failed to open"), tr("%1 is not a valid local file").arg(docLocation.toString()));
    }
    qCDebug(lcExample) << docLocation;
}

void PDFViewer::bookmarkSelected(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    const int page = index.data(QPdfBookmarkModel::PageNumberRole).toInt();
    pdfView->pageNavigation()->setCurrentPage(page);
}

void PDFViewer::on_actionOpen_triggered()
{
    QUrl toOpen = QFileDialog::getOpenFileUrl(this, tr("Choose a PDF"), QUrl(), "Portable Documents (*.pdf)");
    if (toOpen.isValid())
        open(toOpen);
}

void PDFViewer::on_actionQuit_triggered()
{
    QApplication::quit();
}

void PDFViewer::on_actionZoom_In_triggered()
{
    pdfView->setZoomFactor(pdfView->zoomFactor() * zoomMultiplier);
}

void PDFViewer::on_actionZoom_Out_triggered()
{
    pdfView->setZoomFactor(pdfView->zoomFactor() / zoomMultiplier);
}

void PDFViewer::on_actionPrevious_Page_triggered()
{
    pdfView->pageNavigation()->goToPreviousPage();
}

void PDFViewer::on_actionNext_Page_triggered()
{
    pdfView->pageNavigation()->goToNextPage();
}

void PDFViewer::on_actionContinuous_triggered()
{
    pdfView->setPageMode(ui->actionContinuous->isChecked() ? QPdfView::MultiPage : QPdfView::SinglePage);
}
