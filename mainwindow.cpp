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

    ui->gWidget->setPeriodic(ui->periodicCheckBox->isChecked());
    // advanced
    ui->gWidget->setTicker(0);



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
    for(int i = 0; i<100; i++)
        ui->gWidget->stateStep();
    this->repaint();
}

void MainWindow::on_primitiveSetupButton_clicked()
{
    qDebug() << "Primitive setup";
    ui->gWidget->primitiveSetUp();
}

void MainWindow::on_periodicCheckBox_stateChanged(int arg1)
{
    ui->gWidget->setPeriodic(ui->periodicCheckBox->isChecked());
}

void MainWindow::on_neighborhoodBox_currentIndexChanged(int index)
{
    ui->gWidget->setNeighbourhoodType(index);
}

