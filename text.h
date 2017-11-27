#ifndef TEXT_H
#define TEXT_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtWidgets>
#include"global.h"

class Text: public QGraphicsItem
{
public:
    Text();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int x,y,w,h,highscore = 0,lifes = 3,level = 0,timeElapsed;
    bool over= false;
    bool completed = false;
};

#endif // TEXT_H
