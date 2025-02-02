#ifndef PAGESELECTOR_H
#define PAGESELECTOR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPdfDocument;
class QPdfPageNavigator;
class QToolButton;
QT_END_NAMESPACE

class QHBoxLayout;

class PageSelector : public QWidget
{
    Q_OBJECT

public:
    explicit PageSelector(QWidget *parent = nullptr);
    ~PageSelector();

    void setPageNavigation(QPdfPageNavigator *pageNavigation);

private slots:
    void onCurrentPageChanged(int page);
    void pageNumberEdited();

private:
    QPdfPageNavigator *m_pageNavigation;

    QLineEdit *m_pageNumberEdit;
    QLabel *m_pageCountLabel;
    QToolButton *m_previousPageButton;
    QToolButton *m_nextPageButton;
    QHBoxLayout *layout;
};

#endif // PAGESELECTOR_H
