#include "card.h"
#include "shop.h"
#include <QDrag>
#include <QMimeData>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include <QApplication>


const QMap<QString ,int> Card::map = {
    {"SunFlower",0},
    {"Peashooter",1},
    {"CherryBomb",2},
    {"WallNut",3},
    {"SnowPea",4},
    {"PotatoMine",5},
    {"Repeater",6},
};

const QVector<QString> Card::name = {
    "SunFlower",
    "Peashooter",
    "CherryBomb",
    "WallNut",
    "SnowPea",
    "PotatoMine",
    "Repeater",
};

const QVector<int> Card::cost = {50,100,150,50,172,25,200};

const QVector<int> Card::cool = {227,227,606,606,227,606,227};

Card::Card(QString s){
    text = s;
    counter = 0;
}

QRectF Card::boundingRect() const{
    return QRectF(-50,-30,100,60);
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->scale(0.6,0.58);
    painter->drawPixmap(QRect(-50,-70,100,140),QPixmap(":/images/Card.png"));
    painter->drawPixmap(QRect(-35,-42,70,70),QPixmap(":/images/"+text+".png"));
    QFont font;
    font.setPointSizeF(15);
    painter->drawText(-30, 60, QString("%1").arg(cost[map[text]], 3));

    // 绘制黑色的冷却框
    if(counter<cool[map[text]]){
        QBrush brush(QColor(0,0,0,200));
        painter->setBrush(brush);
        painter->drawRect(QRectF(-48,-68,98,132 * (1 - counter / cool[map[text]])));
    }
}

void Card::advance(int phase){
    if(!phase)return;
    update();
    if(counter<cool[map[text]]){
        ++counter;
    }
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(counter<cool[map[text]]){
        event->setAccepted(false);
    }

    Shop*shop = static_cast<Shop*>(parentItem());
    if(cost[map[text]]>(shop->sun))
        event->setAccepted(false);
    setCursor(Qt::ArrowCursor);
}

// 处理卡牌鼠标移动事件（实现拖拽逻辑）
void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // ===== 1. 检查是否达到拖拽触发距离 =====
    // 计算鼠标当前位置与左键按下位置的距离
    // QApplication::startDragDistance() 返回系统默认的最小拖拽距离（通常5-10像素）
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
        < QApplication::startDragDistance()) {
        return; // 移动距离不足，不触发拖拽
    }

    // ===== 2. 创建拖拽对象 =====
    QDrag* drag = new QDrag(event->widget());  // 参数为事件源控件（卡牌所在的视图控件）

    // ===== 3. 准备拖拽数据 =====
    QMimeData* mime = new QMimeData;
    // 加载卡牌对应植物的图片资源（根据text变量如"SunFlower"）
    QImage image(":/images/" + text + ".png");

    // 设置MIME数据（两种格式备用）：
    mime->setText(text);                  // 文本格式存储植物类型（如"SunFlower"）
    mime->setImageData(image);            // 图像格式存储卡牌图片

    drag->setMimeData(mime);              // 关联数据到拖拽对象

    // ===== 4. 设置拖拽视觉效果 =====
    drag->setPixmap(QPixmap::fromImage(image));  // 拖拽时跟随的缩略图
    drag->setHotSpot(QPoint(35,35));            // 鼠标在缩略图中的锚点位置（居中偏下）

    // ===== 5. 执行拖拽操作 =====
    // exec()会阻塞直到拖拽完成，返回拖拽结果（但此处未使用返回值）
    drag->exec();

    // ===== 6. 恢复光标样式 =====
    setCursor(Qt::ArrowCursor);  // 拖拽结束后重置为默认箭头光标
}

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ArrowCursor);

}
