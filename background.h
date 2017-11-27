#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Background : public QGraphicsItem
{
public:
    Background();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPixmap image;
    int highscore = 0, lifes = 3;

};

#endif // BACKGROUND_H
