#include "Button.h"
#include <QPen>
#include <QPainter>
#include <QDebug>

Button::Button()
{
    this->setMinimumSize(QSize(60,60));
   // QString styleSheet = "QPushButton{border:1px solid gray;}QPushButton:pressed{border:1px solid  rgb(24, 24, 24);}";
    QString styleSheet = "border:1px solid gray;";
    this->setStyleSheet(styleSheet);
}

void Button::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int width = this->rect().width();            //左右间隔 30
    int height = this->rect().height();          //上下间隔30
    QBrush brush(color);
    QPen pen;

    QPainterPath path;
    switch(type)
    {
    case 1:
        path.moveTo(10,10);
        path.lineTo(QPoint(width-10,10));
        path.lineTo(QPoint(width-10,10+(height-10)/5*3));
        path.lineTo(QPoint(width/2,height-10));
        path.lineTo(QPoint(10,10+(height-10)/5*3));
        path.lineTo(QPoint(10,10));
        painter.setBrush(brush);
        painter.drawPath(path);
        break;
    case 2:
        path.moveTo(width/2,10);
        path.lineTo(QPoint(width-10,10+(height-10)/5*2));
        path.lineTo(QPoint(width-10,height-10));
        path.lineTo(QPoint(10,height-10));
        path.lineTo(QPoint(10,10+(height-10)/5*2));
        path.lineTo(QPoint(width/2,10));
        painter.setBrush(brush);
        painter.drawPath(path);
        break;
    case 3:
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawRect(10,10,width-20,height-20);
        painter.setBrush(brush);
        painter.drawRect(15,15,width-30,height-30);

        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(Qt::black,2));
        painter.drawLine(width/2,18,width/2,height-18);
        break;
    case 4:
        painter.setBrush(brush);
        painter.drawRect(10,10,width-20,height-20);
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(Qt::black,1));
        painter.drawLine(width/2,10,width/2,height-10);
        break;
    default:
        break;

    }
}
