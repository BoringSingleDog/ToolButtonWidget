#ifndef SUBDIALOG_H
#define SUBDIALOG_H

#include <QDialog>
#include "datatype.h"
#include "BtnWidget.h"
#include "ConfigDialog.h"
#include <QMouseEvent>
#include <QComboBox>
#include <QCheckBox>
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
    void getPLCChooseResult(QString &windowType, int &isExecCom, int &commandID, int &useBackLight, int &addClear, int &useWindIDShift, int &windowIDShift, QString &devType, QString &AddrType, int &addrNumber);
    void setAddrWidgetType(int bit);            //窗口显示类型， bit = 0/1
    void setSubControlEnable(bool wordCombox, bool addTips, bool indexCombox , bool systemRegister = true, bool userCustomTag = true,bool isHideIndexCheckbox = true);
    void getConfigurePassword(QString &password,int &isHidden);
    void setDataBasePage(FormulaItem *item);
    void getDataBaseResult(FormulaItem& item);
    void getDeivceProperty(QString& deviceName,QString& addrType,QString& position,QString& deviceType,QString& screenType,QString& commProtocal,QString& stationID);
    void setWidgetInfoDisable(QString& text);
    void setWidgetInfoEnable(QString& text);
    void setCurrentDevPro(DevProperty& dev);
    void setAddNewDeviceFalg(bool flag){isNewAddDevice = flag;}
private:
    void initWidgetControl();
    void initWatchNeedlePage();
    void initPLCControlSubPage();
    void initDataBaseSubPage();
    void initNewDeicePropertyPage();            //初始化系统参数界面-新增设备
    void initAddHMIDevicePage();
    void initWidgetNumber(QComboBox* box,int startNumber,int endNumber);

    void establishConnectRelation(QCheckBox *checkbox , QWidget *widget,int bit = 0);
private slots:
    void on_wholeCircular_clicked(bool checked);
    void on_AddrTagBaseBtn_clicked();
    void on_ExitBtn_clicked();
    void on_ConfirmBtn_clicked();
    void on_WatchNeedleSystemRegister_stateChanged(int arg1);
    void on_UserCustomTagCheckbox_stateChanged(int arg1);
    void on_IndexRegisterCheckbox_2_stateChanged(int arg1);
    void on_ExecSpecialCommand_stateChanged(int arg1);
    void on_UseWindowIDCheckBox_stateChanged(int arg1);
    void doListItemChanged(int index);
    void on_EnableReadOnly_stateChanged(int arg1);
    void on_ComConfigBtn_clicked();
    void on_ConfigLocationBtn_clicked();
    void on_DataTransformWayBtn_clicked();
    void on_AddScropLimitBtn_clicked();
    void on_PresetStationUseStationVaraiable_stateChanged(int arg1);
    void on_DeviceLocationCombox_currentTextChanged(const QString &arg1);
    void on_NewDeviceRadioBtn_clicked();

protected:
    bool   eventFilter(QObject *obj, QEvent *ev);


private:
    Ui::subDialog *ui;
    BtnWidget *btnWdg = NULL;
    ConfigDialog* configDlg = NULL;

private:
    QString currentDevTypeStr = "";         //当前记录的地址
    QString widgetCaller = "";
    QString currentComInfoStr="";
    int chooseItemIndex = -1;
    int subAddrWidgetType = -1;
    bool isEnableTips = false;
    bool isEnableIndexCombox = false;
    bool isEnableWordWidget = false;
    bool isEnableStstemRegister = false;
    bool isEnableUseCustom = false;
    bool isEnableIndexCheck = false;
    bool isNewAddDevice = true;             //是否是新建设备
    QVector<QString> comInfo;
};

#endif // SUBDIALOG_H
