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
#include "BtnWidget.h"
#include "Button.h"
#include "CustomDelegate.h"

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
    void initTabSubWidget(bool isShow);
    void initWindowPage();                  //初始化部分控件设置
    void initBitStatusPage(int type);       //初始化位状态指示灯和切换开关界面          0-位状态指示灯  1-位状态切换开关
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
    void initImageCheckPage();              //初始化图片检视界面
    void initVNCViewerPage();               //初始化VNC界面
    void initQRCodePage();                  //初始化二维码页面
    void initWeChatQRCodePage();            //初始化微信二维码页面
    void initDateAndTimePage();             //初始化日期时间界面
    void initTimerControlPage();            //初始化计时器界面
    void initSchedulePage();                //初始化排程界面
    void initSystemParameterPage();         //初始化系统参数界面

    void initSystemUI();                    //将一些不能重复进行初始化的操作再此进行
    void establishConnectRelation(QCheckBox *checkbox , QWidget *widget,int bit = 0);           //bit参数决定checkbox的选中和关联窗口的显示、隐藏关系，0(选中-显示，未选中-隐藏)，1(选中-隐藏，未选中-显示)
    void showPLCControlWidget();
    void showDataTransBackground();
    void showShleduleWidget();
    void compoundDataTransItem();       //合成数据资料传输背景Item
    void compoundScheduleItem();        //合成排程新增Item
    void configureLBWidget(bool wordCombox, bool addrTips, bool indexCombox, bool systemRegister, bool userCustom,bool hideIndexCheck = true);
    void configureLWWidget(bool wordCombox, bool addrTips, bool indexCombox, bool systemRegister, bool userCustom,bool hideIndexCheck = true);
    void initFontControl(QComboBox *combox);                                   //初始化字体控件
    void initSystemPataTable();
    bool checkIllegalChara(QString arg);


private slots:
    void doDealMenuAction();
    void doColorButtonClicked();            //颜色选择下拉按钮
    void doBrushStyleSelect();
    void doBrushTableItemClicked(QTableWidgetItem* item);
    void doBrushItemClicked(int,int);
    void doAddbuttonClicked();              //PLC控制界面新增按钮
    void doShowDataTransBackground();
    void doDataTransSettingBtn();           //资料传输背景界面设置按钮
    void doDeleteListItem();                //资料传输背景界面删除按钮
    void doAddNewScheduleItem();            //新增排程Item
    void doDeleteScheduleItem();            //删除排程Item
    void doConfigureScheduleItem();         //配置排程Item
    void doTableCheck(int arg1);
    void doLineEditTextChanged();
    void doListItemClicked(int row);
    void doTableViewTextChanged(QStandardItem*  item);
    void doItemClicked(QModelIndex index);
    void doDevTableClicked(QTableWidgetItem* item);

 protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void mousePressEvent(QMouseEvent *event);


