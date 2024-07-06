#include "pdfviewer_win.h"
#include "ui_pdfviewer_win.h"

#include "searchresultdelegate.h"
#include "zoomselector_win.h"

#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QPdfBookmarkModel>
#include <QPdfDocument>
#include <QPdfPageNavigator>
#include <QPdfPageSelector>
#include <QPdfSearchModel>
#include <QShortcut>
#include <QStandardPaths>
#include <QtMath>

const qreal zoomMultiplier = qSqrt(2.0);

Q_LOGGING_CATEGORY(lcExample, "qt.examples.pdfviewer")

PDFViewer::PDFViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PDFViewer())
    , zoomSelector(new ZoomSelector(this))
    , pageSelector(new QPdfPageSelector(this))
    , searchModel(new QPdfSearchModel(this))
    , searchField(new QLineEdit(this))
    , document(new QPdfDocument(this))
{
    ui->setupUi(this);

    zoomSelector->setMaximumWidth(150);
    ui->mainToolBar->insertWidget(ui->actionZoom_In, zoomSelector);

    ui->mainToolBar->insertWidget(ui->actionForward, pageSelector);
    connect(pageSelector, &QPdfPageSelector::currentPageChanged, this, &PDFViewer::pageSelected);
    pageSelector->setDocument(document);
    auto nav = ui->pdfView->pageNavigator();
    connect(nav, &QPdfPageNavigator::currentPageChanged, pageSelector, &QPdfPageSelector::setCurrentPage);
    connect(nav, &QPdfPageNavigator::backAvailableChanged, ui->actionBack, &QAction::setEnabled);
    connect(nav, &QPdfPageNavigator::forwardAvailableChanged, ui->actionForward, &QAction::setEnabled);

    connect(zoomSelector, &ZoomSelector::zoomModeChanged, ui->pdfView, &QPdfView::setZoomMode);
    connect(zoomSelector, &ZoomSelector::zoomFactorChanged, ui->pdfView, &QPdfView::setZoomFactor);
    zoomSelector->reset();

    QPdfBookmarkModel *bookmarkModel = new QPdfBookmarkModel(this);
    bookmarkModel->setDocument(document);

    ui->bookmarkView->setModel(bookmarkModel);
    connect(ui->bookmarkView, &QAbstractItemView::activated, this, &PDFViewer::bookmarkSelected);

    ui->thumbnailsView->setModel(document->pageModel());

    searchModel->setDocument(document);
    ui->pdfView->setSearchModel(searchModel);
    ui->searchToolBar->insertWidget(ui->actionFindPrevious, searchField);
    connect(new QShortcut(QKeySequence::Find, this), &QShortcut::activated, this, [this]() {
        searchField->setFocus(Qt::ShortcutFocusReason);
    });
    searchField->setPlaceholderText(tr("Find in document"));
    searchField->setMaximumWidth(400);
    connect(searchField, &QLineEdit::textEdited, this, [this](const QString &text) {
        searchModel->setSearchString(text);
        ui->tabWidget->setCurrentWidget(ui->searchResultsTab);
    });
    ui->searchResultsView->setModel(searchModel);
    ui->searchResultsView->setItemDelegate(new SearchResultDelegate(this));
    connect(ui->searchResultsView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &PDFViewer::searchResultSelected);

    ui->pdfView->setDocument(document);

    connect(ui->pdfView, &QPdfView::zoomFactorChanged,
            zoomSelector, &ZoomSelector::setZoomFactor);

    connect(ui->actionOpen, &QAction::triggered, this, &PDFViewer::actionOpen_triggered);
    connect(ui->actionContinuous, &QAction::triggered, this, &PDFViewer::actionContinuous_triggered);
    connect(ui->actionNext_Page, &QAction::triggered, this, &PDFViewer::actionNext_Page_triggered);
    connect(ui->actionPrevious_Page, &QAction::triggered, this, &PDFViewer::actionPrevious_Page_triggered);
    connect(ui->actionForward, &QAction::triggered, this, &PDFViewer::actionNext_Page_triggered);
    connect(ui->actionBack, &QAction::triggered, this, &PDFViewer::actionPrevious_Page_triggered);
    connect(ui->actionForward, &QAction::triggered, this, &PDFViewer::actionForward_triggered);
    connect(ui->actionFindNext, &QAction::triggered, this, &PDFViewer::actionFindNext_triggered);
    connect(ui->actionFindPrevious, &QAction::triggered, this, &PDFViewer::actionFindPrevious_triggered);
    connect(ui->actionZoom_In, &QAction::triggered, this, &PDFViewer::actionZoom_In_triggered);
    connect(ui->actionZoom_Out, &QAction::triggered, this, &PDFViewer::actionZoom_Out_triggered);
    connect(ui->actionQuit, &QAction::triggered, this, &PDFViewer::actionQuit_triggered);
}

