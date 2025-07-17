#ifndef SUN_H
#define SUN_H

#include "other.h"
#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "shop.h"
#include <QObject>
class Shop;
class Sun :public QObject, public Other
{
    Q_OBJECT
public:
    Sun();
    Sun(QPointF pos);
    ~Sun() override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void advance(int phase) override;
private:
    QMovie *movie;
    QPointF dest;
    int counter;
    int time;
    qreal speed;
    Shop *shop;

};

#endif // SUN_H
