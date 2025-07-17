#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsItem>
#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QGraphicsScene>
#include <QMovie>
#include <QPainter>
#include "plant.h"

class Zombie : public QGraphicsItem
{
public:
    int hp;
    int atk;
    int state;
    qreal speed;
    enum{Type = UserType + 2};
public:
    Zombie();
    ~Zombie() override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type() const override;
    void setMovie(QString path);
    void setHead(QString path);
protected:
    QMovie *movie;
    QMovie *head;
};

#endif // ZOMBIE_H
