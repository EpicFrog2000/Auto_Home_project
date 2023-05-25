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
#include <QSpacerItem>
#include <QSlider>
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

public slots:

};
#endif // MAINWINDOW_H
