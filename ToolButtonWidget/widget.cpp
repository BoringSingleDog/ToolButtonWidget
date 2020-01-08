#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QBrush>
#include <QDebug>
#include <QTableWidget>
#include <QPalette>


Widget::Widget(QWidget *parent) :
    QWidget(parent),ui(new Ui::Widget)
{
    ui->setupUi(this);
}


Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.translate(0,0);
    painter.setRenderHint(QPainter::Antialiasing,true);

    //绘制背景
    painter.setBrush(brushColor);
    painter.setPen(Qt::white);
    painter.drawRect(this->rect().x(),this->rect().y(),this->rect().x()+this->rect().width(),this->rect().y()+this->rect().height());

   if(brushStyle == NoBrushStyle)
   {
       drawWidgetStyle(NoBrushStyle,painter,this,4,brushPointColor);
   }
   else if(brushStyle == WiderSpacePointStyle)
   {
       qDebug()<<"较宽间距的点状样式";

       drawPointBrushStyle(painter,this,10,brushPointColor);
   }
   else if(brushStyle == MiddleSpacePointStyle)
   {
       qDebug()<<"中等间距的点状样式";
       drawPointBrushStyle(painter,this,8,brushPointColor);
   }
   else if(brushStyle == NarrowSpacePointStyle)
   {
       qDebug()<<"窄间距的点状样式";
       drawPointBrushStyle(painter,this,6,brushPointColor);
   }
   else if(brushStyle == NarrowerSpacePointStyle)
   {
       qDebug()<<"较窄间距的点状样式";
       drawPointBrushStyle(painter,this,4,brushPointColor);
   }
   else if(brushStyle == TranslucentWiderSpacePointStyle)
   {
       qDebug()<<"半透明较宽间距的点状样式";
       QColor rgba = QColor(brushColor).toRgb();
       rgba.setAlphaF(1);
       brushPointColor = rgba;
       brushColor.setAlphaF(0.5);
       drawPointBrushStyle(painter,this,10,brushPointColor);
       brushPointColor = Qt::white;
   }
   else if(brushStyle == TranslucentMiddleSpacePointStyle)
   {
       qDebug()<<"半透明中等间距的点状样式";
       QColor rgba = QColor(brushColor).toRgb();
       rgba.setAlphaF(1);
       brushPointColor = rgba;
       brushColor.setAlphaF(0.5);
       qDebug()<<"the point color is： "<<brushPointColor.name();
       drawPointBrushStyle(painter,this,8,brushPointColor);
       brushPointColor = Qt::white;
   }
   else if(brushStyle == TranslucentNarrowSpacePointStyle)
   {
       qDebug()<<"半透明较窄间距的点状样式";
       QColor rgba = QColor(brushColor).toRgb();
       rgba.setAlphaF(1);
       brushPointColor = rgba;
       brushColor.setAlphaF(0.5);
       drawPointBrushStyle(painter,this,6,brushPointColor);
       brushPointColor = Qt::white;
   }
   else if(brushStyle == TranslucentNarrowerSpacePointStyle)
   {
       qDebug()<<"半透明较窄间距的点状样式";
       QColor rgba = QColor(brushColor).toRgb();
       rgba.setAlphaF(1);
       brushPointColor = rgba;
       brushColor.setAlphaF(0.5);
       drawPointBrushStyle(painter,this,4,brushPointColor);
       brushPointColor = Qt::white;
   }
   else if(brushStyle == AlternatePixelPoints)
   {
       qDebug()<<"交替式像素点";
       drawAlternatePointStyle(painter,this,1,brushPointColor);
   }
   else if(brushStyle == Alternate3PixelPoints)
   {
       drawAlternatePointStyle(painter,this,3,brushPointColor);
   }
   else if(brushStyle == TranslucentAlternatePixelPoints)
   {
       qDebug()<<"像素点颜色和图形背景颜色进行交换";
       drawAlternatePointStyle(painter,this,1,brushPointColor);
   }
   else if(brushStyle == TranslucentAlternate3PixelPoints)
   {
       qDebug()<<"像素点颜色和图形背景颜色进行交换";
       drawAlternatePointStyle(painter,this,3,brushPointColor);
   }
   else if(brushStyle == CrossPixelPoint)
   {
       qDebug()<<"十字形样式";
       drawCrossPixpelPointStyle(painter,this,3,brushPointColor);
   }
   else if(brushStyle == TanslucentCrossPixpelPoint)
   {
       qDebug()<<"颜色交换的十字样式";
       drawCrossPixpelPointStyle2(painter,this,3,brushPointColor);
   }
   else if(brushStyle == FineObliquLeftLine)
   {
       qDebug()<<"细等宽度的从左开始的斜线";
       drawLinesSinceRightToLeft(painter,this,8,1,brushPointColor);
   }
   else if(brushStyle == FineObliquRightLine)
   {
       qDebug()<<"细等宽度的从右开始的斜线";
       drawLineSinceLeftToRight(painter,this,8,1,brushPointColor);
   }
   else if(brushStyle == MiddleObliquLeftLine)
   {
      qDebug()<<"中等宽度的从左开始的斜线";
      drawLinesSinceRightToLeft(painter,this,8,2,brushPointColor);
   }
   else if(brushStyle == MiddleObliquRightLine)
   {
       qDebug()<<"中等宽度的从右开始的斜线";
       drawLineSinceLeftToRight(painter,this,8,2,brushPointColor);
   }
   else if(brushStyle == WiderObliquLeftLine)
   {
       qDebug()<<"从左上角开始的较宽的斜线";
       drawLineSinceLeftToRight(painter,this,8,3,brushPointColor);
   }
   else if(brushStyle == WiderObliquRightLine)
   {
      qDebug()<<"从右上角开始的较宽的斜线";
      drawLinesSinceRightToLeft(painter,this,8,3,brushPointColor);
   }
   else if(brushStyle == VerticalWiderLine)
   {
       qDebug()<<"竖直方向上间距较宽的水平线";
       drawVeritcalLine(painter,10,2,this,brushPointColor);
   }
   else if(brushStyle == HorizonWiderLine)
   {
       qDebug()<<"水平方向上间距较宽的水平线";
       drawHorizonTalLine(painter,8,2,this,brushPointColor);
   }
   else if(brushStyle == VerticalFineLine )
   {
       qDebug()<<"竖直方向上细线条的水平线";
       drawVeritcalLine(painter,8,1,this,brushPointColor);
   }
   else if(brushStyle == HorizonFineLine )
   {
       qDebug()<<"水平方向上细线条的水平线";
       drawHorizonTalLine(painter,8,1,this,brushPointColor);
   }
   else if(brushStyle == VerticalBlodLine)
   {
       qDebug()<<"竖直方向上粗线条的竖直线";
       drawVeritcalLine(painter,8,3,this,brushPointColor);
   }
   else if(brushStyle == HorizonBlodLine)
   {
       qDebug()<<"水平方向上粗线条的水平线";
       drawHorizonTalLine(painter,8,3,this,brushPointColor);
   }
   else if(brushStyle == SymmetricWallBrush)
   {
       qDebug()<<" 绘制对角的墙砖";
       int space = 9;
       drawWallBrush(painter,this,space,1,brushPointColor);
   }
   else if(brushStyle == HorizonWallBrush )
   {
       qDebug()<<"绘制水平方向上的墙砖";
       drawHorizonWallBrush(painter,this,8,0,brushPointColor);
    }

   //绘制圆环
   if(partternType == 1)
        drawRingInWidget(painter,this);

}

