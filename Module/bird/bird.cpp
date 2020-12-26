#include "bird.h"

Bird::Bird(QWidget *parent)
    : QWidget(parent)
{
    setMaximumSize(35,35);
    setMinimumSize(35,35);
    timer=new QTimer(this);
    name=":/Images/bird2.png";
    timer->start(200);
}

Bird::~Bird()
{
}

void Bird::play()
{
    timer->start(200);
}

void Bird::stop()
{
    timer->stop();
}

void Bird::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    painter.setWindow(-20,-20,40,40);	///Установите холст равным центральной координате смещения,
    ///чтобы центральная ось абсолютных координат была 20,0
    pix.load(name);
    painter.rotate(0);
    painter.drawPixmap(-20,-20,40,40,pix);
}


