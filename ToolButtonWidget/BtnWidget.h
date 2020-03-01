#ifndef BTNWIDGET_H
#define BTNWIDGET_H

#include <QDialog>
#include "datatype.h"
#include <QString>

namespace Ui {
class BtnWidget;
}

class BtnWidget : public QDialog
{
    Q_OBJECT

public:
    explicit BtnWidget(QWidget *parent = 0);
    ~BtnWidget();

    void showIndexWidget(BtnWidgetType type);
    QString getChooseItemText(){return chooseItemText;}
    void setCurrentDevType(int key){devType = key;}            //key--0--系统寄存器；  key--0--用户自定义标签
    void setWidgetCallerName(QString Name){callerName = Name;}

private slots:
    void on_closeBtn_clicked();
    void on_ConfirmButton_clicked();
    void on_CancelButton_clicked();
    void on_listWidget_currentTextChanged(const QString &currentText);

private:
    void initAddrTagPage();         //初始化地址标签界面
    void initDevTypeListWidget();   //初始化地址标签列表

private:
    Ui::BtnWidget *ui;
    QString chooseItemText = "";
    int devType = -1;
    QString callerName = "";

};

#endif // BTNWIDGET_H
