#include "Font.h"
#include <cstring>

Font::Font(QWidget *parent)
    : QWidget(parent)
{
    this->data=0;
    this->len=1;
    memset(num,0,sizeof(num));
    lcdList[0]=":/Images/scoreNumber/0.png";
    lcdList[1]=":/Images/scoreNumber/1.png";
    lcdList[2]=":/Images/scoreNumber/2.png";
    lcdList[3]=":/Images/scoreNumber/3.png";
    lcdList[4]=":/Images/scoreNumber/4.png";
    lcdList[5]=":/Images/scoreNumber/5.png";
    lcdList[6]=":/Images/scoreNumber/6.png";
    lcdList[7]=":/Images/scoreNumber/7.png";
    lcdList[8]=":/Images/scoreNumber/8.png";
    lcdList[9]=":/Images/scoreNumber/9.png";
    this->setValue(0);

    this->setGeometry(100,100,28*4,36);
}

Font::~Font()
{
}
void Font::setValue(int v)
{
    data=v;
    runtime();
}

int Font::value() const
{
    return data;
}

void Font::runtime()
{
    int i=0;
    int t=this->data;
    while(t>0&&i<4)
    {
        num[i]=t%10;
        t/=10;
        i++;
    }
    len=i;
    update();
}

void Font::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    int Minw=28*4;
    painter.setWindow(0,0,Minw,36);
    int k=0;
    for(int i=Minw-25;i>0;i-=28)
    {
        pix.load(lcdList[num[k]]);
        painter.drawPixmap(i,0,24,36,pix);
        k++;
        if(k>=len)
            break;
    }
}