PDFViewer::~PDFViewer()
{
    delete ui;
}

void PDFViewer::open(const QUrl &docLocation)
{
    if (docLocation.isLocalFile()) {
        document->load(docLocation.toLocalFile());
        pageSelected(0);
    } else {
        const QString message = tr("%1 is not a valid local file").arg(docLocation.toString());
        qCDebug(lcExample).noquote() << message;
        QMessageBox::critical(this, tr("Failed to open"), message);
    }
    qCDebug(lcExample) << docLocation;
}

void PDFViewer::bookmarkSelected(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    const int page = index.data(int(QPdfBookmarkModel::Role::Page)).toInt();
    const qreal zoomLevel = index.data(int(QPdfBookmarkModel::Role::Level)).toReal();
    ui->pdfView->pageNavigator()->jump(page, {}, zoomLevel);
}

void PDFViewer::pageSelected(int page)
{
    auto nav = ui->pdfView->pageNavigator();
    nav->jump(page, {}, nav->currentZoom());
    const auto documentTitle = document->metaData(QPdfDocument::MetaDataField::Title).toString();
    setWindowTitle(!documentTitle.isEmpty() ? documentTitle : QStringLiteral("PDF Viewer"));
    setWindowTitle(tr("%1: page %2 (%3 of %4)")
                   .arg(documentTitle.isEmpty() ? u"PDF Viewer"_qs : documentTitle,
                        pageSelector->currentPageLabel(), QString::number(page + 1), QString::number(document->pageCount())));
}

void PDFViewer::searchResultSelected(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if (!current.isValid())
        return;

    const int page = current.data(int(QPdfSearchModel::Role::Page)).toInt();
    const QPointF location = current.data(int(QPdfSearchModel::Role::Location)).toPointF();
    ui->pdfView->pageNavigator()->jump(page, location);
    ui->pdfView->setCurrentSearchResultIndex(current.row());
}

void PDFViewer::actionOpen_triggered()
{
    if (fileDialog == nullptr) {
        fileDialog = new QFileDialog(this, tr("Choose a PDF"),
                                       QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
        fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
        fileDialog->setMimeTypeFilters({"application/pdf"});
    }

    if (fileDialog->exec() == QDialog::Accepted) {
        const QUrl toOpen = fileDialog->selectedUrls().constFirst();
        ui->actionBack->setEnabled(true);
        ui->actionForward->setEnabled(true);
        if (toOpen.isValid())
            open(toOpen);
    }
}

void PDFViewer::actionQuit_triggered()
{
    close();
}

void PDFViewer::actionZoom_In_triggered()
{
    ui->pdfView->setZoomFactor(ui->pdfView->zoomFactor() * zoomMultiplier);
}

void PDFViewer::actionZoom_Out_triggered()
{
    ui->pdfView->setZoomFactor(ui->pdfView->zoomFactor() / zoomMultiplier);
}

void PDFViewer::actionPrevious_Page_triggered()
{
    auto nav = ui->pdfView->pageNavigator();
    if (nav->currentPage() == 0) {
        nav->jump(document->pageCount() - 1, {}, nav->currentZoom());
    } else {
        nav->jump(nav->currentPage() - 1, {}, nav->currentZoom());
    }
}

void PDFViewer::actionNext_Page_triggered()
{
    auto nav = ui->pdfView->pageNavigator();
    if (nav->currentPage() == document->pageCount() - 1) {
        nav->jump(0, {}, nav->currentZoom());
    } else {
        nav->jump(nav->currentPage() + 1, {}, nav->currentZoom());
    }
}

void PDFViewer::thumbnailsView_activated(const QModelIndex &index)
{
    auto nav = ui->pdfView->pageNavigator();
    nav->jump(index.row(), {}, nav->currentZoom());
}

void PDFViewer::actionContinuous_triggered()
{
    ui->pdfView->setPageMode(ui->actionContinuous->isChecked() ?
                                 QPdfView::PageMode::MultiPage :
                                 QPdfView::PageMode::SinglePage);
}

void PDFViewer::actionBack_triggered()
{
    ui->pdfView->pageNavigator()->back();
}

void PDFViewer::actionForward_triggered()
{
    ui->pdfView->pageNavigator()->forward();
}

void PDFViewer::actionFindNext_triggered()
{
    int next = ui->searchResultsView->currentIndex().row() + 1;
    if (next >= searchModel->rowCount({}))
        next = 0;
    ui->searchResultsView->setCurrentIndex(searchModel->index(next));
}

void PDFViewer::actionFindPrevious_triggered()
{
    int prev = ui->searchResultsView->currentIndex().row() - 1;
    if (prev < 0)
        prev = searchModel->rowCount({}) - 1;
    ui->searchResultsView->setCurrentIndex(searchModel->index(prev));
}
