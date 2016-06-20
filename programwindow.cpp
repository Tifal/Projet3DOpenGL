#include "programwindow.h"

/** Constructor to initialize and create the content of the window.
 * @brief ProgramWindow::ProgramWindow
 */
static QString choice="choice1";

ProgramWindow::ProgramWindow() : QWidget()
{
    setMinimumSize(800, 800);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowTitle("Test");

    slider = new QSlider(Qt::Orientation::Horizontal, this);
    screen = new DisplayWindow(this);

    label = new QLabel("Step number : 1", this);
    label->setAlignment(Qt::AlignCenter);
    label->setMaximumHeight(30);

    swapLabel = new QLabel("Numbers of furthers steps to be swapped",this);

    demoButton = new QPushButton("Start demo", this);
    demoButton->setIcon(QIcon("icons/Gtk-media-play-ltr.svg"));
    stopButton = new QPushButton("Stop", this);
    stopButton->setIcon(QIcon("icons/Gtk-media-stop.svg"));
    pauseButton = new QPushButton("Pause", this);
    pauseButton->setIcon(QIcon("icons/Fairytale_player_pause.svg"));
    pauseButton->setDisabled(true);
    stopButton->setDisabled(true);
    stepForward = new QPushButton(this);
    stepForward->setIcon(QIcon("icons/forward.png"));
    stepBackward = new QPushButton(this);
    stepBackward->setIcon(QIcon("icons/backward.png"));

    coordinatesWindow = new CoordinatesWindow;
    swapWindow = new SwapWindow;

    resetButton = new QPushButton("Reset Camera", this);

    displayFileCoordinates=new QPushButton("Display file coordinates",this);
    displayChoice1=new QRadioButton("Rows = Timesteps / Columns = Markers",this);
    displayChoice2=new QRadioButton("Rows = Markers / Columns = Timesteps",this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(screen, 0, 0, 1, 5);
    layout->addWidget(label,1,0,1,5);
    layout->addWidget(slider,2,0,1,5);
    layout->addWidget(demoButton,3,0);
    layout->addWidget(pauseButton,3,1);
    layout->addWidget(stopButton,3,2);
    layout->addWidget(stepBackward, 3, 3);
    layout->addWidget(stepForward, 3, 4);

    frontSideCamera = new QPushButton("front side", this);
    backSideCamera = new QPushButton("back side", this);
    leftSideCamera = new QPushButton("left side", this);
    rightSideCamera = new QPushButton("right side", this);
    selectModeButton = new QPushButton("select markers",this);
    linkModeButton = new QPushButton("link markers",this);
    displayLinksButton = new QCheckBox("display links", this);
    eraseOneLinkButton = new QPushButton("erase one link", this);
    eraseLinks = new QPushButton("erase all links", this);
    saveSkeletonButton = new QPushButton("save skeleton", this);
    formerSteps = new QPushButton("display former steps", this);
    swapMarkersButton = new QPushButton("swap markers", this);
    swapModeButton = new QPushButton("swap mode", this);
    numberOfFormerSteps = new QComboBox(this);
    displayFormerStepsSelectedMarkers = new QCheckBox("display for selected markers only", this);
    formerStepsLine = new QRadioButton("lines", this);
    formerStepsPoints = new QRadioButton("points", this);
    formerStepsLine->setChecked(true);
    furtherSteps = new QPushButton("display further steps", this);
    //numberOfFurtherSteps = new QComboBox(this);
    numberOfSwapedSteps = new QComboBox(this);

    selectModeButton->setCheckable(true);
    linkModeButton->setCheckable(true);
    eraseOneLinkButton->setCheckable(true);
    displayLinksButton->setCheckable(true);
    displayLinksButton->setChecked(true);
    formerSteps->setCheckable(true);
    furtherSteps->setCheckable(true);
    swapModeButton->setCheckable(true);

    setLayout(layout);

    slider->setMinimum(0);
    numberOfFormerSteps->setCurrentIndex(0);
    numberOfSwapedSteps->setCurrentIndex(0);

    filewindow=new FileWindow;

    /*
     * QTabWidget
     */
    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->setMaximumHeight(250);

    QWidget *cameraTab = new QWidget(tabWidget);
    QGridLayout *cameraTabLayout = new QGridLayout(cameraTab);
    cameraTabLayout->addWidget(resetButton,2,1);
    cameraTabLayout->addWidget(backSideCamera,1,1);
    cameraTabLayout->addWidget(leftSideCamera, 2, 0);
    cameraTabLayout->addWidget(rightSideCamera, 2, 2);
    cameraTabLayout->addWidget(frontSideCamera, 3, 1);
    cameraTab->setLayout(cameraTabLayout);

    QWidget *fileTab = new QWidget(tabWidget);
    QGridLayout *fileTabLayout = new QGridLayout(fileTab);

    fileTabLayout->addWidget(displayFileCoordinates,5,1,2,2);
    fileTabLayout->addWidget(displayChoice1,5,0);
    fileTabLayout->addWidget(displayChoice2,6,0);
    fileTab->setLayout(fileTabLayout);

    QWidget *selectionTab = new QWidget(tabWidget);
    QVBoxLayout *selectionTabLayout = new QVBoxLayout(selectionTab);
    selectionTabLayout->addWidget(selectModeButton);
    //selectionTabLayout->addWidget(coordinatesWindow);
    QScrollArea *scrollAreaSelection = new QScrollArea(selectionTab);
    scrollAreaSelection->setGeometry(500, 500, 600, 400);
    scrollAreaSelection->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    scrollAreaSelection->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scrollAreaSelection->setWidgetResizable(true);
    scrollAreaSelection->setWidget(coordinatesWindow);
    selectionTabLayout->addWidget(scrollAreaSelection);
    selectionTab->setLayout(selectionTabLayout);

    QWidget *linkTab = new QWidget(tabWidget);
    QGridLayout *linkTabLayout = new QGridLayout(linkTab);
    linkTabLayout->addWidget(linkModeButton, 0, 0);
    linkTabLayout->addWidget(displayLinksButton, 0, 1);
    linkTabLayout->addWidget(eraseOneLinkButton, 0, 2);
    linkTabLayout->addWidget(eraseLinks, 0, 3);
    linkTabLayout->addWidget(saveSkeletonButton, 1, 0);
    linkTab->setLayout(linkTabLayout);

    QWidget *formerFurtherStepsTab = new QWidget(tabWidget);
    QGridLayout *formerFurtherStepsTabLayout = new QGridLayout(formerFurtherStepsTab);
    formerFurtherStepsTabLayout->addWidget(formerSteps, 0, 0);
    formerFurtherStepsTabLayout->addWidget(numberOfFormerSteps, 0, 1);
    formerFurtherStepsTabLayout->addWidget(displayFormerStepsSelectedMarkers, 0, 2);
    formerFurtherStepsTabLayout->addWidget(formerStepsLine, 0, 3);
    formerFurtherStepsTabLayout->addWidget(formerStepsPoints, 0, 4);
    formerFurtherStepsTabLayout->addWidget(furtherSteps, 1, 0);
    //formerFurtherStepsTabLayout->addWidget(numberOfFurtherSteps, 1, 1);
    formerFurtherStepsTab->setLayout(formerFurtherStepsTabLayout);

    QWidget *swappingTab = new QWidget(tabWidget);
    QGridLayout *swappingTabLayout = new QGridLayout(swappingTab);
    swappingTabLayout->addWidget(swapModeButton,0, 0);
    swappingTabLayout->addWidget(swapLabel,0,1);
    swappingTabLayout->addWidget(numberOfSwapedSteps,0,2);
    swappingTabLayout->addWidget(swapMarkersButton, 0, 3);
    QScrollArea *scrollAreaSwapping = new QScrollArea(swappingTab);
    scrollAreaSwapping->setGeometry(500, 500, 600, 400);
    scrollAreaSwapping->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scrollAreaSwapping->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    scrollAreaSwapping->setWidgetResizable(true);
    scrollAreaSwapping->setWidget(swapWindow);
    swappingTabLayout->addWidget(scrollAreaSwapping, 1, 0, 1, 4);
    swappingTab->setLayout(swappingTabLayout);

    tabWidget->addTab(cameraTab, "Camera");
    tabWidget->addTab(fileTab, "File");
    tabWidget->addTab(selectionTab, "Selection");
    tabWidget->addTab(linkTab, "Link");
    tabWidget->addTab(formerFurtherStepsTab, "Former/Further Steps");
    tabWidget->addTab(swappingTab, "Swapping");
    layout->addWidget(tabWidget, 4, 0, 1, 5);

    /*
     *
     */
    show();
    configureScreen();
}

ProgramWindow::ProgramWindow(QString fileName) : ProgramWindow() {
    setData(fileName);
    connectWidgets();
}

/** Method that initializes the screen.
 * @brief ProgramWindow::configureScreen
 */

void ProgramWindow::configureScreen() {
    screen->setViewPort();
    screen->setProjection();
    screen->setModelView();
}

void ProgramWindow::setData(QString fileName) {
    data.loadData(fileName);
    screen->setData(&data);
    swapWindow->setData(&data);
    coordinatesWindow->setData(&data);
    slider->setMaximum(data.getDataCoordinatesSize() - 1);
    for(int i = 0 ; i < data.getDataCoordinatesSize() ; i++) {
        numberOfFormerSteps->addItem(QString::number(i));
        numberOfSwapedSteps->addItem(QString::number(i));
    }
    //connectWidgets();
}

void ProgramWindow::connectWidgets() {
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeStep(int)));
    connect(demoButton, SIGNAL(clicked(bool)), this, SLOT(startDemo()));
    connect(pauseButton, SIGNAL(clicked(bool)), this, SLOT(pauseDemo()));
    connect(stopButton, SIGNAL(clicked(bool)), this, SLOT(stopDemo()));
    connect(stepBackward, SIGNAL(pressed()), this, SLOT(decrementSlider()));
    connect(stepForward, SIGNAL(pressed()), this, SLOT(incrementSlider()));
    connect(resetButton, SIGNAL(clicked(bool)), screen, SLOT(resetCamera()));
    connect(frontSideCamera, SIGNAL(clicked(bool)), screen, SLOT(moveCameraToFrontSide()));
    connect(backSideCamera, SIGNAL(clicked(bool)), screen, SLOT(moveCameraToBackSide()));
    connect(leftSideCamera, SIGNAL(clicked(bool)), screen, SLOT(moveCameraToLeftSide()));
    connect(rightSideCamera, SIGNAL(clicked(bool)), screen, SLOT(moveCameraToRightSide()));
    connect(selectModeButton, SIGNAL(clicked(bool)), this, SLOT(pickMode()));
    connect(linkModeButton, SIGNAL(clicked(bool)), this, SLOT(pickMode()));
    connect(eraseOneLinkButton, SIGNAL(clicked(bool)), this, SLOT(pickMode()));
    connect(swapModeButton, SIGNAL(clicked(bool)), this, SLOT(pickMode()));
    connect(displayLinksButton, SIGNAL(clicked(bool)), this, SLOT(enableDisplayLinks()));
    connect(eraseLinks, SIGNAL(clicked(bool)), screen, SLOT(resetLinkedMarkersIndexes()));
    connect(saveSkeletonButton, SIGNAL(clicked(bool)), this, SLOT(saveSkeleton()));
    connect(screen, SIGNAL(markerPicked(int, int)), this, SLOT(fillCoordinatesSwapWindows(int, int)));
    connect(coordinatesWindow, SIGNAL(lineRemoved(int)), screen, SLOT(removePickedIndex(int)));
    connect(formerSteps, SIGNAL(clicked(bool)), this, SLOT(enableDisplayFormerSteps()));
    connect(numberOfFormerSteps, SIGNAL(currentIndexChanged(int)), screen, SLOT(setNumberOfFormerStepsDisplayed(int)));
    connect(displayFormerStepsSelectedMarkers, SIGNAL(clicked(bool)), this, SLOT(enableDisplayFormerStepsSelectedMarkers()));
    connect(formerStepsLine, SIGNAL(toggled(bool)), this, SLOT(choosePointsLinesFormerSteps()));
    connect(formerStepsPoints, SIGNAL(toggled(bool)), this, SLOT(choosePointsLinesFormerSteps()));
    connect(furtherSteps, SIGNAL(clicked(bool)), this, SLOT(enableDisplayFurtherSteps()));
    connect(numberOfSwapedSteps, SIGNAL(currentIndexChanged(int)), screen, SLOT(setNumberOfFurtherStepsDisplayed(int)));
    connect(swapMarkersButton, SIGNAL(clicked(bool)), this, SLOT(swapMarkers()));
    connect(numberOfSwapedSteps, SIGNAL(currentIndexChanged(int)), swapWindow, SLOT(setNumberOfFurtherSteps(int)));
    connect(displayChoice1,SIGNAL(toggled(bool)),this,SLOT(changeChoice1()));
    connect(displayChoice2,SIGNAL(toggled(bool)),this,SLOT(changeChoice2()));
    connect(displayFileCoordinates,SIGNAL(clicked(bool)),this,SLOT(displayFile()));
    connect(screen, SIGNAL(markerToBeSwappedPicked(int,int,int)), swapWindow, SLOT(addSelectedMarker(int,int,int)));
    connect(screen, SIGNAL(removeMarkerToBeSwapped(int)), swapWindow, SLOT(removeSelectedMarker(int)));
    connect(screen, SIGNAL(changeColorMarkerToBeSwapped(int,int)), swapWindow, SLOT(changeMarkerColorToBeSwapped(int,int)));
}

