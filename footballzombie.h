#ifndef FOOTBALLZOMBIE_H
#define FOOTBALLZOMBIE_H

#include "zombie.h"
#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class FootballZombie : public Zombie
{
public:
    FootballZombie();
    void advance(int phase) override;

};

#endif // FOOTBALLZOMBIE_H
