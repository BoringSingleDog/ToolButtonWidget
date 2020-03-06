                                                                                                                                                                                                                                                                                             #ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QButtonGroup>
#include <QMenu>
#include <QAction>
#include <QTableWidget>
#include <QComboBox>
#include "datatype.h"
#include "subDialog.h"
#include "widget.h"
#include <QLabel>
#include <QMouseEvent>
#include <QCheckBox>
#include <QListWidget>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void showComfirm(ToolButtonType widgetType/* DevInfo* devInfo  */);
private:
    void initWindowPage();                  //初始化部分控件设置
    void initMultStatusSwitchPage();        //初始化多状态切换开关页面
    void initMultStatusLightPage();         //初始化多状态指示灯页面
    void initFuncKeyPage(int arg);          //初始化功能键页面
    void hideFuncKeyButton();
    void initSliderSwitchPage();            //初始化滑动开关界面
    void initControlCode();                 //完成部分控件的手动创建
    void initProjectMenuPage();             //完成项目选单部分控件的手动创建
    void initColorChooseComBox(QTableWidget* table,QLineEdit* lineEdit,QComboBox *comBox);
    void initValueItemPage();
    void initCharaItemPage();
    void initPieCharacterPage();            //初始化圆饼图
    void initNumberComBox(QComboBox* comBox,int startValue,int endValue);
    void initPartternStyleComBox();         //初始化圆饼图界面图案样式下拉列表
    void initDynamicClibrationPage();      //初始化动态刻度界面
    void initDataGroupPage();               //初始化数据群组界面
    void initXYCurveImagePage();            //初始化XY曲线图
    void initWatchNeedlePage();             //初始化表针界面
    void initMoveGraphicalPage();           //初始化移动图形界面
    void initIndirectWindowPage();          //初始化间接窗口界面
    void initDirectWidgetPage();            //初始化直接窗口界面
    void initDataTranportPage();            //初始化数据资料传输
    void initDataTransBackground();         //初始化数据传输资料背景

    void establishConnectRelation(QCheckBox *checkbox , QWidget *widget);
    void showPLCControlWidget();
    void showDataTransBackground();

private slots:
    void doDealMenuAction();
    void doColorButtonClicked();            //颜色选择下拉按钮
    void doBrushStyleSelect();
    void doBrushTableItemClicked(QTableWidgetItem* item);
    void doBrushItemClicked(int,int);
    void doAddbuttonClicked();              //PLC控制界面新增按钮
    void doShowDataTransBackground();


 protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


//由界面控件自己形成的槽函数
private slots:
    void on_BitStatusLightRadio_clicked();
    void on_BitStatusSwitRadio_clicked();
    void on_MultStatusSwitchRadio_clicked();
    void on_MultStatusLightRadio_clicked();
    void on_EjectWindowsRadio_clicked();
    void on_SwitchPublicWindowsRadio_clicked();
    void on_SwitchBaBaseWindowsRadio_clicked();
    void on_TriggerMacroinstructionRadio_clicked();
    void on_WindowControlItemRadio_clicked();
    void on_PictureInterceptionRadio_clicked();
    void on_EnableCheckBox_stateChanged(int arg1);
    void on_closeWindowRadio_clicked();
    void on_returnPreWindwosRadio_clicked();
    void on_EnterKeyRadio_clicked();
    void on_MultipleFunctionsAddAction_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_rollModelCheckBox_clicked();
    void on_SliderSwitchEnableCheckBox_clicked();
    void on_WatchEnableCheckBox_clicked();
    void on_ProjectDataSouceCombox_currentIndexChanged(int index);
    void on_EnableDelHistoryFileCheckBox_clicked();
    void on_ProjectDataTypeCombox_currentTextChanged(const QString &arg1);
    void on_WatchAddrEnable_clicked();
    void on_ValueItemEnableCheckBox_clicked(bool checked);
    void on_useDiffAddrInRW_clicked(bool checked);
    void on_enableInputFcuntion_clicked(bool checked);
    void on_InputInvalidEnable_clicked(bool checked);
    void on_MultipleLinesShowCheckbox_clicked(bool checked);
    void on_checkBox_4_clicked(bool checked);
    void on_circularPointSizeSlider_valueChanged(int value);
    void on_channelNumberCount_currentTextChanged(const QString &arg1);
    void on_PieChartFontColor_currentIndexChanged(int index);
    void on_PieChartPaPatternCombox_currentIndexChanged(int index);
  //  void on_comboBox_15_currentIndexChanged(int index);
    void on_dataShowStyle_currentTextChanged(const QString &arg1);
    void on_PieChartFontComBox_currentTextChanged(const QString &arg1);
    void on_FontSizeComBox_currentTextChanged(const QString &arg1);
    void on_RotateDirectionButton_clicked();
    void on_DynamicCalibrationStyleCombox_currentTextChanged(const QString &arg1);
    void on_DynamicScalrRadiusSlider_valueChanged(int value);
    void on_UseScaleChartCheckBox_stateChanged(int arg1);
    void on_UseRegisterData_stateChanged(int arg1);
    void on_DataGroupUseShiftAddrCheckBox_stateChanged(int arg1);
    void on_DataGroupTotalChannelCombox_currentTextChanged(const QString &arg1);
    void on_enableWatchCheckBox_stateChanged(int arg1);
    void on_DataLimitSourceFromRegister_stateChanged(int arg1);
    void on_XYCurveChannelCountSpinbox_valueChanged(int arg1);
    void on_XYCuroveDataLimitDesc_clicked();
    void on_XYCurveControlAddrSettingBtn_clicked();
    void on_CancelBtn_clicked();
    void on_UseValueFromRegister_stateChanged(int arg1);
    void on_WatchNeedleSettingBtn_clicked();
    void on_BarGraphControlSettingBtn_clicked();
    void on_ClearAddrSetting_clicked();
    void on_MoreInformation1_clicked();
    void on_MoreInfomation2_clicked();
    void on_LimitValueFromRegister_stateChanged(int arg1);
    void on_LimitValueAddiDescBtn_clicked();
    void on_UseWindowShift_stateChanged(int arg1);

