#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
//#include <QLCDNumber>
#include <QTimer>
#include <QDataStream>
#include <QLabel>
#include <QPainter>
#include <QPixmap>

#include <Module/bird/bird.h>
#include <Module/ground/ground.h>
#include "Module/pipe/pipe.h"
#include "Module/scoreboard/scoreboard.h"
#include "Module/fbnumLCD/Font.h"
#include "Module/redyboard/redyboard.h"

#include <QtGui>
#include <QMouseEvent>
#include <math.h>
//#include <QSettings>
#include <QDataStream>
#include <QFile>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia>
#include <QUrl>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);    ///Нарисуйте фоновую картинку
    void mousePressEvent(QMouseEvent *event);	///Обработка нажатия мыши
    void keyPressEvent(QKeyEvent *event);	///Обработка нажатия клавиатуры

private slots:				
    void birdAction();			///Обработка действий птиц
    void pipeAction();			///Обработка действий труб
    void collision();			///Проверка на удар
    void scoreDete();			///Рисование очков в самой игре
    void scbAction();			///Табло анимации
private:
    void mainAction();			///Главный триггер - это функция исполнения мыши и обработки событий клавиатуры.
    void createPipe();			///Изначально создать трубу
    void gameLose();			///Проигрышь
    void gameStart();			///Начало игры
    void gameRedy();
    void saveTop();			///Сохранение лучшего результата
    void loadTop();			///загрузка лучшего результата
private:	
    Bird *birds;			///Создать птицу
    double birdV;			///Скорость птицы
    double timedata;			///Отметка времени таймера птицы
    QTimer *birdTimer;			///Таймер для контроля движения птицы
    double fpV[15];
    double fpp;
    enum{stop=0,start=1,redy=2};		///3 пронумерованных значения представляют текущее состояние игры
    int gamemod;		///состояние игры
    RedyBoard *myredyBoard;	///Панель подготовки в начале
    enum{pipeCount=5};		///Константа для количества труб(в оригинальной игре одновременно на экране максимум 5 труб)
    Pipe *pipe[pipeCount];		///Создать трубы
    QTimer *pipeTimer;		///Удаленная обработка конвейерного таймера и таймера выполняет несколько основных задач обработки окна.
    int pipeTValue;
    int pipeXgap;		///Расстояние между трубами
    int lastPipe;		///Последняя труба
    Ground *thisGround;		///Прокрутка анимации земли
    ScoreBoard *scoreBoard;	///Табло
    bool isScobOk;		///Статус отображения табло
    int score;			///Очки
    int top;			///Лучший результат
    bool cx;			///Для предотвращения повторной индикации состояния интеграции
    QTimer *scobTimer;		///Обработка табло запускается, когда игра окончена.
    Font *scoreLCD;		///Малое табло
    QLabel *replay;		///Кнопка запуска игры после проигрыша
    bool isHit; /// флаг удара
};

#endif // MAINWINDOW_H
