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

void Cell::assignTime(int _x, int _y, double _TIME, int height, int width, bool periodic)
{
    double dx = (double)x; // id_x
    double d_x = (double)_x; // grain_x
    double dy = (double)y; // id_y
    double d_y = (double)_y; // grain_y

    double l;
    double rx;
    double ry;

    // ---------------------
    if(periodic)
    {
        double powx; double powy;

        double deltax1 = dx - d_x; // regular one
        double deltax2; // możliwe że periodycznie jest bliżej
        if(dx < d_x)
        {
            deltax2 = (dx + height) - d_x;
        }
        else
        {
            deltax2 = (d_x + height) - dx;
        }
        double deltay1 = dy - d_y;
        double deltay2;
        if(dy < d_y)
        {
            deltay2 = (dy + width) - d_y;
        }
        else
        {
            deltay2 = (d_y + width) - dy;
        }
        // lesser deltas go to l, rx, ry
        deltax1 < deltax2 ? powx = deltax1 : powx = deltax2;
/*
        if( deltax2 < deltax1 )
        {
            qDebug() << "deltax1 = " << deltax1 << ", deltax2 = " << deltax2 << ", dx = " << dx << ", d_x = " << d_x;
        }
*/
        deltay1 < deltay2 ? powy = deltay1 : powy = deltay2;

        l = qSqrt( qPow(powx, 2) + qPow(powy,2) );
        rx = powx / l;
        ry = powy / l;

    }
    else
    {
        l = qSqrt( qPow((dx - d_x), 2) + qPow((dy -d_y),2) );
        rx = (dx - d_x) / l;
        ry = (dy - d_y) / l;
    }
/*
    l = qSqrt( qPow((dx - d_x), 2) + qPow((dy -d_y),2) );
    rx = (dx - d_x) / l;
    ry = (dy - d_y) / l;
    */
    this->time = _TIME + (qAbs(rx) + qAbs(ry))*1.1;

}
