#ifndef GLOBAL_H
#define GLOBAL_H
#include "fly.h"
#include "laser.h"
#include "ship.h"

 static Fly *flies [48];
 static Laser *lasers [10];
 static int flymovement = 0;
 static int death= 0;
 static bool startflies = false;
 static bool shootInterval = true;
 static QTimer *powerTimer;


#endif // GLOBAL_H

