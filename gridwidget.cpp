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


//------------------------------------------------------------

void gridwidget::primitiveSetUp()
{
    //this->grid.clear();

    for(int i = 0; i < this->height(); i++)
    {
        for(int j = 0; j < this->width(); j++)
        {
            Cell cell;
            cell.x = i;
            cell.y = j;
            cell.setState(0);
            cell.grain = NULL;

            this->grid.append(cell);
        }
    }

    this->addGrain();

    this->repaint();
}

void gridwidget::paintEvent(QPaintEvent *)
{
    //qDebug() << "Repaint set. h: " << this->height() << " w:" << width();


    QBrush noBrush("#ffffff");
    QBrush halfBrush("#D3D3D3");

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
                {
                    QBrush fullBrush(grains.at( grid[i*width()+j].grain ));
                    painter.fillRect(rect, fullBrush);
                }
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
    // happens once
    qDebug() << "State step";
    if(this->GLOBALTIME == 0)
    {
        for(int i = 0; i<this->height(); i++)
        {
            for(int j = 0; j<this->width(); j++)
            {
                if(grid[i*this->width()+j].getState() == 2)
                {
                    qDebug() << "Supposed initial" << i << ", " << j;
                    // pass center of the grain that causes the ruckus
                    //this->frontalMoore(i, j);
                    /*
                    this->frontalMoore(i,
                                       j,
                                       grainsx[grid[i*this->width()+j].grain],
                                       grainsy[grid[i*this->width()+j].grain]
                                      );
                                      */
                }
            }
        }
    }


    this->GLOBALTIME += 0.2;

    for(int i = 0; i < this->front.length(); i++)
    {
        if(front[i].time < this->GLOBALTIME)
        {
            //qDebug() << front[i].x <<", " << front[i].y << " time = " << front[i].time;

            //qDebug() << "Pop! x = " << front[i].x << " y = " << front[i].y;
            // zamień go na state 2
            grid[front[i].x*this->width()+front[i].y].setState(2);
            //this->frontalMoore(front[i].x, front[i].y);

            this->frontalMoore(front[i].x,
                               front[i].y,
                               grainsx[grid[front[i].x*this->width()+front[i].y].grain],
                               grainsy[grid[front[i].x*this->width()+front[i].y].grain]
                               );
            // wychodzi z frontu, koniec zmian
            front.removeAt(i);
        }
    }
}

void gridwidget::frontalMoore(int i, int j, int ci, int cj)
{

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
            grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
            // pilot for state
            grid[ current ].grain = grid[i*width() + j].grain;

            front.append(grid[ current ]);
        }
        // 1
        current = (((i+this->height())-1)%this->height() )*this->width() + ((j+this->width()))%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
            // pilot for state
            grid[ current ].grain = grid[i*width() + j].grain;

            front.append(grid[ current ]);
        }

        // 2
        current = (((i+this->height())-1)%this->height())*this->width() + ((j+this->width())+1)%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
            // pilot for state
            grid[ current ].grain = grid[i*width() + j].grain;

            front.append(grid[ current ]);
        }

        // 3
        current = (((i+this->height()))%this->height())*this->width() + ((j+this->width())-1)%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
            // pilot for state
            grid[ current ].grain = grid[i*width() + j].grain;

            front.append(grid[ current ]);
        }

        // 5
        current = (((i+this->height()))%this->height())*this->width() + ((j+this->width())+1)%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
            // pilot for state
            grid[ current ].grain = grid[i*width() + j].grain;

            front.append(grid[ current ]);
        }

        // 6
        current = (((i+this->height())+1)%this->height())*this->width() + ((j+this->width())-1)%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
            // pilot for state
            grid[ current ].grain = grid[i*width() + j].grain;

            front.append(grid[ current ]);
        }

        // 7
        current = (((i+this->height())+1)%this->height())*this->width() + ((j+this->width()))%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
            // pilot for state
            grid[ current ].grain = grid[i*width() + j].grain;

            front.append(grid[ current ]);
        }

        // 8
        current = (((i+this->height())+1)%this->height())*this->width() + ((j+this->width())+1)%this->width();
        if(this->grid[ current ].state == 0)
        {
            grid[ current ].setState(1);
            //grid[ current ].assignTime(i, j, this->GLOBALTIME);
            grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
            // pilot for state
            grid[ current ].grain = grid[i*width() + j].grain;

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
                grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
                // pilot for state
                grid[ current ].grain = grid[i*width() + j].grain;

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
                grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
                // pilot for state
                grid[ current ].grain = grid[i*width() + j].grain;

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
                grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
                // pilot for state
                grid[ current ].grain = grid[i*width() + j].grain;

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
                grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
                // pilot for state
                grid[ current ].grain = grid[i*width() + j].grain;

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
                grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
                // pilot for state
                grid[ current ].grain = grid[i*width() + j].grain;

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
                grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
                // pilot for state
                grid[ current ].grain = grid[i*width() + j].grain;

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
                grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
                // pilot for state
                grid[ current ].grain = grid[i*width() + j].grain;

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
                grid[ current ].assignTime(ci, cj, this->GLOBALTIME);
                // pilot for state
                grid[ current ].grain = grid[i*width() + j].grain;

                front.append(grid[ current ]);
            }
        }

            //if(grid[ (i+1)*this->width() + (j+1)] ==  1)
            //    neighbours.append(grid[ (i+1)*this->width() + (j+1)]);
        //qDebug () << "DEBUG 2";
    }

    //return neighbours;
}

void gridwidget::addGrain()
{
    int r = qrand()%256;
    int g = qrand()%256;
    int b = qrand()%256;
    QColor ncol(r, g, b, 255);

    int xx;
    int yy;
    do{
        xx = qrand() % this->height();
        yy = qrand() % this->width();

    } while( this->grid[xx*this->width()+yy].grain != NULL);

    this->grains.append(ncol);
    this->grainsx.append(xx);
    this->grainsy.append(yy);

    this->grid[xx*this->width()+yy].state = 2;
    this->grid[xx*this->width()+yy].grain = grains.length()-1;

    qDebug() << "Grain " <<     this->grid[xx*this->width()+yy].grain <<" at " << xx << ", " << yy;

    this->frontalMoore(xx,
                       yy,
                       xx,
                       yy
                      );

}
