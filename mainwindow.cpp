/* This game was made for a school project and still has some issues */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <iostream>
#include "ship.h"
#include "laser.h"
#include "background.h"
#include <QTime>

using namespace std ;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    //Setting up the ui
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    this->installEventFilter(this);

    scene->setSceneRect(00,00,850,900);
    ui->graphicsView->setSceneRect(scene->sceneRect());
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->show();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/new/Images/habitacion_moscas.jpg"));

    //Set the pos of every fly in the map
    for (int i = 0; i < 48; i++)
    {
        flies[i] = new Fly;
        flies[i]->num = i;
        if (i <4)
        {
        flies[i]->setPos((850-(65*4)) /2  +i *65, 70+(i/4) *50);
        flies[i]->type = 1;
        flies[i]->image.load(":/new/Images/flies1.png");
        }
        else if (i >3 && i<10)
        {
        flies[i]->setPos((850-(65*6)) /2 +(i-4) *65, 120 +(i/10)*50);
        flies[i]->type = 2;
        flies[i]->image.load(":/new/Images/flies2.png");
        }
        else if (i >9 && i<18)
        {
        flies[i]->setPos((850-(65*8))/2 +(i-10) *65, 200 +(i/18)*50);
        flies[i]->type = 3;
        flies[i]->image.load(":/new/Images/flies3.png");
        }
        else if (i >17 && i<28)
        {
        flies[i]->setPos((850-(65*10))/2 +(i - 18) *65, 250 +(i/28)*50);
        flies[i]->type =4;
        flies[i]->image.load(":/new/Images/flies4.png");
        }
        else if (i >27 && i<38)
        {
        flies[i]->setPos((850-(65*10))/2 +(i - 28) *65, 300 +(i/38)*50);
        flies[i]->type = 4;
        flies[i]->image.load(":/new/Images/flies4.png");
        }
        else if (i >37 && i<48)
        {
        flies[i]->setPos((850-(65*10))/2 +(i - 38) *65, 350 +(i/48)*50);
        flies[i]->type = 4;
        flies[i]->image.load(":/new/Images/flies4.png");
        }
        flies[i]->initialpos_x =  flies[i]->x;
        flies[i]->initialpos_y =  flies[i]->y;

        scene->addItem(flies[i]);
        }
    //Fill the lasers[] with lasers
    for (int i= 0; i < 10; i++)
    {
        lasers[i] = new Laser;
        lasers[i]->setOpacity(0);
        scene->addItem(lasers[i]);
    }
    //Creates timers
    shiptimer = new QTimer(this);
    shiptimer->setInterval(0);
    flytimer = new QTimer(this);
    flytimer->setInterval(8);
    lasertimer = new QTimer(this);
    lasertimer->setInterval(5);
    attacktimer = new QTimer(this);
    attacktimer->setInterval(700);
    endGameTimer= new QTimer(this);
    endGameTimer->setInterval(0);
    powerTimer=new QTimer(this);
    //Connects each timer to its function
    connect(shiptimer,SIGNAL(timeout()),this,SLOT(updater()));
    connect(flytimer,SIGNAL(timeout()),this,SLOT(flyupdater()));
    connect(lasertimer,SIGNAL(timeout()),this,SLOT(laserupdater()));
    connect(lasertimer,SIGNAL(timeout()),this,SLOT(laserupdater()));
    connect(attacktimer,SIGNAL(timeout()),this,SLOT(attackupdater()));
    connect(endGameTimer,SIGNAL(timeout()),this,SLOT(endGameupdater()));
    connect(powerTimer,SIGNAL(timeout()),this,SLOT(powerControler()));
    first = new Ship;
    map = new Background;
    //start the game
    startGame();
}
void MainWindow::startGame()
{
    // Set the flies opacity to 100
    for (int i = 0; i < 48; i++)
    {
        flies[i]->alive = true;
    }
    // Set lasers opacity to 0
    for (int i = 0; i < 10; i++)
    {
        lasers[i]->alive = false;
    }
    text =new Text;
    scene->addItem(first);
    scene->addItem(map);
    scene->addItem(text);
    text->setZValue(7);
    text->lifes = 3;
    text->level++;
    playing= true;
    first->setOpacity(100);
    this->show();
    scene->update();
    this->update();

    //Start the timers
    shiptimer->start();
    flytimer->start();
    lasertimer->start();
    attacktimer->start();
    endGameTimer->start();
    this->setFocus();
}
//Function called to go to the next level
void MainWindow::nextLevel()
{
    for (int i= 0; i < 48; i++)
    {
        flies[i]->alive = true;
        flies[i]->setOpacity(100);
    }
    for (int i= 0; i < 10; i++)
    {
        lasers[i]->alive = false;
        lasers[i]->setOpacity(0);
    }
    text->level++;
    if (text->level == 2)
    {
        ui->graphicsView->setBackgroundBrush(QPixmap(":/new/Images/nave_moscas.jpg"));
    }
    else if (text->level == 3)
    {
        ui->graphicsView->setBackgroundBrush(QPixmap(":/new/Images/planeta_moscas.jpg"));
    }
    first->x =850/2;
    first->y = 750;
}

