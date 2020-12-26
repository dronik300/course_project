#ifndef PIPE_H
#define PIPE_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

class Pipe : public QWidget
{
    Q_OBJECT

public:
    Pipe(QWidget *parent = 0);
    ~Pipe();
    int getGap();
private:
    void setGapSize(int w);

protected:
    void paintEvent(QPaintEvent *);
    int Gap;

};

#endif // PIPE_H
