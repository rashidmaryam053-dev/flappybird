#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsTextItem>
#include "bird.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void setBird(Bird *b);
    void restart();
    void gameOver();

    bool started;
    bool over;

private slots:
    void spawnPillar();
    void gameLoop();

private:
    Bird *bird;
    QTimer *gameTimer;
    QTimer *pillarTimer;

    QGraphicsTextItem *scoreText;
    int score;
};

#endif // SCENE_H
