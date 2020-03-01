#ifndef SUBDIALOG_H
#define SUBDIALOG_H

#include <QDialog>
#include "datatype.h"
#include "BtnWidget.h"
#include <QMouseEvent>

namespace Ui {
class subDialog;
}

class subDialog : public QDialog
{
    Q_OBJECT

public:
    explicit subDialog(QWidget *parent = 0);
    ~subDialog();

    void showSubDialog(subWidgetType type);
    void getRotateParameter(int &ClockWise,int &startPos,int &endPos);
    void setWidgetCaller(QString widgetName){widgetCaller = widgetName;}

private:
    void initWidgetControl();
    void initWatchNeedlePage();


private slots:
    void on_wholeCircular_clicked(bool checked);
    void on_IndexRegisterCheckbox_stateChanged(int arg1);
    void on_AddrTagBaseBtn_clicked();
    void on_ExitBtn_clicked();
    void on_ConfirmBtn_clicked();
    void on_WatchNeedleSystemRegister_stateChanged(int arg1);
    void on_UserCustomTagCheckbox_stateChanged(int arg1);
    void on_IndexRegisterCheckbox_2_stateChanged(int arg1);

protected:
    bool   eventFilter(QObject *obj, QEvent *ev);


private:
    Ui::subDialog *ui;
    BtnWidget *btnWdg = NULL;


private:
    QString currentDevTypeStr = "";         //当前记录的地址
    QString widgetCaller = "";
};

#endif // SUBDIALOG_H
