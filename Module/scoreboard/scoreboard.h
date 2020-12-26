#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QLCDNumber>
#include "Module/fbnumLCD/Font.h"

///Табло используется исключительно для отображения результатов
class ScoreBoard : public QWidget
{
    Q_OBJECT

public:
    ScoreBoard(QWidget *parent = 0);
    ~ScoreBoard();

    void setScore(int score,int top);	///Установите отображаемое значение: балл, наивысший балл.

protected:
    void paintEvent(QPaintEvent *);

private:
    int Score;		///Очки
    int top;		///Лучший результат
    QString medal[3];	///Медаль
    Font *scoreLcd;	///Очки текущей игры
    Font *topLcd;		///Лучший счёт
};

#endif // SCOREBOARD_H
