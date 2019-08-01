#ifndef GLobj_H
#define GLobj_H

#include <QtOpenGL/QGLWidget>
#include <QtGui>
#include <string>
#include <QObject>

class GLobj : public QGLWidget  {
    Q_OBJECT

public:
    GLobj(QWidget *parent = 0, int scene = 1);
    ~GLobj();
    void drawShapes();
    void drawFractal(float x, float y, int count, int max);
    void drawWave(int a, int f);
    void drawFunction();
    void setAmp(int amp);
    void setFreq(int freq);
    void setFileName(std::string fileName);

    int scene;
    int A; // amplitude of volume
    int f; // frequency of station
    std::string fileName;

public slots:
    void redrawAmp(int value);
    void redrawFreq(int value);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void ngon(int n);
    void resize(int x, int y);
    void display(void);
    void reshape(int w, int h);
    void exit(int);
};

#endif
