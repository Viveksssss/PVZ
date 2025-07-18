#include "basiczombie.h"
#include <QRandomGenerator>
#include "plant.h"
BasicZombie::BasicZombie()
{
    hp = 270;
    atk = 100 * 33 / 1000;
    speed = 80.0 * 33 / 1000 / 4.7;
    if (QRandomGenerator::global()->bounded(100) % 2)
        setMovie(":/images/ZombieWalk1.gif");
    else
        setMovie(":/images/ZombieWalk2.gif");
}

void BasicZombie::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
    {
        if (state < 2)
        {
            state = 2;
            setMovie(":/images/ZombieDie.gif");
            setHead(":/images/ZombieHead.gif");
        }
        else if (movie->currentFrameNumber() == movie->frameCount() - 1)
            delete this;
        return;
    }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        Plant *plant = qgraphicsitem_cast<Plant *>(items[0]);
        plant->hp -= atk;
        if (state != 1)
        {
            state = 1;
            setMovie(":/images/ZombieAttack.gif");
        }
        return;
    }
    if (state)
    {
        state = 0;
        if (QRandomGenerator::global()->bounded(100) % 2)
            setMovie(":/images/ZombieWalk1.gif");
        else
            setMovie(":/images/ZombieWalk2.gif");
    }
    setX(x() - speed);
}
