#include "gamewindow.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <time.h>
#include <sys/time.h>
#include <iostream>

#include <QtCore>
#include <QtGui>

//#include <omp.h>

using namespace std;


int main(int argc, char **argv)
{
    srand(time(NULL));
    QGuiApplication app(argc, argv);
    
    QSurfaceFormat format;
    format.setSamples(16);
    
    paramCamera* c=new paramCamera();
    
    QTimer* calendar = new QTimer;

    GameWindow* window[4];
    for(int i = 0; i < 4; i++)
    {
        if (i == 0)
            window[i] = new GameWindow();
        else
            window[i] = new GameWindow(30);
        window[i]->setSeason(i);
        window[i]->c = c;
        window[i]->setFormat(format);
        window[i]->resize(500,375);
        int x = i%2;
        int y = i>>1;
                
        window[i]->setPosition(x*500,y*450);
        window[i]->show();

        calendar->connect(calendar, SIGNAL(timeout()),window[i], SLOT(updateSeason()));
    }
    
    calendar->start(20);

    return app.exec();
}

