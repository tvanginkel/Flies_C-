#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include "ship.h"
#include "laser.h"
#include "fly.h"
#include "background.h"
#include "text.h"
#include "global.h"
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void startGame();
    void moveFly();
    void laserMove();
    void laserCollides();
    void attack();
    void checklost();
    void nextLevel();
    QSet<int> pressedKeys;
    bool playing;
    Text *text;
    Ship *first;
    Background *map;

    ~MainWindow();

public slots:
    void updater();
    void flyupdater();
    void laserupdater();
    void attackupdater();
    void shootControl();
    void endGameupdater();
    void powerControler();
    void startTimers();



protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *shiptimer;
    QTimer *flytimer;
    QTimer *lasertimer;
    QTimer *attacktimer;
    QTimer *endGameTimer;
//    QTimer *delay;
};

#endif // MAINWINDOW_H
