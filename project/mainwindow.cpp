
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "Sphere.h"
#include "editspheredialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = this->findChild<BlobScene*>("scene");
    list = this->findChild<QListWidget*>("sphereList");

    connect(this->findChild<QPushButton*>("addSphere"), SIGNAL (released()), this, SLOT (addSphere()));
    connect(this->findChild<QPushButton*>("removeSphere"), SIGNAL (released()), this, SLOT (removeSphere()));
    connect(this->findChild<QRadioButton*>("toggleBlobify"), SIGNAL (released()), this, SLOT (toggleBlobify()));
    connect(list, SIGNAL (doubleClicked(const QModelIndex&)), this, SLOT (modifySphere(const QModelIndex&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addSphere()
{
    qInfo() << "Adding sphere";
    Sphere* sphere = scene->makeSphere();
    sphere->setScale(1);
    sphere->setPosition(QVector3D(0,0,0));
    list->addItem(sphere);
}

void MainWindow::removeSphere()
{
    qInfo() << "Removing sphere";
}

void MainWindow::toggleBlobify()
{
    qInfo() << "Toggling blobify";
}

void MainWindow::modifySphere(const QModelIndex &index)
{
    Sphere* selected = (Sphere*)list->selectedItems()[0];
    QVector3D position = selected->position();
    float scale = selected->scale();
    EditSphereDialog dlg(this, position, scale);
    int result = dlg.exec();
    if(result == 1) {
        selected->setPosition(dlg.position());
        selected->setScale(dlg.scale());
    }
}