private:
    subDialog *subDlg = NULL;
    int clickRadioButtonID = -1;
    ToolButtonType currentType;
    QString  backgroundColor="";               //背景颜色
    QString  chooseColor="";                   //选择颜色
    QString  PieChartBorderColorName="";       //图形边框颜色
    QString  PieChartFontColorName="";         //图形字体颜色
    QString  PieChartBackgroundName="";        //图形背景颜色
    QString  PieChartPatternColorName="";      //图形样式颜色
    int m_rotateDirection = -1;             //0是逆时针，1是顺时针
    int m_startPos = 0;
    int m_endPos = 0;                       //圆形的起始点和结束点
    QMap<int,QString> PieChartPartColor;    //圆饼图的通道以及对应颜色
    QString  DynamicScaleColorStr="";       //刻度颜色
    QString  ScaleChartColorStr = "";       //刻度符号界面的颜色
    QString  DataGroupColorStr = "";        //数据群组界面选定的颜色
    QString  WatchNeedleColorStr = "";      //表针中超出下限的数据颜色
    QString  NormaleValueColorStr = "";     //表针中正常范围的数据颜色
    QString  TopLimitValueColorStr = "";    //表针中超出上限的数据颜色
    QString  WatchNeedlFontColorStr = "";   //表针中文字的颜色

//Qt控件
private:
    Ui::Dialog *ui;  
    QButtonGroup* funcButtonGroup;

    QMenu* multipleFunctionsMenu;
    QAction *delayWidgetAction;
    QAction *BitStatusWidgetAction;         //位状态窗口按钮
    QAction *multipleStatusWidgetAction;    //多状态窗口按钮
    QAction *switchBaseWidgetAction;        //切换基本窗口
    QAction *triggerMacroInstruction;       //触发宏指令按钮
    QTableWidget *ProjectMenuColorTable;    //项目选单中颜色选择
    QLineEdit *colorChooseLineEdit;

    QTableWidget *ProjectMenuChooseTable;    //项目选单中颜色选择
    QLineEdit *ChooseLineEdit;

    QTableWidget *PieChartBorderColor;      //外框颜色
    QLineEdit *PieChartBorderLineEdit;

    QTableWidget *PieChartFontColor;        //字体颜色
    QLineEdit    *PieChartFontLineEdit;

    QTableWidget *PieChartBackground;       //背景颜色
    QLineEdit    *PieChartBackLineEdit;

    QTableWidget *PieChartPattern;          //图案颜色
    QLineEdit    *PieChartPatternLineEdit;

    QTableWidget *DynamicScaleColor;        //刻度颜色选择下拉列表
    QLineEdit    *DynamicScaleColorLineEdit;

    QTableWidget *ScaleChartColor;
    QLineEdit    *ScaleChartColorLineEdit;

    QTableWidget *DataGroupColor;           //数据群组颜色选择下拉栏
    QLineEdit    *DataGroupColorLineEdit;


    QTableWidget *PieChartPatternStyle;     //画刷样式表


    QTableWidget *WatchNeedleColor;         //表针元件中的下限颜色
    QLineEdit    *WatchNeedleLineEdit;

    QTableWidget *NormalValueColor;         //表针元件中的正常数据的颜色
    QLineEdit    *NormalValueLineEdit;

    QTableWidget *TopLimitValueColor;       //表针元件中超出上限的数据颜色
    QLineEdit    *TopLimitValueLineEdit;

    QTableWidget *WatchNeedleFontColor;     //表针元件中的文字的颜色
    QLineEdit    *WatchNeedleFontLineEdit;


    QListWidget *PLClistWidget = NULL;

    QListWidget *TransBackground = NULL;    //资料传输背景

    QWidget      *DynamicScaleTipWidget = NULL;
    QLabel       *DynamicScaleTipLabel = NULL;

};

#endif // DIALOG_H