//由界面控件自己形成的槽函数
private slots:
    void on_BitStatusLightRadio_clicked();
    void on_UserOperatorLimitCombox_activated(const QString &arg1);
    void on_ConfirmBeforeOperator_stateChanged(int arg1);
    void on_EnabelKeySoundSetting_stateChanged(int arg1);
    void on_UserOperatorLimitCombox_currentTextChanged(const QString &arg1);
    void on_MoreImageBtnLibrary_clicked();

    //位状态指示灯/切换开关图片属性界面
    void on_TurnOnWith0_clicked();
    void on_TurnOnWith1_clicked();
    void on_TurnOnWith2_clicked();
    void on_TurnOnWith3_clicked();
    void on_TurnOnWith4_clicked();
    void on_TurnOnWith5_clicked();

    void on_GalleryButton_clicked();
    void on_ImageCopyCurrentConfigure_clicked();
    void on_PartternCopyCurrentConfigure_clicked();
    void on_UseVectorGraph_stateChanged(int arg1);
    void on_UseImageCheckbox_stateChanged(int arg1);
    void on_InnerCheckBox_stateChanged(int arg1);
    void on_OutsideCheckBox_stateChanged(int arg1);
    void on_InnerCheckBox_clicked();
    void on_OutsideCheckBox_clicked();

    //位状态指示灯/切换开关标签属性界面
    void on_BitStatusTagFlashSpeedSlider_valueChanged(int value);
    void on_BitStatusTagFlashSpeedSpin_valueChanged(int arg1);
    void on_TextLibraryButton_clicked();

    void on_StatusPreviousButton_clicked();
    void on_StatusNextButton_clicked();
    void on_StatusOneButton_clicked();
    void on_StatusTwoButton_clicked();

    //多状态指示灯/多状态切换开关
    void on_MultStatusReadWriteCheck_stateChanged(int arg1);
    void on_MultStatusNumberCombox_currentIndexChanged(int index);

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
    void on_SourceAddrSettingBtn_clicked();
    void on_AddressTypeComobox_currentTextChanged(const QString &arg1);
    void on_OKBtn_clicked();
    void on_TargetAddrSettingBtn_clicked();
    void on_ConfirmSettingBtn_clicked();
    void on_DirAddrSettingBtn_clicked();
    void on_DataTransSourceAddrBtn_clicked();
    void on_DataTransTargetAddrBtn_clicked();
    void on_PropertyAddrSetting_clicked();
    void on_ControlAddrSettingBtn_clicked();
    void on_LimitDataAddrOfMoveGraphics_clicked();
    void on_ConfigureButton_clicked();
    void on_ChooseFileAddrSettingBtn_clicked();
    void on_TextBaseBtn_clicked();
    void on_QRCodeDeviceSettingBtn_clicked();
    void on_QRCodeModeCombox_currentTextChanged(const QString &arg1);
    void on_HourseTagSettingButton_clicked();
    void on_comboBox_14_currentTextChanged(const QString &arg1);
    void on_InputBitSettingButton_clicked();
    void on_ExportBitButton_clicked();
    void on_TimerBitSettingButton_clicked();
    void on_PresetTimeButton_clicked();
    void on_ResetBitButton_clicked();
    void on_RecordBitButton_clicked();
    void on_ConstNumberRadio_clicked();
    void on_AddressRadio_clicked();
    void on_ShceduleTargetAddrSettingBtn_clicked();
    void on_TextWriteAddrSettingBtn_clicked();
    void on_BitSaveAsOn_clicked();
    void on_BitSaveAsOff_clicked();
    void on_wordWWriteRadio_clicked();
    void on_ReadAndWriteUseDiff_stateChanged(int arg1);
    void on_BitStatusSwitch_clicked();
    void on_BitStatusReadAddrSettingBtn_clicked();
    void on_BitStatusWriteAddrSettingBtn_clicked();
    void on_MoveGridButton_clicked();
    void on_PrintBackupsServiceButton_clicked();
    void on_TimeSynButton_clicked();
    void on_EmailButton_clicked();
    void on_FormulaDataBaseButton_clicked();
    void on_DevicePageButton_clicked();
    void on_HMIPropertyButton_clicked();
    void on_GeneralPropertyButton_clicked();
    void on_SystemSettingButton_clicked();
    void on_RemoteButton_clicked();
    void on_UsePasswordButton_clicked();
    void on_ExtendMemoryButton_clicked();
    void on_addNewDevice_clicked();
    void on_DeleteDevTableItem_clicked();
    void on_ProtectOrSetting_clicked();
    void on_ClockFromCombox_currentTextChanged(const QString &arg1);
    void on_ClockType_currentTextChanged(const QString &arg1);
    void on_PrsetStyleSheet_currentIndexChanged(int index);
    void on_DirectLoginWithoutPassword_stateChanged(int arg1);
    void on_EditUserPassword_clicked();
    void on_StateAdderConfigreBtn_clicked();
    void on_ControlAddrConfigureBtn_clicked();
    void on_OpenContactsConfig_clicked();
    void on_addFormulaItem_clicked();
    void on_deleteFormulaItem_clicked();
    void on_importDataBaseFile_clicked();
    void on_exportDataBaseFile_clicked();
    void on_AddNewItem_clicked();
    void on_deleteOneItem_clicked();
    void on_ConfigureTableView_clicked();
    void on_addNewHMIDevice_clicked();

