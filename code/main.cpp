#include "UIWindow.h"
#include "TaskScheduler.h"
#include <QApplication>
#include <QLabel>
#include <QString>
#include <QTextStream>
#include <QIODevice>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    /*QString str;
    QTextStream tout(&str,QIODevice::WriteOnly);
    tout<<"Hello Qt\n Hello World\tJay";
     QApplication app(argc, argv);
     QLabel *label = new QLabel(str);
     label->show();*/
    //TaskScheduler tsd;
    cout<<"Under Construction ... "<<endl<<"Hello"<<argc<<endl;
    //tsd.input(argc);
    //tsd.execute();
    //tsd.output();
    //system("PAUSE");
    QApplication app(argc, argv);
    UIWindow window;
    window.show();
    return app.exec();
}
