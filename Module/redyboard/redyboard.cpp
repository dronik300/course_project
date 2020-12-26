#include "redyboard.h"

RedyBoard::RedyBoard(QWidget *parent)
    : QWidget(parent)
{
    this->setGeometry(0,0,380,500);
    label=new QLabel(tr("<font color=red>Управление:кнопки мыши или пробел</font>"),this);
    label->move(80,480);
}

RedyBoard::~RedyBoard()
{

}

void RedyBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    painter.setWindow(0,0,380,500);
    pix.load(":/Images/ready.png");
    painter.drawPixmap(0,0,380,500,pix);
}
