#include "laser.h"

Laser::Laser()
{
    x=0;
    y=0;
    height = 50;
    width = 200;
    image.load(":/new/Images/laser.png");
}
//The area of the laser
QRectF Laser::boundingRect() const
{
    return QRectF(x + 60,y,width - 175,height - 40);
}
//Paints the laser in the scene
void Laser::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(x,y,width ,height,image);
}
void Laser::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}
