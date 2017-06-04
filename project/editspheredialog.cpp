#include "editspheredialog.h"
#include "ui_editspheredialog.h"

EditSphereDialog::EditSphereDialog(QWidget *parent, QVector3D position, float scale) :
    QDialog(parent),
    ui(new Ui::EditSphereDialog)
{
    ui->setupUi(this);
    this->findChild<QDoubleSpinBox*>("ValueX")->setValue(position.x());
    this->findChild<QDoubleSpinBox*>("ValueY")->setValue(position.y());
    this->findChild<QDoubleSpinBox*>("ValueZ")->setValue(position.z());
    this->findChild<QDoubleSpinBox*>("ValueScale")->setValue(scale);
}

EditSphereDialog::~EditSphereDialog()
{
    delete ui;
}

QVector3D EditSphereDialog::position()
{
    QVector3D result;
    result.setX(this->findChild<QDoubleSpinBox*>("ValueX")->value());
    result.setY(this->findChild<QDoubleSpinBox*>("ValueY")->value());
    result.setZ(this->findChild<QDoubleSpinBox*>("ValueZ")->value());
    return result;
}

float EditSphereDialog::scale()
{
    return this->findChild<QDoubleSpinBox*>("ValueScale")->value();
}
