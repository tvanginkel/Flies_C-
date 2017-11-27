#include "background.h"

Background::Background()
{

}
//The area of the background
QRectF Background::boundingRect() const
{
    return QRectF(0,0,850,900);
}
//Paints the background in the scene
void Background::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     painter->drawPixmap(0,0,850,900,image);
}
