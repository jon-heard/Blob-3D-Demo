
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->findChild<QPushButton*>("addSphere"), SIGNAL (released()), this, SLOT (addSphere()));
    connect(this->findChild<QPushButton*>("removeSphere"), SIGNAL (released()), this, SLOT (removeSphere()));
    connect(this->findChild<QRadioButton*>("toggleBlobify"), SIGNAL (released()), this, SLOT (toggleBlobify()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addSphere()
{
    qInfo() << "Adding sphere";
}

void MainWindow::removeSphere()
{
    qInfo() << "Removing sphere";
}

void MainWindow::toggleBlobify()
{
    qInfo() << "Toggling blobify";
}
