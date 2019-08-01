 #include <QApplication>
 #include <QDesktopWidget>
 #include "mainwindow.h"

 int main(int argc, char *argv[])
 {
     QApplication app(argc, argv);
     MainWindow mainWin;
     mainWin.resize(1000, 600);
     mainWin.show();
     return app.exec();
 }
