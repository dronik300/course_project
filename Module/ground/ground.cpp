#include "ground.h"

Ground::Ground(QWidget *parent)
    : QWidget(parent)
{
    this->setMaximumSize(380,60);
    this->setMinimumSize(380,60);
    ground=(":/Images/ground.png");
}

Ground::~Ground()
{

}

void Ground::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(ground);
    painter.drawPixmap(0,0,450,60,pixmap);
}
