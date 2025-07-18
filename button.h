#ifndef BUTTON_H
#define BUTTON_H

#include "other.h"
#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QSoundEffect>
#include <QMediaPlayer>
class QTimer;
class QGraphicsSceneMouseEvent;
class QStyleOptionGraphicsItem;
class Button : public Other
{
public:
    Button(QMediaPlayer*s,QTimer*t);
    QRectF boundingRect()const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QMediaPlayer *sound;
    QTimer *timer;
};

#endif // BUTTON_H