/** Method that changes the step of the view.
 * @brief ProgramWindow::changeStep
 * @param index
 */

void ProgramWindow::changeStep(int index) {
    screen->setCurrentStep(index);
    label->setText("Step number : " + QString::number(index + 1));
    swapWindow->setCurrentStep(index);
    coordinatesWindow->setCurrentStep(index);
    //updateWindowCoordinates();
    /*if(numberOfSwapedSteps->count()>data.getDataCoordinatesSize()-slider->value()){
        while(numberOfSwapedSteps->count()>data.getDataCoordinatesSize()-slider->value()){
           numberOfSwapedSteps->removeItem(numberOfSwapedSteps->count()-1);
        }
    }
    else if(numberOfSwapedSteps->count()<data.getDataCoordinatesSize()-slider->value()){
        while(numberOfSwapedSteps->count()<data.getDataCoordinatesSize()-slider->value()){
            numberOfSwapedSteps->addItem(QString::number(numberOfSwapedSteps->count()));
        }
    }*/
    //swapWindow->updateCoordinates();

    screen->update();
}

void ProgramWindow::keyPressEvent(QKeyEvent *event) {
    setFocus();
    if(event->key() == Qt::Key_Left) {
        slider->setValue(slider->value() - 1);
    }
    if(event->key() == Qt::Key_Right) {
        slider->setValue(slider->value() + 1);
    }
}

