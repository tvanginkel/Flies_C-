#ifndef SHIP_H
#define SHIP_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "baseship.h"

class Ship : public BaseShip
{
public:
    Ship();
    QRectF boundingRect() const ;
    int power = 0;
    bool powerMode = false;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


};

#endif // SHIP_H
