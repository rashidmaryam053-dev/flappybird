#include "pillaritem.h"
#include <QRandomGenerator>
#include <QGraphicsScene>

PillarItem::PillarItem()
{
    topPillar = new QGraphicsPixmapItem(QPixmap(":/pp.png"));
    bottomPillar = new QGraphicsPixmapItem(QPixmap(":/pp.png"));

    qreal gap = 120;
    qreal halfW = topPillar->boundingRect().width() / 2;

    topPillar->setPos(-halfW,
                      -topPillar->boundingRect().height() - gap);
    bottomPillar->setPos(-halfW, gap);

    addToGroup(topPillar);
    addToGroup(bottomPillar);

    yPos = QRandomGenerator::global()->bounded(-100, 100);
    setPos(300, yPos);

    anim = new QPropertyAnimation(this, "x");
    anim->setStartValue(300);
    anim->setEndValue(-300);
    anim->setDuration(2000);
    anim->setEasingCurve(QEasingCurve::Linear);

    connect(anim, &QPropertyAnimation::finished, [=](){
        scene()->removeItem(this);
        delete this;
    });

    anim->start();
}

PillarItem::~PillarItem() {}

qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::setX(qreal newX)
{
    m_x = newX;
    setPos(newX, yPos);
}
