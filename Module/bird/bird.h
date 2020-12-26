#ifndef BIRD_H
#define BIRD_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>

class Bird : public QWidget
{
    Q_OBJECT
///Унаследованный от QWidget необходимо использовать этот макрос для обработки
public:
    Bird(QWidget *parent = 0);
    ~Bird();
    void play();
    void stop();
protected:
    void paintEvent(QPaintEvent *);		///Рисование
private:
    QTimer *timer;
    QString name;	///Путь к изображению птицы
};

#endif // BIRD_H
