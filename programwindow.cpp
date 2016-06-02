#include "programwindow.h"

/** Constructor to initialize and create the content of the window.
 * @brief ProgramWindow::ProgramWindow
 */
static QString choice="choice1";

ProgramWindow::ProgramWindow() : QWidget()
{
    setFixedSize(800, 800);

    setWindowTitle("Test");

    QString s("files/comb_traj_20160219_121123.dat");
    data.loadData(s);

    slider = new QSlider(Qt::Orientation::Horizontal, this);

    screen = new DisplayWindow(this);

    label = new QLabel("Step number : 1", this);
    label->setAlignment(Qt::AlignCenter);
    label->setMaximumHeight(30);

    demoButton = new QPushButton("Start demo", this);
    demoButton->setIcon(QIcon("icons/Gtk-media-play-ltr.svg"));
    stopButton = new QPushButton("Stop", this);
    stopButton->setIcon(QIcon("icons/Gtk-media-stop.svg"));
    pauseButton = new QPushButton("Pause", this);
    pauseButton->setIcon(QIcon("icons/Fairytale_player_pause.svg"));
    pauseButton->setDisabled(true);
    stopButton->setDisabled(true);


    coordinatesWindow = new CoordinatesWindow;

    QPushButton *resetButton = new QPushButton("Reset Camera", this);

    QPushButton *displayFileCoordinates=new QPushButton("Display file coordinates",this);
    QRadioButton *displayChoice1=new QRadioButton("View of Mr. Holt",this);
    QRadioButton *displayChoice2=new QRadioButton("View of Mr. Nilsen",this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(screen,0,0,1,3);
    layout->addWidget(label,1,0,1,3);
    layout->addWidget(slider,2,0,1,3);
    layout->addWidget(demoButton,3,0);
    layout->addWidget(pauseButton,3,1);
    layout->addWidget(stopButton,3,2);
    layout->addWidget(resetButton,4,0,1,3);
    layout->addWidget(displayFileCoordinates,5,1,2,2);
    layout->addWidget(displayChoice1,5,0);
    layout->addWidget(displayChoice2,6,0);

    selectModeButton = new QPushButton("select markers",this);
    linkModeButton = new QPushButton("link markers",this);
    QPushButton *eraseLinks = new QPushButton("erase links", this);
    formerSteps = new QPushButton("display former steps", this);
    numberOfFormerSteps = new QComboBox(this);
    formerStepsLine = new QRadioButton("lines", this);
    formerStepsPoints = new QRadioButton("points", this);
    formerStepsLine->setChecked(true);
    furtherSteps = new QPushButton("display further steps", this);
    numberOfFurtherSteps = new QComboBox(this);

    layout->addWidget(selectModeButton, 7,0);
    layout->addWidget(linkModeButton, 7, 1);
    layout->addWidget(eraseLinks, 7, 2);
    layout->addWidget(formerSteps, 8, 0, 2, 1);
    layout->addWidget(numberOfFormerSteps, 8, 1, 2, 1);
    layout->addWidget(formerStepsLine, 8, 2);
    layout->addWidget(formerStepsPoints, 9, 2);
    layout->addWidget(furtherSteps, 10, 0);
    layout->addWidget(numberOfFurtherSteps, 10, 1);
    selectModeButton->setCheckable(true);
    linkModeButton->setCheckable(true);
    formerSteps->setCheckable(true);
    furtherSteps->setCheckable(true);

    setLayout(layout);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeStep(int)));
    connect(demoButton, SIGNAL(clicked(bool)), this, SLOT(startDemo()));
    connect(pauseButton, SIGNAL(clicked(bool)), this, SLOT(pauseDemo()));
    connect(stopButton, SIGNAL(clicked(bool)), this, SLOT(stopDemo()));
    connect(resetButton, SIGNAL(clicked(bool)), screen, SLOT(resetCamera()));
    connect(selectModeButton, SIGNAL(clicked(bool)), this, SLOT(selectOrLinkMode()));
    connect(linkModeButton, SIGNAL(clicked(bool)), this, SLOT(selectOrLinkMode()));
    connect(eraseLinks, SIGNAL(clicked(bool)), screen, SLOT(resetLinkedMarkersIndexes()));
    connect(screen, SIGNAL(markerPicked(int, int)), this, SLOT(fillWindowCoordinates(int, int)));
    connect(coordinatesWindow, SIGNAL(lineRemoved(int)), screen, SLOT(removePickedIndex(int)));
    connect(formerSteps, SIGNAL(clicked(bool)), this, SLOT(enableDisplayFormerSteps()));
    connect(numberOfFormerSteps, SIGNAL(currentIndexChanged(int)), screen, SLOT(setNumberOfFormerStepsDisplayed(int)));
    connect(formerStepsLine, SIGNAL(toggled(bool)), this, SLOT(choosePointsLinesFormerSteps()));
    connect(formerStepsPoints, SIGNAL(toggled(bool)), this, SLOT(choosePointsLinesFormerSteps()));
    connect(furtherSteps, SIGNAL(clicked(bool)), this, SLOT(enableDisplayFurtherSteps()));
    connect(numberOfFurtherSteps, SIGNAL(currentIndexChanged(int)), screen, SLOT(setNumberOfFurtherStepsDisplayed(int)));

    connect(displayChoice1,SIGNAL(toggled(bool)),this,SLOT(changeChoice1()));
    connect(displayChoice2,SIGNAL(toggled(bool)),this,SLOT(changeChoice2()));
    connect(displayFileCoordinates,SIGNAL(clicked(bool)),this,SLOT(displayFile()));
    screen->setData(data.getDataCoordinates());

    //screen->setCoordinates(data.get1Vector(0));
    slider->setMinimum(0);
    slider->setMaximum(data.getDataCoordinatesSize() - 1);
    for(int i = 0 ; i < data.getDataCoordinatesSize() ; i++) {
        numberOfFormerSteps->addItem(QString::number(i));
        numberOfFurtherSteps->addItem(QString::number(i));
    }
    numberOfFormerSteps->setCurrentIndex(10);
    //screen->setNumberOfFormerStepsDisplayed(10);
    numberOfFurtherSteps->setCurrentIndex(10);

    filewindow=new FileWindow;

    show();
    coordinatesWindow->show();
}

