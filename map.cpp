#include "map.h"
#include "shovel.h"

Map::Map()
{
    dragOver = false;
    setAcceptDrops(true);
}

QRectF Map::boundingRect()const{
    return QRectF(-369,-235,738,470);
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

}

void Map::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData() -> hasText()){
        event->setAccepted(true);
        dragOver = true;
        update();
    }
    else
        event->setAccepted(false);
}

void Map::dragLeaveEvent(QGraphicsSceneDragDropEvent *event){
    dragOver = false;
    update();
}

void Map::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dragOver = false;
    if(event->mimeData()->hasText()){
        QString s = event->mimeData()->text();
        QPointF pos = mapToScene(event->pos());
        pos.setX((int(pos.x())-249) / 82 * 82 + 290);
        pos.setY((int(pos.y())-81) / 98 * 98 + 130);
        if(s == "Shovel"){
            Shovel*shovel = static_cast<Shovel*>(scene()->items(QPointF(830,15))[0]);
            shovel->removePlant(pos);
        }
        else{
            Shop*shop = static_cast<Shop*>(scene()->items(QPointF(300,15))[0]);
            shop->addPlant(s,pos);
        }
    }
    update();
}
