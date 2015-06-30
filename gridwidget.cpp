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

    if(grid.size() < this->height()*this->width() + 1)
    {
    for(int i = 0; i < this->height(); i++)
    {
        for(int j = 0; j < this->width(); j++)
        {
            Cell cell;
            cell.x = i;
            cell.y = j;
            cell.setState(0);
            cell.grain = -1; // NULLTEST

            this->grid.append(cell);
        }
    }
    }
    for(int i = 0; i < 10; i++)
        this->addGrain();

    this->repaint();
}

void gridwidget::paintEvent(QPaintEvent *)
{
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
    qDebug() << "Globaltime = " << GLOBALTIME << ", periodic = " << this->periodic;

    this->GLOBALTIME += 0.2;

    for(int i = 0; i < this->front.length(); i++)
    {
        if(front[i].time < this->GLOBALTIME)
        {
            grid[front[i].x*this->width()+front[i].y].setState(2);

            this->multigrainMoore(front[i].x,
                               front[i].y,
                               grainsx[grid[front[i].x*this->width()+front[i].y].grain],
                               grainsy[grid[front[i].x*this->width()+front[i].y].grain]
                               );

            front.removeAt(i);
        }
    }
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

    } while( this->grid[xx*this->width()+yy].grain != -1); // NULLTEST

    this->grains.append(ncol);
    this->grainsx.append(xx);
    this->grainsy.append(yy);

    this->grid[xx*this->width()+yy].state = 2;
    this->grid[xx*this->width()+yy].grain = grains.length()-1;

    //qDebug() << "Grain " <<     this->grid[xx*this->width()+yy].grain <<" at " << xx << ", " << yy;
    this->multigrainMoore(xx, yy, xx, yy);
}

void gridwidget::multigrainMoore(int i, int j, int ci, int cj)
{
    QList<int> currents;

    if(this->periodic)
    {
        //0
        currents.append((((i+this->height())-1)%this->height())*this->width() + ((j+this->width())-1)%this->width());
        //1
        currents.append((((i+this->height())-1)%this->height() )*this->width() + ((j+this->width()))%this->width());
        //2
        currents.append((((i+this->height())-1)%this->height())*this->width() + ((j+this->width())+1)%this->width());
        //3
        currents.append((((i+this->height()))%this->height())*this->width() + ((j+this->width())-1)%this->width());
        //5
        currents.append((((i+this->height()))%this->height())*this->width() + ((j+this->width())+1)%this->width());
        //6
        currents.append((((i+this->height())+1)%this->height())*this->width() + ((j+this->width())-1)%this->width());
        //7
        currents.append((((i+this->height())+1)%this->height())*this->width() + ((j+this->width()))%this->width());
        //8
        currents.append((((i+this->height())+1)%this->height())*this->width() + ((j+this->width())+1)%this->width());

        for(int k = 0; k < currents.length(); k++)
        {
            if(this->grid[currents[k]].state == 0)
            {
                grid[ currents[k] ].setState(1);
                grid[ currents[k] ].assignTime(ci, cj, this->GLOBALTIME, this->height(), this->width(),this->getPeriodic());
                // grain change - blatantly
                grid[ currents[k] ].grain = grid[ i*width() + j].grain;

                front.append(grid[ currents[k] ]);
                //qDebug() << "Currents["<<k<<"] = "<< currents[k] << "becomes " << grid[ currents[k] ].grain;
            }
        }

    }
    else
    {
        // 0
        if(!( ((i-1)<0) || ((i-1)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
            currents.append((i-1)*this->width() + (j-1));
        // 1
        if(!( ((i-1)<0) || ((i-1)>this->height()-1) || ((j)<0) || ((j)>this->width()-1) ))
            currents.append((i-1)*this->width() + (j));
        // 2
        if(!( ((i-1)<0) || ((i-1)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
            currents.append((i-1)*this->width() + (j+1));
        // 3
        if(!( ((i)<0) || ((i)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
            currents.append((i)*this->width() + (j-1));
        // 5
        if(!( ((i)<0) || ((i)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
            currents.append((i)*this->width() + (j+1));
        // 6
        if(!( ((i+1)<0) || ((i+1)>this->height()-1) || ((j-1)<0) || ((j-1)>this->width()-1) ))
            currents.append((i+1)*this->width() + (j-1));
        // 7
        if(!( ((i+1)<0) || ((i+1)>this->height()-1) || ((j)<0) || ((j)>this->width()-1) ))
            currents.append((i+1)*this->width() + (j));
        // 8
        if(!( ((i+1)<0) || ((i+1)>this->height()-1) || ((j+1)<0) || ((j+1)>this->width()-1) ))
            currents.append((i+1)*this->width() + (j+1));

        for(int k = 0; k < currents.length(); k++)
        {
            if(this->grid[currents[k]].state == 0)
            {
                grid[ currents[k] ].setState(1);
                grid[ currents[k] ].assignTime(ci, cj, this->GLOBALTIME, this->height(), this->width(), this->getPeriodic());
                // grain change - blatantly
                grid[ currents[k] ].grain = grid[ i*width() + j].grain;

                front.append(grid[ currents[k] ]);
                //qDebug() << "Currents["<<k<<"] = "<< currents[k] << "becomes " << grid[ currents[k] ].grain;
            }
        }
    }
}
