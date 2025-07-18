#include "mainwindow.h"
#include <QUrl>
#include <QRandomGenerator>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QAudioDevice>      // 音频设备类
#include <QMediaDevices>     // 音频设备管理
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QRandomGenerator::global()->bounded(uint(QTime(0,0,0).secsTo(QTime::currentTime())));
    // sound = new QSoundEffect;
    // sound->setSource(QUrl(":/images/Grazy Dave.mp3"));
    // sound->setLoopCount(QSoundEffect::Infinite);

    QMediaPlayer *sound = new QMediaPlayer;
    sound->setSource(QUrl::fromLocalFile("/home/vivek/Tmp/PVZ/Grazy Dave.mp3"));
    QAudioOutput *output = new QAudioOutput;
    output->setDevice(QMediaDevices::defaultAudioOutput());
    sound->setAudioOutput(output);
    sound->setLoops(QSoundEffect::Infinite);
    sound->play();

    timer = new QTimer;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(150, 0, 900, 600);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    Shop *shop = new Shop;
    shop->setPos(520, 45);
    scene->addItem(shop);
    Shovel *shovel = new Shovel;
    shovel->setPos(830, 40);
    scene->addItem(shovel);
    Button *button = new Button(sound, timer);
    button->setPos(970, 20);
    scene->addItem(button);
    Map *map = new Map;
    map->setPos(618, 326);
    scene->addItem(map);
    for (int i = 0; i < 5; ++i)
    {
        Mower *mower = new Mower;
        mower->setPos(210, 130 + 98 * i);
        scene->addItem(mower);
    }
    view = new QGraphicsView(scene, this);
    view->resize(902, 602);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/images/Background.jpg"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &MainWindow::addZombie);
    connect(timer, &QTimer::timeout, this, &MainWindow::check);
    // sound->setVolume(50);  // 设置音量
    // sound->play();



    timer->start(33);
    view->show();
}

MainWindow::~MainWindow()
{
    // delete sound;
    delete timer;
    delete scene;
    delete view;
}

void MainWindow::addZombie()
{
    static int low = 4;
    static int high = 8;
    static int maxtime = 20 * 1000 / 33;
    static int time = maxtime / 2;
    static int counter = 0;
    if (++counter >= time)
    {
        if (++low > high)
        {
            maxtime /= 1.3;
            high *= 2;
        }
        counter = 0;
        time = QRandomGenerator::global()->bounded(100) % (2 * maxtime / 3) + maxtime / 3;
        int type = QRandomGenerator::global()->bounded(10000) % 100;
        int i = QRandomGenerator::global()->bounded(100) % 5;
        Zombie *zombie;
        if (type < 40)
            zombie = new BasicZombie;
        else if (type < 70)
            zombie = new ConeZombie;
        else if (type < 80)
            zombie = new BucketZombie;
        else if (type < 90)
            zombie = new ScreenZombie;
        else
            zombie = new FootballZombie;
        zombie->setPos(1028, 130 + 98 * i);
        scene->addItem(zombie);
    }
}

void MainWindow::check()
{
    static int time = 1 * 1000 / 33;
    static int counter = 0;
    if (++counter >= time)
    {
        counter = 0;
        const QList<QGraphicsItem *> items = scene->items();
        foreach (QGraphicsItem *item, items)
            if (item->type() == Zombie::Type && item->x() < 200)
            {
                scene->addPixmap(QPixmap(":/images/ZombiesWon.png"))->setPos(336, 92);
                scene->advance();
                timer->stop();
                return;
            }
    }
}
