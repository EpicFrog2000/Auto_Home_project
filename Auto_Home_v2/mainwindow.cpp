#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Auto_Home");

    QVBoxLayout *vbox = new QVBoxLayout();
    QPushButton *btn1 = new QPushButton("debug/pause/exit czy cos");

    labeldebug = new QLabel("x");

    vbox->addWidget(createTabWidget());
    vbox->addWidget(btn1);
    vbox->addWidget(labeldebug);

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

QWidget *MainWindow::createNewOknoLocation(QString nazwa)
{
    QWidget *line = new QWidget();
    QCheckBox *Chb1 = new QCheckBox(line);

    QLabel *nazwaMiejsca = new QLabel(nazwa);
    QPushButton *get = new QPushButton("get");
    QPushButton *send = new QPushButton("send");
    QLabel *Pbprocenty = new QLabel("0%");
    QSlider *Pb1 = new QSlider;
    Pb1->setFixedWidth(200);
    Pb1->setValue(0);
    Pb1->setMinimum(0);
    Pb1->setMaximum(100);
    nazwaMiejsca->setFixedWidth(125);
    get->setFixedWidth(75);
    send->setFixedWidth(75);
    Pbprocenty->setFixedWidth(35);
    Chb1->setChecked(true);
    Chb1->setDisabled(true);
    Pb1->setOrientation(Qt::Horizontal);
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(Chb1);
    hbox->addWidget(nazwaMiejsca);
    hbox->addWidget(Pb1);
    hbox->addWidget(Pbprocenty);
    hbox->addWidget(get);
    hbox->addWidget(send);  //TODO make this button contact with hatdware to  start moving motor to value from slider

    line->setLayout(hbox);

    int intValue = 42; // Replace with input from hardware

    // When pressed change button it changes slider to value from hardware
    auto updatePb1Value = [=]() {
        Pb1->setValue(intValue);
    };
    connect(get, &QPushButton::clicked, updatePb1Value);

    //when value changes it sends it to hardware
    connect(Pb1, &QSlider::valueChanged, this, [Pbprocenty, Chb1, Pb1, this](int value) {
        Pbprocenty->setText(QString::number(value) + "%");
        if (value == 100) {
            Chb1->setChecked(true);
        } else {
            Chb1->setChecked(false);
        }
        set_value(Pbprocenty->text()); // Call the set_value function
    });

    return line;
}

QWidget *MainWindow::createRoom1()
{
    QWidget* tab1 = new QWidget();
    QVBoxLayout* tab1Layout = new QVBoxLayout(tab1);
    // Add more locations if needed
    tab1Layout->addWidget(createNewOknoLocation("okno nad stołem"));
    tab1Layout->addWidget(createNewOknoLocation("okno koło szafy"));
    tab1Layout->addWidget(createNewOknoLocation("okno koło drzwi"));

    tab1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    tab1->setMaximumHeight(150);

    return tab1;
}

void MainWindow::set_value(QString str)
{
    labeldebug->setText(str);
    output = str;
}

MainWindow::~MainWindow()
{
    delete tabWidget;
    // Delete other dynamically allocated objects as needed
}
