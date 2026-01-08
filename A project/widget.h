#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include "scene.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Scene *scene;
    Bird *bird;
    QGraphicsView *view;
};

#endif
