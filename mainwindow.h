#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_growButton_clicked();

    void on_primitiveSetupButton_clicked();

    void on_rulesetBox_currentIndexChanged(int index);

    void on_periodicCheckBox_stateChanged(int arg1);

    void on_neighborhoodBox_currentIndexChanged(int index);

    void on_spinBox0_valueChanged(double arg1);

    void on_spinBox1_valueChanged(double arg1);

    void on_spinBox2_valueChanged(double arg1);

    void on_spinBox3_valueChanged(double arg1);

    void on_spinBox4_valueChanged(double arg1);

    void on_spinBox5_valueChanged(double arg1);

    void on_spinBox6_valueChanged(double arg1);

    void on_spinBox7_valueChanged(double arg1);

    void on_spinBox8_valueChanged(double arg1);

    void on_chanceVsSpinBox_valueChanged(double arg1);

    void on_anythingSpinBox_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
