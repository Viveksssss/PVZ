#ifndef BUCKETZOMBIE_H
#define BUCKETZOMBIE_H

#include "zombie.h"
#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class BucketZombie : public Zombie
{
public:
    BucketZombie();
    void advance(int phase) override;
};

#endif // BUCKETZOMBIE_H
