#ifndef BASICZOMBIE_H
#define BASICZOMBIE_H

#include "zombie.h"
#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class BasicZombie : public Zombie
{
public:
    BasicZombie();
    void advance(int phase) override;
};

#endif // BASICZOMBIE_H
