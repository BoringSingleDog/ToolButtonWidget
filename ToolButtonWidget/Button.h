#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
class Button : public QPushButton
{
public:
    Button();
    void paintEvent(QPaintEvent *event);
    void setPainterColor(QColor buttonColor){color = buttonColor;}
    void setButtonType(int buttonType){type = buttonType;}
private:
    QColor color;
    int type = -1;
};

#endif // BUTTON_H
