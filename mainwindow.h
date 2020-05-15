#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <exception>
#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();

    void on_playbutton_toggled(bool checked);

    void on_speedbutton_toggled(bool checked);

    void on_reversespeed_toggled(bool checked);

    void on_playbutton_2_clicked();

private:
    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H
