#include "gridwidget.h"

#include <QDebug>
#include <QtGui>
#include <time.h>

gridwidget::gridwidget(QWidget *parent) :
    QWidget(parent), GLOBALTIME(0)
{
    qDebug() << "Screen set. h: " << this->height() << " w:" << width();
    qsrand(time(NULL));
    for(int i = 0; i < 9; i++)
        this->detailP.append(0);
}

double gridwidget::getVonneumannP() const
{
    return vonneumannP;
}

void gridwidget::setVonneumannP(double value)
{
    vonneumannP = value;
}

double gridwidget::getMooreP() const
{
    return mooreP;
}

void gridwidget::setMooreP(double value)
{
    mooreP = value;
}

double gridwidget::getAnythingP() const
{
    return anythingP;
}

void gridwidget::setAnythingP(double value)
{
    anythingP = value;
}

int gridwidget::getTicker() const
{
    return ticker;
}

void gridwidget::setTicker(int value)
{
    ticker = value;
}

int gridwidget::getNeighbourhoodType() const
{
    return neighbourhoodType;
}

void gridwidget::setNeighbourhoodType(int value)
{
    neighbourhoodType = value;
    qDebug() << "NeighbourhoodType = " << this->getNeighbourhoodType();
}

bool gridwidget::getPeriodic() const
{
    return periodic;
}

void gridwidget::setPeriodic(bool value)
{
    periodic = value;
}


void gridwidget::setRuleset(int _r)
{
    this->ruleset = _r;
    qDebug() << "Ruleset " << this->ruleset;
}

double gridwidget::randP()
{
    return ((double)(qrand() % 101)) / 100;
}

/*
QList<int> gridwidget::checkMoore(int i, int j)
{

     0|1|2
     3| |5
     6|7|8

    QList<int> neighbours;
    if(this->periodic)
    {
        //qDebug() << "0| r "(((i+this->height())-1)%this->height())<< ", " << ((j+this->width())-1)%this->width();
        //qDebug() << "0| nr "(((i+this->height())-1)%this->height())*this->width() + ((j+this->width())-1)%this->width();
       //if(i*this->width()+j > 217549)
            //qDebug() << "Attempt at i,j " << i << "," << j;
        // 0
        if(this->grid[ (((i+this->height())-1)%this->height())*this->width() + ((j+this->width())-1)%this->width() ] ==  1)
            neighbours.append(grid[ (((i+this->height())-1)%this->height())*this->width() + ((j+this->width())-1)%this->width() ]);
        // 1
        if(this->grid[ (((i+this->height())-1)%this->height() )*this->width() + ((j+this->width()))%this->width() ] ==  1)
            neighbours.append(grid[ (((i+this->height())-1)%this->height())*this->width() + ((j+this->width()))%this->width() ]);
        // 2
        if(this->grid[ (((i+this->height())-1)%this->height())*this->width() + ((j+this->width())+1)%this->width() ] ==  1)
            neighbours.append(grid[ (((i+this->height())-1)%this->height())*this->width() + ((j+this->width())+1)%this->width() ]);
        // 3
        if(this->grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())-1)%this->width() ] ==  1)
            neighbours.append(grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())-1)%this->width() ]);
        // 5
        if(this->grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())+1)%this->width() ] ==  1)
            neighbours.append(grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())+1)%this->width() ]);
        // 6
        if(this->grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width())-1)%this->width() ] ==  1)
            neighbours.append(grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width())-1)%this->width() ]);
        // 7
        if(this->grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width()))%this->width() ] ==  1)
            neighbours.append(grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width()))%this->width() ]);
        // 8
        if(this->grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width())+1)%this->width() ] ==  1)
            neighbours.append(grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width())+1)%this->width() ]);
    }
    else
    {
        //if(!( ((i-1)<0) || ((i-1)>rows-1) || ((j-1)<0) || ((j-1)>columns-1) ))
        //    fellas.append(grid[i-1][j-1]);
        // 0
        //qDebug () << "DEBUG 1";
        if(!( ((i-1)<0) || ((i-1)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
            if(grid[ (i-1)*this->width() + (j-1)] ==  1)
                neighbours.append(grid[ (i-1)*this->width() + (j-1)]);
        // 1
        if(!( ((i-1)<0) || ((i-1)>this->height()-1) || ((j)<0) || ((j)>this->width()-1) ))
            if(grid[ (i-1)*this->width() + (j)] ==  1)
                neighbours.append(grid[ (i-1)*this->width() + j]);
        // 2
        if(!( ((i-1)<0) || ((i-1)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
            if(grid[ (i-1)*this->width() + (j+1)] ==  1)
                neighbours.append(grid[ (i-1)*this->width() + (j+1)]);
        // 3
        if(!( ((i)<0) || ((i)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
            if(grid[ (i)*this->width() + (j-1)] ==  1)
            neighbours.append(grid[ i*this->width() + (j-1)]);
        // 5
        if(!( ((i)<0) || ((i)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
            if(grid[ (i)*this->width() + (j+1)] ==  1)
                neighbours.append(grid[ i*this->width() + (j+1)]);
        // 6
        if(!( ((i+1)<0) || ((i+1)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
            if(grid[ (i+1)*this->width() + (j-1)] ==  1)
                neighbours.append(grid[ (i+1)*this->width() + (j-1)]);
        // 7
        if(!( ((i+1)<0) || ((i+1)>this->height()-1) || ((j)<0) || ((j)>this->width()-1) ))
            if(grid[ (i+1)*this->width() + (j)] ==  1)
                neighbours.append(grid[ (i+1)*this->width() + (j)]);
        // 8
        if(!( ((i+1)<0) || ((i+1)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
            if(grid[ (i+1)*this->width() + (j+1)] ==  1)
                neighbours.append(grid[ (i+1)*this->width() + (j+1)]);
        //qDebug () << "DEBUG 2";
    }

    return neighbours;
}
*/

