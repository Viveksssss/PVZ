#ifndef REPEATER_H
#define REPEATER_H

#include "plant.h"
#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "zombie.h"
#include "pea.h"

class Repeater : public Plant
{
public:
    Repeater();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};

#endif // REPEATER_H
