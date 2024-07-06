#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QPoint>

///
/// login window class
///

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QMouseEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void pushButtonSignIn_clicked();

    void pushButtonShowPass_clicked();

private:
    QSqlDatabase auth;
    Ui::MainWindow *ui;
    bool showPassClicked {false};
    QPoint cursorPos;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};
#endif // MAINWINDOW_H
