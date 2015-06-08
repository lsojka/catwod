#include "cell.h"


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