//绘制左上到右下的曲线
void Widget::drawLineSinceLeftToRight(QPainter &painter, QWidget *paintWidget, int space, int lineWidth, QColor color)
{
    int winWidth = paintWidget->rect().width();
    int winHeight = paintWidget->rect().height();

    int xStopFlag = qMin(winWidth,winHeight);
    if(xStopFlag == winWidth )
    {
        qDebug()<<"该窗口是一个宽度<高度的窗口";
        for(int i=0;i<(winWidth+winHeight)/space;i++)
        {
            int startPosX = 0;
            int startPOSY= 0;
            int endPosX = 0;
            int endPosY = 0;

            if(i*space <= winWidth)
            {
                startPosX = paintWidget->rect().x();
                startPOSY = paintWidget->rect().y()+ winHeight - i*space;
                endPosX = paintWidget->rect().x() +i*space;
                endPosY = paintWidget->rect().y()+winHeight;
            }
            else if( i*space>winWidth && i*space <= winHeight )
            {
                int shiftPos = space- winWidth%space;
                int stepValue = (i-(winWidth/space)-1)*space;
                startPosX = paintWidget->rect().x();
                startPOSY = paintWidget->rect().y()+ winHeight - i*space;
                endPosX = paintWidget->rect().x() +winWidth;
                endPosY = paintWidget->rect().y()+winHeight-shiftPos-stepValue;

            }
            else if(i*space > winHeight)
            {
                int shiftPos = space-winHeight%space;
                startPosX = paintWidget->rect().x()-shiftPos+(i-(winHeight/space))*space;
                startPOSY = paintWidget->rect().y();
                endPosX = paintWidget->rect().x() +winWidth;
                endPosY = paintWidget->rect().y()+winWidth-(i-(winHeight/space))*space+shiftPos;
            }
            QPen pen;
            pen.setWidth(lineWidth);
            pen.setColor(color);
            painter.setPen(pen);
            painter.drawLine(startPosX,startPOSY,endPosX,endPosY);
        }
    }
    else
    {
        for(int i=0;i<(winWidth+winHeight)/space;i++)
        {
            int startPosX = 0;
            int startPOSY= 0;
            int endPosX = 0;
            int endPosY = 0;
            if(i*space <= winHeight)
            {
                startPosX = paintWidget->rect().x();
                startPOSY = paintWidget->rect().y()+ winHeight - i*space;
                endPosX = paintWidget->rect().x()+i*space;
                endPosY = paintWidget->rect().y()+winHeight;
            }
            else if( i*space>winHeight && i*space <= winWidth )
            {
                int shiftPos = space- winHeight%space;
                int stepValue = (i-(winHeight/space)-1)*space;
                startPosX = paintWidget->rect().x()+shiftPos+stepValue;
                startPOSY = paintWidget->rect().y();
                endPosX = paintWidget->rect().x()+i*space;
                endPosY = paintWidget->rect().y()+winHeight;
            }
            else if(i*space > winWidth)
            {
                int shiftPos = space- winWidth%space;
                int stepValue = (i-(winWidth/space)-1)*space;
                startPosX = paintWidget->rect().x()+(winWidth-winHeight)+shiftPos+stepValue;
                startPOSY = paintWidget->rect().y();
                endPosX = paintWidget->rect().x()+winWidth;
                endPosY = paintWidget->rect().y()+winHeight-shiftPos-stepValue;
            }
            QPen pen;
            pen.setWidth(lineWidth);
            pen.setColor(color);
            painter.setPen(pen);
            painter.drawLine(startPosX,startPOSY,endPosX,endPosY);
        }
    }
}

