#ifndef MOWER_H
#define MOWER_H

#include "other.h"
#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "zombie.h"

/*
 *  小推车
    静止 → 碰到僵尸 → 启动秒杀 → 一路狂飙 → 出屏自杀
*/
class Mower : public Other
{
public:
    Mower();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;
    bool flag;
    qreal speed;
};

#endif // MOWER_H
