#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QSizePolicy>
#include <QSlider>
#include <QString>
#include <QTimer>
#include <QEventLoop>
#include <QtSerialPort/QSerialPort>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTabWidget* tabWidget;
    QTabWidget* createTabWidget();
    QWidget* createRoom1();
    QWidget* createNewOknoLocation(QString nazwa);

    QLabel* labelDebug;
    void setValue(QString str);
    QString output;
    //int readSerialData();
};

#endif // MAINWINDOW_H