/*
QList<int> gridwidget::checkMooreBaggins(int i, int j)
{

    QList<int> neighbours;
    if(this->periodic)
    {
        // 3
        if(this->grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())-1)%this->width() ] ==  1)
            neighbours.append(grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())-1)%this->width() ]);
        // 5
        if(this->grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())+1)%this->width() ] ==  1)
            neighbours.append(grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())+1)%this->width() ]);
    }
    else
    {
        // 3
        if(!( ((i)<0) || ((i)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
            if(grid[ (i)*this->width() + (j-1)] ==  1)
            neighbours.append(grid[ i*this->width() + (j-1)]);
        // 5
        if(!( ((i)<0) || ((i)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
            if(grid[ (i)*this->width() + (j+1)] ==  1)
                neighbours.append(grid[ i*this->width() + (j+1)]);
    }

    return neighbours;
}

QList <int> gridwidget::checkVonNeumann(int i, int j)
{
    QList<int> neighbours;
    if(this->periodic)
    {
        //qDebug() << "0| r "(((i+this->height())-1)%this->height())<< ", " << ((j+this->width())-1)%this->width();
        //qDebug() << "0| nr "(((i+this->height())-1)%this->height())*this->width() + ((j+this->width())-1)%this->width();
       //if(i*this->width()+j > 217549)
            //qDebug() << "Attempt at i,j " << i << "," << j;
        // 1
        if(this->grid[ (((i+this->height())-1)%this->height() )*this->width() + ((j+this->width()))%this->width() ] ==  1)
            neighbours.append(grid[ (((i+this->height())-1)%this->height())*this->width() + ((j+this->width()))%this->width() ]);
        // 3
        if(this->grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())-1)%this->width() ] ==  1)
            neighbours.append(grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())-1)%this->width() ]);
        // 5
        if(this->grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())+1)%this->width() ] ==  1)
            neighbours.append(grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())+1)%this->width() ]);
        // 7
        if(this->grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width()))%this->width() ] ==  1)
            neighbours.append(grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width()))%this->width() ]);
    }
    else
    {
        //if(!( ((i-1)<0) || ((i-1)>rows-1) || ((j-1)<0) || ((j-1)>columns-1) ))
        //    fellas.append(grid[i-1][j-1]);
        // 0
        //qDebug () << "DEBUG 1";
        // 1
        if(!( ((i-1)<0) || ((i-1)>this->height()-1) || ((j)<0) || ((j)>this->width()-1) ))
            if(grid[ (i-1)*this->width() + (j)] ==  1)
                neighbours.append(grid[ (i-1)*this->width() + j]);
        // 3
        if(!( ((i)<0) || ((i)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
            if(grid[ (i)*this->width() + (j-1)] ==  1)
            neighbours.append(grid[ i*this->width() + (j-1)]);
        // 5
        if(!( ((i)<0) || ((i)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
            if(grid[ (i)*this->width() + (j+1)] ==  1)
                neighbours.append(grid[ i*this->width() + (j+1)]);
        // 7
        if(!( ((i+1)<0) || ((i+1)>this->height()-1) || ((j)<0) || ((j)>this->width()-1) ))
            if(grid[ (i+1)*this->width() + (j)] ==  1)
                neighbours.append(grid[ (i+1)*this->width() + (j)]);
        //qDebug () << "DEBUG 2";
    }

    return neighbours;
}


QList<int> gridwidget::volatileMoore(int i, int j)
{

    QList<int> neighbours;
    if(this->periodic)
    {
        //qDebug() << "0| r "(((i+this->height())-1)%this->height())<< ", " << ((j+this->width())-1)%this->width();
        //qDebug() << "0| nr "(((i+this->height())-1)%this->height())*this->width() + ((j+this->width())-1)%this->width();
       //if(i*this->width()+j > 217549)
            //qDebug() << "Attempt at i,j " << i << "," << j;
        // 0
        if(this->grid[ (((i+this->height())-1)%this->height())*this->width() + ((j+this->width())-1)%this->width() ] ==  1 && this->randP() < this->detailP[0])
            neighbours.append(grid[ (((i+this->height())-1)%this->height())*this->width() + ((j+this->width())-1)%this->width() ]);
        // 1
        if(this->grid[ (((i+this->height())-1)%this->height() )*this->width() + ((j+this->width()))%this->width() ] ==  1 && this->randP() < this->detailP[1])
            neighbours.append(grid[ (((i+this->height())-1)%this->height())*this->width() + ((j+this->width()))%this->width() ]);
        // 2
        if(this->grid[ (((i+this->height())-1)%this->height())*this->width() + ((j+this->width())+1)%this->width() ] ==  1 && this->randP() < this->detailP[2])
            neighbours.append(grid[ (((i+this->height())-1)%this->height())*this->width() + ((j+this->width())+1)%this->width() ]);
        // 3
        if(this->grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())-1)%this->width() ] ==  1 && this->randP() < this->detailP[3])
            neighbours.append(grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())-1)%this->width() ]);
        // 5
        if(this->grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())+1)%this->width() ] ==  1 && this->randP() < this->detailP[5])
            neighbours.append(grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())+1)%this->width() ]);
        // 6
        if(this->grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width())-1)%this->width() ] ==  1 && this->randP() < this->detailP[6])
            neighbours.append(grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width())-1)%this->width() ]);
        // 7
        if(this->grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width()))%this->width() ] ==  1 && this->randP() < this->detailP[7])
            neighbours.append(grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width()))%this->width() ]);
        // 8
        if(this->grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width())+1)%this->width() ] ==  1 && this->randP() < this->detailP[8])
            neighbours.append(grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width())+1)%this->width() ]);
    }
    else
    {
        //if(!( ((i-1)<0) || ((i-1)>rows-1) || ((j-1)<0) || ((j-1)>columns-1) ))
        //    fellas.append(grid[i-1][j-1]);
        // 0
        //qDebug () << "DEBUG 1";
        if(!( ((i-1)<0) || ((i-1)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
            if(grid[ (i-1)*this->width() + (j-1)] ==  1 && this->randP() < this->detailP[0])
                neighbours.append(grid[ (i-1)*this->width() + (j-1)]);
        // 1
        if(!( ((i-1)<0) || ((i-1)>this->height()-1) || ((j)<0) || ((j)>this->width()-1) ))
            if(grid[ (i-1)*this->width() + (j)] ==  1 && this->randP() < this->detailP[1])
                neighbours.append(grid[ (i-1)*this->width() + j]);
        // 2
        if(!( ((i-1)<0) || ((i-1)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
            if(grid[ (i-1)*this->width() + (j+1)] ==  1 && this->randP() < this->detailP[2])
                neighbours.append(grid[ (i-1)*this->width() + (j+1)]);
        // 3
        if(!( ((i)<0) || ((i)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
            if(grid[ (i)*this->width() + (j-1)] ==  1 && this->randP() < this->detailP[3])
            neighbours.append(grid[ i*this->width() + (j-1)]);
        // 5
        if(!( ((i)<0) || ((i)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
            if(grid[ (i)*this->width() + (j+1)] ==  1 && this->randP() < this->detailP[5])
                neighbours.append(grid[ i*this->width() + (j+1)]);
        // 6
        if(!( ((i+1)<0) || ((i+1)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
            if(grid[ (i+1)*this->width() + (j-1)] ==  1 && this->randP() < this->detailP[6])
                neighbours.append(grid[ (i+1)*this->width() + (j-1)]);
        // 7
        if(!( ((i+1)<0) || ((i+1)>this->height()-1) || ((j)<0) || ((j)>this->width()-1) ))
            if(grid[ (i+1)*this->width() + (j)] ==  1 && this->randP() < this->detailP[7])
                neighbours.append(grid[ (i+1)*this->width() + (j)]);
        // 8
        if(!( ((i+1)<0) || ((i+1)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
            if(grid[ (i+1)*this->width() + (j+1)] ==  1 && this->randP() < this->detailP[8])
                neighbours.append(grid[ (i+1)*this->width() + (j+1)]);
        //qDebug () << "DEBUG 2";
    }

    return neighbours;
}

QList<int> gridwidget::volatileVonNeumann(int i, int j)
{

    QList<int> neighbours;
    if(this->periodic)
    {
        //qDebug() << "0| r "(((i+this->height())-1)%this->height())<< ", " << ((j+this->width())-1)%this->width();
        //qDebug() << "0| nr "(((i+this->height())-1)%this->height())*this->width() + ((j+this->width())-1)%this->width();
       //if(i*this->width()+j > 217549)
            //qDebug() << "Attempt at i,j " << i << "," << j;
        // 1
        if(this->grid[ (((i+this->height())-1)%this->height() )*this->width() + ((j+this->width()))%this->width() ] ==  1 && this->randP() < this->detailP[1])
            neighbours.append(grid[ (((i+this->height())-1)%this->height())*this->width() + ((j+this->width()))%this->width() ]);
        // 3
        if(this->grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())-1)%this->width() ] ==  1 && this->randP() < this->detailP[3])
            neighbours.append(grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())-1)%this->width() ]);
        // 5
        if(this->grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())+1)%this->width() ] ==  1 && this->randP() < this->detailP[5])
            neighbours.append(grid[ (((i+this->height()))%this->height())*this->width() + ((j+this->width())+1)%this->width() ]);
        // 7
        if(this->grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width()))%this->width() ] ==  1 && this->randP() < this->detailP[7])
            neighbours.append(grid[ (((i+this->height())+1)%this->height())*this->width() + ((j+this->width()))%this->width() ]);
    }
    else
    {
        //if(!( ((i-1)<0) || ((i-1)>rows-1) || ((j-1)<0) || ((j-1)>columns-1) ))
        //    fellas.append(grid[i-1][j-1]);
        // 1
        if(!( ((i-1)<0) || ((i-1)>this->height()-1) || ((j)<0) || ((j)>this->width()-1) ))
            if(grid[ (i-1)*this->width() + (j)] ==  1 && this->randP() < this->detailP[1])
                neighbours.append(grid[ (i-1)*this->width() + j]);
        // 3
        if(!( ((i)<0) || ((i)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
            if(grid[ (i)*this->width() + (j-1)] ==  1 && this->randP() < this->detailP[3])
            neighbours.append(grid[ i*this->width() + (j-1)]);
        // 5
        if(!( ((i)<0) || ((i)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
            if(grid[ (i)*this->width() + (j+1)] ==  1 && this->randP() < this->detailP[5])
                neighbours.append(grid[ i*this->width() + (j+1)]);
        // 7
        if(!( ((i+1)<0) || ((i+1)>this->height()-1) || ((j)<0) || ((j)>this->width()-1) ))
            if(grid[ (i+1)*this->width() + (j)] ==  1 && this->randP() < this->detailP[7])
                neighbours.append(grid[ (i+1)*this->width() + (j)]);
    }

    return neighbours;
}
*/

