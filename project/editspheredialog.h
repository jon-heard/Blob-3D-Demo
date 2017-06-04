#ifndef EDITSPHEREDIALOG_H
#define EDITSPHEREDIALOG_H

#include <QDialog>
#include <QVector3D>

namespace Ui {
class EditSphereDialog;
}

class EditSphereDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditSphereDialog(QWidget *parent, QVector3D position, float scale);
    ~EditSphereDialog();
    QVector3D position();
    float scale();
private:
    Ui::EditSphereDialog *ui;
};

#endif // EDITSPHEREDIALOG_H
