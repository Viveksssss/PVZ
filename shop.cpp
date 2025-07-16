#include "shop.h"


Shop::Shop()
{
    sun = 200;
    counter = 0;
    time = int(7.0 * 1000 / 33);
    Card*card = nullptr;
    for(int i = 0;i<Card::name.size();++i){
        card = new Card(Card::name[i]);
        card->setParentItem(this);
        card->setPos(-157 + 65 * i,-2);
    }
}

QRectF Shop::boundingRect() const{
    /*
        局部坐标系示意图（以商店为例）：
                  ↑ y
                  |
        -270      |       +270
          +-------+-------+
          |       |       |
          |       |(0,0)  |
          |      中心      |
        - +-------+-------+
          |       |       |
          |       |       |
          +-------+-------+
                  ←-------→ x
                 -45    +45
    */
    return QRectF(-270,-45,540,90);
}

void Shop::advance(int phase){
    if(!phase){
        return;
    }
    // 无需强制重绘，可能未发生变化
    // update();
    if(++counter>=time){
        counter = 0;
        scene()->addItem(new Sun);
    }
}


// 向场景中添加植物的函数
// 参数：
//   - s: 植物类型字符串标识（如"SunFlower"）
//   - pos: 要放置植物的场景坐标位置
void Shop::addPlant(QString s, QPointF pos) {
    // ===== 1. 检测目标位置是否已有植物 =====
    QList<QGraphicsItem*> items = scene()->items(pos);
    foreach(QGraphicsItem* item, items) {
        if(item->type() == Plant::Type)  // 如果该位置已有植物
            return;  // 直接返回，不重复放置
    }

    // ===== 2. 根据选择创建对应植物 =====
    Plant* plant = nullptr;
    switch(Card::map[s]) {  // 通过卡牌映射表获取植物类型编号
        case 0: plant = new SunFlower; break;   // 向日葵
        case 1: plant = new Peashooter; break;  // 豌豆射手
        case 2: plant = new CherryBomb; break;  // 樱桃炸弹
        case 3: plant = new WallNut; break;     // 坚果墙
        case 4: plant = new SnowPea; break;     // 寒冰射手
        case 5: plant = new PotatoMine; break;  // 土豆地雷
        case 6: plant = new Repeater; break;    // 双重射手
    }

    // ===== 3. 放置植物到场景 =====
    plant->setPos(pos);          // 设置植物位置
    scene()->addItem(plant);     // 添加到场景

    // ===== 4. 重置卡牌冷却 =====
    QList<QGraphicsItem*> child = childItems();  // 获取所有子项（卡牌）当前是商店，获取所有的卡牌
    foreach(QGraphicsItem* item, child) {
        Card* card = static_cast<Card*>(item);   // 转换为卡牌类型
        if(card->text == s) {    // 找到对应的卡牌
            card->counter = 0;    // 重置冷却计数器
        }
    }

    // ===== 5. 重置商店冷却 =====
    counter = 0;  // 全局冷却计数器归零
}