// Updates the ship
void MainWindow::updater()
{
    this->setFocus();
    scene->update(map->boundingRect());
}
// Updates the flies
void MainWindow::flyupdater()
{
    attack();
    moveFly();
    this->setFocus();
    scene->update(map->boundingRect());
}
// Updates the lasers
void MainWindow::laserupdater()
{
    laserMove();
    laserCollides();
    this->setFocus();
    scene->update(map->boundingRect());
}
//Checks if you lost the game or you won
void MainWindow::endGameupdater()
{
    checklost();
    this->setFocus();
    scene->update(map->boundingRect());
}

//Decides when to attack and who will attack with rand()
void MainWindow::attackupdater()
{
    int randomattack4;
    int randomattack1;
    if (text->level == 1)
    {
        randomattack4 = qrand() % ((200 + 1) - 0) + 0;
        randomattack1 = qrand() % ((10 + 1) - 0) + 0;
    }
    else if (text->level == 2)
    {
      randomattack4 = qrand() % ((120 + 1) - 0) + 0;
      randomattack1 = qrand() % ((7 + 1) - 0) + 0;
    }
    else if (text->level == 3)
    {
      randomattack4 = qrand() % ((70 + 1) - 0) + 0;
      randomattack1 = qrand() % ((5 + 1) - 0) + 0;
    }

    //Decides when de flies type 4 will attack
    if (randomattack4 < 40 )
    {
        int randomfly4 = qrand() % ((47 + 1) - 18) + 18;
        //If the random fly is alive
        if (flies[randomfly4]->alive && flies[randomfly4]->attack != true)
        {
        flies[randomfly4]->attack = true;
        flies[randomfly4]->attack_x = flies[randomfly4]->x;
        flies[randomfly4]->attack_y = flies[randomfly4]->y;
        }
        //Else if it's death, get the nearest fly
        else if (flies[randomfly4]->alive != true && flies[randomfly4]->attack != true)
        {
            for (int i = randomfly4;i <48; i++ )
            {
                if (flies[i]->alive&& flies[i]->attack != true)
                {
                    flies[i]->attack = true;
                    flies[i]->attack_x = flies[i]->x;
                    flies[i]->attack_y = flies[i]->y;
                    break;
                }
                else if (i == 47)
                {
                    for (int a = randomfly4; a >= 0; a--)
                    {
                        if (flies[a]->alive&& flies[a]->attack != true)
                        {
                            flies[a]->attack = true;
                            flies[a]->attack_x = flies[a]->x;
                            flies[a]->attack_y = flies[a]->y;
                            break;
                        }
                    }
                }
            }
        }
    }
    // Decides when de flies type 1 and type 2 will attack
     else if (randomattack1 < 2 )
    {
        int type2 = 0;
        int randomfly1 = qrand() % ((3 + 1) - 0) + 0;
        int randomfly2_1 = qrand() % ((7 + 1) - 4) + 4;
        int randomfly2_2 = qrand() % ((7 + 1) - 4) + 4;
        for (int i = 0; i < 48; i++)
        {
            if (flies[i]->alive && flies[i]->type == 2)
                type2++;
        }
        //If type 1 it's alive and type 2 also is alive
        if (flies[randomfly1]->alive && flies[randomfly1]->attack != true
            && flies[randomfly2_1]->alive && flies[randomfly2_1]->attack != true
            && flies[randomfly2_2]->attack != true && randomfly2_1 != randomfly2_2)
        {
        flies[randomfly1]->attack = true;
        flies[randomfly1]->attack_x = flies[randomfly1]->x;
        flies[randomfly1]->attack_y = flies[randomfly1]->y;
        flies[randomfly2_1]->attack = true;
        flies[randomfly2_1]->attack_x = flies[randomfly2_1]->x;
        flies[randomfly2_1]->attack_y = flies[randomfly2_1]->y;
        flies[randomfly2_2]->attack = true;
        flies[randomfly2_2]->attack_x = flies[randomfly2_2]->x;
        flies[randomfly2_2]->attack_y = flies[randomfly2_2]->y;
        }
        //Else if type 1 is alive but type 2 is death
        else if ( type2<=1 && flies[randomfly1]->alive
                 && flies[randomfly1]->attack != true)
        {
            flies[randomfly1]->attack = true;
            flies[randomfly1]->attack_x = flies[randomfly1]->x;
            flies[randomfly1]->attack_y = flies[randomfly1]->y;
        }

    }
}
//Controls the time between shoots
void MainWindow::shootControl()
{
    shootInterval = true;   
}
// When it's called turn off the power
void MainWindow::powerControler()
{
    first->powerMode = false;
    first->power= 0;
}
//Check if you win or you loose the game
void MainWindow::checklost()
{

    for (int i = 0; i < 48; i++)
    {
        if (flies[i]->alive != true)
        {
            death++;
        }
    }

    if (text->lifes == 0)
    {
        playing = false;
        text->over = true;
        shiptimer->stop();
        lasertimer->stop();
        flytimer->stop();
        attacktimer->stop();

        for (int i = 0; i < 48; i++)
            flies[i]->setOpacity(0);
        for (int i = 0; i < 10; i++)
            lasers[i]->setOpacity(0);
        first->setOpacity(0);
    }

    else if (death == 48)
    {
        if (text->level==3)
        {
            text->completed= true;
            shiptimer->stop();
            lasertimer->stop();
            flytimer->stop();
            attacktimer->stop();
            for (int i = 0; i < 48; i++)
                flies[i]->setOpacity(0);
            for (int i = 0; i < 10; i++)
                lasers[i]->setOpacity(0);
            first->setOpacity(0);
        }
        else
        {
            nextLevel();
            death = 0;
        }

    }
        death= 0;
}
//Start all timers
void MainWindow::startTimers()
{
    shiptimer->start();
    flytimer->start();
    lasertimer->start();
    attacktimer->start();
    endGameTimer->start();
}
 // Checks all flies , and if they are attacking, they move
