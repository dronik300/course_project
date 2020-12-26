#include "mainwindow.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <ctime>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setFixedSize(380,500);
    this->setWindowIcon(QIcon(":/Images/bird1.png"));
    this->move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2);
    for(int i=0;i<pipeCount;i++)	/// Создать объект конвейера
        pipe[i]=new Pipe(this);
    createPipe();
    pipeTimer =new QTimer(this);	//Таймер, создающий конвейер Следующие
    connect(pipeTimer,SIGNAL(timeout()),this,SLOT(pipeAction()));
    connect(pipeTimer,SIGNAL(timeout()),this,SLOT(collision()));
    connect(pipeTimer,SIGNAL(timeout()),this,SLOT(scoreDete()));
    pipeTValue=8;
    birds=new Bird(this);
    birds->move(60,250);
    this->fpV[0]=-3;
    this->fpV[1]=-4;
    this->fpV[2]=-3;
    this->fpV[3]=-2;
    this->fpV[4]=-1;
    this->fpV[5]=-1;
    this->fpV[6]=-1;
    this->fpV[7]=0;
    this->fpV[8]=1;
    this->fpV[9]=1;
    this->fpV[10]=2;
    this->fpV[11]=2;
    this->fpV[12]=2;
    this->fpV[13]=3;
    this->fpV[14]=3;
    this->fpp=0;
    birdTimer=new QTimer(this);
    connect(birdTimer,SIGNAL(timeout()),this,SLOT(birdAction()));
    //birdTimer->start(20);
    birdV=0;
    gamemod=redy;		//Состояние игры изменено на готов
    score=0;
    top=0;
    loadTop();		//Загрузка запись счета
    scoreLCD=new Font(this);	///Реализация табло
    scoreLCD->setValue(0);
    scoreLCD->move(140,-100);
    scoreBoard=new ScoreBoard(this);
    scoreBoard->move(-350,100);
    scobTimer=new QTimer(this);
    connect(scobTimer,SIGNAL(timeout()),this,SLOT(scbAction()));
    thisGround=new Ground(this);
    thisGround->move(0,450);
    myredyBoard=new RedyBoard(this);
    myredyBoard->setFixedSize(380,500);
    myredyBoard->move(0,0);
    replay=new QLabel(this);
    QPixmap pix;
    pix.load(":/Images/replay.png");		///Все материалы записаны в файл ресурсов и будут добавлены в приложение при компиляции. Чтобы вызвать файл ресурсов, вам нужно всего лишь использовать ":"
    replay->setPixmap(pix);
    replay->setFixedSize(140,80);
    replay->move(120,-400);
    isHit=0;
    this->setWindowTitle("Qt FlappyBird");		///установка заголовка
}

void MainWindow::createPipe()		//Инициализируйте трубу.
{
    int startx=500;		//Расположение первой трубы
    pipeXgap=200;		///интервал
    int pipR;			///Сгенерирует случайное число в вертикальном положении
    qsrand(time(NULL));		///qrand - это функция случайных чисел для qt. Это то же самое, что и rand для c, и необходимо инициализировать начальное число.
    for(int i=0;i<pipeCount;i++)
    {
        pipR=qrand()%201;
        pipe[i]->move(startx+i*pipeXgap,-200+pipR);
        lastPipe=i;
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *)		//Cоздания фона
{
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/Images/bg.png");
    painter.drawPixmap(0,0,380,450,pixmap);
}

void MainWindow::mousePressEvent(QMouseEvent *event)	//нажатие мыши
{
    //И левая, и правая кнопки могут управлять перемещением птиц,
    //а для предотвращения вылета за пределы карты добавлена ​​функция birds-> pos (). Y ()> 0.
    if((event->button()==Qt::LeftButton||event->button()==Qt::RightButton)&&birds->pos().y()>0)
    {
        if(gamemod==stop)		//Если игра остановлена, то есть в состоянии сбоя, событие может быть инициировано только после того, как табло будет на месте.
        {
            if(isScobOk)
                if((event->pos().x()>=120&&event->pos().x()<=260)&&(event->pos().y()>=400&&event->pos().y()<=480))
                {
                    gameRedy();
                }

        }
        else
        {
            mainAction();  //Остальная часть обработки событий прописана в функции, так как она универсальна для клавиатуры и мыши
        }

    }
}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //Управление клавиатурой: пробелом и клавишей вверх
    if((event->key()==Qt::Key_Space||event->key()==Qt::Key_Up)&&birds->pos().y()>0)
    {
        mainAction();
    }
}