//绘制右上到左下的曲线
void Widget::drawLinesSinceRightToLeft(QPainter &painter, QWidget *paintWidget, int space, int lineWidth, QColor color)
{
    int winWidth = paintWidget->rect().width();
    int winHeight = paintWidget->rect().height();
    int xStopFlag = qMin(winWidth,winHeight);
    if(xStopFlag == winWidth )
    {
        for(int i=0;i<(winWidth+winHeight)/space;i++)
        {
            int startPosX = 0;
            int startPOSY= 0;
            int endPosX = 0;
            int endPosY = 0;
            if(i*space <= winWidth)
            {
                startPosX = paintWidget->rect().x()+winWidth;
                startPOSY = paintWidget->rect().y()+ winHeight - i*space;
                endPosX = paintWidget->rect().x() +winWidth-i*space;
                endPosY = paintWidget->rect().y()+winHeight;
            }
            else if( i*space>winWidth && i*space <= winHeight )
            {
                int stepValue = i*space -winWidth;
                startPosX = paintWidget->rect().x()+winWidth;
                startPOSY = paintWidget->rect().y()+ winHeight - i*space;
                endPosX = paintWidget->rect().x();
                endPosY = paintWidget->rect().y()+winHeight-stepValue;
            }
            else if(i*space > winHeight)
            {
                int stepValue = i*space -winWidth;
                startPosX = paintWidget->rect().x()+winWidth;
                startPOSY = paintWidget->rect().y()+ winHeight - i*space;
                endPosX = paintWidget->rect().x();
                endPosY = paintWidget->rect().y()+winHeight-stepValue;
            }
            QPen pen;
            pen.setColor(color);
            pen.setWidth(lineWidth);
            painter.setPen(pen);
            painter.drawLine(startPosX,startPOSY,endPosX,endPosY);
        }
    }
    else
    {
        for(int i=0;i<(winWidth+winHeight)/space;i++)
        {
            int startPosX = 0;
            int startPOSY= 0;
            int endPosX = 0;
            int endPosY = 0;
            if(i*space <= winHeight)
            {
                startPosX = paintWidget->rect().x()+winWidth;
                startPOSY = paintWidget->rect().y()+ winHeight - i*space;
                endPosX = paintWidget->rect().x() +winWidth-i*space;
                endPosY = paintWidget->rect().y()+winHeight;
            }
            else if( i*space>winHeight && i*space <= winWidth )
            {
                int shiftPos = space- winHeight%space;
                int stepValue = (i-(winHeight/space)-1)*space;
                startPosX = paintWidget->rect().x()+winWidth-shiftPos-stepValue;
                startPOSY = paintWidget->rect().y();
                endPosX = paintWidget->rect().x()+(winWidth-winHeight)-shiftPos-stepValue;
                endPosY = paintWidget->rect().y()+winHeight;
            }
            else if(i*space > winWidth)
            {
                int shiftPos = space-winHeight%space;
                startPosX = paintWidget->rect().x()+winWidth+shiftPos-(i-(winHeight/space))*space;
                startPOSY = paintWidget->rect().y();
                endPosX = paintWidget->rect().x();
                endPosY = paintWidget->rect().y()+winWidth-(i-(winHeight/space))*space+shiftPos;
            }
            QPen pen;
            pen.setColor(color);
            pen.setWidth(lineWidth);
            painter.setPen(pen);
            painter.drawLine(startPosX,startPOSY,endPosX,endPosY);
        }
    }
}

