#ifndef PLANT_H
#define PLANT_H

#include <QGraphicsItem>
#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QMovie>
#include <QPainter>
#include <QGraphicsScene>

class Plant : public QGraphicsItem
{
public:
    int hp;
    int state;
    enum{Type = UserType + 1};
    Plant();
    ~Plant();
    QRectF boundingRect()const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type()const override;
    void setMovie(QString path);
protected:
    QMovie*movie;
    int atk;
    int counter;
    int time;
};

#endif // PLANT_H
