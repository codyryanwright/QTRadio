// Name: Cody Wright
// Date: 
// Citation: 

 #include <QtGui>
 #include "globj.h"
 #include "mainwindow.h"

 MainWindow::MainWindow()
 {
     QWidget *radio = new QWidget;
     radio->setMinimumWidth(250);
     radio->setMaximumWidth(250);
     radio->setMinimumHeight(600);
     radio->setMaximumHeight(600);
     radio->setWindowTitle("Radio");

     amSpinBox = new QSpinBox;
     amSpinBox->setRange(540, 1600);
     amSpinBox->setSingleStep(10);
     amSpinBox->setSuffix(" AM");

     QDoubleSpinBox *fmSpinBox = new QDoubleSpinBox;
     fmSpinBox->setRange(88.1, 107.9);
     fmSpinBox->setDecimals(1);
     fmSpinBox->setSingleStep(.2);
     fmSpinBox->setSuffix(" FM");

     QRadioButton *amRadioButton = new QRadioButton("AM");
     QRadioButton *fmRadioButton = new QRadioButton("FM");

     // Bass
     QSlider *bassSlider = new QSlider(Qt::Vertical);
     bassSlider->setRange(0, 100);
     bassSlider->setMinimumHeight(100);
     bassSlider->setMaximumHeight(100);
     QSpinBox *bassSpinBox = new QSpinBox();
     bassSpinBox->setMaximum(100);
     QObject::connect(bassSpinBox, SIGNAL(valueChanged(int)), bassSlider, SLOT(setValue(int)));
     QObject::connect(bassSlider, SIGNAL(valueChanged(int)), bassSpinBox, SLOT(setValue(int)));
     QLabel *bassLabel = new QLabel("Bass");

     // Treble
     QSlider *trebleSlider = new QSlider(Qt::Vertical);
     trebleSlider->setRange(0, 100);
     trebleSlider->setMinimumHeight(100);
     trebleSlider->setMaximumHeight(100);
     QSpinBox *trebleSpinBox = new QSpinBox();
     trebleSpinBox->setMaximum(100);
     QObject::connect(trebleSpinBox, SIGNAL(valueChanged(int)), trebleSlider, SLOT(setValue(int)));
     QObject::connect(trebleSlider, SIGNAL(valueChanged(int)), trebleSpinBox, SLOT(setValue(int)));
     QLabel *trebleLabel = new QLabel("Treble");

     // Volume
     volumeDial = new QDial();
     volumeDial->setRange(0, 100);
     QLCDNumber *volumeLCD = new QLCDNumber();
     volumeLCD->setSegmentStyle(QLCDNumber::Flat);
     QObject::connect(volumeDial, SIGNAL(valueChanged(int)), volumeLCD, SLOT(display(int)));
     QLabel *volumeLabel = new QLabel("Volume");
     
     // Exit
     QPushButton *exitButton = new QPushButton("Exit");
     connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));

     QGridLayout *layout = new QGridLayout;
     layout->addWidget(amSpinBox, 0, 0);
     layout->addWidget(fmSpinBox, 0, 1);
     layout->addWidget(amRadioButton, 1, 0);
     layout->addWidget(fmRadioButton, 1, 1);
     layout->addWidget(bassSlider, 2, 0);
     layout->addWidget(trebleSlider, 2, 1);
     layout->addWidget(bassSpinBox, 3, 0);
     layout->addWidget(trebleSpinBox, 3, 1);
     layout->addWidget(bassLabel, 4, 0);
     layout->addWidget(trebleLabel, 4, 1);
     layout->addWidget(volumeDial, 5, 0);
     layout->addWidget(volumeLCD, 6, 0);
     layout->addWidget(volumeLabel, 7, 0);
     layout->addWidget(exitButton, 7, 1);
     radio->setLayout(layout);
     radio->show();
     
     setCentralWidget(radio);
     
     createActions();
     createMenus();
     createStatusBar();
     createDockWindows();

     setWindowTitle(tr("Radio"));
     
     setUnifiedTitleAndToolBarOnMac(true);
 }

void MainWindow::open()
 {
     QString fileName = QFileDialog::getOpenFileName(this);
     delete function;
     function = new GLobj(0, 2);
     function->setFileName(fileName.toStdString());
     layout->addWidget(function, 1, 1);
 }

 void MainWindow::about()
 {
    QMessageBox::about(this, tr("About I4"),
             tr("Demostration of a radio with graphics."));
 }

 void MainWindow::createActions()
 {
     openAct = new QAction(tr("&Open"), this);
     openAct->setShortcuts(QKeySequence::Open);
     openAct->setStatusTip(tr("Open an existing file"));
     connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

     quitAct = new QAction(tr("&Quit"), this);
     quitAct->setShortcuts(QKeySequence::Quit);
     quitAct->setStatusTip(tr("Quit the application"));
     connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

     aboutAct = new QAction(tr("&About"), this);
     aboutAct->setStatusTip(tr("Show the application's About box"));
     connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

     aboutQtAct = new QAction(tr("About &Qt"), this);
     aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
     connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
 }

 void MainWindow::createMenus()
 {
     fileMenu = menuBar()->addMenu(tr("&File"));
     fileMenu->addAction(openAct);
     fileMenu->addSeparator();
     fileMenu->addAction(quitAct);
     viewMenu = menuBar()->addMenu(tr("&View"));
     menuBar()->addSeparator();
     helpMenu = menuBar()->addMenu(tr("&Help"));
     helpMenu->addAction(aboutAct);
     helpMenu->addAction(aboutQtAct);
 }

 void MainWindow::createStatusBar()
 {
     statusBar()->showMessage(tr("Ready"));
 }

 void MainWindow::setCurrentFile(const QString &fileName)
 {
     curFile = fileName;
     textEdit->document()->setModified(false);
     setWindowModified(false);

     QString shownName = curFile;
     if (curFile.isEmpty())
         shownName = "untitled.txt";
     setWindowFilePath(shownName);
 }


 void MainWindow::createDockWindows()
 {
     QDockWidget *dock = new QDockWidget(tr("Graphics"), this);
     dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
     dock->setMinimumWidth(750);
     
     QWidget *multiWidget = new QWidget();
     layout = new QGridLayout();
     
     shapes = new GLobj(0, 1);
     wave = new GLobj(0, 4);
     wave->setFreq(amSpinBox->value());
     wave->setAmp(volumeDial->value());
     QObject::connect(volumeDial, SIGNAL(valueChanged(int)), wave, SLOT(redrawAmp(int)));
     QObject::connect(amSpinBox, SIGNAL(valueChanged(int)), wave, SLOT(redrawFreq(int)));
     fractal = new GLobj(0, 3);
     function = new GLobj(0, 2);

     shapes->QWidget::setMinimumSize(375, 300);
     wave->QWidget::setMinimumSize(375, 300);
     fractal->QWidget::setMinimumSize(375, 300);
     function->QWidget::setMinimumSize(375, 300);
     shapes->QWidget::setMaximumSize(375, 300);
     wave->QWidget::setMaximumSize(375, 300);
     fractal->QWidget::setMaximumSize(375, 300);
     function->QWidget::setMaximumSize(375, 300);
     
     layout->addWidget(shapes, 0, 0);
     layout->addWidget(wave, 0, 1);
     layout->addWidget(fractal, 1, 0);
     layout->addWidget(function, 1, 1);
     
     multiWidget->setLayout(layout);
     
     dock->setWidget(multiWidget);
     addDockWidget(Qt::RightDockWidgetArea, dock);
     viewMenu->addAction(dock->toggleViewAction());
 }
