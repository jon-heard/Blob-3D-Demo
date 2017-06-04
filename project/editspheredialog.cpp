#include "editspheredialog.h"
#include "ui_editspheredialog.h"

EditSphereDialog::EditSphereDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditSphereDialog)
{
    ui->setupUi(this);
}

EditSphereDialog::~EditSphereDialog()
{
    delete ui;
}