private:
    subDialog *subDlg = NULL;
    BtnWidget *btnWdg = NULL;
    int currentBitStatus = -1;              //0 - 指示灯  1-切换开关

    QString PhotoColorStr = "";                 //图片颜色
    QString innerColorStr = "";                 //内部颜色
    QString outsideColorStr = "";               //外框颜色
    QString partternColorStr = "";              //图案颜色
    QString BitStatusTagColorStr = "";          //标签颜色

    QString sliderBorderColorStr="";           //滑动条边框颜色
    QString sliderBackColorStr= "";            //背景颜色
    QString sliderRailColorStr = "";           //滑轨颜色
    QString sliderControlStr = "";             //滑动条整体颜色
    int sliderButtonType = -1;                 //滑块颜色
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
    QString QRCodeColorStr = "";            //二维码中选中的显示颜色
    QString WeChatQRCodeColorStr = "";      //微信二维码选中的颜色
    QString DateTimeFontColorStr = "";      //日期时间中选定字体的显示颜色
    QString CurSorColorStr= "";             //系统参数中鼠标光标颜色
    QString CursorChooseColorStr = "";      //系统参数中选择颜色

    int addressType;                    //地址模式
    QString timeInterval;               //频率
    int transDataSize;                  //传输数据大小
    int isExecCode;                     //是否执行在打开指定窗口时才执行代码
    QString codeStr;                    //执行的代码名称
    int  codeIndex;                     //代码的Index
    QString sourceDev;
    QString sourceAddr;
    QString sourceShiftStr;

    QString targetDev;
    QString targetAddr;
    QString targetShiftAddr;

    bool showStatus = true;
    QStringList LWlist;
    QStringList LBlist;
    QStringList windowTypeList;

    QString currentScheduleText = "";   //当前选中的排程Item
    QString compoundSchText = "";
    bool isShowTextWrite = true;       //是否显示文字写入Groupbox
    bool isInitWrite = true;
    bool isNewAddItem = true;
    int formulaListRow = -1;
    int currentFormulaRow = -1;
    int currentDevRow = -1;

    QMap<QString,QVector<FormulaItem>> m_allData;   //数据库配方界面右侧所有信息  配方名称 -- 右侧对应的数据
    QMap<int,DevProperty> devData;                  //数据库设备界面上的设备表信息  行号--设备信息

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

    QTableWidget *BitStatusImageColor = NULL;               //位状态图片颜色
    QLineEdit *BitStatusImageColorLineEdit = NULL;

    QTableWidget *BitStatusInnerColor = NULL;
    QLineEdit *BitStatusInnerColorLineEdit = NULL;

    QTableWidget *BitStatusOutSideColor = NULL;
    QLineEdit *BitStatusOutSideColorLineEdit = NULL;

    QTableWidget *BitStatusPartternColor = NULL;
    QLineEdit *BitStatusPartternColorLineEdit = NULL;

    QTableWidget *BitStatusTagColor = NULL;
    QLineEdit    *BitStatusTagColorLineEdit = NULL;

    QTableWidget *ProjectMenuChooseTable = NULL;    //项目选单中颜色选择
    QLineEdit *ChooseLineEdit = NULL;

    QTableWidget *PieChartBorderColor = NULL;      //外框颜色
    QLineEdit *PieChartBorderLineEdit = NULL;

    QTableWidget *PieChartFontColor = NULL;        //字体颜色
    QLineEdit    *PieChartFontLineEdit = NULL;

    QTableWidget *PieChartBackground = NULL;       //背景颜色
    QLineEdit    *PieChartBackLineEdit = NULL;

    QTableWidget *PieChartPattern = NULL;          //图案颜色
    QLineEdit    *PieChartPatternLineEdit = NULL;


    QTableWidget *SliderBorderTable = NULL;
    QLineEdit    *SliderBorderLineEdit = NULL;

    QTableWidget *SliderBackgroundTable = NULL;
    QLineEdit    *SliderBackgroundLineEdit = NULL;

    QTableWidget *SliderRailTable = NULL;
    QLineEdit    *SliderRailLineEdit = NULL;

    QTableWidget *SliderControlColor = NULL;
    QLineEdit    *SliderControlLineEdit = NULL;


    QTableWidget *DynamicScaleColor = NULL;        //刻度颜色选择下拉列表
    QLineEdit    *DynamicScaleColorLineEdit = NULL;

    QTableWidget *ScaleChartColor = NULL;
    QLineEdit    *ScaleChartColorLineEdit = NULL;

    QTableWidget *DataGroupColor = NULL;           //数据群组颜色选择下拉栏
    QLineEdit    *DataGroupColorLineEdit = NULL;

    QTableWidget *PieChartPatternStyle;     //画刷样式表

    QTableWidget *WatchNeedleColor = NULL;         //表针元件中的下限颜色
    QLineEdit    *WatchNeedleLineEdit = NULL;

    QTableWidget *NormalValueColor = NULL;         //表针元件中的正常数据的颜色
    QLineEdit    *NormalValueLineEdit = NULL;

    QTableWidget *TopLimitValueColor = NULL;       //表针元件中超出上限的数据颜色
    QLineEdit    *TopLimitValueLineEdit = NULL;

    QTableWidget *WatchNeedleFontColor = NULL;     //表针元件中的文字的颜色
    QLineEdit    *WatchNeedleFontLineEdit = NULL;

    QListWidget *PLClistWidget = NULL;              //PLC控制Item
    QListWidget *ScheduleItemWidget = NULL;         //排程列表

    QListWidget *TransBackground = NULL;    //资料传输背景

    QWidget      *DynamicScaleTipWidget = NULL;
    QLabel       *DynamicScaleTipLabel = NULL;

    QTableWidget *QRCodeColorTable = NULL;          //二维码显示颜色
    QLineEdit    *QRCodeColorLineEdit = NULL;

    QTableWidget *DateTimeFontColorTable = NULL;
    QLineEdit    *DateTimeFontColorLineEdit = NULL;


    QTableWidget *CursorColorTable = NULL;
    QLineEdit    *CursorColorLineEdit = NULL;

    QTableWidget *CursorChooseColorTable = NULL;
    QLineEdit    *CursorChooseColorLineEdit = NULL;

    QPushButton *addButton = NULL;                  //资料传输背景界面上的按钮
    QPushButton *deleteButton = NULL;
    QPushButton *settingButton  = NULL;

    QPushButton *addSchedule = NULL;                  //排程界面上的按钮
    QPushButton *deleteSchedule = NULL;
    QPushButton *configureSchedule  = NULL;


    Button *sliderButton1 = NULL;
    Button *sliderButton2 = NULL;
    Button *sliderButton3 = NULL;
    Button *sliderButton4 = NULL;


    QStandardItemModel *dataModel;             //配方数据库

};

#endif // DIALOG_H
