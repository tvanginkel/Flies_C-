#ifndef LASER_H
#define LASER_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "baseship.h"



class Laser : public QGraphicsItem
{
public:
    Laser();
    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPos(int x, int y);
    int x,y,height,width;
    QPixmap image;
    int direction;
    BaseShip *father;
    bool alive = false;


};

#endif // LASER_H
