#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Auto_Home");

    QVBoxLayout *vbox = new QVBoxLayout();
    QPushButton *btn1 = new QPushButton("debug/pause/exit czy cos");

    vbox->addWidget(createTabWidget());
    vbox->addWidget(btn1);

    setLayout(vbox);
}

QTabWidget *MainWindow::createTabWidget()
{
    tabWidget = new QTabWidget();

    tabWidget->addTab(createRoom1(), "Pokój 1");
    // Add more tabs if needed
    // tabWidget->addTab(createRoom2(), "Pokój 2");
    // tabWidget->addTab(createRoom3(), "Pokój 3");

    return tabWidget;
}

QWidget *MainWindow::createRoom1()
{
    QWidget* tab1 = new QWidget();
    QVBoxLayout* tab1Layout = new QVBoxLayout(tab1);

    tab1Layout->addWidget(createNewOknoLocation("okno nad stołem"));
    tab1Layout->addWidget(createNewOknoLocation("okno koło szafy"));
    tab1Layout->addWidget(createNewOknoLocation("okno koło drzwi"));

    tab1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    tab1->setMaximumHeight(150);

    return tab1;
}

QWidget *MainWindow::createNewOknoLocation(QString nazwa)
{
    QWidget *line = new QWidget();
    QCheckBox *Chb1 = new QCheckBox(line);
    QSlider *Pb1 = new QSlider(Qt::Horizontal, line); // Specify the slider orientation
    QLabel *nazwaMiejsca = new QLabel(nazwa);
    QPushButton *change = new QPushButton("change");
    QLabel *Pbprocenty = new QLabel("0%"); //depends on progress bar fillement

    Pb1->setFixedWidth(200);
    Pb1->setValue(0);
    Pb1->setMinimum(0);
    Pb1->setMaximum(100);
    nazwaMiejsca->setFixedWidth(125);
    change->setFixedWidth(75);
    Pbprocenty->setFixedWidth(35);
    Chb1->setChecked(true); //depends on percentage
    Chb1->setDisabled(true); // Disable mouse actions

    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(Chb1);
    hbox->addWidget(nazwaMiejsca);
    hbox->addWidget(Pb1);
    hbox->addWidget(Pbprocenty);
    hbox->addWidget(change);

    line->setLayout(hbox);

    connect(Pb1, &QSlider::valueChanged, this, [Pbprocenty, Chb1](int value) {
        Pbprocenty->setText(QString::number(value) + "%");
        if (value == 100) {
            Chb1->setChecked(true);
        }else{
            Chb1->setChecked(false);
        }
    });

    return line;
}



MainWindow::~MainWindow()
{

}
