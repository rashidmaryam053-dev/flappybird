#ifndef BIRD_H
#define BIRD_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Bird : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bird(QPixmap pixmap);

    void fall();
    void jump();
    void reset();

private:
    int velocity;
};

#endif
