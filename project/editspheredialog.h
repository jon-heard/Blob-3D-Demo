#ifndef EDITSPHEREDIALOG_H
#define EDITSPHEREDIALOG_H

#include <QDialog>

namespace Ui {
class EditSphereDialog;
}

class EditSphereDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditSphereDialog(QWidget *parent = 0);
    ~EditSphereDialog();

private:
    Ui::EditSphereDialog *ui;
};

#endif // EDITSPHEREDIALOG_H
