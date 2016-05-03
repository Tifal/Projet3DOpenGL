#include "programwindow.h"


ProgramWindow::ProgramWindow() : QWidget()
{
    setFixedSize(800, 800);

    setWindowTitle("Test");

    slider = new QSlider(Qt::Orientation::Horizontal, this);

    screen = new DisplayWindow(this);

    label = new QLabel("Step number : 1", this);
    label->setAlignment(Qt::AlignCenter);
    label->setMaximumHeight(30);

    demoButton = new QPushButton("Start demo", this);
    //demoButton->setIcon(QIcon("icons/Gtk-media-play-ltr.svg"));
    stopButton = new QPushButton("Stop", this);
    //stopButton->setIcon(QIcon("icons/Gtk-media-stop.svg"));
    pauseButton = new QPushButton("Pause", this);
    //pauseButton->setIcon(QIcon("icons/Fairytale_player_pause.svg"));
    pauseButton->setDisabled(true);
    stopButton->setDisabled(true);

    QPushButton *resetButton = new QPushButton("Reset Camera", this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(screen,0,0,1,3);
    layout->addWidget(label,1,0,1,3);
    layout->addWidget(slider,2,0,1,3);
    layout->addWidget(demoButton,3,0);
    layout->addWidget(pauseButton,3,1);
    layout->addWidget(stopButton,3,2);
    layout->addWidget(resetButton,4,0,1,3);

    setLayout(layout);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeStep(int)));
    connect(demoButton, SIGNAL(clicked(bool)), this, SLOT(startDemo()));
    connect(pauseButton, SIGNAL(clicked(bool)), this, SLOT(pauseDemo()));
    connect(stopButton, SIGNAL(clicked(bool)), this, SLOT(stopDemo()));

    connect(resetButton, SIGNAL(clicked(bool)), screen, SLOT(resetCamera()));

    QString s("files/comb_traj_20160219_121123.dat");
    data.loadData(s);
    screen->setCoordinates(data.get1Vector(0));

    slider->setMinimum(0);
    slider->setMaximum(data.getDataCoordinatesSize() - 1);
}

void ProgramWindow::configureScreen() {
    screen->setViewPort();
    screen->setProjection();
    screen->setModelView();
}

void ProgramWindow::changeStep(int index) {
    screen->setCoordinates(data.get1Vector(index));
    label->setText("Step number : " + QString::number(index + 1));
     //calls paintGL
    screen->update();
}

void ProgramWindow::demoPlaying() {
    slider->setValue(slider->value() + 1);
    if(slider->value() == slider->maximum()) {
        stopDemo();
    }
}

void ProgramWindow::pauseDemo() {
    emit stopTimer();
    delete timer;
    demoButton->setEnabled(true);
    pauseButton->setDisabled(true);
}

void ProgramWindow::startDemo() {
    demoButton->setDisabled(true);
    pauseButton->setEnabled(true);
    stopButton->setEnabled(true);
    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    timer->start(1000/35);
    connect(this, SIGNAL(stopTimer()), timer, SLOT(stop()));
    connect(timer, SIGNAL(timeout()), this, SLOT(demoPlaying()));
}

void ProgramWindow::stopDemo() {
    slider->setValue(0);
    if(pauseButton->isEnabled()) {
        pauseDemo();
    }
    else {
        demoButton->setEnabled(true);
    }
    stopButton->setDisabled(true);
}

