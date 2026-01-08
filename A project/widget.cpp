#include "widget.h"
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(500, 600);

    scene = new Scene(this);

    // BACKGROUND
    QGraphicsPixmapItem * pixItem = new QGraphicsPixmapItem (QPixmap(":/back.jpeg"));
    scene->addItem(pixItem);
    pixItem->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2,pixItem->boundingRect().height()/2 )); //to bring sky in center

    // BIRD
    bird = new Bird(QPixmap(":/flappyup (1).png"));
    bird->setPos(-100, 0);
    bird->setZValue(1);
    scene->addItem(bird);
    scene->setBird(bird);

    // VIEW
    view = new QGraphicsView(scene, this);
    view->setSceneRect(scene->sceneRect());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(500, 600);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);
    setLayout(layout);
}

Widget::~Widget() {}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        bird->jump();
        scene->started = true;
    }

    if (event->key() == Qt::Key_R)
        scene->restart();
}