void Widget::drawHorizonTalLine(QPainter &painter, int space, int lineWidth, QWidget *paintWidget,QColor color)
{
    for(int i =0;i< paintWidget->rect().height()/2;i++)
    {
        QPen pen;
        pen.setColor(color);
        pen.setWidth(lineWidth);
        painter.setPen(pen);
        painter.drawLine(paintWidget->rect().x(),paintWidget->rect().y()+i*space,paintWidget->rect().width(),paintWidget->rect().y()+i*space);
    }
}

void Widget::drawVeritcalLine(QPainter &painter, int space, int lineWidth, QWidget *paintWidget,QColor color)
{
    for(int i=0;i<paintWidget->rect().width()/2;i++)
    {
       QPen pen;
       pen.setColor(color);
       pen.setWidth(lineWidth);
       painter.setPen(pen);
       painter.drawLine( paintWidget->rect().x()+i*space,paintWidget->rect().y(),paintWidget->rect().x()+i*space,paintWidget->rect().y()+paintWidget->rect().height() );
    }
}

void Widget::drawWallBrush(QPainter &painter, QWidget *paintWidget, int space, int lineWidth, QColor color)
{
    drawLineSinceLeftToRight(painter,paintWidget,space,lineWidth,color);
    int shiftPos = (paintWidget->width()+paintWidget->height())%space+1;
    for(int i=0;i<paintWidget->geometry().width()/2;i++)
    {
        for(int j=0;j<paintWidget->geometry().height()/2;j++)
        {
            int startPosX = paintWidget->rect().x()+paintWidget->rect().width()-  i*space-shiftPos;
            int startPosY = paintWidget->rect().y() + j*space;
            int endPosX = paintWidget->rect().x()+paintWidget->rect().width() - space/2-i*space-shiftPos;
            int endPosY = paintWidget->rect().y()+ space/2+j*space;
            painter.drawLine(startPosX,startPosY,endPosX,endPosY);
        }
    }
}

void Widget::drawHorizonWallBrush(QPainter &painter, QWidget *paintWidget, int space, int lineWidth, QColor color)
{

    painter.setPen(color);
    for(int i =0;i<paintWidget->geometry().height()/2;i++)
    {
        painter.drawLine(paintWidget->rect().x(),paintWidget->rect().y()+i*space,paintWidget->rect().x()+paintWidget->geometry().width(),paintWidget->rect().y()+i*space);
        for(int j=0;j<paintWidget->geometry().width()/space;j++)
        {
              if(i%2 != 0)
                 painter.drawLine(paintWidget->rect().x()+j*space,paintWidget->rect().y()+i*space,paintWidget->rect().x()+j*space,paintWidget->rect().y()+i*space+space);
              else
                 painter.drawLine(paintWidget->rect().x()+j*space+space/2,paintWidget->rect().y()+i*space,paintWidget->rect().x()+j*space+space/2,paintWidget->rect().y()+i*space+space);
        }
    }
}

