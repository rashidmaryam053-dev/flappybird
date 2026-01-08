#include "bird.h"

Bird::Bird(QPixmap pixmap)
{
    setPixmap(pixmap);
    setScale(0.15);
    velocity = 0;
}

void Bird::fall()
{
    velocity +=1;       // gravity
    setY(y() + velocity);
}

void Bird::jump()
{
    velocity = -13;       // REDUCED jump
}

void Bird::reset()
{
    velocity = 0;
}
