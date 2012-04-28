#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtGui>
#include <QTextFormat>
#include "TaskScheduler.h"

QT_BEGIN_NAMESPACE
class QTextEdit;
class QLineEdit;
class QPushButton;
class QLabel;
QT_END_NAMESPACE

//![0]
class UIWindow : public QWidget
{
    Q_OBJECT

public:

    UIWindow();

private slots:
    void setInput();
    void setOutput();

private:
    void setupGui();

private:
    QVBoxLayout * mainLayout;
    QLabel *output;
    QTextEdit *textEdit;
    QLabel *fileNameLabel;
    QLabel *outputLabel;
    QLineEdit *fileNameLineEdit;
    QPushButton *insertTextObjectButton;
    QPushButton *processButton;
};
//![0]

#endif
