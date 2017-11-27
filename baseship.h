#ifndef BASESHIP_H
#define BASESHIP_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class BaseShip : public QGraphicsItem
{
public:
    BaseShip();
    int x,y,height,width;
    QPixmap image;

};

#endif // BASESHIP_H