/*
void gridwidget::stateStep()
{
    //qDebug() << "Growth step";
    this->isNotDone = false;
    QList<int> _grid;
    QList<int> neighbors;
    for(int i = 0; i < this->grid.length(); i++)
        _grid.append(0);
    // advanced increments per iteration
    this->setTicker(this->getTicker()+1);


    // walk through old states to determine new ones
    for(int i = 0; i < this->height(); i++)
    {
        for(int j = 0; j < this->width(); j++)
        {
            // regular 2D CA ---------------------------------------
            if(this->ruleset == 0)
            {
                if(this->grid[i*this->width()+j] == 1)
                {
                    _grid[i*this->width()+j] = this->grid[i*this->width()+j];
                    //qDebug() << "Rerite (" << i << "," << j << ")";
                }
                else if(this->grid[i*this->width()+j] == 0)
                {
                    switch(this->getNeighbourhoodType())
                    {
                    case 0:
                        neighbors = this->checkMoore(i, j);
                    break;
                    case 1:
                        neighbors = this->checkVonNeumann(i, j);
                    break;
                    default:
                        qDebug() << "Bad neighbourhood";
                    break;
                    }

                    if(neighbors.length() > 0)
                        _grid[i*this->width()+j] = 1; // very simplified transistion
                }
            }
            // Game of Life ----------------------------------------
            else if(this->ruleset == 1)
            {
                if(this->grid[i*this->width()+j] == 1)
                {
                    neighbors = this->checkMoore(i, j);
                    if((neighbors.length() == 2) || (neighbors.length() == 3))
                        this->grid[i*this->width()+j] = 1;
                    else// if((neighbors.length() < 2) || (neighbors.length() > 3))
                        this->grid[i*this->width()+j] = 0;

                }
                else if(this->grid[i*this->width()+j] == 0)
                {
                    neighbors = this->checkMoore(i, j);
                    if(neighbors.length() == 3)
                        _grid[i*this->width()+j] = 1;
                }
            }
            // ------------------------------------------------
            // Hex
            else if(this->ruleset == 2)
            {

                if(this->grid[i*this->width()+j] == 1)
                {
                    _grid[i*this->width()+j] = this->grid[i*this->width()+j];
                }
                else if(this->grid[i*this->width()+j] == 0)
                {
                    // this->checkHex(i,j) ?
                    if(i % 2 == 1)
                        neighbors = this->checkVonNeumann(i, j);
                    else if(i % 2 == 0)
                        neighbors = this->checkMoore(i, j);

                    if(neighbors.length() > 0)
                        _grid[i*this->width()+j] = 1; // very simplified transistion
                }
            }
            // Penta
            else if(this->ruleset == 3)
            {
                if(this->grid[i*this->width()+j] == 1)
                {
                    _grid[i*this->width()+j] = this->grid[i*this->width()+j];
                }
                else if(this->grid[i*this->width()+j] == 0)
                {
                    // this->checkPenta(i,j) ?
                    if(i % 4 == 0)
                        neighbors = this->checkMoore(i, j);
                    else
                        neighbors = this->checkVonNeumann(i, j);

                    if(neighbors.length() > 0)
                        _grid[i*this->width()+j] = 1; // very simplified transistion
                }
            }
            // hepta
            else if(this->ruleset == 4)
            {
                if(this->grid[i*this->width()+j] == 1)
                {
                    _grid[i*this->width()+j] = this->grid[i*this->width()+j];
                }
                else if(this->grid[i*this->width()+j] == 0)
                {
                    // this->checkHepta(i,j) ?
                    if(i % 4 == 0)
                        neighbors = this->checkVonNeumann(i, j);
                    else
                        neighbors = this->checkMoore(i, j);

                    if(neighbors.length() > 0)
                        _grid[i*this->width()+j] = 1; // very simplified transistion
                }
            }
            // -----------------------------------------
            // paraHex
            else if(this->ruleset == 5)
            {

                if(this->grid[i*this->width()+j] == 1)
                {
                    _grid[i*this->width()+j] = this->grid[i*this->width()+j];
                }
                else if(this->grid[i*this->width()+j] == 0)
                {
                    if(this->getTicker() % 2 == 1)
                        neighbors = this->checkVonNeumann(i, j);
                    else if(this->ticker % 2 == 0)
                        neighbors = this->checkMoore(i, j);

                    if(neighbors.length() > 0)
                        _grid[i*this->width()+j] = 1; // very simplified transistion
                }
            }
            // paraPenta
            else if(this->ruleset == 6)
            {
                if(this->grid[i*this->width()+j] == 1)
                {
                    _grid[i*this->width()+j] = this->grid[i*this->width()+j];
                }
                else if(this->grid[i*this->width()+j] == 0)
                {
                    if(this->getTicker() % 4 == 0)
                        neighbors = this->checkMoore(i, j);
                    else
                        neighbors = this->checkVonNeumann(i, j);

                    if(neighbors.length() > 0)
                        _grid[i*this->width()+j] = 1; // very simplified transistion
                }
            }
            // rectangle
            else if(this->ruleset == 7)
            {
                if(this->grid[i*this->width()+j] == 1)
                {
                    _grid[i*this->width()+j] = this->grid[i*this->width()+j];
                }
                else if(this->grid[i*this->width()+j] == 0)
                {
                    if(this->getTicker() % 4 == 0)
                        neighbors = this->checkMoore(i, j);
                    else
                        neighbors = this->checkMooreBaggins(i, j);

                    if(neighbors.length() > 0)
                        _grid[i*this->width()+j] = 1; // very simplified transistion
                }
            }
            // chanceAny
            else if(this->ruleset == 8)
            {
                if(this->grid[i*this->width()+j] == 1)
                {
                    _grid[i*this->width()+j] = this->grid[i*this->width()+j];
                }
                else if(this->grid[i*this->width()+j] == 0)
                {
                    double Pp = ((double)(qrand() % 101)) / 100;

                    if(Pp < this->getAnythingP())
                    {
                        switch(this->getNeighbourhoodType())
                        {
                        case 0:
                            neighbors = this->checkMoore(i, j);
                            break;
                        case 1:
                            neighbors = this->checkVonNeumann(i, j);
                            break;
                        default:
                            break;
                        }
                        if(neighbors.length() > 0)
                        {
                            _grid[i*this->width()+j] = 1; // very simplified transistion
                        }
                    }
                }
            }
            // 9 - prawdopodobieństwo wskazuje sąsiedztwo
            else if(this->ruleset == 9)
            {
                if(this->grid[i*this->width()+j] == 1)
                {
                    _grid[i*this->width()+j] = this->grid[i*this->width()+j];
                }
                else if(this->grid[i*this->width()+j] == 0)
                {
                    //double Pp = ((double)(qrand() % 101)) / 100;

                    if(this->randP() < this->getMooreP())
                        neighbors = this->checkMoore(i, j);
                    else
                        neighbors = this->checkVonNeumann(i, j);


                    if(neighbors.length() > 0)
                        _grid[i*this->width()+j] = 1; // very simplified transistion
                }
            }
            // 10 - unsureMoore, unsureVonNeumann - uwzględniający prawdopodobieństwa
            if(this->ruleset == 10)
            {
                if(this->grid[i*this->width()+j] == 1)
                {
                    _grid[i*this->width()+j] = this->grid[i*this->width()+j];
                    //qDebug() << "Rerite (" << i << "," << j << ")";
                }
                else if(this->grid[i*this->width()+j] == 0)
                {
                    switch(this->getNeighbourhoodType())
                    {
                    case 0:
                        neighbors = this->volatileMoore(i, j);
                    break;
                    case 1:
                        neighbors = this->volatileVonNeumann(i, j);
                    break;
                    default:
                        qDebug() << "Bad neighbourhood";
                    break;
                    }

                    if(neighbors.length() > 0)
                        _grid[i*this->width()+j] = 1; // very simplified transistion
                }
            }

        }
    }


    this->grid.clear();
    grid.append(_grid);

    _grid.clear();
    neighbors.clear();
}
*/