void ProgramWindow::fillCoordinatesSwapWindows(int index, int color) {
    coordinatesWindow->addLineCoordinates(index, color);
    //swapWindow->addSelectedMarker(index, color);
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

void ProgramWindow::incrementSlider() {
    slider->setValue(slider->value() + 1);
}

void ProgramWindow::decrementSlider() {
    slider->setValue(slider->value() - 1);
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

void ProgramWindow::pickMode() {
    if(sender() == (QObject*)selectModeButton) {
        if(selectModeButton->isChecked()) {
            screen->setSelectMarkerMode(true);
            screen->setLinkMarkerMode(false);
            screen->setEraseOneLinkMode(false);
            screen->setSwapMode(false);
            linkModeButton->setChecked(false);
            eraseOneLinkButton->setChecked(false);
            swapModeButton->setChecked(false);
        }
        else {
            screen->setSelectMarkerMode(false);
        }
    }
    else if(sender() == (QObject*)linkModeButton) {
        if(linkModeButton->isChecked()) {
            screen->setLinkMarkerMode(true);
            screen->setSelectMarkerMode(false);
            screen->setEraseOneLinkMode(false);
            screen->setSwapMode(false);
            selectModeButton->setChecked(false);
            eraseOneLinkButton->setChecked(false);
            swapModeButton->setChecked(false);
        }
        else {
            screen->setLinkMarkerMode(false);
        }
    }
    else if(sender() == (QObject*)eraseOneLinkButton) {
        if(eraseOneLinkButton->isChecked()) {
            screen->setEraseOneLinkMode(true);
            screen->setSelectMarkerMode(false);
            screen->setLinkMarkerMode(false);
            screen->setSwapMode(false);
            selectModeButton->setChecked(false);
            linkModeButton->setChecked(false);
            swapModeButton->setChecked(false);
        }
        else {
            screen->setEraseOneLinkMode(false);
        }
    }
    else if(sender() == (QObject*)swapModeButton){
        if(swapModeButton->isChecked()) {
            screen->setSwapMode(true);
            screen->setSelectMarkerMode(false);
            screen->setLinkMarkerMode(false);
            screen->setEraseOneLinkMode(false);
            selectModeButton->setChecked(false);
            linkModeButton->setChecked(false);
            eraseOneLinkButton->setChecked(false);
        }
        else {
            screen->setSwapMode(false);
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

void ProgramWindow::enableDisplayLinks() {
    if(displayLinksButton->isChecked()) {
        screen->setDisplayLinks(true);
    }
    else {
        screen->setDisplayLinks(false);
    }
}

void ProgramWindow::enableDisplayFormerStepsSelectedMarkers() {
    if(displayFormerStepsSelectedMarkers->isChecked()) {
        screen->setFormerStepsSelectedMarkers(true);
    }
    else {
        screen->setFormerStepsSelectedMarkers(false);
    }
}

void ProgramWindow::saveSkeleton() {
    data.saveDataSkeleton(screen->getLinkedMarkersIndexes());
}

void ProgramWindow::swapMarkers() {
    std::array<int, 2> markersToBeSwapped = screen->getMarkersToBeSwaped();
    std::array<int, 2> selectedMarkersToBeSwapped;
    int numberOfStepsToBeSwapped = swapWindow->getNumberOfFurtherStepsToUpdate();
    selectedMarkersToBeSwapped[0] = screen->getSelectedMarkerIndexes().indexOf(screen->getMarkersToBeSwaped().at(0));
    selectedMarkersToBeSwapped[1] = screen->getSelectedMarkerIndexes().indexOf(screen->getMarkersToBeSwaped().at(1));
    if(markersToBeSwapped[0] != -1 && markersToBeSwapped[1] != -1) {
        for(int i = 0 ; i <= numberOfStepsToBeSwapped ; i++) {
            data.swapMarkersData(markersToBeSwapped, slider->value() + i);
            swapWindow->updateCoordinates();
        }
        if(selectedMarkersToBeSwapped[0] != -1 && selectedMarkersToBeSwapped[1] != -1) {
            coordinatesWindow->swapCoordinates(selectedMarkersToBeSwapped);
        }
        screen->update();
    }
}
