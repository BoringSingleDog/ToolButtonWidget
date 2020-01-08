#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBrush>
#include <QPainter>
#include <QMouseEvent>
#include <QColor>
namespace Ui {
class Widget;
}

enum CustomBrushStyle{
    NoBrushStyle = 0,
    WiderSpacePointStyle,               //较宽间距的点状样式
    MiddleSpacePointStyle,              //中等间距的点状样式
    NarrowSpacePointStyle,              //窄间距的点状样式
    NarrowerSpacePointStyle,            //较窄间距的点状样式

    TranslucentWiderSpacePointStyle,               //半透明较宽间距的点状样式
    TranslucentMiddleSpacePointStyle,              //半透明中等间距的点状样式
    TranslucentNarrowSpacePointStyle,              //半透明窄间距的点状样式
    TranslucentNarrowerSpacePointStyle,            //半透明较窄间距的点状样式

    AlternatePixelPoints,               //交替式像素点
    Alternate3PixelPoints,              //交替式3个像素点
    TranslucentAlternatePixelPoints,    //像素点颜色和图形背景颜色进行交换
    TranslucentAlternate3PixelPoints,   //像素点颜色和图形背景颜色进行交换

    CrossPixelPoint,                    //十字形样式
    TanslucentCrossPixpelPoint,         //颜色交换的十字样式
    FineObliquLeftLine,     //细等宽度的从左开始的斜线
    FineObliquRightLine,    //细等宽度的从右开始的斜线
    MiddleObliquLeftLine,   //中等宽度的从左开始的斜线
    MiddleObliquRightLine,  //中等宽度的从右开始的斜线
    WiderObliquLeftLine,    //从左上角开始的较宽的斜线
    WiderObliquRightLine,   //从右上角开始的较宽的斜线

    VerticalWiderLine,  //竖直方向上间距较宽的竖直线
    HorizonWiderLine,   //水平方向上间距较宽的水平线
    VerticalFineLine,   //竖直方向上细线条的竖直线
    HorizonFineLine,    //水平方向上细线条的水平线
    VerticalBlodLine,   //竖直方向上粗线条的竖直线
    HorizonBlodLine,    //水平方向上粗线条的水平线
    SymmetricWallBrush, //窗口对称角的墙状
    HorizonWallBrush,   //水平方向上的墙状
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void setWindowBrushStyle(CustomBrushStyle type){brushStyle = type;};        //窗体的画刷风格
    void setWidgetbackgroundColor(QColor color){BackgroundColor = color;};      //窗体的背景颜色
    void setWidgetBrushColor(QColor color){brushColor = color;};
    void setWidgetPartternBorderColor(QString borderColor){PartternBorderColor = borderColor;};                    //图形变宽的背景颜色
    void setWidgetRingTextColor(QString color){WholeRingTextColor = color;};         //所有圆环文字对应的颜色
    void setWidgetRingTextColor(int index,QString color){TextColorMap.insert(index,color);};    //某一部分圆环文字对应的颜色
    void setWidgetRingCount(int count){ChannelCount = count;};                   //圆环非等分数量
    void setWidgetRingColor(int index,QString color){ColorMap.insert(index,color);};       //设置对应通道的颜色
    void setWidgetSubRingRadius(int radius){SubCenterRingRadius = radius;};                //中心圆环的半径大小
    void setWidgetRingTextProperty(QString fontName,int fontSize,QString textShowStyle)        //设置扇形图的文字属性
    {
        RingTextFontName = fontName;
        RingTextFontSize = fontSize;
        RingTextShowStyle = textShowStyle;
    };
    void setWidgetRingDrawDirection(int direction,int startPos,int endPos)      //参数1：扇形方向（1顺时针，0逆时针），参数2：扇形的起始角度，参数3：扇形的结束角度;
    {
        RingDrawStartPos = startPos;
        RingDrawEndPos = endPos;
        RingDrawDirection = direction;
    }
    void setDrawParttern(int type){partternType = type;};
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void initBrushWidget();
    void drawLineSinceLeftToRight(QPainter &painter,QWidget *paintWidget,int space,int lineWidth,QColor color);
    void drawLinesSinceRightToLeft(QPainter &painter,QWidget *paintWidget,int space,int lineWidth,QColor color);
    void drawHorizonTalLine(QPainter &painter, int space,int lineWidth,QWidget *paintWidget,QColor color);
    void drawVeritcalLine( QPainter &painter, int space,int lineWidth,QWidget* paintWidget,QColor color);
    void drawWallBrush(QPainter &painter, QWidget *paintWidget,int space,int lineWidth,QColor color);           //绘制墙状的画刷风格
    void drawHorizonWallBrush(QPainter &painter, QWidget *paintWidget,int space,int lineWidth,QColor color);
    void drawWidgetStyle(CustomBrushStyle type,QPainter &painter, QWidget *paintWidget,int space,QColor color);
    void drawPointBrushStyle(QPainter &painter,QWidget *paintWidget,int space,QColor color);
    void drawAlternatePointStyle(QPainter& painter,QWidget* paintWidget,int pointNum,QColor bkgdColor);
    void drawCrossPixpelPointStyle(QPainter& painter,QWidget* paintWidget,int pointNum,QColor bkgdColor);
    void drawCrossPixpelPointStyle2(QPainter& painter,QWidget* paintWidget,int pointNum,QColor bkgdColor);
    void drawGradientArc(QPainter *painter, int radius, double startAngle, double angleLength, int arcHeight, QColor color ,int channelData);     //绘制扇形
    void drawRingInWidget(QPainter& painter,QWidget* paintWidget);

private:
    Ui::Widget *ui;
    QBrush brush;
    CustomBrushStyle brushStyle;
    QColor BackgroundColor;             //窗体背景色
    QColor TextColor;
    QString WholeRingColor;             //整个圆环的背景颜色
    QString WholeRingTextColor ;        //整个圆环的字体颜色
    QMap<int,QString> ColorMap;         //部分圆环的背景颜色
    QMap<int,QString> TextColorMap;     //部分圆环字体对应颜色
    QMap<int,CustomBrushStyle> channelStyle;    //部分通道对应的样式
    int ChannelCount = 2;               //圆环通道数
    int SubCenterRingRadius = 0;        //中心圆的半径
    QString RingTextFontName;           //文字字体
    int RingTextFontSize;               //文字大小
    QString RingTextShowStyle = "百分比";        //文字数据显示格式
    int RingDrawStartPos = 0;           //扇形的起始角度
    int RingDrawEndPos = 360;           //扇形的结束角度
    int RingDrawDirection = 1;          //扇形的绘制方向:  1--顺时针 0--为逆时针
    QString PartternBorderColor;        //图形背景边框颜色
    QColor brushPointColor = Qt::white; //绘制样式的像素点的颜色
    QColor brushColor = Qt::black;
    int partternType;
};

#endif // WIDGET_H
