#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    // Set window title
    setWindowTitle("Auto_Home");

    // Create the main layout
    QVBoxLayout *vbox = new QVBoxLayout();

    // Create a button for debugging purposes
    QPushButton *btn1 = new QPushButton("debug/pause/exit czy cos");

    // Create a label for debugging purposes
    labelDebug = new QLabel("x");

    // Add the tab widget and debug widgets to the main layout
    vbox->addWidget(createTabWidget());
    vbox->addWidget(btn1);       // DELETE AFTER DEBUGGING
    vbox->addWidget(labelDebug); // DELETE AFTER DEBUGGING

    // Set the main layout
    setLayout(vbox);
}

QTabWidget *MainWindow::createTabWidget()
{
    // Create the tab widget
    tabWidget = new QTabWidget();

    // Add tabs to the tab widget
    tabWidget->addTab(createRoom1(), "Pokój 1");
    // Add more tabs if needed
    // tabWidget->addTab(createRoom2(), "Pokój 2");
    // tabWidget->addTab(createRoom3(), "Pokój 3");

    return tabWidget;
}

QWidget *MainWindow::createNewOknoLocation(QString nazwa)
{
    // Create a new widget for the location
    QWidget *line = new QWidget();

    // Create a checkbox for the location
    QCheckBox *Chb1 = new QCheckBox(line);

    // Create labels, buttons, and sliders for the location
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

    // Create a horizontal layout for the location
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(Chb1);
    hbox->addWidget(nazwaMiejsca);
    hbox->addWidget(Pb1);
    hbox->addWidget(Pbprocenty);
    hbox->addWidget(get);
    hbox->addWidget(send);  // TODO: Connect this button to hardware to start moving motor to the value from the slider

    // Set the layout for the location widget
    line->setLayout(hbox);

    int intValue = 42; // Replace with input from hardware

    // When "get" button is pressed, update the slider value from hardware
    auto updatePb1Value = [=]() {
        Pb1->setValue(intValue);
    };
    connect(get, &QPushButton::clicked, updatePb1Value);

    // When slider value changes, update labels and send the value to hardware
    connect(Pb1, &QSlider::valueChanged, this, [Pbprocenty, Chb1, Pb1, this](int value) {
        Pbprocenty->setText(QString::number(value) + "%");
        if (value == 100) {
            Chb1->setChecked(true);
        } else {
            Chb1->setChecked(false);
        }
        setValue(Pbprocenty->text()); // Call the set_value function
    });

    return line;
}

QWidget *MainWindow::createRoom1()
{
    // Create a widget for room 1
    QWidget *tab1 = new QWidget();

    // Create a layout for room 1
    QVBoxLayout *tab1Layout = new QVBoxLayout(tab1);

    // Add locations to room 1
    tab1Layout->addWidget(createNewOknoLocation("okno nad stołem"));
    tab1Layout->addWidget(createNewOknoLocation("okno koło szafy"));
    tab1Layout->addWidget(createNewOknoLocation("okno koło drzwi"));

    // Set the size policy and maximum height for room 1
    tab1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    tab1->setMaximumHeight(150);

    return tab1;
}

void MainWindow::setValue(QString str)
{
    // Set the debug label text
    labelDebug->setText(str);
    output = str;
}

MainWindow::~MainWindow()
{
    // Clean up dynamically allocated objects
    delete tabWidget;
    // Delete other dynamically allocated objects as needed
}
