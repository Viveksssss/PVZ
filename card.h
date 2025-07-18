#ifndef CARD_H
#define CARD_H

#include "other.h"
#include <QObject>


class Card : public Other
{
public:
    Card();
    int counter;
    QString text;
    Card(QString s);
    const static QMap<QString ,int>map;
    const static QVector<QString> name;
    const static QVector<int>cost;
    const static QVector<int>cool;
    QRectF boundingRect()const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*item,QWidget*widget)override;
    void advance(int phase)override;
    void mousePressEvent(QGraphicsSceneMouseEvent*event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent*event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*event)override;
};

#endif // CARD_H