void MainWindow::mainAction()
{
    //Общая обработка событий
    if(gamemod==redy)	//Если готов: начать игру, птица начинает двигаться, труба начинает двигаться.
    {
        gameStart();
        timedata=8;
        birdTimer->start(timedata);
        pipeTimer->start(pipeTValue);
        fpp=0.0;
        birdV=fpV[int(fpp)];		///Каждый раз, когда он срабатывает, птица летит вверх, что означает отрицательную скорость.
    }
    else if(gamemod==start)	//Если игра находится в стартовом состоянии, обрабатывается только поза птицы.
    {
        fpp=0.0;
        birdV=fpV[int(fpp)];
        timedata=8;
        birdTimer->setInterval(timedata);
        //emit birds->fly();
    }
}

void MainWindow::birdAction()
{
    //Время движения птицы. Здесь определяется степень сложности передвижения птицы.
    birds->move(birds->pos().x(),birds->pos().y()+birdV);

    if(fpp<14.0)
        fpp+=0.2;
    else
        fpp=14.0;
    birdV=fpV[int(fpp)];

    if(birds->pos().y()+birds->height()>=450)
    {
        birds->move(birds->pos().x(),450-birds->height()+5);
        birdTimer->stop();
        isHit=true;
        gameLose();
    }

}

void MainWindow::pipeAction()
{
    int pipR;
    for(int i=0;i<pipeCount;i++)
    {
        pipe[i]->move(pipe[i]->pos().x()-1,pipe[i]->pos().y());
        if(pipe[i]->pos().x()<-100)
        {
            pipR=qrand()%200;
            pipe[i]->move(pipe[lastPipe]->pos().x()+pipeXgap,-200+pipR);
            lastPipe=i;
        }
    }
}

void MainWindow::collision()
{
    int birdRx=birds->pos().x()+30;
    int birdDy=birds->pos().y()+30;
    for(int i=0;i<pipeCount;i++)
    {
        if (birds->pos().y()<20)
        {
            gameLose();
        }
        if(birdRx>=pipe[i]->x()&&birds->pos().x()<=pipe[i]->pos().x()+pipe[i]->width()-10)
        {
            if(birds->y() <= (pipe[i]->y()+250) || birdDy >= (pipe[i]->y()+250+pipe[i]->getGap()))
                gameLose();
        }
    }
}

void MainWindow::scoreDete()
{
    //Рисование очков в самой игре
    for(int i=0;i<pipeCount;i++)
    {
        if(birds->pos().x()+birds->width()>=pipe[i]->pos().x()+35&&birds->pos().x()+birds->width()<=pipe[i]->pos().x()+40&&cx)
        {
            this->score+=1;
            scoreLCD->setValue(score);
            if(score>=1000)
            {
                scoreLCD->move(90+14*3,50);
            }
            else if(score>=100)
            {
                scoreLCD->move(90+14*2,50);
            }
            else if(score>=10)
            {
                scoreLCD->move(90+14,50);
            }
            cx=0;
        }

        if(birds->pos().x()>=pipe[i]->pos().x()+68&&birds->pos().x()<=pipe[i]->pos().x()+73)
            cx=1;
    }
}


void MainWindow::scbAction()
{
    ///Анимация табло при неудаче
    scoreBoard->move(scoreBoard->pos().x()+1,scoreBoard->pos().y());
    if(scoreBoard->pos().x()>=40)
    {
        scoreBoard->move(40,scoreBoard->pos().y());
        scobTimer->stop();
        replay->move(120,400);
        isScobOk=1;
    }
}

void MainWindow::gameRedy()
{
    myredyBoard->show();
    scoreBoard->move(-350,100);
    birds->move(60,250);
    replay->move(120,-400);
    createPipe();
    gamemod=redy;
    scoreLCD->setValue(0);
    birds->play();
}

void MainWindow::gameLose()
{
    isScobOk=0;
    gamemod=stop;
    birds->stop();
    pipeTimer->stop();
    if(isHit)
        isHit=false;
    if(score>top)
    {
        top=score;
        saveTop();
    }
    scoreBoard->setScore(score,top);
    scobTimer->start(3);
    scoreLCD->move(140,-100);
}

void MainWindow::gameStart()
{
    gamemod=start;
    myredyBoard->close();
    cx=1;
    score=0;
    scoreLCD->move(90,50);
}

void MainWindow::saveTop()
{
    QFile file("top.txt");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out<<this->top;
}

void MainWindow::loadTop()
{
    QFile file("top.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        in>>this->top;
    }
    else
        top=0;
}


