#ifndef FBNUMLCD_H
#define FBNUMLCD_H

#include <QWidget>
#include <QtGui>
#include <QPainter>
#include <QPixmap>


///Это своего рода шрифт flappybird, который отображает числа
class Font : public QWidget
{
    Q_OBJECT

public:
    Font(QWidget *parent = 0);
    ~Font();

    void setValue(int v);	///Настройки
    int value() const;		///Прочитать значение

protected:
    void paintEvent(QPaintEvent *);

private:
    void runtime();		///Выполнить операцию преобразования

private:
    QString lcdList[10];
    int data;
    int num[4];
    int len;
};

#endif // FBNUMLCD_H