void Widget::drawWidgetStyle(CustomBrushStyle type, QPainter &painter, QWidget *paintWidget, int space, QColor color)
{
    QPen pen;
    pen.setColor(color);
    painter.setPen(pen);
    switch(type)
    {
        case NoBrushStyle:
             painter.setBrush(Qt::NoBrush);
             painter.setPen(Qt::NoPen);
             break;



    }
    painter.drawRect(paintWidget->rect().x(),paintWidget->rect().y(),paintWidget->rect().x()+paintWidget->rect().width(),paintWidget->rect().y()+paintWidget->rect().height());
}

void Widget::drawPointBrushStyle(QPainter &painter, QWidget *paintWidget, int space, QColor color)
{
    painter.setBrush(Qt::NoBrush);
    int pointX = 0;
    int pointY = 0;
    for(int i=0;i<paintWidget->rect().width()/2;i++)
    {
       pointX = paintWidget->rect().x()+i*space/2;
       for(int j=0;j<paintWidget->rect().height()/2;j++)
       {
           if(i%2==0)
                pointY = paintWidget->rect().y()+j*space;
            else if(i%2 == 1)
                pointY = paintWidget->rect().y()+j*space+space/2;
           painter.setPen(color);
           painter.drawPoint(pointX,pointY);
       }
    }
}

//交替3个像素点
void Widget::drawAlternatePointStyle(QPainter &painter, QWidget *paintWidget, int pointNum, QColor bkgdColor)
{
    painter.setBrush(Qt::green);
    QPen pen;
    pen.setColor(bkgdColor);
    painter.setPen(pen);

    int pointX=0;
    int pointY=0;
    for(int i=0;i<paintWidget->rect().width();i++)
    {
        pointX = i;
       if(pointNum == 1)
       {
           for(int j=0;j<paintWidget->rect().height()/2;j++)
           {
               if(j%2==0)
                   pointY = j*2;
               else if(j%2 == 1)
                   pointY = j*2+1;
               painter.drawPoint(pointX,pointY);
           }
       }
       else if(pointNum == 3)
       {
           for(int j=0;j<paintWidget->rect().height();j++)
           {

               if(i%4==0)
               {
                  pointY = paintWidget->rect().y()+j*4;
               }
               else if(i%4 == 1 || i%4== 3)
               {
                   pointY = paintWidget->rect().y()+j*2+1;
               }
               else if(i%4== 2)
               {
                  pointY = paintWidget->rect().y()+j*4+2;
               }

               painter.drawPoint(pointX,pointY);
           }
       }
    }
}

void Widget::drawCrossPixpelPointStyle(QPainter &painter, QWidget *paintWidget, int pointNum, QColor bkgdColor)
{
    painter.setBrush(Qt::green);
    QPen pen;
    pen.setColor(bkgdColor);
    painter.setPen(pen);

    int pointX=0;
    int pointY=0;
    for(int i=0;i<paintWidget->rect().width();i++)
    {
        pointX = i;
        for(int j=0;j<paintWidget->rect().height();++j)
        {
            if((i%4 == 0 || i%4 == 2) && j%2 == 0)
            {
                pointY = j;
            }
            else if(i%4 == 1 && j%4!=0)
            {
               pointY = j;
            }
            else if(j%4 != 2 && i%4 == 3)
            {
                pointY = j;
            }
            painter.drawPoint(pointX,pointY);
        }
    }
}

