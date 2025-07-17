#include "sun.h"
#include <QRandomGenerator>
#include "mainwindow.h"
#include <QObject>
#include <QGraphicsSceneMouseEvent>
Sun::Sun()
{
    // shop = MainWindow::getShop();
    dest = QPointF(290 + QRandomGenerator::global()->bounded(82 * 7),130 + QRandomGenerator::global()->bounded(98 * 5));
    setPos(QPointF(dest.x(),70));
    speed = 60.0 * 50 / 1000;
    counter = 0;
    time = int(10.0 * 1000 / 33);
    movie = new QMovie(":/images/Sun.gif");
    movie -> start();

    // connect(this,&Sun::collected,shop,&Shop::addSun);
    setAcceptedMouseButtons(Qt::LeftButton);
}

Sun::Sun(QPointF pos)
{
    dest = QPointF(pos.x() + QRandomGenerator::global()->bounded(30) - 15,pos.y() + QRandomGenerator::global()->bounded(30) + 15);
    setPos(QPointF(dest.x(),dest.y()));
    speed = 60 * 50 / 1000;
    // 速度 = 60帧/秒 × 50像素/帧 ÷ 1000ms/秒 = 3.0像素/毫秒
    counter = 0;
    time = int(10.0 * 1000 / 33);
    movie = new QMovie(":/images/Sun.gif");
    movie->start();
    setAcceptedMouseButtons(Qt::LeftButton);
}

Sun::~Sun()
{
    if(movie)
        delete movie;
}

QRectF Sun::boundingRect() const
{
    return QRectF(-35,-35,70,70);
}

void Sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(boundingRect(),movie->currentImage());
}

void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Shop*shop = static_cast<Shop*>(scene()->items(QPointF(300,15))[0]);
    shop->sun+=500;
    counter = time;
    event->setAccepted(true);
}

void Sun::advance(int phase)
{
    if(!phase)
        return;
    update();
    if(++counter>=time)
        delete this;
    else if(y()<dest.y())
        setY(y()+speed);
}