void MainWindow::attack()
{
    for (int i = 0; i < 48; i++)
    {
        if (flies[i]->alive && flies[i]->attack)
        {
            //If they touched the bottom of the map
            if (flies[i]->y >= 850)
            {
                flies[i]->attack = false;
                flies[i]->shot = false;
                flies[i]->y = flies[i]->attack_y;
                flies[i]->x = flies[i]->attack_x;
                flies[i]->set_attack = false;
                flies[i]->attack_movement = 0;
            }
            else
            {
                //Set the attack mode depending on the distance of each fly
                //from the ship
                if (flies[i]->set_attack == false)
                {
                    flies[i]->attack_pos = first->x;
                    if (first->x -200 <= flies[i]->x && first->x +200 >= flies[i]->x   )
                        flies[i]->attack_mode = 0;
                    else if (flies[i]->x < first->x)
                        flies[i]->attack_mode = 1;
                    else if (flies[i]->x > first->x)
                        flies[i]->attack_mode = 2;
                    flies[i]->set_attack= true;
                }
                else
                {
                    //If the fly attack_mode is 0 then attack in a specific mode
                    if (flies[i]->attack_mode == 0)
                    {
                        if (flies[i]->attack_movement  <= 100)
                        {
                       flies[i]->y += 2;
                       flies[i]->x +=2;
                      flies[i]->attack_movement++;
                        }
                       else if (flies[i]->attack_movement >100
                                && flies[i]->attack_movement <= 300 )
                       {
                       flies[i]->y += 1;
                       flies[i]->x -=1.5;
                       flies[i]->attack_movement++;
                        }
                       else if (flies[i]->attack_movement >300
                                && flies[i]->attack_movement <= 500)
                        {
                            flies[i]->y += 2;
                            flies[i]->x +=2;
                            flies[i]->attack_movement++;
                        }
                        else if (flies[i]->attack_movement >500
                                 && flies[i]->attack_movement <= 800)
                        {
                            flies[i]->y += 2;
                            flies[i]->x -=2;
                            flies[i]->attack_movement++;
                        }

                     }
                    else if (flies[i]->attack_mode == 1)
                    {
                        flies[i]->y += 2;
                        flies[i]->x +=2;
                        flies[i]->attack_movement++;
                    }
                    else if (flies[i]->attack_mode == 2)
                    {
                        flies[i]->y += 2;
                        flies[i]->x -=2;
                        flies[i]->attack_movement++;
                    }
                }
                //If they are near the ship then shoot
                if ( flies[i]->alive &&first->y -flies[i]->y <= 350 && flies[i]->shot == false)
                {
                    for (int a = 0; a < 10; a++)
                    {
                        if (lasers[a]->alive == false)
                        {
                            lasers[a]->alive = true;
                            lasers[a]->father = flies[i];
                            lasers[a]->direction = 0;
                            lasers[a]->setOpacity(100);
                            lasers[a]->setPos(lasers[a]->father->x - 65,lasers[a]->father->y);
                            flies[i]->shot = true;
                            break;
                        }
                    }

                }
            }
        }
        //If they die while attacking then erase them
        else if (flies[i]->alive == false && flies[i]->attack)
        {
            flies[i]->y = flies[i]->attack_y;
            flies[i]->x = flies[i]->attack_x;
            flies[i]->attack_movement= 0;
            flies[i]->attack=false;
            flies[i]->setOpacity(0);
        }
    }
}

