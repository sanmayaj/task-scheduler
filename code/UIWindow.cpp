#include <QtGui>
#include<QFile>
#include <iostream>
using namespace std;
#include "UIWindow.h"
#include "TaskScheduler.h"

UIWindow::UIWindow()
{
    setupGui();
    setWindowTitle("Task Scheduler");
}

//![1]
void UIWindow::setInput()
{
    QString s = QFileDialog::getOpenFileName(this,"Choose a file","","Text (*.txt)");
    QFile file(s);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    QString text = "";
    QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                text = text+line+"\n";
            }
    textEdit->setText(text);
    repaint();
}

void UIWindow::setOutput()
{
    TaskScheduler tsd;
    QString qstr = textEdit->toPlainText();
    tsd.input(1,qstr.toStdString());
    string str="";
    tsd.execute();
    tsd.output(str);
    QString qst = "";
    qst=qst+str.c_str();
    output->setText(qst);
    outputLabel->setText("Output");
    repaint();
}

void UIWindow::setupGui()
{
    fileNameLabel = new QLabel(tr("Input"));
    outputLabel = new QLabel(tr(""));
    insertTextObjectButton = new QPushButton(tr("Insert File ..."));
    processButton = new QPushButton(tr(" Process "));

    connect(insertTextObjectButton, SIGNAL(clicked()),
            this, SLOT(setInput()));
    connect(processButton, SIGNAL(clicked()),
            this, SLOT(setOutput()));

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(insertTextObjectButton);
    bottomLayout->addWidget(processButton);

    textEdit = new QTextEdit;
    output = new QLabel();
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileNameLabel);
    mainLayout->addWidget(textEdit);
    mainLayout->addLayout(bottomLayout);

    QVBoxLayout *outLayout = new QVBoxLayout;
    outLayout->addWidget(outputLabel);
    outLayout->addWidget(output);

    QHBoxLayout *mLayout = new QHBoxLayout;
    mLayout->addLayout(mainLayout);
    mLayout->addLayout(outLayout);

    setLayout(mLayout);
}


