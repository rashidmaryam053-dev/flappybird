#include "scene.h"
#include "pillaritem.h"
#include <QGraphicsPixmapItem>

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    over = false;
    started = false;
    score = 0;

    setSceneRect(-250, -300, 500, 600);//right bottom left top (anticlockwise)

    // SCORE
    scoreText = new QGraphicsTextItem("Score: 0");
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setFont(QFont("Arial", 18));
    scoreText->setPos(-230, -280);
    scoreText->setZValue(10);
    addItem(scoreText);

    // GAME LOOP TIMER
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &Scene::gameLoop);
    gameTimer->start(16);//frame rate 60FPS (for 16 )

    // PILLAR TIMER
    pillarTimer = new QTimer(this);
    connect(pillarTimer, &QTimer::timeout, this, &Scene::spawnPillar);
    pillarTimer->start(1000); //pillers frame rate (spacing between pillers)
}

void Scene::setBird(Bird *b)
{
    bird = b;
}

void Scene::spawnPillar()
{
    if (!over && started)
        addItem(new PillarItem());
}

void Scene::gameLoop()
{
    if (over || !started) return;

    bird->fall();

    // GROUND COLLISION
    if (bird->y() > 260)
    {
        gameOver();
        return;
    }

    // PILLAR COLLISION
    QList<QGraphicsItem*> hits = bird->collidingItems();
    for (QGraphicsItem *item : hits)
    {
        if (dynamic_cast<QGraphicsPixmapItem*>(item) &&
            dynamic_cast<PillarItem*>(item->parentItem()))
        {
            gameOver();
            return;
        }
    }

    // SCORE UPDATE
    for (QGraphicsItem *item : items())
    {
        PillarItem *p = dynamic_cast<PillarItem*>(item);
        if (!p) continue;

        if (!p->passed && p->x() < bird->x())
        {
            p->passed = true;
            score++;
            scoreText->setPlainText("Score: " + QString::number(score));
        }
    }
}

void Scene::gameOver()
{
    over = true;
    gameTimer->stop();
    pillarTimer->stop();

    QGraphicsTextItem *t =
        new QGraphicsTextItem("GAME OVER\nPress R");
    t->setDefaultTextColor(Qt::red);
    t->setFont(QFont("Arial", 20));
    t->setZValue(20);
    t->setPos(-80, -20);
    addItem(t);
}

void Scene::restart()
{
    clear();

    over = false;
    started = false;
    score = 0;

    // SCORE AGAIN
    scoreText = new QGraphicsTextItem("Score: 0");
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setFont(QFont("Arial", 18));
    scoreText->setPos(-230, -280);
    scoreText->setZValue(10);
    addItem(scoreText);

    bird->reset();
    bird->setPos(-100, 0);
    bird->setZValue(5);
    addItem(bird);

    gameTimer->start();
    pillarTimer->start();
}
