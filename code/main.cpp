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
    cout<<"Under Construction ... "<<endl<<"Hello"<<argc<<endl;
    QApplication app(argc, argv);
    UIWindow window;
    window.show();
    return app.exec();
}
