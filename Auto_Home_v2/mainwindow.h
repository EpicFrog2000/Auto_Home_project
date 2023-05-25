#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QProgressBar>
#include <QLabel>
#include <QSizePolicy>
#include <QSlider>
#include <QString>
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTabWidget *tabWidget;
    QTabWidget *createTabWidget();
    QWidget *createRoom1();
    QWidget *createNewOknoLocation(QString nazwa);

    QLabel *labeldebug;
    void set_value(QString str);
    QString output;
};
#endif // MAINWINDOW_H
