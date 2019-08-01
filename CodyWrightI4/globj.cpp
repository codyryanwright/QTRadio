// Name: Cody Wright
// Date: 7/2/2019
// Comment: Accumulated the sources from previous assignments.

#include <QtGui/QtGui>
#include <QtOpenGL/QtOpenGL>
#include <QObject>
#include <math.h>
#include "globj.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <fstream>

#define PI (3.141592653589793)

GLobj::GLobj(QWidget *parent, int scene)
    : QGLWidget(parent)
{
  this->scene = scene;
  
  // Set defaults
  setAmp(1);
  setFreq(1);
  setFileName("");
}

GLobj::~GLobj()
{
 
}

void GLobj::setAmp(int amp)
{
  A = amp; // One-letter name for mathematical variable
}

void GLobj::setFreq(int freq)
{
  f = freq;
}

void GLobj::setFileName(std::string fileName)
{
  this->fileName = fileName;
}

//Initialize the GL settings
void GLobj::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

//Set up the viewport based on the screen dimentions
//Function is called implicitly by initializeGL and when screen is resized
void GLobj::resizeGL( int w, int h )
{
    //algorithm to keep scene "square" (preserve aspect ratio)
    //even if screen is streached

    glViewport(0, 0, w, h);

    //setup the projection and switch to model view for transformations


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(scene == 1)
    {
    //  gluPerspective(45, 1.0f, 1.0f, 1.0f);
      glFrustum(-1.0, 1.0, -1.0, 1.0, 0.0, 100.0);
    }
    else
      glOrtho(-1, 1, -1, 1, -1, 1);
    
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //implicit call to paintGL after resized
}

//Paints the GL scene
void GLobj::paintGL()
{ 

  glClear (GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  
  if (scene == 1)
  {
    drawShapes();
  }
  else if (scene == 2)
  {
    drawFunction();
  }
  else if (scene == 3)
  {
      float x = 1.0f, y = 1.0f;
      int count = 0, max = 5;
      
      drawFractal(x, y, count, max);
  }
  else if (scene == 4)
  {
    drawWave(1, 1);
  }
  
  glFlush();
}

void GLobj::drawShapes()
{  
  float radius = 0.3;

  glPointSize(4);
  glLineWidth(4);
  
  glTranslatef(0.0f, 0.0f, 0.0f);
  glRotatef(20.0f, 1.0f, 1.0f, 1.0f);
  glTranslatef(0.5f, 0.0f, -0.5f);
    
  // Draw color cube with 6 quads
  glBegin(GL_QUADS);                
    // Top face (y = radius)
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f( radius, radius, -radius);
    glVertex3f(-radius, radius, -radius);
    glVertex3f(-radius, radius,  radius);
    glVertex3f( radius, radius,  radius);

    // Bottom face (y = -radius)
    glColor3f(1.0f, 0.0f, 0.0f);     // Red 
    glVertex3f( radius, -radius,  radius);
    glVertex3f(-radius, -radius,  radius);
    glVertex3f(-radius, -radius, -radius);
    glVertex3f( radius, -radius, -radius);

    // Front face  (z = radius)
    glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
    glVertex3f( radius,  radius, radius);
    glVertex3f(-radius,  radius, radius);
    glVertex3f(-radius, -radius, radius);
    glVertex3f( radius, -radius, radius);

    // Back face (z = -radius)
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f( radius, -radius, -radius);
    glVertex3f(-radius, -radius, -radius);
    glVertex3f(-radius,  radius, -radius);
    glVertex3f( radius,  radius, -radius);

    // Left face (x = -radius)
    glColor3f(1.0f, 0.5f, 0.0f);     // Orange
    glVertex3f(-radius,  radius,  radius);
    glVertex3f(-radius,  radius, -radius);
    glVertex3f(-radius, -radius, -radius);
    glVertex3f(-radius, -radius,  radius);

    // Right face (x = radius)
    glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
    glVertex3f(radius,  radius, -radius);
    glVertex3f(radius,  radius,  radius);
    glVertex3f(radius, -radius,  radius);
    glVertex3f(radius, -radius, -radius);
  glEnd();  // End of drawing color-cube

  glLoadIdentity();
  glScalef(1.01f, 1.01f, 1.0f);
  
  //Draw Point
  glBegin(GL_POINTS);
    glColor3f(0.8f, 0.0f, 1.0f);
    glVertex2f(-.70f, .70f);
  glEnd();

  glLoadIdentity();
  glScalef(1.01f, 1.01f, 1.0f);
  
  // Draw a Line
  glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.9f, 0.9f);
    glVertex2f(-0.9f, -0.5f);
  glEnd();

  glLoadIdentity();
  glRotatef(10.0, 0.0, 0.0, 1.0);
  
  // Draw a Line Strip
  glBegin(GL_LINE_STRIP);
    glColor3f(0.5f, 0.2f, 0.1f);
    glVertex2f(0.0f, -0.6f);
    glVertex2f(-0.2f, -0.4f);
    glVertex2f(0.0f, -0.2f);
  glEnd();

  glLoadIdentity();
  glTranslatef(1.5f, 1.5f, 0.0f);
  
  // Draw triangle
  glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(-0.9f, -0.9f);
    glVertex2f(-0.5f, -0.9f);
    glVertex2f(-0.7f, -0.5);
  glEnd();

  glLoadIdentity();
  glScalef(1.5f, 1.5f, 0.0f);

  // Draw a square
  glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5, 0.2f);
    glVertex2f(-0.2f, 0.1f);
    glVertex2f(-0.2f, 0.3f);
    glVertex2f(-0.4f, 0.3f);
    glVertex2f(-0.4f, 0.1f);
  glEnd();

  glLoadIdentity();
  glScalef(1.5f, 1.5f, 0.0f);
  glTranslatef(-0.2, -0.6, 0.0);
  // Draw pentagon
  glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(-0.15f, 0.1f);
    glVertex2f(-0.05f, 0.2f);
    glVertex2f(0.05f, 0.1f);
  glEnd();

  glLoadIdentity();
  glScalef(0.9f, 0.9f, 0.0f);
  // Draw hexagon
  glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-0.4f, -0.2f);
    glVertex2f(-0.6f, -0.2f);
    glVertex2f(-0.7f, -0.4f);
    glVertex2f(-0.6f, -0.6f);
    glVertex2f(-0.4f, -0.6f);
    glVertex2f(-0.3f, -0.4f);
    glVertex2f(-0.4f, -0.2f);
  glEnd();
  
  glLoadIdentity(); 
}