void gridwidget::primitiveSetUp()
{
    this->grid.clear();
/*
    for(int i = 0; i < this->height()*this->width(); i++)
    {
        this->grid.append(0);
    }
*/
    for(int i = 0; i < this->height(); i++)
    {
        for(int j = 0; j < this->width(); j++)
        {
            Cell cell;
            cell.x = i;
            cell.y = j;
            cell.setState(0);

            this->grid.append(cell);
        }
    }

    this->grid[400/2*this->width()+ 400/2].setState(2);
    //qDebug() << "front.length = " << this->front.length();
    // frontal moore here., so front.lenght goes from 0 to something
    //this->frontalMoore(400/2, 400/2);
    // crude debug -> print front values here... or in frotnalMoore
    //qDebug() << "front.length = " << this->front.length();

    this->repaint();
}

void gridwidget::paintEvent(QPaintEvent *)
{
    //qDebug() << "Repaint set. h: " << this->height() << " w:" << width();

    QBrush noBrush("#ffffff");
    QBrush halfBrush("#B94E48");
    QBrush fullBrush("#882D17");
    QPainter painter(this);

    //qDebug() << "grid.size = " << grid.size();
    if(grid.size() > 0)
    {
        for(int i = 0; i < this->height(); i++)
        {
            for(int j = 0; j < this->width(); j++)
            {
                QRect rect(j, i, 1, 1);
                if(this->grid[i*this->width()+j].getState() == 2 )
                    painter.fillRect(rect, fullBrush);
                else if(this->grid[i*this->width()+j].getState() == 1)
                    painter.fillRect(rect, halfBrush);
                else
                    painter.fillRect(rect, noBrush);
            }
        }
    }
}



