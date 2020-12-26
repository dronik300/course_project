#ifndef REDYBOARD_H
#define REDYBOARD_H

#include <QWidget>
#include <QtGui>
#include <QPainter>
#include <QPixmap>
#include <QLabel>

///Доска подсказок статуса подготовки
class RedyBoard : public QWidget
{
    Q_OBJECT

public:
    RedyBoard(QWidget *parent = 0);
    ~RedyBoard();
protected:
    void paintEvent(QPaintEvent *);

private:
    QLabel *label;
};

#endif // REDYBOARD_H
