#include "text.h"
#include<iostream>
using namespace std;

Text::Text()
{
    w=350;
    h=50;
    x=450;
    y=480;
}
//The area of the text
QRectF Text::boundingRect() const
{
    return QRect(x, y, w, h);
}
//Paints the text in the scene
void Text::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QFont font=painter->font() ;
    if (this->over ==true)
    {
        font.setPointSize ( 45 );
        QPen pen(Qt::red);
        painter->setPen(pen);
         painter->setFont(font);
         painter->drawText( x -175,y - 50, "GAME OVER" );
    }
    else
         {
        font.setPointSize ( 12 );
        QPen pen(Qt::red);
        painter->setPen(pen);
        painter->setFont(font);
        painter->drawText(100,30,"HIGHSCORE");
        pen.setColor(Qt::red);
        painter->setPen(pen);
        painter->drawText(100,60,QString::number(this->highscore));
        pen.setColor(Qt::red);
        painter->setPen(pen);
        painter->drawText(725,30,"LIFES");
        pen.setColor(Qt::red);
        painter->setPen(pen);
        painter->drawText(725,60,QString::number(this->lifes));
        pen.setColor(Qt::red);
        painter->setPen(pen);
        painter->drawText(425,30,"LEVEL");
        pen.setColor(Qt::red);
        painter->setPen(pen);
        painter->drawText(425,60,QString::number(this->level));
    }
    if (this->completed)
    {
        QPen pen(Qt::red);
        font.setPointSize (30);
        pen.setColor(Qt::green);
        painter->setFont(font);
        painter->setPen(pen);
        painter->drawText(x -150,y - 50,"WELL DONE");
        painter->drawText(x -250,y - 100,"YOU'VE COMPLETED THE GAME");
    }
}
