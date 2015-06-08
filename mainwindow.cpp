#include "mainwindow.h"
#include "ui_mainwindow.h"

// CA1d

#include <QDebug>
#include <QtGui>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gWidget->setNeighbourhoodType(ui->neighborhoodBox->currentIndex());
    ui->gWidget->setRuleset(ui->rulesetBox->currentIndex());
    ui->gWidget->setPeriodic(ui->periodicCheckBox->isChecked());
    // advanced
    ui->gWidget->setTicker(0);
    ui->gWidget->setAnythingP(ui->anythingSpinBox->value());
    ui->gWidget->setMooreP(ui->chanceVsSpinBox->value());
    ui->gWidget->setVonneumannP(1 - ui->gWidget->getMooreP());

    ui->gWidget->detailP[0] = ui->spinBox0->value();
    ui->gWidget->detailP[1] = ui->spinBox1->value();
    ui->gWidget->detailP[2] = ui->spinBox2->value();
    ui->gWidget->detailP[3] = ui->spinBox3->value();
    //ui->gWidget->detailP[4] = ui->spinBox4->value();
    ui->gWidget->detailP[5] = ui->spinBox5->value();
    ui->gWidget->detailP[6] = ui->spinBox6->value();
    ui->gWidget->detailP[7] = ui->spinBox7->value();
    ui->gWidget->detailP[8] = ui->spinBox8->value();


    ui->gWidget->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_growButton_clicked()
{
    qDebug() << "Grow!";
    // growpreparations
    ui->gWidget->setTicker(0);

    // growloop
    for(int i = 0; i<20; i++)
        ui->gWidget->stateStep();
    this->repaint();
}

void MainWindow::on_primitiveSetupButton_clicked()
{
    qDebug() << "Primitive setup";
    ui->gWidget->primitiveSetUp();
}

void MainWindow::on_rulesetBox_currentIndexChanged(int index)
{
    ui->gWidget->setRuleset(index);
}

void MainWindow::on_periodicCheckBox_stateChanged(int arg1)
{
    ui->gWidget->setPeriodic(ui->periodicCheckBox->isChecked());
}

void MainWindow::on_neighborhoodBox_currentIndexChanged(int index)
{
    ui->gWidget->setNeighbourhoodType(index);
}

void MainWindow::on_spinBox0_valueChanged(double arg1)
{
    ui->gWidget->detailP[0] = arg1;
}

void MainWindow::on_spinBox1_valueChanged(double arg1)
{
    ui->gWidget->detailP[1] = arg1;
}

void MainWindow::on_spinBox2_valueChanged(double arg1)
{
    ui->gWidget->detailP[2] = arg1;
}

void MainWindow::on_spinBox3_valueChanged(double arg1)
{
    ui->gWidget->detailP[3] = arg1;
}

void MainWindow::on_spinBox4_valueChanged(double arg1)
{
    ui->gWidget->detailP[4] = arg1;
}

void MainWindow::on_spinBox5_valueChanged(double arg1)
{
    ui->gWidget->detailP[5] = arg1;
}

void MainWindow::on_spinBox6_valueChanged(double arg1)
{
    ui->gWidget->detailP[6] = arg1;
}

void MainWindow::on_spinBox7_valueChanged(double arg1)
{
    ui->gWidget->detailP[7] = arg1;
}

void MainWindow::on_spinBox8_valueChanged(double arg1)
{
    ui->gWidget->detailP[8] = arg1;
}

void MainWindow::on_chanceVsSpinBox_valueChanged(double arg1)
{
    ui->gWidget->setMooreP(arg1);
    ui->gWidget->setVonneumannP(1 - arg1);
}

void MainWindow::on_anythingSpinBox_valueChanged(double arg1)
{
    ui->gWidget->setAnythingP(arg1);
}
