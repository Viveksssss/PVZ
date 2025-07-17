#ifndef MAP_H
#define MAP_H

#include "other.h"
#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QGraphicsSceneDragDropEvent>
#include "shop.h"
#include <QMimeData>

class Map : public Other
{
public:
    Map();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    bool dragOver;
};

#endif // MAP_H