void gridwidget::stateStep()
{
// change to parameter
    //qDebug() << "Globaltime " << this->GLOBALTIME;
    if(this->GLOBALTIME == 0)
    {
        for(int i = 0; i<this->height(); i++)
        {
            for(int j = 0; j<this->width(); j++)
            {
                if(grid[i*this->width()+j].getState() == 2)
                {
                    qDebug() << "Supposed initial";
                    this->frontalMoore(i, j);
                }
            }
        }
    }

    this->GLOBALTIME += 0.2;
    for(int i = 0; i < this->front.length(); i++)
    {
        if(front[i].time < this->GLOBALTIME)
        {
            //qDebug() << "Pop! x = " << front[i].x << " y = " << front[i].y;
            // zamień go na state 2
            grid[front[i].x*this->width()+front[i].y].setState(2);
            // wrzuć martwych (==0) sąsiadów na front
            this->frontalMoore(front[i].x, front[i].y);
            // wychodzi z frontu, koniec zmian
            front.removeAt(i);
        }
    }
    //qDebug() << "Globaltime = " << this->GLOBALTIME;
    //qDebug() << "front.size = " << front.size();
}

void gridwidget::frontalMoore(int i, int j)
{

    //QList<Cell> neighbours;
    int current;

    // if the nieghbour is "0", put'm on the front

    if(this->periodic)
    {
        // 0
        current = (((i+this->height())-1)%this->height())*this->width() + ((j+this->width())-1)%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
            front.append(grid[ current ]);
        }
        // 1
        current = (((i+this->height())-1)%this->height() )*this->width() + ((j+this->width()))%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
            front.append(grid[ current ]);
        }

        // 2
        current = (((i+this->height())-1)%this->height())*this->width() + ((j+this->width())+1)%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
            front.append(grid[ current ]);
        }

        // 3
        current = (((i+this->height()))%this->height())*this->width() + ((j+this->width())-1)%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
            front.append(grid[ current ]);
        }

        // 5
        current = (((i+this->height()))%this->height())*this->width() + ((j+this->width())+1)%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
            front.append(grid[ current ]);
        }

        // 6
        current = (((i+this->height())+1)%this->height())*this->width() + ((j+this->width())-1)%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
            front.append(grid[ current ]);
        }

        // 7
        current = (((i+this->height())+1)%this->height())*this->width() + ((j+this->width()))%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
            front.append(grid[ current ]);
        }

        // 8
        current = (((i+this->height())+1)%this->height())*this->width() + ((j+this->width())+1)%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
            front.append(grid[ current ]);
        }
    }
    else
    {
        // 0
        //qDebug () << "DEBUG 1";
        if(!( ((i-1)<0) || ((i-1)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
        {
            current = (i-1)*this->width() + (j-1);
            if(grid[ current ].state ==  0)
            {

                grid[ current ].setState(1);
                //grid[ current ].assignTime(i, j, this->GLOBALTIME);
                grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
                front.append(grid[ current ]);
            }
        }

        //neighbours.append(grid[ (i-1)*this->width() + (j-1)]);
        // 1
        if(!( ((i-1)<0) || ((i-1)>this->height()-1) || ((j)<0) || ((j)>this->width()-1) ))
        {
            current = (i-1)*this->width() + (j);
            if(grid[ current ].state ==  0)
            {
                grid[ current ].setState(1);
                //grid[ current ].assignTime(i, j, this->GLOBALTIME);
                grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
                front.append(grid[ current ]);
            }
        }
            //if(grid[ (i-1)*this->width() + (j)] ==  1)
            //    neighbours.append(grid[ (i-1)*this->width() + j]);
        // 2
        if(!( ((i-1)<0) || ((i-1)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
        {
            current = (i-1)*this->width() + (j+1);
            if(grid[ current ].state ==  0)
            {
                grid[ current ].setState(1);
                //grid[ current ].assignTime(i, j, this->GLOBALTIME);
                grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
                front.append(grid[ current ]);
            }
        }

            //if(grid[ (i-1)*this->width() + (j+1)] ==  1)
            //    neighbours.append(grid[ (i-1)*this->width() + (j+1)]);
        // 3
        if(!( ((i)<0) || ((i)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
        {
            current = (i)*this->width() + (j-1);
            if(grid[ current ].state ==  0)
            {
                grid[ current ].setState(1);
                //grid[ current ].assignTime(i, j, this->GLOBALTIME);
                grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
                front.append(grid[ current ]);
            }
        }

            //if(grid[ (i)*this->width() + (j-1)] ==  1)
            //neighbours.append(grid[ i*this->width() + (j-1)]);
        // 5
        if(!( ((i)<0) || ((i)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
        {
            current = (i)*this->width() + (j+1);
            if(grid[ current ].state ==  0)
            {
                grid[ current ].setState(1);
                //grid[ current ].assignTime(i, j, this->GLOBALTIME);
                grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
                front.append(grid[ current ]);
            }
        }
            //if(grid[ (i)*this->width() + (j+1)] ==  1)
            //    neighbours.append(grid[ i*this->width() + (j+1)]);
        // 6
        if(!( ((i+1)<0) || ((i+1)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
        {
            current = (i+1)*this->width() + (j-1);
            if(grid[ current ].state ==  0)
            {
                grid[ current ].setState(1);
                //grid[ current ].assignTime(i, j, this->GLOBALTIME);
                grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
                front.append(grid[ current ]);
            }
        }
            //if(grid[ (i+1)*this->width() + (j-1)] ==  1)
            //    neighbours.append(grid[ (i+1)*this->width() + (j-1)]);
        // 7
        if(!( ((i+1)<0) || ((i+1)>this->height()-1) || ((j)<0) || ((j)>this->width()-1) ))
        {
            current = (i+1)*this->width() + (j);
            if(grid[ current ].state ==  0)
            {
                grid[ current ].setState(1);
                //grid[ current ].assignTime(i, j, this->GLOBALTIME);
                grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
                front.append(grid[ current ]);
            }
        }

            //if(grid[ (i+1)*this->width() + (j)] ==  1)
            //    neighbours.append(grid[ (i+1)*this->width() + (j)]);
        // 8
        if(!( ((i+1)<0) || ((i+1)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
        {
            current = (i+1)*this->width() + (j+1);
            if(grid[ current ].state ==  0)
            {
                grid[ current ].setState(1);
                //grid[ current ].assignTime(i, j, this->GLOBALTIME);
                grid[ current ].assignTime(this->height()/2, this->width()/2, this->GLOBALTIME);
                front.append(grid[ current ]);
            }
        }

            //if(grid[ (i+1)*this->width() + (j+1)] ==  1)
            //    neighbours.append(grid[ (i+1)*this->width() + (j+1)]);
        //qDebug () << "DEBUG 2";
    }

    //return neighbours;
}
