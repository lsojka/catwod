#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QRect>
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <cell.h>

class gridwidget : public QWidget
{
    Q_OBJECT
public:
    explicit gridwidget(QWidget *parent = 0);

    bool isNotDone;
    bool periodic;
    int ruleset;
    int neighbourhoodType;

    // advanced
    int ticker;
    double anythingP;
    double mooreP;
    double vonneumannP;
    QList<double> detailP;

    //QList<int> grid;
    QList<Cell> grid;

    // frontal
    double GLOBALTIME;
    double TIMESTEP;
    QList<Cell> front;

    // multigrain
    QList<QColor> grains;
    QList<int> grainsx;
    QList<int> grainsy;

    // ------------------------------
    void primitiveSetUp();
    // transistions
    void stateStep();
    int transistion(QList<int> neighbours);

        // basic
    //QList<int> checkMoore(int i, int j);
    QList<int> checkVonNeumann(int i, int j);
    void setRuleset(int _r);

    bool getPeriodic() const;
    void setPeriodic(bool value);

    int getNeighbourhoodType() const;
    void setNeighbourhoodType(int value);

        // advanced
    QList<int> checkMooreBaggins(int i, int j);
    QList<int> volatileMoore(int i, int j);
    QList<int> volatileVonNeumann(int i, int j);

    void setDetailPelement(int pos);
    double randP();

    int getTicker() const;
    void setTicker(int value);

    double getAnythingP() const;
    void setAnythingP(double value);

    double getMooreP() const;
    void setMooreP(double value);

    double getVonneumannP() const;
    void setVonneumannP(double value);

    // ball
    //void frontalMoore(int i, int j, int ci, int cj);

    // multigrain
    QList<Cell> checkMoore(int i, int j);
    void multigrainMoore(int i, int j, int ci, int cj);

    void addGrain();


private:
    void paintEvent(QPaintEvent *);

signals:

public slots:

};

#endif // GRIDWIDGET_H
