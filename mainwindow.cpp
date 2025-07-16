#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "shop.h"
#include "card.h"
#include <shovel.h>
#include <button.h>
#include "map.h"
#include "mower.h"
#include "basiczombie.h"
#include "conezombie.h"
#include "bucketzombie.h"
#include "screenzombie.h"
#include "footballzombie.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);
    // 背景音乐
    sound = new QSoundEffect();
    sound->setSource(QUrl::fromLocalFile(":/images/Grazy Dave.mp3"));
    sound->setLoopCount(QSoundEffect::Infinite);

    // 定时器
    timer = new QTimer;

    // 游戏场景
    scene = new QGraphicsScene(this);
    scene->setSceneRect(150,0,900,600);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    // (0,0)
    //   +---------------------------+
    //   |       |                   |
    //   |       | 900x600           |
    //   |       |                   |
    //   +---------------------------+（1050,600）


    // 商店
    Show*shop = new Shop;
    shop->setPos(520,45);
    scene->addItem(shop);

    // 铲子
    Shovel*shovel = new Shovel;
    shovel->setPos(830,40);
    scene->addItem(shovel);

    // 控制按钮
    Button*button = new Button(sound,timer);
    button->setPos(970,20);
    scene->addItem(button);

    // 地图背景
    Map*map = new Map;
    map->setPos(618,326);
    scene->addItem(map);

    // 添加五个小推车
    for(int i = 0; i < 5; ++i){
            Mower* mower = new Mower;
            // Y坐标计算：130 + 98*i（保持等距排列）
            mower->setPos(210, 130 + 98*i);  // 放置在每行最左侧
            scene->addItem(mower);
        }

    // ==================== 视图设置 ====================
    view = new QGraphicsView(scene,this);
    view->resize(902,602);  // 视图窗口大小（略大于场景逻辑尺寸）
    view->setRenderHint(QPainter::Antialiasing);  // 启用抗锯齿
    view->setBackgroundBrush(QPixmap(":/images/Background.jpg"));  // 设置背景图
    view->setCacheMode(QGraphicsView::CacheBackground);  // 缓存背景提升性能
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);  // 渲染优化

    // ==================== 游戏逻辑连接 ====================
    // 定时器信号连接：
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);  // 推进所有场景项
    connect(timer, &QTimer::timeout, this, &MainWindow::addZombie);     // 僵尸生成逻辑
    connect(timer, &QTimer::timeout, this, &MainWindow::check);         // 游戏状态检查

    // ==================== 启动游戏 ====================
    sound->play();      // 播放背景音乐
    timer->start(33);   // 启动游戏循环（33ms间隔≈30FPS）
    view->show();       // 显示主视图

}

MainWindow::~MainWindow()
{
    delete sound;
    delete timer;
    delete scene;
    delete view;
}

void MainWindow::addZombie()
{
    // 静态变量（持久化，函数多次调用时保留值）
    static int low = 4;          // 当前波次已生成僵尸数量
    static int high = 8;         // 当前波次僵尸数量上限
    static int maxtime = 20 * 1000 / 33;  // 最大生成间隔（基于33FPS，约20秒）
    static int time = maxtime / 2;        // 实际生成间隔（初始约10秒）
    static int counter = 0;      // 计数器，统计调用次数

    // 检查是否达到生成条件
    if (++counter >= time) {     // 每次调用counter+1，超过time时生成僵尸
        // 难度提升逻辑：当生成数量low超过上限high时
        if (++low > high) {      // low自增并检查
            maxtime /= 1.3;      // 缩短最大间隔（僵尸更快出现）
            high *= 2;           // 提高下一波僵尸数量上限
        }

        // 重置计数器和随机生成间隔
        counter = 0;
        time = QRandomGenerator::global()->bounded(2 * maxtime / 3) + maxtime / 3;
        // time ∈ [maxtime/3, maxtime]，避免过于规律

        // 随机生成僵尸类型
        int type = QRandomGenerator::global()->bounded(100);  // 0~99随机数
        Zombie *zombie;
        if (type < 40)       zombie = new BasicZombie;    // 40% 普通僵尸
        else if (type < 70)  zombie = new ConeZombie;     // 30% 路障僵尸
        else if (type < 80)  zombie = new BucketZombie;   // 10% 铁桶僵尸
        else if (type < 90)  zombie = new ScreenZombie;   // 10% 屏幕门僵尸
        else                 zombie = new FootballZombie; // 10% 橄榄球僵尸

        // 随机选择行（0~4）
        int i = QRandomGenerator::global()->bounded(5);
        // 设置僵尸初始位置（x=1028屏幕右侧，y按行偏移）
        zombie->setPos(1028, 130 + 98 * i);
        // 添加到场景
        scene->addItem(zombie);
    }
}

void MainWindow::check()
{
    static int time = 1 * 1000 / 33;
    static int counter = 0;
    if(++counter >= time){
        counter = 0;
        const QList<QGraphicsItem*>items = scene->items();
        foreach(QGraphcisItem*item,items){
            if(item->type() == Zombie::Type && item->x() < 200){
                scene->addPixmap(QPixmap(":/images/ZombiesWon.png"))->setPos(336,92);
                scene->advance();
                timer->stop();
                return;
            }
        }
    }
}
