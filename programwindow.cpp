#include "programwindow.h"


ProgramWindow::ProgramWindow() : QWidget()
{
    setFixedSize(800, 800);

    setWindowTitle("Test");

    slider = new QSlider(Qt::Orientation::Horizontal, this);
    slider->setMinimum(0);
    slider->setMaximum(299);

    screen = new DisplayWindow(this);

    label = new QLabel("Step number : 1", this);
    label->setAlignment(Qt::AlignCenter);
    label->setMaximumHeight(30);

    demoButton = new QPushButton("Demo", this);
    demoButton->setIcon(QIcon("Gtk-media-play-ltr.svg"));

    QPushButton *resetButton = new QPushButton("Reset Camera", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(screen);
    layout->addWidget(label);
    layout->addWidget(slider);
    layout->addWidget(demoButton);
    layout->addWidget(resetButton);

    setLayout(layout);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeStep(int)));
    connect(demoButton, SIGNAL(clicked(bool)), this, SLOT(launchDemo()));
    connect(resetButton, SIGNAL(clicked(bool)), screen, SLOT(resetCamera()));

    QString s("comb_traj_20160219_121123.dat");
    initData(s);
    screen->setCoordinates(data.get1Vector(0));
}

void ProgramWindow::configureScreen() {
    screen->setViewPort();
    screen->setProjection();
    screen->setModelView();
}

void ProgramWindow::initData(QString& fileName) {
    data.loadData(fileName);
}

void ProgramWindow::changeStep(int index) {
    screen->setCoordinates(data.get1Vector(index));
    label->setText("Step number : " + QString::number(index + 1));
     //calls paintGL
    screen->update();
}

void ProgramWindow::demo() {
    slider->setValue(slider->value() + 1);
    if(slider->value() == slider->maximum()) {
        emit stopTimer();
        slider->setValue(0);
        delete timer;
        demoButton->setEnabled(true);
    }
}

void ProgramWindow::launchDemo() {
    demoButton->setDisabled(true);
    timer = new QTimer(this);
    slider->setValue(0);
    timer->start(1000/45);
    connect(this, SIGNAL(stopTimer()), timer, SLOT(stop()));
    connect(timer, SIGNAL(timeout()), this, SLOT(demo()));
}


