#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

namespace Ui { class MainWindow; }
class BlobScene;
class QListWidget;
class QRadioButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void addSphere();
    void removeSphere();
    void toggleIsRenderingMetaballs();
    void modifySphere(const QModelIndex &index);
private:
    Ui::MainWindow *ui;

    BlobScene* scene;
    QListWidget* list;
    QRadioButton* _toggleIsRenderingMetaballs;
};

#endif // MAINWINDOW_H