void Widget::drawCrossPixpelPointStyle2(QPainter &painter, QWidget *paintWidget, int pointNum, QColor bkgdColor)
{
    painter.setBrush(Qt::green);
    QPen pen;
    pen.setColor(bkgdColor);
    painter.setPen(pen);

    int pointX=0;
    int pointY=0;
    for(int i=0;i<paintWidget->rect().width();++i)
    {
        pointX = i;
        for(int j=0;j<paintWidget->rect().height();++j)
        {
            if((i%8 == 0 || i%8==4) && j%2==0 )
            {
                pointY = j;
            }
            else if((i%8)%2 ==1 && j%2 == 1 )
            {
                pointY = j;
            }
            if(i%8 == 2 && (j%8!=3 && j%8!=5 && j%8!=7))
            {
                pointY = j;
            }
            else if(i%8 == 6 && (j%8!=1 && j%8!=3 && j%8!=7))
            {
                pointY = j;
            }
            painter.drawPoint(pointX,pointY);
        }
    }
}

void Widget::drawGradientArc(QPainter *painter, int radius, double startAngle, double angleLength, int arcHeight, QColor color, int channelData)
{
    //设置渐变色
    /*
    QRadialGradient gradient(0,0,radius);       //圆心，以及边缘弧度
    gradient.setColorAt(0,color);               //渐变色的起始点颜色
    gradient.setColorAt(1.0,color);             //渐变色的结束点的颜色
    painter->setBrush(gradient);
    */


    QRectF rect(-radius,-radius,radius<<1,radius<<1);               //设定扇形所在区域
    QPainterPath path;
    path.arcTo(rect,startAngle,angleLength);

    //内部椭圆
    QPainterPath subPath;
    subPath.addEllipse(rect.adjusted(arcHeight,arcHeight,-arcHeight,-arcHeight));

    //绘制路径为外圆减去内圆
    path -= subPath;

    //文字字体
    QFont font;
    font.setFamily(RingTextFontName);
    font.setPointSize(RingTextFontSize);

    if(PartternBorderColor == "None")
        painter->setPen(QColor(BackgroundColor));               //边框颜色设置为背景颜色
    else
        painter->setPen(QColor(PartternBorderColor));           //边框颜色
    painter->drawPath(path);            //指定绘画路径

    //绘制文字
    painter->setPen(QColor(WholeRingTextColor));             //字体颜色
    painter->setFont(font);

    QRectF rectPoint = path.boundingRect();
    QPointF centerPoint = rectPoint.center();


    //计算中心点的缩放比例  70

    painter->rotate(90);

    double scalePre = 1-(arcHeight/90.0);
    QPointF textPoint;

    textPoint.setX(centerPoint.x()+SubCenterRingRadius);
    textPoint.setY(centerPoint.y());

    qDebug()<<"未经过缩放前的中心点的坐标是:("<<rectPoint.center().x()<<" , "<<rectPoint.center().y()<<") ,缩放比例是： "<<QString::number(scalePre,'f',2)<<" 缩放后的中心点的坐标是： ("<<textPoint.x()<<","<<textPoint.y()<<")";



    if(RingTextShowStyle == "无")
        painter->drawText(textPoint,"");
    else if(RingTextShowStyle == "百分比")
         painter->drawText(textPoint,QString("%1%").arg(channelData));
    else
         painter->drawText(textPoint,QString::number(channelData));


    painter->setPen(Qt::black);
    painter->drawPoint(centerPoint);
    painter->setPen(Qt::red);
    painter->drawPoint(textPoint);


    painter->rotate(-90);

}

