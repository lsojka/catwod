#ifndef CELL_H
#define CELL_H


class Cell
{
public:

    int x;
    int y;
    int state; // 0, 1, 2
    int grain;
    double time;

    Cell();
    void assignTime(int _x, int _y, double _TIME, int height, int width, bool periodic);
    // method of calculcating the time
    // IN - (_x, _y) referentional ones

    int getState() const;
    void setState(int value);
    double getTime() const;
    void setTime(double value);
};

#endif // CELL_H
