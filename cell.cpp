#include "cell.h"
#include "cmath"
#include <QDebug>
#include <qmath.h>

int Cell::getState() const
{
    return state;
}

void Cell::setState(int value)
{
    state = value;
}

double Cell::getTime() const
{
    return time;
}

void Cell::setTime(double value)
{
    time = value;
}

Cell::Cell()
{

}

void Cell::assignTime(int _x, int _y, double _TIME)
{
    /*
    int ab = (x - _x)*(x - _x) + (y - _y)*(y - _y);
    double l = sqrt((double)ab);
    double rx = ((double)(x-_x)) / l;
    double ry = ((double)(y-_y)) / l;

    //qDebug() << "l=" << l << " rx=" << rx << " ry=" << ry;

    this->time = _TIME + ((qAbs(rx)+qAbs(ry)) * 1.1);
    //qDebug() << " abs(rx)=" << qAbs(rx) << " abs(ry)=" << qAbs(ry);
    //qDebug() << "x=" << x << " y=" << y << " time=" << this->time;
*/
    double dx = (double)x;
    double d_x = (double)_x;
    double dy = (double)y;
    double d_y = (double)_y;

    double l = qSqrt( qPow((dx - d_x), 2) + qPow((dy -d_y),2) );
    double rx = (dx - d_x) / l;
    double ry = (dy - d_y) / l;
    this->time = _TIME + (qAbs(rx) + qAbs(ry))*1.1;
}
