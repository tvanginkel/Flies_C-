#include "ship.h"
Ship::Ship()
{
    x=850 / 2;
    y=750;
    height = 75;
    width = 75;
    image.load(":/new/Images/Ship.png");
}
//The area of the ship
QRectF Ship::boundingRect() const
{
    return QRectF(x - 20,y,width ,height );
}
//Paints the ship in the scene
 void Ship::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
 {
     painter->drawPixmap(x,y,width,height,image);
 }
