 #ifndef MAINWINDOW_H
 #define MAINWINDOW_H

 #include <QtGui>
 #include <string>

 class QAction;
 class QMenu;
 class QTextEdit;
 class GLobj;

 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();
     GLobj *shapes;
     GLobj *wave;
     GLobj *fractal;
     GLobj *function;
     QTextEdit* textEdit;
     QSpinBox *amSpinBox;
     QDial *volumeDial;
     QGridLayout *layout;

 private slots:
     void open();
     void about();
     void setCurrentFile(const QString&);

 private:
     void createActions();
     void createMenus();
     void createStatusBar();
     void createDockWindows();
     
     QString curFile;
     QMenu *fileMenu;
     QMenu *editMenu;
     QMenu *viewMenu;
     QMenu *helpMenu;
     QAction *openAct;
     QAction *aboutAct;
     QAction *aboutQtAct;
     QAction *quitAct;
 };

 #endif