void Widget::drawRingInWidget(QPainter &painter, QWidget *paintWidget)
{
    painter.setRenderHint(QPainter::Antialiasing,true);                 //开启反锯齿

    int radius = 90;                //半径
    int arcHeight = 90 - SubCenterRingRadius;
    painter.translate(paintWidget->rect().width()>>1,paintWidget->rect().height()>>1);
    painter.rotate(-90);    //逆时针旋转90度

    double channelSum = 0;
    int count = ChannelCount;      //划分的通道数
    for(int i=0;i<=count;i++)
    {
        channelSum+=i;
    }

    int startRadius = RingDrawStartPos;
    double shiftPos = 0.0;
    double startPos = RingDrawStartPos;
    int shiftSumPos = 0;

    int channelData = -1;
    QStringList colorList = QColor::colorNames();

    //设置颜色
    for(int i=1;i<=count;i++)
    {
        if(RingTextShowStyle == "百分比")
        {
            channelData = i*100/channelSum;
            if(i == count)
            {
                int leave = channelSum - count;
                channelData = 100 -(leave*100/channelSum);
            }
        }
        else if(RingTextShowStyle == "数据")
            channelData = i;

        QColor color = QColor(colorList[i+18]);
        if(ColorMap.contains(i))
        {
            color =QColor(ColorMap.value(i));
        }
        if(RingDrawEndPos > 0)       //指定了弧形的扫过范围
        {
            if(RingDrawDirection == 0)         //逆时针绘制
            {
                startPos += RingDrawEndPos/channelSum*(i-1);
                shiftPos = RingDrawEndPos/channelSum*i;
                drawGradientArc(&painter,radius,startPos,shiftPos,arcHeight,color,channelData);
            }
            else{    //顺时针画图
                 startPos -= (RingDrawEndPos)/channelSum*i;
                 shiftPos = (RingDrawEndPos)/channelSum*i;
                 drawGradientArc(&painter,radius,startPos,shiftPos,arcHeight,color,channelData);
            }
        }
        else
        {
            if(RingDrawDirection == 1)
            {
                if(i!= count)
                    drawGradientArc(&painter,radius,startRadius -(360/channelSum*i),360/channelSum*i,arcHeight,color,channelData);
                else
                    drawGradientArc(&painter,radius,-360,360+startRadius,arcHeight,color,channelData);
                startRadius = startRadius- (360/channelSum*i);
            }
            else
            {
                if(i!=count)
                    drawGradientArc(&painter,radius,startRadius,360/channelSum*i,arcHeight,color,channelData);
                else
                    drawGradientArc(&painter,radius,startRadius,360-startRadius,arcHeight,color,channelData);
               startRadius += 360/channelSum*i;
            }
        }
    }

    QPainterPath tempPath;
    painter.setBrush(BackgroundColor);
    painter.setPen(Qt::NoPen);

    //使用画刷遮蔽调多余部分的样式
    if(SubCenterRingRadius == 0 && RingDrawEndPos == 360)  //没有内圆
    {
        tempPath.addEllipse(this->rect().x()-radius,this->rect().y()-radius,180,180);
    }
    else if(SubCenterRingRadius != 0 && RingDrawEndPos == 360 && RingDrawStartPos == 0)
    {
        tempPath.addEllipse(this->rect().x()-radius,this->rect().y()-radius,180,180);
        QRect rect;
        rect.adjust(SubCenterRingRadius,SubCenterRingRadius,-SubCenterRingRadius,-SubCenterRingRadius);
        QPainterPath path;
        path.arcTo(rect,0,360);
        tempPath -= path;
    }
    else if(SubCenterRingRadius == 0 && RingDrawEndPos < 360 && RingDrawStartPos >= 0)      //是一个扇形
    {
        if(RingDrawDirection == 0)         //逆时针绘制
        {
            QRect rect(this->rect().x()-radius,this->rect().y()-radius,180,180);
            tempPath.arcTo(rect,RingDrawStartPos,RingDrawEndPos);
        }
        else
        {
            QRect rect(this->rect().x()-radius,this->rect().y()-radius,180,180);
            tempPath.arcTo(rect,RingDrawStartPos-RingDrawEndPos,RingDrawEndPos);
        }
    }
    else if(SubCenterRingRadius != 0 && RingDrawEndPos < 360 && RingDrawStartPos >= 0)
    {
        if(RingDrawDirection == 0)         //逆时针绘制
        {
            QRect rect(this->rect().x()-radius,this->rect().y()-radius,180,180);
            tempPath.arcTo(rect,RingDrawStartPos,RingDrawEndPos);
            rect.adjust(arcHeight,arcHeight,-arcHeight,-arcHeight);
            QPainterPath path;
            path.arcTo(rect,RingDrawStartPos,RingDrawEndPos);
            tempPath -= path;
        }
        else
        {
            QRect rect(this->rect().x()-radius,this->rect().y()-radius,180,180);
            tempPath.arcTo(rect,RingDrawStartPos-RingDrawEndPos,RingDrawEndPos);
            rect.adjust(arcHeight,arcHeight,-arcHeight,-arcHeight);
            QPainterPath path;
            path.arcTo(rect,RingDrawStartPos-RingDrawEndPos,RingDrawEndPos);
            tempPath -= path;
        }
    }
    QPainterPath leavePath;
    leavePath.addRect(-101,-125,201,251);
    leavePath -= tempPath;
    painter.drawPath(leavePath);
}

