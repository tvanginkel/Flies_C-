#ifndef FLY_H
#define FLY_H
#include "baseship.h"

class Fly : public BaseShip
{
public:
    Fly();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPos(int x, int y);
    void set_y(int y);
    void set_x(int x);
    void setType(int type);
    int num;
    int type;
    int initialpos_x;
    int initialpos_y;
    int attack_movement = 0;
    int attack_pos;
    int attack_y,attack_x;
    int attack_mode;
    bool alive = false;
    bool attack = false;
    bool shot = false;
    bool set_attack = false;
};

#endif // FLY_H
