#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QObject>

class PillarItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)

public:
    PillarItem();
    ~PillarItem();

    qreal x() const;
    void setX(qreal newX);

    bool passed = false;

private:
    QGraphicsPixmapItem *topPillar;
    QGraphicsPixmapItem *bottomPillar;
    QPropertyAnimation *anim;
    qreal m_x;
    int yPos;
};

#endif