// A and f are connected by a slot to widgets in mainwindow
void GLobj::drawWave(int A, int f)
{
  glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 1.0f);
    float dx = .001;
    for(float x = -1.0; x <= 1.0; x = x + dx)
      glVertex2f(x, A*cos(2*PI*f*x));
  glEnd();
}

void GLobj::redrawAmp(int value)
{
  setAmp(value);
  updateGL();
}

void GLobj::redrawFreq(int value)
{
  setFreq(value);
  updateGL();
}

// my recursive fractal function
void GLobj::drawFractal(float x, float y, int count, int max)
{
  if(count == max) return;
  
  glBegin(GL_POLYGON);
    glColor3f(1.0f - .2*(count), 1.0f, 0.0f);
    glVertex2f(x, y);
    glVertex2f(x, -y);
    glVertex2f(-x, -y);
    glVertex2f(-x, x);
  glEnd();
 
  drawFractal((x - .2), (y - .2), ++count, max);
}

void GLobj::drawFunction()
{ 
  int size = 10;
  float points[size];

  if(fileName == "") // default
    for(int i = 0; i < size; ++i)
      points[i] = i;
  else // following UI file load
  {
    std::fstream myfile(fileName.c_str(), std::ios_base::in);
    
    myfile >> size; // assumes first number is the size of array to be loaded
     
    for (int i = 1; i < size; ++i)
        myfile >> points[i]; // following numbers are loaded into array
  }
  
  glPointSize(4);
  glLineWidth(4);
  
  // Draw a Line
  glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 0.0f, 1.0f);
    for(int i = 0; i < size; ++i)
      glVertex2f(.1*points[i] - .5, .02*(points[i]*points[i]) - .75);
  glEnd();
}