/** Method that initializes the screen.
 * @brief ProgramWindow::configureScreen
 */

void ProgramWindow::configureScreen() {
    screen->setViewPort();
    screen->setProjection();
    screen->setModelView();
}

/** Method that changes the step of the view.
 * @brief ProgramWindow::changeStep
 * @param index
 */


void ProgramWindow::changeStep(int index) {
    //screen->setCoordinates(data.get1Vector(index));
    screen->setCurrentStep(index);
    label->setText("Step number : " + QString::number(index + 1));
    updateWindowCoordinates();
    //calls paintGL
    screen->update();
}

void ProgramWindow::fillWindowCoordinates(int index, int color) {
    coordinatesWindow->addLineCoordinates(data.get1Marker(slider->value(), index), color);
}

void ProgramWindow::updateWindowCoordinates() {
    QVector<Marker> markerVector;
    for(auto index : screen->getSelectedMarkerIndexes()) {
        markerVector.append(data.get1Marker(slider->value(), index));
    }
    coordinatesWindow->updateCoordinates(markerVector);
}


/** Method that manages the demo playing.
 * @brief ProgramWindow::demoPlaying
 */

void ProgramWindow::demoPlaying() {
    slider->setValue(slider->value() + 1);
    if(slider->value() == slider->maximum()) {
        stopDemo();
    }
}

/** Method that pauses the demo.
 * @brief ProgramWindow::pauseDemo
 */

void ProgramWindow::pauseDemo() {
    emit stopTimer();
    delete timer;
    demoButton->setEnabled(true);
    pauseButton->setDisabled(true);
}

/** Method that starts the demo.
 * @brief ProgramWindow::startDemo
 */

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

/** Method that stops the demo.
 * @brief ProgramWindow::stopDemo
 */

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

void ProgramWindow::changeChoice1(){
   choice="choice1";
}
void ProgramWindow::changeChoice2(){
    choice="choice2";
}

void ProgramWindow::displayFile(){
    qDebug() << "displayFile";
    const char* myChar = choice.toStdString().c_str();
    if(strcmp(myChar,"choice1")==0){
      filewindow->setViewMrHolt();
        filewindow->show();
        /*QWidget *w=new QWidget();
        w->show();*/
    }
    else if(strcmp(myChar,"choice2")==0){
        filewindow->setViewMrNilsen();
        filewindow->show();

    }
}

void ProgramWindow::selectOrLinkMode() {
    if(sender() == (QObject*)selectModeButton) {
        if(selectModeButton->isChecked()) {
            screen->setSelectMarkerMode(true);
            screen->setLinkMarkerMode(false);
            linkModeButton->setChecked(false);
        }
        else {
            screen->setSelectMarkerMode(false);
        }
    }
    else {
        if(linkModeButton->isChecked()) {
            screen->setLinkMarkerMode(true);
            screen->setSelectMarkerMode(false);
            selectModeButton->setChecked(false);
        }
        else {
            screen->setLinkMarkerMode(false);
        }
    }
}

void ProgramWindow::enableDisplayFormerSteps() {
    if(formerSteps->isChecked()) {
        screen->setDisplayFormerSteps(true);
    }
    else {
        screen->setDisplayFormerSteps(false);
    }
}

void ProgramWindow::choosePointsLinesFormerSteps() {
     if(sender() == (QObject*)formerStepsPoints) {
         screen->setFormerStepsPoints(true);
     }
     else {
         screen->setFormerStepsPoints(false);
     }
}

void ProgramWindow::enableDisplayFurtherSteps() {
    if(furtherSteps->isChecked()) {
        screen->setDisplayFurtherSteps(true);
    }
    else {
        screen->setDisplayFurtherSteps(false);
    }
}

void ProgramWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Enter) {
        data.swapMarkersData(screen->getMarkersToBeSwaped(), slider->value());
        std::cout << "Program marker 1 red =" << data.get1Marker(slider->value(),screen->getMarkersToBeSwaped().at(0)).getRedId() << std::endl;
    }
    screen->update();
}