// Move the flies
void MainWindow::moveFly()
{
    if (startflies == false)
    {
        for (int i = 0; i < 100; i++)
        {
            for (int a = 0; a < 48; a++)
            {
                if (flies[a]->attack == true)
                flies[a]->attack_x -= 1;
                else
                flies[a]->x -= 1;
            }
        }
        startflies= true;
    }
    else if (flymovement <200 )
    {
        for (int i = 0; i < 48; i++)
        {
             if (flies[i]->attack == true)
             flies[i]->attack_x += 1;
             else
             flies[i]->x += 1;
        }
        flymovement++;
    }
    else
    {
        for (int i = 0; i < 48; i++)
        {
             if (flies[i]->attack == true)
             flies[i]->attack_x -= 1;
             else
             flies[i]->x -= 1;
        }
        flymovement++;
        if (flymovement == 400)
        {
            flymovement = 0;
        }
    }

}
//Move the lasers
void MainWindow::laserMove()
{
    for (int i = 0; i < 10; i++)
    {
        if (lasers[i]->alive)
        {
            //If the laser is direction 1 (Means the ship shot it)
            if (lasers[i]->direction == 1)
            {
                 if ( lasers[i]->y == 0)
                 {
                   lasers[i]->alive = false;
                   lasers[i]->setOpacity(0);
                 }
                 else
                  lasers[i]->y -=2;
            }
            //If the laser is direction 0 (Means the fly shot it)
            else if (lasers[i]->direction == 0)
            {
                if ( lasers[i]->y == 850)
                {
                  lasers[i]->alive = false;
                  lasers[i]->setOpacity(0);
                }
                else
                 lasers[i]->y += 1;
            }
        }
    }
}
//Detects lasers collision with flies
void MainWindow::laserCollides()
{
    for (int i =0; i <10; i++ )
    {
        if (lasers[i]->alive)
        {
           for (int a =0; a <48; a++ )
            {
               //If the ship shot the laser and it's touching a fly
              if (flies[a]->alive&& lasers[i]->direction == 1
                  &&lasers[i]->collidesWithItem(flies[a]))
              {
                  if (flies[a]->type == 1)
                  {
                      if(flies[a]->attack)
                      {
                          text->highscore += 20;
                          first->power=qrand() % ((3 + 1) - 1) + 1;
                          first->powerMode = true;
                          if (first->power==1 || first->power == 3)
                          {
                             powerTimer->setInterval(20000);
                             powerTimer->start();
                          }
                          else if(first->power==2)
                          {
                             powerTimer->setInterval(10000);
                             powerTimer->start();
                          }

                      }
                      else
                      {
                           text->highscore += 15;
                      }
                  }
                  else if (flies[a]->type == 2)
                  {
                      if(flies[a]->attack)
                      {
                          text->highscore += 12;
                      }
                      else
                      {
                           text->highscore += 10;
                      }
                  }
                  else if (flies[a]->type == 3)
                  {
                      if(flies[a]->attack)
                      {
                          text->highscore += 5;
                      }
                      else
                      {
                           text->highscore += 5;
                      }
                  }
                  else if (flies[a]->type == 4)
                  {
                      if(flies[a]->attack)
                      {
                          text->highscore += 2;
                      }
                      else
                      {
                           text->highscore += 1;
                      }
                  }
                lasers[i]->alive = false;
                flies[a]->alive = false;
                lasers[i]->setOpacity(0);
                flies[a]->setOpacity(0);
              }
               //If the fly shot the laser  and it's touching the ship
              else if (flies[a]->alive&& lasers[i]->direction == 0
                       &&lasers[i]->collidesWithItem(first))
              {
                  lasers[i]->alive = false;
                  lasers[i]->setOpacity(0);
                  text->lifes--;
                  break;
              }
               //If the ship collides with a fly
              else if (flies[a]->alive &&first->collidesWithItem(flies[a])
                       && text->lifes > 0)
              {
                  flies[a]->alive = false;
                  flies[a]->setOpacity(0);
                  text->lifes--;
                  break;
              }
            }
        }
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int num = 0;
    // If you press the left key move the ship to the left
    if (event->key() == Qt::Key_Left)
    {
        //If the power 3 is active then move faster
        if (first->powerMode && first->power == 3)
            first->x -=30;
        else
        first->x -= 15;
    }
        // If you press the right key move the ship to the left
    if (event->key()== Qt::Key_Right)
    {
        //If the power 3 is active then move faster
        if (first->powerMode && first->power == 3)
            first->x += 30;
        else
            first->x += 15;
    }
    // If you press the space key shoot
     if (event->key() == Qt::Key_Space)
    {
        for (int i = 0; i < 10; i++)
        {
            if (lasers[i]->alive == false )
            {
                //If the power 2 is active then shoot without delay
               if (first->powerMode &&first->power == 2)
                {
                    lasers[i]->alive = true;
                    lasers[i]->father = first;
                    lasers[i]->setOpacity(100);
                    lasers[i]->direction = 1;
                    lasers[i]->setPos(lasers[i]->father->x - 60,lasers[i]->father->y);
                    break;
                }
                else if (shootInterval)
                {
                    //If the power 1 is active then shoot three lasers at the same time
                   if (first->powerMode &&first->power == 1)
                   {
                       lasers[i]->alive = true;
                       lasers[i]->father = first;
                       lasers[i]->setOpacity(100);
                       lasers[i]->direction = 1;
                       lasers[i]->setPos(lasers[i]->father->x - 60
                                         ,lasers[i]->father->y);
                       for (int a = 0; a < 10; a++)
                       {
                           if (lasers[a]->alive == false)
                           {
                               lasers[a]->alive = true;
                               lasers[a]->father = first;
                               lasers[a]->setOpacity(100);
                               lasers[a]->direction = 1;
                               lasers[a]->setPos(lasers[i]->father->x - 60
                                                 ,lasers[i]->father->y);
                               num++;
                               if (num==2)
                                   break;
                           }
                       }
                       QTimer::singleShot(700,this,SLOT(shootControl()));
                       shootInterval = false;
                       break;
                   }
                   else
                   {
                       lasers[i]->alive = true;
                       lasers[i]->father = first;
                       lasers[i]->setOpacity(100);
                       lasers[i]->direction = 1;
                       lasers[i]->setPos(lasers[i]->father->x - 60,lasers[i]->father->y);
                       QTimer::singleShot(700,this,SLOT(shootControl()));
                       shootInterval = false;
                       break;

                   }
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
