#include "gridwidget.h"

#include <QDebug>
#include <QtGui>
#include <time.h>

gridwidget::gridwidget(QWidget *parent) :
    QWidget(parent)
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


void gridwidget::paintEvent(QPaintEvent *)
{
    //qDebug() << "Repaint set. h: " << this->height() << " w:" << width();

    QBrush noBrush("#ffffff");
    QBrush fullBrush("#27408B");
    QPainter painter(this);

    //qDebug() << "grid.size = " << grid.size();
    if(grid.size() > 0)
    {
        for(int i = 0; i < this->height(); i++)
        {
            for(int j = 0; j < this->width(); j++)
            {
                QRect rect(j, i, 1, 1);
                if(this->grid[i*this->height()+j] == 1) // replace with "alive" clause
                    painter.fillRect(rect, fullBrush);
                else if(this->grid[i*this->height()+j] == 0)
                    painter.fillRect(rect, noBrush);
                else
                    painter.fillRect(rect, noBrush);
            }
        }
    }
}

void gridwidget::primitiveSetUp()
{
    this->grid.clear();

    for(int i = 0; i < this->height()*this->width(); i++)
    {
        this->grid.append(0);
    }
    // specific

    this->grid[400/2*this->width()+ 400/2] = 1;

    this->repaint();
}

void gridwidget::setRuleset(int _r)
{
    this->ruleset = _r;
    qDebug() << "Ruleset " << this->ruleset;
}



QList<int> gridwidget::checkMoore(int i, int j)
{
    /*
     0|1|2
     3| |5
     6|7|8
     */
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


QList<int> gridwidget::checkMooreBaggins(int i, int j)
{
    /*
     0|1|2
     3| |5
     6|7|8
     */
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
    /*
      |1|
     3| |5
      |7|
     */
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

    /*
    if(this->getTicker() % 2 == 1)
        qDebug() << "Ticker even, = " << this->getTicker() << " , Moore.";
    else if(this->ticker % 2 == 0)
        qDebug() << "Ticker even, = " << this->getTicker() << " , VonNeumann.";
    */

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

// write ranP
double gridwidget::randP()
{
    return ((double)(qrand() % 101)) / 100;
}

QList<int> gridwidget::volatileMoore(int i, int j)
{
    /*
     0|1|2
     3| |5
     6|7|8
     */
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
    /*
      |1|
     3| |5
      |7|
     */
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
