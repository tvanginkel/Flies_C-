#include "fly.h"

Fly::Fly()
{
    x = 0;
    y = 0;
    height = 60;
    width = 60;
}
//The area of the fly
QRectF Fly::boundingRect() const
{
    return QRectF(x,y,width -47 ,height );
}
//Paints the fly in the scene
void Fly::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(x,y,width,height,image);
}
void Fly::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}
void Fly::set_x(int x)
{
    this->x = x;
}
void Fly::set_y(int y)
{
    this->y = y;
}
void Fly::setType(int type)
{
    this->type = type;
}
