#include "dialog.h"
#include "ui_dialog.h"
#include "CustomDelegate.h"
#include <QDebug>
#include <QColorDialog>
#include <QFontDatabase>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QTime>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QDialog>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::Window |Qt::WindowStaysOnTopHint);
    this->setModal(true);
    subDlg = new subDialog(this);
    btnWdg = new BtnWidget(this);
    initWindowPage();
    initControlCode();
    initProjectMenuPage();
    initValueItemPage();
    initCharaItemPage();
    initPieCharacterPage();
    initDynamicClibrationPage();
    initDataGroupPage();
    initXYCurveImagePage();
    initWatchNeedlePage();
    initMoveGraphicalPage();

    LWlist<<"LW"<<"RW"<<"RW_A"<<"RWI"<<"EM0"<<"EM1"<<"EM2"<<"EM3"<<"EM4"<<"EM5"<<"EM6"<<"EM7"<<"EM8"<<"EM9";
    LBlist<<"LB"<<"RW"<<"RW_A_Bit"<<"LW_Bit"<<"RBI";
    windowTypeList<<"10.WINDOW_010"<<"50.Keypad 1-Integer"<<"51.Keypad 2-Integer"<<"52.Keypad 3-Integer"<<"53.Keypad 3-Integer"<<"54.Keypad 5-HEX"<<"58.Keypad 9-Numeric"<<"60.ASCII Small"<<"62.ASCII　Upper S"<<"63.ASCII Lower S"<<"70.Login & logout"<<"71.Add account"<<"72.Delete account"<<"73.Set privilege"<<"74.Set password"<<"76.EasyAccess 2.0 Setting"<<"77.EasyAccess 2.0 Proxy Setting"<<"80.Screen SAver"<<"82.Wechat Code";
    initSystemUI();

}

Dialog::~Dialog()
{
    delete ui;
}

/**********************************************************************************************/
/******************************          UI界面控件代码          ********************************/
/**********************************************************************************************/

void Dialog::showComfirm(ToolButtonType widgetType)
{
    currentType = widgetType;
    switch(widgetType){
    case BitStatusPointLight:
        this->setFixedSize(QSize(570,800));
        initTabSubWidget(true);
        initBitStatusPage(0);
        ui->generalProStack->setCurrentIndex(1);                //一般属性
        ui->SecurityStackWidget->setCurrentIndex(0);            //安全界面
        ui->PhotoConfigureStackWidget->setCurrentIndex(0);      //图片界面
        ui->ControlTagStackWidget->setCurrentIndex(0);          //标签界面
        setWindowTitle("新增 位状态指示灯/位状态切换开关 元件");
        break;
    case MultStatsPointLight:
        this->setFixedSize(QSize(570,800));
        initTabSubWidget(true);
        ui->generalProStack->setCurrentIndex(0);
        ui->SecurityStackWidget->setCurrentIndex(0);            //安全界面
        ui->PhotoConfigureStackWidget->setCurrentIndex(0);      //图片界面
        ui->ControlTagStackWidget->setCurrentIndex(0);          //标签界面
        //ui->ElementPropertyTab->removeTab(1);
        ui->MultStatusLightRadio->setChecked(true);
        initMultStatusLightPage();
        initBitStatusPage(0);
        setWindowTitle("新增 多状态指示灯/多状态切换开关 元件");
        break;
    case BitStatusConfigure:                                    //位状态设置
        this->setFixedSize(QSize(570,800));
        initTabSubWidget(true);
        ui->generalProStack->setCurrentIndex(2);
        ui->SecurityStackWidget->setCurrentIndex(0);            //安全界面
        ui->PhotoConfigureStackWidget->setCurrentIndex(0);      //图片界面
        ui->ControlTagStackWidget->setCurrentIndex(0);          //标签界面
        //ui->ElementPropertyTab->removeTab(1);
        initBitStatusPage(1);
        setWindowTitle("新增 位状态设置 元件");
        break;
    case MultStatusConfigure:                                   //多状态设置界面
        this->setFixedSize(QSize(570,800));
        initTabSubWidget(true);
        ui->generalProStack->setCurrentIndex(3);
        ui->SecurityStackWidget->setCurrentIndex(0);            //安全界面
        ui->PhotoConfigureStackWidget->setCurrentIndex(0);      //图片界面
        ui->ControlTagStackWidget->setCurrentIndex(0);          //标签界面
        //ui->ElementPropertyTab->removeTab(1);
        initBitStatusPage(1);
        setWindowTitle("新增 多状态设置 元件");
        break;
    case BitStatusSelectSwitch:
        this->setFixedSize(QSize(570,800));
        initTabSubWidget(true);
        initBitStatusPage(1);
        setWindowTitle("新增 位状态切换开关/位状态指示灯 元件");
        ui->SecurityStackWidget->setCurrentIndex(0);            //安全界面
        ui->PhotoConfigureStackWidget->setCurrentIndex(0);      //图片界面
        ui->ControlTagStackWidget->setCurrentIndex(0);          //标签界面
        //ui->ElementPropertyTab->removeTab(1);
        ui->generalProStack->setCurrentIndex(1);
        break;
    case MultStatusSelectSwitch:
        this->setFixedSize(QSize(570,800));
        initTabSubWidget(true);
        ui->MultStatusSwitchRadio->setChecked(true);
        initMultStatusSwitchPage();
        initBitStatusPage(1);
        setWindowTitle("新增 多状态切换开关/多状态指示灯 元件");
        ui->SecurityStackWidget->setCurrentIndex(0);            //安全界面
        ui->PhotoConfigureStackWidget->setCurrentIndex(0);      //图片界面
        ui->ControlTagStackWidget->setCurrentIndex(0);          //标签界面
        //ui->ElementPropertyTab->removeTab(1);
        ui->generalProStack->setCurrentIndex(0);
        break;
    case FunctionKeyTool:
        this->setFixedSize(QSize(570,800));
        initTabSubWidget(true);
        setWindowTitle("新增 功能键 元件");
        initFuncKeyPage(0);
        ui->generalProStack->setCurrentIndex(4);
        ui->SecurityStackWidget->setCurrentIndex(0);            //安全界面
        ui->PhotoConfigureStackWidget->setCurrentIndex(0);      //图片界面
        ui->ControlTagStackWidget->setCurrentIndex(0);          //标签界面
        //ui->ElementPropertyTab->removeTab(1);
        initBitStatusPage(1);
        break;
    case CompMultFuncButton:
        this->setFixedSize(QSize(570,800));
        initTabSubWidget(true);
        setWindowTitle("新增 复合式多功能 元件");
        ui->generalProStack->setCurrentIndex(5);
        ui->SecurityStackWidget->setCurrentIndex(0);            //安全界面
        ui->PhotoConfigureStackWidget->setCurrentIndex(0);      //图片界面
        ui->ControlTagStackWidget->setCurrentIndex(0);          //标签界面
        initBitStatusPage(1);
        break;
    case SliderSwitch:
        this->setFixedSize(QSize(570,800));
        initTabSubWidget(true);
        initBitStatusPage(1);
        initSliderSwitchPage();
        setWindowTitle("新增 滑动开关 元件");
        ui->generalProStack->setCurrentIndex(6);
        ui->SecurityStackWidget->setCurrentIndex(0);            //安全界面
        ui->PhotoConfigureStackWidget->setCurrentIndex(0);      //图片界面
        ui->AppearanceStackWidget->setCurrentIndex(0);          //外观界面
        ui->ElementPropertyTab->setTabEnabled(1,true);             //显示外观界面
        ui->ElementPropertyTab->setTabEnabled(4,false);            //隐藏标签界面
        ui->ElementPropertyTab->setStyleSheet("QTabBar::tab:disabled {width: 0; color: transparent;}");
        break;
    case ProjectChooseList:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 项目选单 元件");
        ui->generalProStack->setCurrentIndex(7);
        ui->SecurityStackWidget->setCurrentIndex(0);            //安全界面
        ui->PhotoConfigureStackWidget->setCurrentIndex(0);      //图片界面
        ui->ControlTagStackWidget->setCurrentIndex(0);          //标签界面
        //ui->ElementPropertyTab->removeTab(1);
        break;
    case NumberShowButton:
        setWindowTitle("新增 数值 元件");
        ui->generalProStack->setCurrentIndex(8);
        break;
    case CharacterShowButton:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 字符 元件");
        ui->generalProStack->setCurrentIndex(9);
        break;
    case PieChartItem:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 圆饼图 元件");
        ui->generalProStack->setCurrentIndex(10);
        break;
    case DynamicClibration:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 动态刻度 元件");
        ui->generalProStack->setCurrentIndex(11);
        break;
    case DataGroupItem:
        setWindowTitle("新增 数据群组 元件");
        ui->generalProStack->setCurrentIndex(12);
        break;
    case XYEllispImage:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 XY曲线图 元件");
        ui->generalProStack->setCurrentIndex(13);
        break;
    case HistogramPage:
        setWindowTitle("新增 棒图 元件");
        ui->generalProStack->setCurrentIndex(14);
        break;
    case WatchNeedlePage:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 表针 元件");
        ui->generalProStack->setCurrentIndex(15);
        break;
    case DynamicPainttingPage:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 动态绘图 元件");
        ui->generalProStack->setCurrentIndex(16);
        break;
    case MoveGrapgicalPage:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 移动图形 元件");
        ui->generalProStack->setCurrentIndex(17);
        break;
    case PLCControlPage:
        this->setFixedSize(QSize(570,800));
        this->setWindowTitle("PLC控制");
        showPLCControlWidget();
        break;
    case IndirectWidgetPage:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 间接窗口 元件");
        initIndirectWindowPage();
        ui->generalProStack->setCurrentIndex(18);
        break;
     case DirectWidgetPage:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 直接窗口 元件");
        initDirectWidgetPage();
        ui->generalProStack->setCurrentIndex(19);
        break;
     case DataTransportPage:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 数据资料传输窗口 元件");
        initDataTranportPage();
        ui->generalProStack->setCurrentIndex(20);
        break;
     case DataTransportBackground:
        this->setFixedSize(QSize(570,800));
        showDataTransBackground();
        break;
     case PhotoCheckPage:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 图片检视 元件");
        initImageCheckPage();
        ui->generalProStack->setCurrentIndex(22);
        break;
     case VNCViewerPage:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 VNC Viewer 元件");
        initVNCViewerPage();
        ui->generalProStack->setCurrentIndex(23);
        break;
     case QRCodePage:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 二维码显示 元件");
        initQRCodePage();
        ui->generalProStack->setCurrentIndex(24);
        break;
     case WeChatQRCodePage:
        this->setFixedSize(QSize(570,800));
        this->setWindowTitle("新增 微信二维码 元件");
        initWeChatQRCodePage();
        ui->generalProStack->setCurrentIndex(24);
        break;
     case DateAndTimePage:
        this->setFixedSize(QSize(570,800));
        setWindowTitle("新增 日期/时间 元件");
        initDateAndTimePage();
        ui->generalProStack->setCurrentIndex(25);
        break;
     case TimerControlPage:
        this->setFixedSize(QSize(1080,770));
        setWindowTitle("新增 计时器 元件");
        initTimerControlPage();
        ui->generalProStack->setCurrentIndex(26);
        break;
     case ScheduleControlPage:
        showShleduleWidget();
        break;
     case SystemParamterPage:
        initSystemParameterPage();
        this->setFixedSize(QSize(740,800));
        initTabSubWidget(false);
        ui->generalProStack->setCurrentIndex(28);
        setWindowTitle("系统参数设置");
        break;
    }
}

void Dialog::initTabSubWidget(bool isShow)
{
    if(!isShow)
    {
        ui->ElementPropertyTab->setTabEnabled(1,false);            //隐藏标签界面
        ui->ElementPropertyTab->setTabEnabled(2,false);            //隐藏标签界面
        ui->ElementPropertyTab->setTabEnabled(3,false);            //隐藏标签界面
        ui->ElementPropertyTab->setTabEnabled(4,false);            //隐藏标签界面
        ui->ElementPropertyTab->setStyleSheet("QTabBar::tab:disabled {width: 0; color: transparent;}");
        ui->generalProStack->setToolTip("");
        ui->ElementPropertyTab->setTabText(0,"");
        ui->ElementPropertyTab->setTabText(1,"");
        ui->ElementPropertyTab->setTabText(2,"");
        ui->ElementPropertyTab->setTabText(3,"");
    }
    else
    {
        ui->ElementPropertyTab->setTabEnabled(1,true);            //隐藏标签界面
        ui->ElementPropertyTab->setTabEnabled(2,true);            //隐藏标签界面
        ui->ElementPropertyTab->setTabEnabled(3,true);            //隐藏标签界面
        ui->ElementPropertyTab->setTabEnabled(4,true);            //隐藏标签界面
        ui->ElementPropertyTab->setStyleSheet("QTabBar::tab:enabled {width: 0; color: transparent;}");
        ui->generalProStack->setToolTip("");
        ui->ElementPropertyTab->setTabText(0,"一般属性");
        ui->ElementPropertyTab->setTabText(1,"安全");
        ui->ElementPropertyTab->setTabText(2,"图片");
        ui->ElementPropertyTab->setTabText(3,"标签");
    }
}

void Dialog::initWindowPage()
{
    //功能键元件的一般属性页面
    funcButtonGroup = new QButtonGroup;
    funcButtonGroup->addButton(ui->SwitchBaBaseWindowsRadio);
    funcButtonGroup->addButton(ui->SwitchPublicWindowsRadio);
    funcButtonGroup->addButton(ui->EjectWindowsRadio);
    funcButtonGroup->addButton(ui->returnPreWindwosRadio);
    funcButtonGroup->addButton(ui->closeWindowRadio);
    funcButtonGroup->addButton(ui->TriggerMacroinstructionRadio);
    funcButtonGroup->addButton(ui->WindowControlItemRadio);
    funcButtonGroup->addButton(ui->PictureInterceptionRadio);
    funcButtonGroup->addButton(ui->EnterKeyRadio);
    funcButtonGroup->addButton(ui->BackSpaceKeyRadio);
    funcButtonGroup->addButton(ui->clearKeyRadio);
    funcButtonGroup->addButton(ui->EscKeyRadio);
    funcButtonGroup->addButton(ui->DeleteKeyRadio);
    funcButtonGroup->addButton(ui->LeftKeyRadio);
    funcButtonGroup->addButton(ui->RightKeyRadio);
    funcButtonGroup->addButton(ui->IncKeyRadio);
    funcButtonGroup->addButton(ui->clearKeyRadio);
    funcButtonGroup->addButton(ui->DecKeyRadio);
    funcButtonGroup->addButton(ui->CodeKeyRadio);
}

void Dialog::initBitStatusPage(int type)    //0 -指示灯  1-切换开关
{
    ui->ElementPropertyTab->setTabEnabled(1,false);           //隐藏外观界面
    ui->ElementPropertyTab->setTabEnabled(4,true);            //显示标签界面
    ui->ElementPropertyTab->setStyleSheet("QTabBar::tab:disabled {width: 0; color: transparent;}");


    currentBitStatus = type;
    //初始化位状态指示灯/切换开关的一般属性界面
    ui->BitStatusLightWriteAddr->hide();
    establishConnectRelation(ui->ReadAndWriteUseDiff,ui->BitStatusLightWriteAddr);

    ui->BitStatusWriteSubWidget->hide();
    establishConnectRelation(ui->ReadAndWriteUseDiff,ui->BitStatusWriteSubWidget);

    ui->BitStatusReadAddr->clear();
    ui->BitStatusReadAddr->addItems(LBlist);
    ui->BitStatusReadAddr->setCurrentIndex(0);

    ui->BitStatusWriteAddr->clear();
    ui->BitStatusWriteAddr->addItems(LBlist);
    ui->BitStatusWriteAddr->setCurrentIndex(0);


    ui->PartternGalleryButton->setEnabled(false);

    if(type == 0)
    {
        ui->BitStatusProperty->hide();
        ui->BitStatusMacroinstruction->hide();
        ui->BitStatusLightFlashType->show();
        ui->ReadAndWriteUseDiff->hide();
        ui->BitStatusLightWriteAddr->hide();

        ui->SecurityControlgGroup->hide();          //隐藏安全控制
        ui->KeySoundGroup->hide();

        ui->InnerCheckBox->setChecked(false);
        ui->InnerColorCombox->hide();
    }
    else if(type == 1)
    {
        ui->BitStatusProperty->show();
        ui->BitStatusMacroinstruction->show();
        ui->BitStatusLightFlashType->hide();
        ui->ReadAndWriteUseDiff->show();
        ui->BitStatusLightWriteAddr->show();
        ui->BitStatusLightWriteAddr->setTitle("");

        ui->SecurityControlgGroup->show();          //隐藏安全控制
        ui->KeySoundGroup->show();

        ui->InnerCheckBox->setChecked(true);
        ui->InnerColorCombox->show();
    }
    else if(type == 2)      //滑动开关
    {

    }
    else if(type == 3)      //项目选单
    {

    }

    //位状态指示灯安全属性界面
    ui->ConfirmWaitTimeLineEdit->setText("10");
    ui->LeastKeyTime->clear();
    QStringList itemText;
    itemText<<"0"<<"0"<<"0.1"<<"0.2"<<"0.3"<<"0.4"<<"0.5"<<"0.6"<<"0.7"<<"0.8"<<"0.9";
    ui->LeastKeyTime->addItems(itemText);

    QString itemStr = "";
    for(int i=1;i<=100;i++)
    {
        itemStr = QString::number(i);
        ui->LeastKeyTime->addItem(itemStr);
    }
    ui->LeastKeyTime->setCurrentIndex(0);
    ui->RegisterValueWidget->hide();
    ui->UseLimitSubWidget->hide();

    ui->KeySoundPreSetting->hide();
    ui->SoundLibraryButton->setEnabled(false);
    ui->PlaySoundButton->setEnabled(false);

    ui->RegisterValueWidget->hide();
    ui->UseRegisterValue->setChecked(false);
    establishConnectRelation(ui->UseRegisterValue,ui->RegisterValueWidget);

    //图片属性
    ui->UseVectorGraphGroupBox->hide();
    establishConnectRelation(ui->UseVectorGraph,ui->UseVectorGraphGroupBox);
    ui->UseImageCheckbox->setChecked(true);

    //标签属性
    ui->TextLibraryTagWidget->hide();
    ui->UseTextLibraryCheckbox->setChecked(false);
    establishConnectRelation(ui->UseTextLibraryCheckbox,ui->TextLibraryTagWidget);

    initNumberComBox(ui->BitStatusTagSizeCombox,5,256);
    initFontControl(ui->BiStatusTagFontCombox);


    ui->TurnOnToOffCheckbox->setChecked(true);
    establishConnectRelation(ui->TurnOnToOffCheckbox,ui->BitStatusTagStatusWidget);
    establishConnectRelation(ui->TurnOnToOffCheckbox,ui->PropertyLabel );
    establishConnectRelation(ui->TurnOnToOffCheckbox,ui->BitStatusTagStatusButton);
    establishConnectRelation(ui->TurnOnToOffCheckbox,ui->CopyCurrentStatusToAllStatus);

    initNumberComBox(ui->MultStatusNumberCombox,1,257);
}


//隐藏多状态指示灯中部分控件来实现多状态切换开关页面
void Dialog::initMultStatusSwitchPage()
{
    ui->MultStatusReadAddrGroup->setTitle(QStringLiteral("读取/写入地址"));
    ui->MultStatusWriteAddrGroup->show();
    ui->MultStatusWriteAddrGroup->setTitle(QStringLiteral(" "));

    ui->MultStatusProperLabel->hide();
    ui->MultStatusWriteSubWidget->hide();           //隐藏子窗口
    ui->MultStatusSendGroup->show();

    ui->MultStatusReadWriteCheck->show();
    ui->MultStatusOperatorModeCombox->show();
    ui->MultStatusOperatorLabel->show();
    ui->MultStatusCrycleLabel->show();
    ui->MultStatusCrycleCombox->show();
    ui->MultStatusSendCmdCheck->show();
    ui->UseStatusSubWidget->show();
    ui->MultStatusProperLabel->hide();
}
//更改多状态指示灯中的部分控件
void Dialog::initMultStatusLightPage()
{
    ui->MultStatusReadAddrGroup->setTitle(QStringLiteral("读取地址"));
    ui->MultStatusReadWriteCheck->hide();
    ui->MultStatusWriteAddrGroup->hide();
    ui->MultStatusOperatorModeCombox->hide();
    ui->MultStatusOperatorLabel->hide();
    ui->MultStatusCrycleLabel->hide();
    ui->MultStatusCrycleCombox->hide();
    ui->MultStatusSendCmdCheck->hide();
    ui->MultStatusSendGroup->hide();
    ui->UseStatusSubWidget->hide();
    ui->MultStatusProperLabel->show();
}

void Dialog::initFuncKeyPage(int arg)
{
    clickRadioButtonID = arg;
    if(arg == 0 )       //初始化时调用，只隐藏部分
    {
       hideFuncKeyButton();
       ui->SwitchBaBaseWindowsRadio->setChecked(true);

    }
    else if(arg == 1)   //切换公共窗口
    {
        hideFuncKeyButton();
        ui->SwitchPublicWindowsRadio->setChecked(true);

    }
    else if(arg == 2)   //切换基本窗口
    {
        hideFuncKeyButton();
        ui->SwitchBaBaseWindowsRadio->setChecked(true);

    }
    else if(arg == 3)   //宏指令触发
    {
       hideFuncKeyButton();
       ui->MacroInstructionCombox->show();
       ui->MacroInstructionLabel->show();
       ui->TriggerMacroinstructionRadio->setChecked(true);
    }
    else if(arg == 4)   //窗口控制条
    {
        hideFuncKeyButton();
        ui->NoticeGroupBox->hide();
        ui->WindowControlItemRadio->setChecked(true);
    }
    else if(arg == 5)
    {
       hideFuncKeyButton();  //画面截取
       ui->PictureInterceptionRadio->setChecked(true);
       ui->ExportCacheCombox->show();
       ui->ExportCacheDeviceLabel->show();
       ui->GraphRotationCheckBox->show();
       ui->GraphRotationTipsLabel->show();
       ui->NoticeGroupBox->show();
       ui->EnableCheckBox->show();
       ui->NoticeLine->show();
       ui->GraphRotationCheckBox->setDisabled(true);

    }
    else if(arg == 6)    //通知 启用
    {
       ui->ConfigAsONRadio->show();
       ui->ConfigAsOFFRadio->show();
       ui->ConfigAsOFFRadio->setChecked(true);      //设为OFF默认勾选
       ui->FunctionDeviceLabel->show();
       ui->FuncDevCombbox->show();
       ui->FuncAddrLabel->show();
       ui->FuncAddrCombox->show();
       ui->lineEdit_18->show();
       ui->lineEdit_17->show();
       ui->FuncDevConfigureButton->show();
    }
    else if(arg == 7)    //通知不启用
    {
       ui->ConfigAsONRadio->hide();
       ui->ConfigAsOFFRadio->hide();
       ui->FunctionDeviceLabel->hide();
       ui->FuncDevCombbox->hide();
       ui->FuncAddrLabel->hide();
       ui->FuncAddrCombox->hide();
       ui->lineEdit_18->hide();
       ui->lineEdit_17->hide();
       ui->FuncDevConfigureButton->hide();
    }
    else if(arg == 8)   //关闭窗口
    {
        hideFuncKeyButton();
        ui->closeWindowRadio->setChecked(true);
    }
    else if(arg == 9)   //弹出窗口
    {
        hideFuncKeyButton();
        ui->EEjectWidgetSettingPage->show();
    }
}

void Dialog::hideFuncKeyButton()
{
    //隐藏弹出窗口中的部分控件
    ui->EEjectWidgetSettingPage->hide();

    //隐藏画面截取中的部分控件
    ui->ExportCacheCombox->hide();
    ui->ExportCacheDeviceLabel->hide();
    ui->GraphRotationCheckBox->hide();
    ui->GraphRotationTipsLabel->hide();

    //隐藏触发宏指令中部分控件
    ui->MacroInstructionCombox->hide();
    ui->MacroInstructionLabel->hide();

    //显示串口控制条中部分控件
    ui->NoticeGroupBox->show();

    //隐藏通知GroupBox中的部分控件
    ui->ConfigAsONRadio->hide();
    ui->ConfigAsOFFRadio->hide();
    ui->FunctionDeviceLabel->hide();
    ui->FuncDevCombbox->hide();
    ui->FuncAddrLabel->hide();
    ui->FuncAddrCombox->hide();
    ui->lineEdit_18->hide();
    ui->lineEdit_17->hide();
    ui->FuncDevConfigureButton->hide();
    ui->EnableCheckBox->show();
    ui->NoticeLine->show();

    update();
}

void Dialog::initSliderSwitchPage()
{
    //隐藏滑动开关界面的通知GroupBox
    ui->SetAsOFFRadio->hide();
    ui->SetAsONRadio->hide();
    ui->sliderSwitchNoticeGroupWidget->hide();

    ui->PrisonWatchGroupWidget->hide();

    ui->rollValueLabel->hide();
    ui->rollValueLineEdit->hide();


    sliderButton1 = new Button;
    sliderButton2 = new Button;
    sliderButton3 = new Button;
    sliderButton4 = new Button;

    sliderButton1->setPainterColor(QColor(Qt::red));
    sliderButton1->setButtonType(4);
    connect(sliderButton1,&Button::clicked,[this](){sliderButtonType = 4;});

    sliderButton2->setPainterColor(QColor(Qt::red));
    sliderButton2->setButtonType(3);
    connect(sliderButton2,&Button::clicked,[this](){sliderButtonType = 3;});

    sliderButton3->setPainterColor(QColor(Qt::red));
    sliderButton3->setButtonType(2);
    connect(sliderButton3,&Button::clicked,[this](){sliderButtonType = 2;});

    sliderButton4->setPainterColor(QColor(Qt::red));
    sliderButton4->setButtonType(1);
    connect(sliderButton4,&Button::clicked,[this](){sliderButtonType = 1;});


    QHBoxLayout *layout = new QHBoxLayout;
    layout->addStretch();
    layout->addWidget(sliderButton1);
    layout->addStretch();
    layout->addWidget(sliderButton2);
    layout->addStretch();
    layout->addWidget(sliderButton3);
    layout->addStretch();
    layout->addWidget(sliderButton4);
    layout->addStretch();

    ui->SliderButtonWidget->setLayout(layout);


}

void Dialog::initControlCode()
{
    multipleFunctionsMenu = new QMenu;
    QString menuStyleSheet = QString("QMenu::item{padding-left:20px;}");
    multipleFunctionsMenu->setStyleSheet("");

    delayWidgetAction = new QAction("延迟",this);
    delayWidgetAction->setProperty("actionName","delayWidget");
    connect(delayWidgetAction,SIGNAL(triggered()),this,SLOT(doDealMenuAction()));

    BitStatusWidgetAction = new QAction("位状态设置",this);
    BitStatusWidgetAction->setProperty("actionName","BitStatusWidget");
    connect(BitStatusWidgetAction,SIGNAL(triggered()),this,SLOT(doDealMenuAction()));

    multipleStatusWidgetAction = new QAction("多状态设置",this);
    multipleStatusWidgetAction->setProperty("actionName","multipleStatusWidget");
    connect(multipleStatusWidgetAction,SIGNAL(triggered()),this,SLOT(doDealMenuAction()));

    switchBaseWidgetAction = new QAction("切换基本窗口",this);
    switchBaseWidgetAction->setProperty("actionName","switchBaseWidget");
    connect(switchBaseWidgetAction,SIGNAL(triggered()),this,SLOT(doDealMenuAction()));

    triggerMacroInstruction = new QAction("触发宏指令",this);
    triggerMacroInstruction->setProperty("actionName","triggerMacroInstruction");
    connect(triggerMacroInstruction,SIGNAL(triggered()),this,SLOT(doDealMenuAction()));

    multipleFunctionsMenu->addAction(delayWidgetAction);
    multipleFunctionsMenu->addAction(BitStatusWidgetAction);
    multipleFunctionsMenu->addAction(multipleStatusWidgetAction);
    multipleFunctionsMenu->addAction(switchBaseWidgetAction);
    multipleFunctionsMenu->addAction(triggerMacroInstruction);

}

//项目选单部分控件的初始化
void Dialog::initProjectMenuPage()
{
  //【背景】和【选择】两个下拉列表的颜色初始化
  colorChooseLineEdit = new QLineEdit(ui->ProjectMenuBackgroundCombox);
  ProjectMenuColorTable = new QTableWidget(6,8);
  ProjectMenuColorTable->setProperty("tableName","backGroundTable");
  initColorChooseComBox(ProjectMenuColorTable,colorChooseLineEdit,ui->ProjectMenuBackgroundCombox);

  ProjectMenuChooseTable = new QTableWidget(6,8);
  ProjectMenuChooseTable->setProperty("tableName","chooseTable");
  ChooseLineEdit = new QLineEdit(ui->ProjectMenuBackgroundCombox);
  initColorChooseComBox(ProjectMenuChooseTable,ChooseLineEdit,ui->ProjectMenuChooseCombox);

  //只保留预览Group显示，其余全部隐藏
  ui->ProjectDataSourceHistory->hide();
  ui->ProjectAddrGroupBox->hide();
  ui->ControlAddrGroupBox->hide();
  ui->enableConfirmAfterOpened->hide();
  ui->ControlAddrGroupBox->hide();

  //隐藏开启通知
  ui->enableConfirmSaveAsOn->hide();
  ui->enableConfirmSaveAsOff->hide();
  ui->enableConfirmSubWidget->hide();

  //隐藏删除历史文件
  ui->EnableDelHistoryFileCheckBox->hide();

  //资料取样元件索引默认隐藏
  ui->ItemIndexCombox->hide();
  ui->ItemIndexLabel->hide();
}

//下拉列表颜色选择框
void Dialog::initColorChooseComBox(QTableWidget *table, QLineEdit *lineEdit, QComboBox *comBox)
{
    //初始化背景颜色选择combox
    table->setMinimumWidth(comBox->width());
    //隐藏表头
    table->horizontalHeader()->setVisible(false);
    table->verticalHeader()->setVisible(false);
    table->setShowGrid(false);
    //合并最后两行
    table->setSpan(table->rowCount()-2,0,1,8);
    table->setSpan(table->rowCount()-1,0,1,8);

    int startRow = 0;

    if(table->property("tableName").toString() == "PieChartBorderColor" )
    {
       startRow = 1;
       table->setSpan(0,0,1,8);
       table->setRowHeight(0,30);
       QPushButton *nonColor = new QPushButton(QObject::tr("透 明"),this);
       nonColor->setStyleSheet("border:none;");         //设置鼠标按下时的样式
       nonColor->setProperty("colorName","BorderColorNone");
       nonColor->setProperty("tableName",table->property("tableName").toString());
       connect(nonColor,SIGNAL(clicked()),this,SLOT(doColorButtonClicked()));
       table->setCellWidget(0,0,nonColor);
    }

    int k =0 ;
    for(int i=startRow;i<table->rowCount();i++)
    {
        if(i<table->rowCount()-2)
        {
            table->setRowHeight(i,comBox->width()/8);
            for(int j=0;j<8;j++)
            {
                table->setColumnWidth(j,comBox->width()/8);
                QStringList colorList = QColor::colorNames();
                QPushButton *colorButton = new QPushButton("",this);
                colorButton->setAutoFillBackground(true);
                colorButton->setProperty("colorName",colorList[k]);
                QString styleSheet = "background-color:"+colorList[k]+";border:none;";
                colorButton->setStyleSheet(styleSheet);
                colorButton->setProperty("tableName",table->property("tableName").toString());
                table->setCellWidget(i,j,colorButton);
                k++;
                connect(colorButton,SIGNAL(clicked()),this,SLOT(doColorButtonClicked()));
            }
        }
        else if( i == table->rowCount()-2 )
        {
            table->setRowHeight(i,30);
            QLabel *textLable = new QLabel("最近使用的颜色",this);
            textLable->setStyleSheet("background-color: rgb(180, 180, 180);font: 75 10pt \"宋体\" ");
            textLable->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
            table->setCellWidget(i,0,textLable);
        }
        else if( i == table->rowCount()-1)
        {
            table->setRowHeight(i,30);
            QPushButton *moreColor = new QPushButton(QObject::tr("更多颜色...."),this);
            moreColor->setStyleSheet("");
            moreColor->setProperty("colorName","Other");
            moreColor->setProperty("tableName",table->property("tableName").toString());
            connect(moreColor,SIGNAL(clicked()),this,SLOT(doColorButtonClicked()));
            table->setCellWidget(i,0,moreColor);
        }
    }

    lineEdit->setReadOnly(true);
    comBox->setModel(table->model());
    comBox->setView(table);
    comBox->setLineEdit(lineEdit);
}

//数值元件界面
void Dialog::initValueItemPage()
{
    ui->ValueEnableConfirmSubWidget->hide();
    ui->ValueNoticeRadioWidgte->hide();
    ui->SaveAsOn->hide();
    ui->SaveAsOff->hide();
    ui->ValuePageEnableWidget->hide();
    ui->NumberItemWriteAddr->hide();
}

//字符元件界面
void Dialog::initCharaItemPage()
{
    ui->VerticalAlignmentLabel->hide();
    ui->VerticalAlignmentCombox->hide();
}

//圆饼图界面
void Dialog::initPieCharacterPage()
{
    ui->PartternPaintWidget->installEventFilter(this);

    PieChartBorderColor = new QTableWidget(9,8);        //边框颜色
    PieChartBorderColor->setProperty("tableName","PieChartBorderColor");
    PieChartBorderLineEdit = new QLineEdit(ui->PieChartBorderColor);
    (PieChartBorderColor,PieChartBorderLineEdit,ui->PieChartBorderColor);

    PieChartFontColor = new QTableWidget(8,8);          //字体颜色
    PieChartFontColor->setProperty("tableName","PieChartFontColor");
    PieChartFontLineEdit = new QLineEdit(ui->PieChartFontColor);
    initColorChooseComBox(PieChartFontColor,PieChartFontLineEdit,ui->PieChartFontColor);

    PieChartBackground = new QTableWidget(8,8);         //背景颜色
    PieChartBackground->setProperty("tableName","PieChartBackground");
    PieChartBackLineEdit = new QLineEdit(ui->PieChartBackgroundCombox);
    initColorChooseComBox(PieChartBackground,PieChartBackLineEdit,ui->PieChartBackgroundCombox);

    PieChartPattern = new QTableWidget(8,8);            //图案颜色
    PieChartPattern->setProperty("tableName","PieChartPattern");
    PieChartPatternLineEdit = new QLineEdit(ui->PieChartPaPatternCombox);
    initColorChooseComBox(PieChartPattern,PieChartPatternLineEdit,ui->PieChartPaPatternCombox);

    //初始化字体选择

    initFontControl(ui->PieChartFontComBox);
    ui->PieChartFontComBox->setCurrentIndex(0);

    //初始化尺寸下拉列表
    initNumberComBox(ui->FontSizeComBox,5,255);
    ui->FontSizeComBox->setCurrentText("20");

    initNumberComBox(ui->channelNumberCount,2,16);
    ui->channelNumberCount->setCurrentText("2");

    ui->ChannelChooseComBox->clear();
    initNumberComBox(ui->ChannelChooseComBox,1,ui->channelNumberCount->currentText().toInt());
    ui->ChannelChooseComBox->setCurrentText("1");

    PieChartPatternStyle = new QTableWidget(8,4);
    PieChartPatternStyle->horizontalHeader()->setVisible(false);
    PieChartPatternStyle->verticalHeader()->setVisible(false);
    connect(PieChartPatternStyle,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(doBrushTableItemClicked(QTableWidgetItem*)));
    connect(PieChartPatternStyle,SIGNAL(cellClicked(int,int)),this,SLOT(doBrushItemClicked(int,int)));
    //初始化画刷样式选择下拉列表
    initPartternStyleComBox();

    ui->PartternStyleCombox->setModel(PieChartPatternStyle->model());
    ui->PartternStyleCombox->setView(PieChartPatternStyle);

  //  ui->PartternPaintWidget->setWindowBrushStyle(TanslucentCrossPixpelPoint);             //暂时不指定样式
    ui->PartternPaintWidget->setDrawParttern(1);
}

void Dialog::initNumberComBox(QComboBox *comBox, int startValue, int endValue)
{
    comBox->clear();
    for(int i=startValue; i < endValue;i++)
    {
        comBox->addItem(QString::number(i));
    }
}

//初始化圆饼图界面图案样式下拉列表
void Dialog::initPartternStyleComBox()
{
    for(int i=0;i<PieChartPatternStyle->rowCount();++i)
        PieChartPatternStyle->removeRow(0);
    PieChartPatternStyle->setRowCount(8);
    PieChartPatternStyle->setColumnCount(4);
    PieChartPatternStyle->setMinimumSize(QSize(400,800));
    for(int i=0;i< 8;i++)
    {
        if(i<7)
        {
            for(int j=0;j<4;j++)
            {
                Widget *widget = new Widget();
                widget->setStyleSheet("border:none;");
                widget->setWidgetBrushColor(QColor(PieChartPatternColorName));
                widget->setWindowBrushStyle((CustomBrushStyle)(i*4+j));
                widget->setDrawParttern(-1);   //指定绘画的样式
                PieChartPatternStyle->setCellWidget(i,j,widget);
            }
        }
        else
        {
            Widget *widget = new Widget();
            widget->setStyleSheet("border:none;");
            widget->setWidgetBrushColor(QColor(PieChartPatternColorName));
            widget->setWindowBrushStyle((CustomBrushStyle)(28));
            widget->setDrawParttern(-1);   //指定绘画的样式
            PieChartPatternStyle->setCellWidget(7,0,widget);
        }
    }
}

void Dialog::initDynamicClibrationPage()
{
    ui->DynamicScalrRadiusSlider->installEventFilter(this);
    ui->DynamicCalibrationStyleCombox->setCurrentIndex(0);

    //初始化主副刻度尺寸选择下拉列表
    initNumberComBox(ui->MainScaleCombox,1,101);
    initNumberComBox(ui->viceScaleCombox,1,101);

    initNumberComBox(ui->ScaleChartSizeCombox,5,256);
    initFontControl(ui->ScaleChartFontCombox);

    //初始化刻度颜色选择下拉栏
    DynamicScaleColor = new QTableWidget(8,8);
    DynamicScaleColor->setProperty("tableName","DynamicScaleColor");
    DynamicScaleColorLineEdit = new QLineEdit;
    initColorChooseComBox(DynamicScaleColor,DynamicScaleColorLineEdit,ui->ScaleColorCombox);


    //初始化刻度符号界面的颜色选择下拉列表
    ScaleChartColor = new QTableWidget(8,8);
    ScaleChartColor->setProperty("tableName","ScaleChartColor");
    ScaleChartColorLineEdit = new QLineEdit;
    initColorChooseComBox(ScaleChartColor,ScaleChartColorLineEdit,ui->ScaleChartColorCombox);


    //隐藏刻度符号页面的属性设置
    ui->ScaleChartSubWidget->hide();
    ui->stackedWidget->setCurrentIndex(0);

    DynamicScaleTipWidget = new QWidget(this);
    DynamicScaleTipWidget->setWindowFlags(Qt::FramelessWindowHint);
    QHBoxLayout *layout = new QHBoxLayout;
    DynamicScaleTipLabel = new QLabel("20");
    DynamicScaleTipLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    layout->addWidget(DynamicScaleTipLabel);
    layout->setMargin(0);
    DynamicScaleTipWidget->setLayout(layout);
    DynamicScaleTipWidget->setFixedSize(QSize(35,20)); 
}

//初始化数据群组界面中的相关控件
void Dialog::initDataGroupPage()
{

    //初始化数据群组界面中的颜色选择下拉框
    DataGroupColor = new QTableWidget(8,8);
    DataGroupColor->setProperty("tableName","DataGroupColor");
    DataGroupColorLineEdit = new QLineEdit;
    initColorChooseComBox(DataGroupColor,DataGroupColorLineEdit,ui->DataGroupItemColorCombox);

    ui->DataGroupMinValue->setValidator(new QIntValidator(0,32767,this));
    ui->DataGroupMaxValue->setValidator(new QIntValidator(0,32767,this));
    ui->DataGroupMinValue->setText(QString::number(0));
    ui->DataGroupMaxValue->setText(QString::number(32767));

    ui->DataGroupUseShiftAddrCheckBox->setChecked(false);           //默认为不选中
    ui->DataGroupShiftAddrStackWidget->setCurrentIndex(0);

    ui->DataGroupTotalChannelCombox->setCurrentIndex(4);        //指定当前有多少通道总数
    ui->DataGroupWatchSubWidget->setHidden(true);

}

void Dialog::initXYCurveImagePage()
{
    ui->X_Group->hide();
    ui->Y_Group->hide();
    ui->DataLimitSourceFromRegister->setChecked(false);
}

void Dialog::initWatchNeedlePage()
{
    ui->ScaleScopeSubWidget->hide();
    ui->ScaleSubWidget->hide();
    ui->CustomDefineRValue->hide();
    ui->RegisterEquipmentInfoamtion->hide();

    establishConnectRelation(ui->showValueScopeScale,ui->ScaleScopeSubWidget);
    establishConnectRelation(ui->UserCustomDefineWdithCheckBox,ui->CustomDefineRValue);
    establishConnectRelation(ui->UseScaleSymbolCheckbox,ui->ScaleSubWidget);

    WatchNeedleColor = new QTableWidget(8,8);
    WatchNeedleColor->setProperty("tableName","BottomLimitColor");
    QString styleSheet = "background-color:blue;";
    WatchNeedleLineEdit = new QLineEdit();
    WatchNeedleLineEdit->setStyleSheet(styleSheet);
    initColorChooseComBox(WatchNeedleColor,WatchNeedleLineEdit,ui->BottomLimitColorCombox);

    NormalValueColor = new QTableWidget(8,8);
    NormalValueColor->setProperty("tableName","NormalValueColor");
    NormalValueLineEdit = new QLineEdit();
    styleSheet = "background-color:yellow;";
    NormalValueLineEdit->setStyleSheet(styleSheet);
    initColorChooseComBox(NormalValueColor,NormalValueLineEdit,ui->NormalValueColorCombox);

    TopLimitValueColor = new QTableWidget(8,8);
    TopLimitValueColor->setProperty("tableName","TopLimitValueColor");
    TopLimitValueLineEdit = new QLineEdit();
    styleSheet = "background-color:red;";
    TopLimitValueLineEdit->setStyleSheet(styleSheet);
    initColorChooseComBox(TopLimitValueColor,TopLimitValueLineEdit,ui->TopLimitColorCombox);

    //字体选择
    initFontControl(ui->WatchNeedlFontCombox);

    //字体颜色
    WatchNeedleFontColor = new QTableWidget(8,8);
    WatchNeedleFontColor->setProperty("tableName","WatchNeedleFontColor");
    WatchNeedleFontLineEdit = new QLineEdit();
    initColorChooseComBox(WatchNeedleFontColor,WatchNeedleFontLineEdit,ui->WatchNedlFontColor);

    //字体大小
    initNumberComBox(ui->WatchNeedleFontSizeCombox,5,256);



}

void Dialog::initMoveGraphicalPage()
{
    ui->MoveGraphLimitValueWidget->hide();
    ui->MoveGraphPropertyCoordinate->hide();

    for(int i=1;i<257;i++)
    {
        ui->StatusNumbeCombox->addItem(QString::number(i));
    }


    ui->XCoordinateTopLimit->setText("1023");
    ui->XCoordinateTopLimit->setValidator(new QIntValidator(0,1023));
    ui->XCoordinateBottomLimit->setText("0");
}

void Dialog::initIndirectWindowPage()
{
    ui->ShiftValueCombox->hide();
    ui->ShiftValueLabel->hide();

    for(int i= -1024;i<=1024;i++)
        ui->ShiftValueCombox->addItem(QString::number(i));
}

void Dialog::initDirectWidgetPage()
{
    ui->PropertyPosWidget->hide();
    establishConnectRelation(ui->AutoAdjustWindowSizeCheckBox,ui->PropertyPosWidget);

}

void Dialog::initDataTranportPage()
{
    ui->ConfigureSwitchSubWidget->hide();
    ui->DataTransportAddrSubWidget->hide();
    establishConnectRelation(ui->DataTransportEnableCheckBox,ui->ConfigureSwitchSubWidget);
    establishConnectRelation(ui->DataTransportEnableCheckBox,ui->DataTransportAddrSubWidget);
}

void Dialog::initDataTransBackground()
{
    ui->TimeIinterval->clear();

    ui->ConfigureSwitchSubWidget_2->hide();
    ui->DataTransportAddrSubWidget_2->hide();
    ui->SpecialExecCodeCombox->hide();

    establishConnectRelation(ui->DataTransportEnableCheckBox_2,ui->ConfigureSwitchSubWidget_2);
    establishConnectRelation(ui->DataTransportEnableCheckBox_2,ui->DataTransportAddrSubWidget_2);
    establishConnectRelation(ui->ExecCodeWhenOpenSpecialWin,ui->SpecialExecCodeCombox);


    QString timeText = "";

    for(int i=0;i<=25;i++)
    {
        for(int j=0;j<=9;j++)
        {
            if( i <= 0 )
            {
                if(j >1)
                    timeText = QString::number(i)+"."+QString::number(j)+"秒";
            }
            else if( i >= 25  )
            {
                if(j<6)
                    timeText = QString::number(i)+"."+QString::number(j)+"秒";
            }
            else
            {
                timeText = QString::number(i)+"."+QString::number(j)+"秒";
            }
            if(timeText!="")
                ui->TimeIinterval->addItem(timeText);
            ui->TimeIinterval->setCurrentIndex(28);
        }
    }
}

void Dialog::initImageCheckPage()
{

    ui->DirDevAddrCombox->addItems(LWlist);

    ui->DirDynamicPathWidget->hide();
    establishConnectRelation(ui->DynamicFilePathCheckBox,ui->DirDynamicPathWidget);
    establishConnectRelation(ui->DynamicFilePathCheckBox,ui->LocalFirPathCombox,1);

    ui->SendNewsWhenSwitchImage->hide();
    establishConnectRelation(ui->AutoShowNewImage,ui->SendNewsWhenSwitchImage);
    ui->ConfirmSwitchWidget->hide();
    establishConnectRelation(ui->SendNewsWhenSwitchImage,ui->ConfirmSwitchWidget);

    ui->ConfirmAddrWidget->hide();

    ui->ChooseCheckFileAddrWidget->hide();
    establishConnectRelation(ui->CheckFileByUseAddr,ui->ChooseCheckFileAddrWidget);

    ui->ConfigureButton->hide();
    ui->BitStautLabel->hide();

    ui->DirDevAddrCombox->addItems(LWlist);
    establishConnectRelation(ui->SendNewsWhenSwitchImage,ui->ConfigureButton);

}

void Dialog::initVNCViewerPage()
{

    //设置IP输入的条件限制 0~255

    ui->IPFirstNumber->setValidator(new QIntValidator(0,255));
    ui->IPSecondNumber->setValidator(new QIntValidator(0,255));
    ui->IPThirdNumber->setValidator(new QIntValidator(0,255));
    ui->IPFourthNumber->setValidator(new QIntValidator(0,255));


    ui->EnableOnelineEditFunction->setEnabled(false);
    ui->EnabelUseTextBaBaseCheckbox->setEnabled(false);

    ui->PasswordInputWidget->hide();
    establishConnectRelation(ui->DefaultPasswordCheckBox,ui->PasswordInputWidget);

    ui->TextBaseWidget->hide();
    establishConnectRelation(ui->EnableTextBaseCheckBox,ui->TextBaseWidget);

}

void Dialog::initQRCodePage()
{
    ui->QRCodeShiftAddrBit->show();

    ui->QRCodeCorrectStandard->clear();
    ui->QRCodeModeCombox->setCurrentIndex(0);
    QStringList correctStand;
    correctStand<<"L(7%)"<<"M(15%)"<<"Q(25%)"<<"H(30%)-预设";
    ui->QRCodeCorrectStandard->clear();
    ui->QRCodeCorrectStandard->addItems(correctStand);
    ui->QRCodeCorrectStandard->setCurrentIndex(3);

    ui->QRCodeAddress->clear();
    ui->QRCodeAddress->addItems(LWlist);

    QString styleSheet = "background-color:black;";
    QRCodeColorLineEdit->setStyleSheet(styleSheet);

    ui->QRCodeAddLength->setText(QString::number(16));
}

void Dialog::initWeChatQRCodePage()
{

    ui->QRCodeShiftAddrBit->hide();
    ui->QRCodeModeCombox->setCurrentIndex(0);
    QStringList correctStand;
    correctStand<<"L(7%)"<<"M(15%)"<<"Q(25%)"<<"H(30%)-预设";
    ui->QRCodeCorrectStandard->clear();
    ui->QRCodeCorrectStandard->addItems(correctStand);
    ui->QRCodeCorrectStandard->setCurrentIndex(3);

    ui->QRCodeAddress->clear();
    ui->QRCodeAddress->addItem("LW-11770(64 words):微信推送通知的二维码(URL)(EasyAccess 2.0)");
    ui->QRCodeAddress->setCurrentIndex(0);

    ui->QRCodeAddLength->setText(QString::number(64));
}

void Dialog::initDateAndTimePage()
{

    initNumberComBox(ui->DateTimeFontSize,5,256);
    ui->DateTimeFontSize->setCurrentIndex(10);

    initFontControl(ui->DateTimeFontName);
    ui->DateTimeFontName->setCurrentIndex(6);

    DateTimeFontColorTable = new QTableWidget(8,8);
    DateTimeFontColorTable->setProperty("tableName","DateTimeFontColor");
    DateTimeFontColorLineEdit = new QLineEdit();
    initColorChooseComBox(DateTimeFontColorTable,DateTimeFontColorLineEdit,ui->DateTimeFontColor);

    DateTimeFontColorLineEdit->setStyleSheet("background-color:black;");

    ui->DateFormatCombox->hide();
    ui->DateFormateLabel->hide();
    establishConnectRelation(ui->EnabelDateFormatCheckBox,ui->DateFormateLabel);
    establishConnectRelation(ui->EnabelDateFormatCheckBox,ui->DateFormatCombox);

    ui->WeekFormatCombox->hide();
    ui->WeekFormatLabel->hide();
    establishConnectRelation(ui->EnabelWeekFormatCheckBox,ui->WeekFormatCombox);
    establishConnectRelation(ui->EnabelWeekFormatCheckBox,ui->WeekFormatLabel);

    ui->TimeFormatWidget->hide();
    establishConnectRelation(ui->EnabelTimeFormatCheckBox,ui->TimeFormatWidget);

    ui->Hourse12Widget->hide();
    establishConnectRelation(ui->Enable12HoursCheckBox,ui->Hourse12Widget);

    ui->DateTimeFontAlignment->setCurrentIndex(1);
}

void Dialog::initTimerControlPage()
{

    ui->ResetGroupBox->hide();
    ui->CountTimeAddrWidget->hide();
    establishConnectRelation(ui->RecordedCheckBox,ui->CountTimeAddrWidget);

    ui->InputBitAddrCombox->clear();
    ui->InputBitAddrCombox->addItems(LBlist);
    ui->InputBitAddrCombox->setCurrentIndex(0);

    ui->ExportBitCombox->clear();
    ui->ExportBitCombox->addItems(LBlist);
    ui->ExportBitCombox->setCurrentIndex(0);

    ui->TimerBItCombox->clear();
    ui->TimerBItCombox->addItems(LBlist);
    ui->TimerBItCombox->setCurrentIndex(0);

    ui->PresetTimerCombox->clear();
    ui->PresetTimerCombox->addItems(LWlist);
    ui->PresetTimerCombox->setCurrentIndex(0);

    ui->ResetBitCombox->clear();
    ui->ResetBitCombox->addItems(LBlist);
    ui->ResetBitCombox->setCurrentIndex(0);

    ui->RecordBitCombox->clear();
    ui->RecordBitCombox->addItems(LWlist);
    ui->RecordBitCombox->setCurrentIndex(0);

}

void Dialog::initSchedulePage()
{
    ui->TextWriteConfigure->hide();

    ui->ScheduleTargetAddrCombox->clear();
    ui->ScheduleTargetAddrCombox->addItems(LBlist);
    ui->ScheduleTargetAddrCombox->setCurrentIndex(0);

    ui->TextWriteAddrCombox->clear();
    ui->TextWriteAddrCombox->addItems(LWlist);
    ui->TextWriteAddrCombox->setCurrentIndex(0);


    ui->BitSaveAsOn->setChecked(true);
    ui->ConstNumberRadio->setChecked(true);
    ui->WriteValueStackWidget->setCurrentIndex(0);
}

void Dialog::initSystemParameterPage()
{

    //初始化设备界面
    ui->addNewHMIDevice->hide();            //暂时隐藏 新增HMI按钮
    ui->SystemParameterDevTable->setColumnCount(7);
    ui->SystemParameterDevTable->verticalHeader()->setVisible(false);
    QStringList header;
    header<<" "<<"名称"<<"位置"<<"设备类型"<<"界面"<<"通讯协议"<<"站号";
    ui->SystemParameterDevTable->setHorizontalHeaderLabels(header);
    ui->SystemParameterDevTable->horizontalHeader()->setStretchLastSection(true);
    ui->SystemParameterDevTable->setRowCount(1);
    ui->SystemParameterDevTable->setItem(0,0,new QTableWidgetItem("本机,触摸屏"));
    ui->SystemParameterDevTable->item(0,0)->setTextAlignment(Qt::AlignCenter |Qt::AlignHCenter);
    ui->SystemParameterDevTable->setItem(0,1,new QTableWidgetItem("Local HMI"));
    ui->SystemParameterDevTable->item(0,1)->setTextAlignment(Qt::AlignCenter |Qt::AlignHCenter);
    ui->SystemParameterDevTable->setItem(0,2,new QTableWidgetItem("本机"));
    ui->SystemParameterDevTable->item(0,2)->setTextAlignment(Qt::AlignCenter |Qt::AlignHCenter);
    ui->SystemParameterDevTable->setItem(0,3,new QTableWidgetItem("cMT3103(1024x600)"));
    ui->SystemParameterDevTable->item(0,3)->setTextAlignment(Qt::AlignCenter |Qt::AlignHCenter);
    ui->SystemParameterDevTable->setItem(0,4,new QTableWidgetItem("-"));
    ui->SystemParameterDevTable->item(0,4)->setTextAlignment(Qt::AlignCenter |Qt::AlignHCenter);
    ui->SystemParameterDevTable->setItem(0,5,new QTableWidgetItem("-"));
    ui->SystemParameterDevTable->item(0,5)->setTextAlignment(Qt::AlignCenter |Qt::AlignHCenter);
    ui->SystemParameterDevTable->setItem(0,6,new QTableWidgetItem("0"));
    ui->SystemParameterDevTable->item(0,6)->setTextAlignment(Qt::AlignCenter |Qt::AlignHCenter);
    connect(ui->SystemParameterDevTable,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(doDevTableClicked(QTableWidgetItem*)));

    DevProperty dev;
    dev.setDevFull("本机,触摸屏");
    dev.setDevName("Local HMI");
    dev.setDevLoca("本机");
    dev.setDevType("cMT3103(1024x600)");
    dev.setDevScre("-");
    dev.setDevProt("-");
    dev.setDevStID("0");
    devData.insert(0,dev);

    if(ui->SystemParameterDevTable->rowCount() < 1)
        ui->DeleteDevTableItem->setEnabled(false);
    else
        ui->DeleteDevTableItem->setEnabled(true);
    initNumberComBox(ui->HMIStaionIDCombox,0,256);

    //初始化HMI属性页
    ui->CMTProtocalPort->hide();
    ui->CMTProtocalPortlabel->hide();
    establishConnectRelation(ui->SupportCMTProtocal,ui->CMTProtocalPort);
    establishConnectRelation(ui->SupportCMTProtocal,ui->CMTProtocalPortlabel);

    ui->ClockFromCombox->setCurrentIndex(1);
    ui->ClockSubWidget->show();
    ui->ClockDeviceAddr->clear();
    ui->ClockDeviceAddr->addItems(LWlist);

    ui->ClockType->setCurrentIndex(0);
    ui->HMIPopertySubStackWidget->hide();
    ui->OnlySupportUSBLabel->setHidden(true);
    ui->ClockWidth->setHidden(true);
    ui->WidthLabel->setHidden(true);
    ui->PixelLabel->setHidden(true);
    ui->PixelTipsLabel->setHidden(true);
    ui->ScreenCaptureRatio->setHidden(true);
    ui->ScreenCaptureLabel->setHidden(true);
    ui->RowSpacingAfterSwitch->setHidden(true);
    ui->RowSapceingNumber->setHidden(true);
    ui->MeetType->setHidden(true);


    //初始化一般属性
    ui->TimeTagFormatWidget->hide();
    establishConnectRelation(ui->UseLWAsTimeTag,ui->TimeTagFormatWidget);

    initNumberComBox(ui->BackgroundLightSavePower,0,255);
    ui->BackgroundLightSavePower->insertItem(0,"无");
    ui->BackgroundLightSavePower->setCurrentIndex(27);
    initNumberComBox(ui->ScreenPeotectedTime,0,255);
    ui->ScreenPeotectedTime->insertItem(0,"无");
    ui->ScreenPeotectedTime->setCurrentIndex(27);

    ui->ProjectFileSubWidget->hide();
    ui->ProjectFileTipsWidget->hide();
    establishConnectRelation(ui->EnabelProjectFileProtect,ui->ProjectFileSubWidget);
    establishConnectRelation(ui->EnabelProjectFileProtect,ui->ProjectFileTipsWidget);


    ui->InitWindwoType->addItems(windowTypeList);
    ui->InitWindwoType->setCurrentIndex(0);
    ui->ScreenProtectWinType->addItems(windowTypeList);
    ui->ScreenProtectWinType->setCurrentIndex(0);

    ui->ProjectFileIdentityCode->setValidator(new QIntValidator(0,4294901750));
    CursorColorLineEdit->setStyleSheet("background-color:pink;");
    CursorChooseColorLineEdit->setStyleSheet("background-color:green;");


    //初始化系统设置界面
    ui->AutoLogOffTimeLabel->hide();
    ui->AutoLogOffTimeCombox->hide();
    establishConnectRelation(ui->EnabelAutoLogOff,ui->AutoLogOffTimeCombox);
    establishConnectRelation(ui->EnabelAutoLogOff,ui->AutoLogOffTimeLabel);

    ui->EnableWatchDogWidget->hide();
    establishConnectRelation(ui->EnableWatchDog,ui->EnableWatchDogWidget);

    initNumberComBox(ui->CommunWithDevDelayTime,0,601);
    ui->CommunWithDevDelayTime->setCurrentIndex(1);
    initNumberComBox(ui->AutoLogOffTimeCombox,0,257);
    ui->AutoLogOffTimeCombox->setCurrentIndex(1);

    QStringList mouseList;
    mouseList<<"预设"<<"20x20(黑)"<<"30x30(黑)"<<"40x40(黑)"<<"50x50(黑)"<<"20x20(白)"<<"30x30(白)"<<"40x40(白)"<<"50x50(白)";
    ui->MouseLightSize->clear();
    ui->MouseLightSize->addItems(mouseList);
    ui->MouseLightSize->setCurrentIndex(0);

    //初始化远端界面
    ui->VNCServerPasswordWidget->hide();
    establishConnectRelation(ui->ConfigurePasswordFromProFile,ui->VNCServerPasswordWidget);
    ui->ServerUrlLineEdit->hide();
    establishConnectRelation(ui->LoginEasyAccessServer,ui->ServerUrlLineEdit);

    //初始化密码保护界面
    ui->EnableLoginAfterSecurityKey->setChecked(true);
    establishConnectRelation(ui->EnableLoginAfterSecurityKey,ui->ExecLoginLogOut);

    ui->InputPasswordWidget->hide();
    establishConnectRelation(ui->EnableProjectFilePassword,ui->InputPasswordWidget);

    initSystemPataTable();
    ui->PasswordScopeTips->hide();

    //初始化打印/备份服务器
    ui->EnablePrintAndBackupsServer->setChecked(false);
    ui->PrintAndBackupsServerWidget->hide();
    establishConnectRelation(ui->EnablePrintAndBackupsServer,ui->PrintAndBackupsServerWidget);

    //初始化时间同步/夏令时界面
    ui->AutoSynTime->setChecked(true);
    establishConnectRelation(ui->AutoSynTime,ui->SynchroizonationTimeWidget);

    ui->AutoConfigSummerTime->setChecked(true);
    establishConnectRelation(ui->AutoConfigSummerTime,ui->DaylightTimeWidget);

    QStringList monthStr{"一月","二月","三月","四月","五月","六月","七月","八月","九月","十一月","十二月"};
    QStringList weekStr{"星期一","星期二","星期三","星期四","星期五","星期六","星期日"};
    QStringList weekNumStr{"第一个","第二个","第三个","第四个","最后一个"};

    ui->StartMonthCombox->clear();
    ui->StartMonthCombox->addItems(monthStr);
    ui->StartMonthCombox->setCurrentIndex(0);

    ui->EndMonthCombox->clear();
    ui->EndMonthCombox->addItems(monthStr);
    ui->EndMonthCombox->setCurrentIndex(3);

    ui->StartWeekOrderCombox->clear();
    ui->StartWeekOrderCombox->addItems(weekNumStr);
    ui->StartWeekOrderCombox->setCurrentIndex(0);

    ui->EndWeekOrderCombox->clear();
    ui->EndWeekOrderCombox->addItems(weekNumStr);
    ui->EndWeekOrderCombox->setCurrentIndex(2);

    ui->StartWeekCombox->clear();
    ui->StartWeekCombox->addItems(weekStr);
    ui->StartWeekCombox->setCurrentIndex(0);

    ui->EndWeekCombox->clear();
    ui->EndWeekCombox->addItems(weekStr);
    ui->EndWeekCombox->setCurrentIndex(1);

    //初始化邮件界面
    ui->ErrorSubWidget->hide();
    establishConnectRelation(ui->EnableErrorMsgWidget,ui->ErrorSubWidget);

    ui->EnableEmailFunCheckbox->setChecked(false);
    ui->EmailSubWidget->hide();
    establishConnectRelation(ui->EnableEmailFunCheckbox,ui->EmailSubWidget);

    //初始化配方数据库界面
    connect(ui->FormulaListWidget,&QListWidget::currentRowChanged,this,&Dialog::doListItemClicked);
}

void Dialog::initSystemUI()
{
    QString style = "";

    //位状态中相关颜色控件设置
    BitStatusImageColor = new QTableWidget(8,8);               //位状态图片颜色
    BitStatusImageColor->setProperty("tableName","BitStatusImageColor");
    BitStatusImageColorLineEdit = new QLineEdit();
    initColorChooseComBox(BitStatusImageColor,BitStatusImageColorLineEdit,ui->ImageColorCombox);
    style = "background-color:rgb(128,255,255)";
    BitStatusImageColorLineEdit->setStyleSheet(style);


    BitStatusInnerColor = new QTableWidget(8,8);
    BitStatusInnerColor->setProperty("tableName","BitStatusInnerColor");
    BitStatusInnerColorLineEdit = new QLineEdit();
    initColorChooseComBox(BitStatusInnerColor,BitStatusInnerColorLineEdit,ui->InnerColorCombox);

    BitStatusOutSideColor = new QTableWidget(8,8);
    BitStatusOutSideColor->setProperty("tableName","BitStatusOutSideColor");
    BitStatusOutSideColorLineEdit = new QLineEdit();
    initColorChooseComBox(BitStatusOutSideColor,BitStatusOutSideColorLineEdit,ui->OutsideColorCombox);

    BitStatusPartternColor = new QTableWidget(8,8);
    BitStatusPartternColor->setProperty("tableName","BitStatusPartternColor");
    BitStatusPartternColorLineEdit = new QLineEdit();
    initColorChooseComBox(BitStatusPartternColor,BitStatusPartternColorLineEdit,ui->PartternColorCombox);

    //标签属性
    BitStatusTagColor = new QTableWidget(8,8);
    BitStatusTagColor->setProperty("tableName","BitStatusTagColor");
    BitStatusTagColorLineEdit = new QLineEdit();
    initColorChooseComBox(BitStatusTagColor,BitStatusTagColorLineEdit,ui->BitStatusTagColorCombox);
    style = "background-color:black;";
    BitStatusTagColorLineEdit->setStyleSheet(style);


    //初始化二维码和微信二维码界面的颜色选择下拉列表
    QRCodeColorTable = new QTableWidget(8,8);
    QRCodeColorTable->setProperty("tableName","QRCodeColorTable");
    QRCodeColorLineEdit = new QLineEdit();
    initColorChooseComBox(QRCodeColorTable,QRCodeColorLineEdit,ui->QRCodeColor);

    //初始化滑动条中的相关控件颜色
    SliderBorderTable = new QTableWidget(8,8);
    SliderBorderTable->setProperty("tableName","SliderBorderColor");              //滑动开关边框颜色
    SliderBorderLineEdit = new QLineEdit();
    initColorChooseComBox(SliderBorderTable,SliderBorderLineEdit,ui->SliderBorderCombox);

    SliderBackgroundTable  = new QTableWidget(8,8);
    SliderBackgroundTable->setProperty("tableName","SliderBackgroundColor");              //滑动开关背景颜色
    SliderBackgroundLineEdit = new QLineEdit();
    initColorChooseComBox(SliderBackgroundTable,SliderBackgroundLineEdit,ui->SliderBackgroundColor);


    SliderRailTable  = new QTableWidget(8,8);
    SliderRailTable->setProperty("tableName","SliderRailColor");              //滑动开关滑轨颜色
    SliderRailLineEdit = new QLineEdit();
    initColorChooseComBox(SliderRailTable,SliderRailLineEdit,ui->SliderRailColor);


    SliderControlColor = new QTableWidget(8,8);
    SliderControlColor->setProperty("tableName","SliderControlColor");          //滑动块的总体颜色
    SliderControlLineEdit = new QLineEdit();
    initColorChooseComBox(SliderControlColor,SliderControlLineEdit,ui->SliderControlColor);


    CursorColorTable = new QTableWidget(8,8);
    CursorColorTable->setProperty("tableName","CursorColor");
    CursorColorLineEdit = new QLineEdit();
    initColorChooseComBox(CursorColorTable,CursorColorLineEdit,ui->CursorColor);

    CursorChooseColorTable = new QTableWidget(8,8);
    CursorChooseColorTable->setProperty("tableName","CursorChooseColor");
    CursorChooseColorLineEdit = new QLineEdit();
    initColorChooseComBox(CursorChooseColorTable,CursorChooseColorLineEdit,ui->CursorChooseColor);

}

void Dialog::establishConnectRelation(QCheckBox *checkbox, QWidget *widget, int bit)
{
    if(bit != 1)
    {
        int state = 0;
        connect(checkbox,&QCheckBox::stateChanged,[state,widget](const int value)mutable{
            state = value;
            if(state == 2)
                widget->show();
            else if(state == 0)
                widget->hide();
        });
    }
    else
    {
        int state = 0;
        connect(checkbox,&QCheckBox::stateChanged,[state,widget](const int value)mutable{
            state = value;
            if(state == 0)
                widget->show();
            else if(state == 2)
                widget->hide();
        });
    }
}

void Dialog::doDealMenuAction()
{
    QAction *senderAction = qobject_cast<QAction*>(sender());
    if(senderAction->property("actionName").toString() == "delayWidget")
    {
        qDebug()<<"延时按钮被按下";
    }
    else if(senderAction->property("actionName").toString() == "BitStatusWidget")
    {
        qDebug()<<"位状态被按下";
    }
    else if(senderAction->property("actionName").toString() == "multipleStatusWidget")
    {
        qDebug()<<"多状态按钮被按下";
    }
    else if(senderAction->property("actionName").toString() == "switchBaseWidget")
    {
        qDebug()<<"切换基本窗口按钮被按下";
    }
    else if(senderAction->property("actionName").toString() == "triggerMacroInstruction")
    {
        qDebug()<<"触发宏指令按钮被按下";
    }
}

//颜色被选中
void Dialog::doColorButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString tableName = button->property("tableName").toString();
    QString colorName = button->property("colorName").toString();

    if(colorName == "Other")
    {
        QColor color = QColorDialog::getColor(Qt::black);
        colorName = color.name();
        QString styleSheet = "background-color:"+colorName+";";
        if(tableName == "backGroundTable")
        {
          backgroundColor = colorName;
          colorChooseLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "chooseTable")
        {
          chooseColor = colorName;
          ChooseLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "PieChartBorderColor")         //边框颜色
        {
          PieChartBorderColorName = colorName;
          PieChartBorderLineEdit->setStyleSheet(styleSheet);
          ui->PartternPaintWidget->setWidgetPartternBorderColor(colorName);
        }
        else if(tableName == "PieChartFontColor")           //字体颜色
        {
          PieChartFontColorName = colorName;
          PieChartFontLineEdit->setStyleSheet(styleSheet);
          ui->PartternPaintWidget->setWidgetRingTextColor(colorName);
        }
        else if(tableName == "PieChartBackground")          //背景色
        {
          PieChartBackgroundName = colorName;
          PieChartBackLineEdit->setStyleSheet(styleSheet);
          ui->PartternPaintWidget->setWidgetbackgroundColor(QColor(colorName));
        }
        else if(tableName == "PieChartPattern")             //图案颜色
        {
          PieChartPatternColorName = colorName;
          PieChartPatternLineEdit->setStyleSheet(styleSheet);
          ui->PartternPaintWidget->setWidgetBrushColor(QColor(colorName));
          ui->PartternPaintWidget->setWidgetRingColor(ui->ChannelChooseComBox->currentText().toInt(),PieChartPatternColorName);
          initPartternStyleComBox();
        }
        else if(tableName == "DynamicScaleColor")
        {
            DynamicScaleColorStr = colorName;
            DynamicScaleColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "ScaleChartColor")
        {
            ScaleChartColorStr = colorName;
            ScaleChartColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "DataGroupColor")
        {
            DataGroupColorStr = colorName;
            DataGroupColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "BottomLimitColor")
        {
            WatchNeedleColorStr = colorName;
            WatchNeedleLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "NormalValueColor")
        {
            NormaleValueColorStr = colorName;
            NormalValueLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "TopLimitValueColor")
        {
            TopLimitValueColorStr = colorName;
            TopLimitValueLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "WatchNeedleFontColor")
        {
            WatchNeedlFontColorStr = colorName;
            WatchNeedleFontLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "QRCodeColorTable")
        {
            if(ui->QRCodeAddress->currentText().size() > 10)
                WeChatQRCodeColorStr = colorName;
            else
                QRCodeColorStr = colorName;
            QRCodeColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "DateTimeFontColor")
        {
            DateTimeFontColorStr = colorName;
            DateTimeFontColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "BitStatusImageColor")
        {
            PhotoColorStr = colorName;
            BitStatusImageColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "BitStatusInnerColor")
        {
            innerColorStr = colorName;
            BitStatusInnerColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "BitStatusOutSideColor")
        {
            outsideColorStr = colorName;
            BitStatusOutSideColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "BitStatusPartternColor")
        {
            partternColorStr = colorName;
            BitStatusPartternColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "BitStatusTagColor")
        {
            BitStatusTagColorStr = colorName;
            BitStatusTagColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "SliderRailColor")
        {
            sliderRailColorStr = colorName;
            SliderRailLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "SliderBorderColor")
        {
            sliderBorderColorStr = colorName;
            SliderBorderLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "SliderBackgroundColor")
        {
            sliderBackColorStr = colorName;
            SliderBackgroundLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "SliderControlColor")
        {
            sliderControlStr = colorName;
            SliderControlLineEdit->setStyleSheet(styleSheet);
            sliderButton1->setPainterColor(QColor(colorName));
            sliderButton2->setPainterColor(QColor(colorName));
            sliderButton3->setPainterColor(QColor(colorName));
            sliderButton4->setPainterColor(QColor(colorName));
        }
        else if(tableName == "CursorColor")
        {
            CurSorColorStr = colorName;
            CursorColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "CursorChooseColor")
        {
            CursorChooseColorStr = colorName;
            CursorChooseColorLineEdit->setStyleSheet(styleSheet);
        }
    }
    else if(colorName == "BorderColorNone")     //边框颜色设置为透明
    {
      //  qDebug()<<"边框颜色设置为透明........";
        PieChartBorderColorName = "None";
        PieChartBorderLineEdit->setStyleSheet("background-color:white;");
        ui->PartternPaintWidget->setWidgetPartternBorderColor("white");
    }
    else
    {
        QString styleSheet = "background-color:"+colorName+";";
        if(tableName == "backGroundTable")
        {
          backgroundColor = colorName;
          colorChooseLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "chooseTable")
        {
          chooseColor = colorName;
          ChooseLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "PieChartBorderColor")
        {
         // qDebug()<<"边框颜色发生变动........";
          PieChartBorderColorName = colorName;
          PieChartBorderLineEdit->setStyleSheet(styleSheet);
          ui->PartternPaintWidget->setWidgetPartternBorderColor(colorName);
        }
        else if(tableName == "PieChartFontColor")
        {
          // qDebug()<<"字体颜色发生变动........";
          PieChartFontColorName = colorName;
          PieChartFontLineEdit->setStyleSheet(styleSheet);
          ui->PartternPaintWidget->setWidgetRingTextColor(colorName);
        }
        else if(tableName == "PieChartBackground")
        {
         // qDebug()<<"扇形背景颜色发生变动........";
          PieChartBackgroundName = colorName;
          PieChartBackLineEdit->setStyleSheet(styleSheet);
          ui->PartternPaintWidget->setWidgetbackgroundColor(QColor(colorName));
        }
        else if(tableName == "PieChartPattern")         //图形样式颜色
        {
        //  qDebug()<<"指定通道背景颜色发生变动........";
          PieChartPatternColorName = colorName;
          PieChartPatternLineEdit->setStyleSheet(styleSheet);
          ui->PartternPaintWidget->setWidgetBrushColor(QColor(colorName));
          ui->PartternPaintWidget->setWidgetRingColor(ui->ChannelChooseComBox->currentText().toInt(),PieChartPatternColorName);
          initPartternStyleComBox();
        }
        else if(tableName == "DynamicScaleColor")
        {
            DynamicScaleColorStr = colorName;
            DynamicScaleColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "ScaleChartColor")
        {
            ScaleChartColorStr = colorName;
            ScaleChartColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "DataGroupColor")
        {
            DataGroupColorStr = colorName;
            DataGroupColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "BottomLimitColor")
        {
            WatchNeedleColorStr = colorName;
            WatchNeedleLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "NormalValueColor")
        {
            NormaleValueColorStr = colorName;
            NormalValueLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "TopLimitValueColor")
        {
            TopLimitValueColorStr = colorName;
            TopLimitValueLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "WatchNeedleFontColor")
        {
            WatchNeedlFontColorStr = colorName;
            WatchNeedleFontLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "QRCodeColorTable")
        {
            if(ui->QRCodeAddress->currentText().size() > 10)
                WeChatQRCodeColorStr = colorName;
            else
                QRCodeColorStr = colorName;
            QRCodeColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "DateTimeFontColor")
        {
            DateTimeFontColorStr = colorName;
            DateTimeFontColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName ==  "BitStatusImageColor")
        {
            PhotoColorStr = colorName;
            BitStatusImageColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName ==  "BitStatusInnerColor")
        {
            innerColorStr = colorName;
            BitStatusInnerColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName ==  "BitStatusOutSideColor")
        {
            outsideColorStr = colorName;
            BitStatusOutSideColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName ==  "BitStatusPartternColor")
        {
            partternColorStr = colorName;
            BitStatusPartternColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "BitStatusTagColor")
        {
            BitStatusTagColorStr = colorName;
            BitStatusTagColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "SliderRailColor")
        {
            sliderRailColorStr = colorName;
            SliderRailLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "SliderBorderColor")
        {
            sliderBorderColorStr = colorName;
            SliderBorderLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "SliderBackgroundColor")
        {
            sliderBackColorStr = colorName;
            SliderBackgroundLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "SliderControlColor")
        {
            sliderControlStr = colorName;
            SliderControlLineEdit->setStyleSheet(styleSheet);
            sliderButton1->setPainterColor(QColor(colorName));
            sliderButton2->setPainterColor(QColor(colorName));
            sliderButton3->setPainterColor(QColor(colorName));
            sliderButton4->setPainterColor(QColor(colorName));

            qDebug()<<"重新设置滑动条整体颜色";
        }
        else if(tableName == "CursorColor")
        {
            CurSorColorStr = colorName;
            CursorColorLineEdit->setStyleSheet(styleSheet);
        }
        else if(tableName == "CursorChooseColor")
        {
            CursorChooseColorStr = colorName;
            CursorChooseColorLineEdit->setStyleSheet(styleSheet);
        }
    }
    update();       //立即刷新
}

void Dialog::doBrushStyleSelect()
{
    qDebug()<<"画刷类型按钮被点击";
}

void Dialog::doBrushTableItemClicked(QTableWidgetItem *item)
{
    int column = item->column();
    int row = item->row();
    qDebug()<<"鼠标点击的Item位于第 "<<row<<"  行，第 "<<column<<" 列";
}

void Dialog::doBrushItemClicked(int   row, int   column)
{
    qDebug()<<"鼠标点击的Item位于第 "<<row<<"  行，第 "<<column<<" 列";
}

void Dialog::doAddbuttonClicked()
{
    subDlg->setWidgetCaller("PLCControl");
    subDlg->showSubDialog(PLCControlSubWidget);
    if(subDlg->exec() == QDialog::Rejected)
        return;
    QString windowType = "";
    int isExecCom = 0;
    int commandID = 0;
    int useBackLight =0;
    int addClear = 0;
    int useWindIDShift = 0;
    int windowIDShift =0 ;
    QString devType = "";
    QString AddrType = "";
    int addrNumber = -1;
    subDlg->getPLCChooseResult(windowType,isExecCom,commandID,useBackLight,addClear,useWindIDShift,windowIDShift,devType,AddrType,addrNumber);

    QString newItemText = "["+ devType+":"+AddrType+"-"+QString::number(addrNumber)+"] => "+windowType;

    bool isLeft = false;
    QString openLightStr = "";
    if(useBackLight == 2)
    {
        openLightStr = "换页后打开背光灯 ,";
        newItemText +="("+openLightStr;
        isLeft = true;
    }
    else
        openLightStr = "";

    QString addrValueClearStr = "";
    if(addClear == 2)
    {
        addrValueClearStr = "换页后地址数值清零 ";
        if(isLeft)
            newItemText += addrValueClearStr;
        else
            newItemText += "("+ addrValueClearStr;
        isLeft = true;
    }
    else
        addrValueClearStr = "";

    if(isLeft)
        newItemText +=")";

    QString isExecComStr = "";
    if(isExecCom == 2)
    {
        isExecComStr = "执行";
        newItemText += "("+isExecComStr+":窗口"+QString::number(commandID)+")";
    }
    else
        isExecComStr = "";

    if(PLClistWidget!=NULL)
    {
         int itemCount = PLClistWidget->count();
         PLClistWidget->addItem(QString::number(itemCount+1)+"："+newItemText);
    }
}
void Dialog::doShowDataTransBackground()
{

    //重置界面信息
    ui->SourceAddrShift->clear();
    ui->TargetAddressShift->clear();
    ui->ExecCodeWhenOpenSpecialWin->setChecked(false);
    ui->TransDataSize->setText("1");

    ui->generalProStack->setCurrentIndex(21);
    initDataTransBackground();
    this->show();

}

void Dialog::doDataTransSettingBtn()
{
    QString currentText = TransBackground->currentItem()->text();

    QStringList strList = currentText.split(",");
    QString sourceDev;

    QString sourceText = strList.at(0).split("->").first().remove("[").remove("]");
    QString targetText = strList.at(0).split("->").last().remove("[").remove("]");

    if(sourceText.split("：").first() == "lcoal HMI")
        ui->SouceDeviceCombox->setCurrentIndex(0);
    else
        ui->SouceDeviceCombox->setCurrentIndex(1);

    ui->SourceAddressCombox->setCurrentText(sourceText.split("：").last().split("-").first());
    ui->SourceAddrShift->setText(sourceText.split("：").last().split("-").last());


    if(targetText.split("：").first() == "lcoal HMI")
        ui->TargetDeviceCombox->setCurrentIndex(0);
    else
        ui->TargetDeviceCombox->setCurrentIndex(1);

    ui->TargetAddressCombox->setCurrentText(targetText.split("：").last().split("-").first());
    ui->TargetAddressShift->setText(targetText.split("：").last().split("-").last());

    QString transType = strList.at(1).split("：").last();
    if(transType == "位")
        ui->AddressTypeComobox->setCurrentIndex(0);
    else
        ui->AddressTypeComobox->setCurrentIndex(1);
    QString frequency = strList.at(2).split("：").last();
    for(int i=0;i<ui->TimeIinterval->count();i++)
    {
        if(ui->TimeIinterval->itemText(i) == frequency)
        {
            ui->TimeIinterval->setCurrentIndex(i);
        }
    }
    QString transSize = strList.at(3).split("(").first().split("：").last();
    ui->TransDataSize->setText(transSize.remove(transType));
    QString isExec;
    int commanderIndex;
    if(currentText.contains("("))
    {
        isExec = currentText.split("(").last().split("：").first().remove("(");
        commanderIndex = currentText.split("：").last().remove("窗口").remove(")").toInt();
        qDebug()<<" the windows index is : "<<commanderIndex;

        if(isExec == "执行")
            ui->ExecCodeWhenOpenSpecialWin->setChecked(true);
        for(int i=0;i<ui->SpecialExecCodeCombox->count();i++)
        {
            if(ui->SpecialExecCodeCombox->itemText(i).contains(commanderIndex))
            {
                qDebug()<<"the i is : "<<QString::number(i)<<" the item text is : "<<ui->SpecialExecCodeCombox->itemText(i);
                ui->SpecialExecCodeCombox->setCurrentIndex(i);
            }
        }
    }
    this->show();
}

void Dialog::doDeleteListItem()
{
    int row  = TransBackground->currentRow();
    TransBackground->takeItem(row);
    if(TransBackground->count() == 0)
    {
        settingButton->hide();
        deleteButton->hide();
    }
}

//显示排程新增按钮对应的界面
void Dialog::doAddNewScheduleItem()
{
    int count = ScheduleItemWidget->count();
    if(ui->generalProStack->currentIndex() == 27)            //只有当前是排程界面时，才设置默认显示的文字
    {
        ui->ExplainLineEdit->setText("排程"+QString::number(count+1));
        ui->ExplainLineEdit->setFocus();
    }

    this->setWindowTitle("排程");
    ui->generalProStack->setCurrentIndex(27);
    initSchedulePage();         //初始化排程界面
    this->setFixedSize(QSize(570,770));
    this->exec();

}

void Dialog::doDeleteScheduleItem()
{
    int rows = ScheduleItemWidget->currentRow();
    ScheduleItemWidget->takeItem(rows);
    if(ScheduleItemWidget->count() == 0)
    {
        deleteSchedule->hide();             //隐藏配置和删除按钮
        configureSchedule->hide();
    }
}

void Dialog::doConfigureScheduleItem()
{
   this->setWindowTitle("排程");
   ui->generalProStack->setCurrentIndex(27);
   initSchedulePage();         //初始化排程界面
   this->setFixedSize(QSize(570,770));

   QStringList textList = currentScheduleText.split(",");
   QString scheduleName = textList.first().split(":").first();
   ui->ExplainLineEdit->setText(scheduleName);
   if(textList.first().contains("("))
   {
       QString radioName = textList.first().split(":").at(1).split("->").first();
       radioName = radioName.remove("[").remove("]");
       QString radioType = radioName.split("(").first();
       QString constNumber = radioName.split("(").last().remove("(").remove(")");

       QString addrText = textList.first().split("->").last();
       addrText = addrText.remove("[").remove("]");
       QString deviceType = addrText.split(":").first();
       QString addrType = addrText.split(":").last().split("-").first();
       QString shiftAddr = addrText.split(":").last().split("-").last();

       ui->wordWWriteRadio->setChecked(true);           //通过字写入方式生成地址
       ui->ScheduleTargetDeviceCombox->setCurrentText(deviceType);
       ui->ScheduleTargetAddrCombox->setCurrentText(addrType);
       ui->ScheduleTargetShiftCombox->setText(shiftAddr);

       ui->ConstNumberRadio->setChecked(true);
       ui->TextWriteConstValue->setText(constNumber);

       ui->TextWriteConfigure->show();
       ui->WriteValueStackWidget->setCurrentIndex(1);
   }
   else if(textList.first().contains("]]"))
   {
      QString textOne =  textList.first().split("->").first();
      QString radioName = textOne.split("[").at(1);
      QString targetDevice = textOne.split("[").last().split(":").first();
      QString targetAddrText = textOne.split("[").last().split(":").last().remove("]]");
      QString targetAddr = targetAddrText.split("-").first();
      QString targetShift = targetAddrText.split("-").last();

      QString textTwo =  textList.first().split("->").last().remove("[").remove("]");
      QString textWriteDevice = textTwo.split(":").first();
      QString textWriteAddr = textTwo.split(":").last().split("-").first();
      QString textWriteShift = textTwo.split(":").last().split("-").last();

      ui->wordWWriteRadio->setChecked(true);           //通过字写入方式生成地址
      ui->ScheduleTargetDeviceCombox->setCurrentText(targetDevice);
      ui->ScheduleTargetAddrCombox->setCurrentText(targetAddrText);
      ui->ScheduleTargetShiftCombox->setText(targetShift);

      ui->AddressRadio->setChecked(true);
      ui->TextInputValueAddrDevice->setCurrentText(textWriteDevice);
      ui->TextWriteAddrCombox->setCurrentText(textWriteAddr);
      ui->TextInputValueShiftAddr->setText(textWriteShift);

      ui->TextWriteConfigure->show();
      ui->WriteValueStackWidget->setCurrentIndex(1);
   }
   else
   {
       QString radioName = textList.first().split("->").first().split(":").last().remove("[").remove("]");
       QString textTwo = textList.first().split("->").last().remove("[").remove("]");

       QString deviceType = textTwo.split(":").first();
       QString addrType = textTwo.split(":").last().split("-").first();
       QString shiftText = textTwo.split(":").last().split("-").last();

       if(radioName == "位设为ON" )
           ui->BitSaveAsOn->setChecked(true);
       else if(radioName == "位设为OFF")
           ui->BitSaveAsOff->setChecked(true);

       ui->ScheduleTargetDeviceCombox->setCurrentText(deviceType);
       ui->ScheduleTargetAddrCombox->setCurrentText(addrType);
       ui->ScheduleTargetShiftCombox->setText(shiftText);
   }
   this->exec();

}

void Dialog::doTableCheck(int arg1)
{
    QCheckBox* check = (QCheckBox*)(sender());
    int row = check->property("row").toInt();
    int column = check->property("column").toInt();
    qDebug()<<"the row is : "<<row<< "  ,the column is: "<<column<<"  the state is: "<<arg1;
}

void Dialog::doLineEditTextChanged()
{
    QLineEdit *lineEdit = (QLineEdit*)(sender());
    QString text = lineEdit->text();
    if(!checkIllegalChara(text))
    {
       QMessageBox::warning(NULL,"提示","此字段格式无法被接受",QMessageBox::Yes);
       lineEdit->setText("new");
       return;
    }
}

void Dialog::doListItemClicked(int row)
{
    if(row <0)
        return;
    formulaListRow = row;
    //清空右侧表格中的数据
    for(int i= dataModel->rowCount()-1;i>= 0;i--)
    {
        qDebug()<<"要删除的是第： "<<i<<" 行";
        dataModel->removeRow(i);
    }
    QString formulaStr = ((QLineEdit*)(ui->FormulaListWidget->itemWidget(ui->FormulaListWidget->item(row))->children().at(2)))->text();
    if(!m_allData.contains(formulaStr))
    {
        qDebug()<<"未找到该配方对应的数据项";
        return;
    }
    else
    {
        qDebug()<<"the right table has "<<dataModel->rowCount()<<"  行";
        QVector<FormulaItem>  tempFormula = m_allData.value(formulaStr);
        for(QVector<FormulaItem>::iterator iter = tempFormula.begin();iter!= tempFormula.end();iter++)
        {
            qDebug()<<"第 "<<row<<" 行数据表中插入的数据是： "<<iter->proName<<" "<<iter->dataType<<" "<<iter->size<<" "<<iter->showWidth<<" "<<iter->pointNumber<<" "<<iter->alignType;
            int row = dataModel->rowCount();
            dataModel->insertRow(dataModel->rowCount());
            dataModel->setData(dataModel->index(row,0,QModelIndex()),iter->proName);
            dataModel->setData(dataModel->index(row,1,QModelIndex()),iter->dataType);
            dataModel->setData(dataModel->index(row,2,QModelIndex()),iter->size);
            dataModel->setData(dataModel->index(row,3,QModelIndex()),iter->showWidth);
            dataModel->setData(dataModel->index(row,4,QModelIndex()),iter->pointNumber);
            dataModel->setData(dataModel->index(row,5,QModelIndex()),iter->alignType);
         }
    }
}

void Dialog::doTableViewTextChanged(QStandardItem *item)
{
    int row = item->row();
    int column = item->column();
    if(!isNewAddItem)
    {
        QString text = item->text();
        QObjectList obj = ui->FormulaListWidget->itemWidget(ui->FormulaListWidget->currentItem())->children();
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(obj.at(2));
        QString formulaName = lineEdit->text();
        QVector<FormulaItem> tempVec = m_allData.value(formulaName);
        for(QVector<FormulaItem>::iterator iter = tempVec.begin();iter != tempVec.end();++iter)
        {
            if(iter->row == row)
            {
                switch (column)
                {
                case 0:
                    iter->proName = text;
                    break;
                case 1:
                    iter->dataType = text;
                    break;
                case 2:
                    iter->size = text;
                    break;
                case 3:
                    iter->showWidth = text;
                    break;
                case 4:
                    iter->pointNumber = text;
                    break;
                case 5:
                    iter->alignType = text;
                    break;
                default:
                    break;
                }
            }
        }
        m_allData.insert(formulaName,tempVec);
    }
}

void Dialog::doItemClicked(QModelIndex index)
{
    int row = index.row();
    currentFormulaRow = row;
}

void Dialog::doDevTableClicked(QTableWidgetItem *item)
{
    currentDevRow = item->row();
}

void Dialog::showPLCControlWidget()
{
    qDebug()<<"进入到生成PLC控制界面";
 
    QDialog *widget = new QDialog(this);
    widget->setFixedSize(QSize(900,600));
    widget->setWindowTitle("PLC控制");
    QHBoxLayout *Hlayout = new QHBoxLayout;
    QVBoxLayout *Vlayout = new QVBoxLayout;
    
    PLClistWidget = new QListWidget();
    PLClistWidget->addItem("1：[local HMI：LB-3] =>执行宏指令：[ID:001] test mode_com2_rs485_2w(OFF->ON)");
    PLClistWidget->addItem("2：[local HMI：LB-4] =>执行宏指令：[ID:002] test_mode_com2_rs485_4w(OFF->ON)");
    PLClistWidget->addItem("3：[local HMI：LB-2] =>执行宏指令：[ID:003] test_mode_com1_rs232(OFF->ON)");
    PLClistWidget->addItem("4：[local HMI：LB-10] =>执行宏指令：[ID:004] Beep(OFF->ON)");
    PLClistWidget->addItem("5：[local HMI：LB-301] =>执行宏指令：[ID:005] Memory _test(OFF->ON)");
    PLClistWidget->addItem("6：[local HMI：LB-302] =>执行宏指令：[ID:007] Run Memory Test Time(OFF->ON)");
    PLClistWidget->addItem("7：[local HMI：LB-303] =>背光灯控制(打开)");
    PLClistWidget->addItem("8：[local HMI：LB-600] =>执行宏指令：[ID:008] Static IP(OFF->ON))");
    PLClistWidget->addItem("9：[local HMI：LB-601] =>执行宏指令：[ID:009] DHCP(OFF->ON)");
    PLClistWidget->addItem("10：[local HMI：LB-9] =>执行宏指令：[ID:010] test_Result(OFF->ON)");
    PLClistWidget->addItem("11：[local HMI：LB-6] =>执行宏指令：[ID:013] test_mode_com4_rs485_2w(OFF->ON)");
    PLClistWidget->addItem("12：[local HMI：LB-8] =>执行宏指令：[ID:014] test_mode_com3_rs232(OFF->ON)");
    PLClistWidget->addItem("13：[local HMI：LB-1109] =>背光灯控制(返回值)(关闭)(执行：窗口110)");
    PLClistWidget->addItem("14：[local HMI：LW-40] =>切换基本窗口(换页后地址数值归零)");

    //新增 、设置、删除  关闭

    QPushButton *addButton = new QPushButton("新增");
    QPushButton *SettingButton = new QPushButton("设置");
    QPushButton *deleteButton = new QPushButton("删除");
    QPushButton *closeButton = new QPushButton("关闭");

    connect(closeButton,SIGNAL(clicked()),widget,SLOT(close()));
    connect(addButton,&QPushButton::clicked,this,&Dialog::doAddbuttonClicked);


    Hlayout->addWidget(addButton);
    Hlayout->addWidget(SettingButton);
    Hlayout->addWidget(deleteButton);
    Hlayout->addStretch();
    Hlayout->addWidget(closeButton);

    Vlayout->addWidget(PLClistWidget);
    Vlayout->addLayout(Hlayout);

    widget->setLayout(Vlayout);
    widget->show();
}

void Dialog::showDataTransBackground()
{

    QWidget *dialog = new QWidget();
    dialog->setWindowTitle("资料传输(背景)");
    dialog->setFixedSize(QSize(800,600));
    TransBackground = new QListWidget();

    QHBoxLayout *hLayout = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout();

    QTabWidget  *tabWidget = new QTabWidget();
    tabWidget->addTab(TransBackground,"定时式");

    addButton = new QPushButton("新增");
    deleteButton = new QPushButton("删除");
    settingButton = new QPushButton("设置");
    QPushButton *closeButton = new QPushButton("关闭");


    connect(closeButton,&QPushButton::clicked,dialog,&QDialog::close);
    connect(addButton,&QPushButton::clicked,this,&Dialog::doShowDataTransBackground);
    connect(settingButton,SIGNAL(clicked()),this,SLOT(doDataTransSettingBtn()));
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(doDeleteListItem()));


    hLayout->addWidget(addButton);
    hLayout->addWidget(deleteButton);
    hLayout->addWidget(settingButton);
    hLayout->addStretch();
    hLayout->addWidget(closeButton);

    vLayout->addWidget(tabWidget);
    vLayout->addLayout(hLayout);


    if(TransBackground->count() == 0)
    {
        settingButton->hide();
        deleteButton->hide();
    }

    dialog->setLayout(vLayout);
    dialog->show();
}

//显示排程窗口
void Dialog::showShleduleWidget()
{
    QWidget *widget = new QWidget();
    widget->setFixedSize(QSize(570,400));
    widget->setWindowTitle("排程");
    QHBoxLayout *HLayout = new QHBoxLayout();
    QVBoxLayout *VLayout = new QVBoxLayout();
    ScheduleItemWidget = new QListWidget();

    addSchedule = new QPushButton("新增");
    deleteSchedule = new QPushButton("删除");
    configureSchedule = new QPushButton("配置");
    QPushButton *closeButton =  new QPushButton("关闭");

    connect(addSchedule,SIGNAL(clicked()),this,SLOT(doAddNewScheduleItem()));
    connect(deleteSchedule,SIGNAL(clicked()),this,SLOT(doDeleteScheduleItem()));
    connect(configureSchedule,SIGNAL(clicked()),this,SLOT(doConfigureScheduleItem()));
    connect(closeButton,SIGNAL(clicked()),widget,SLOT(close()));
    connect(ScheduleItemWidget,&QListWidget::currentTextChanged,[=](QString itemText){
        currentScheduleText = itemText;
    });

    if(ScheduleItemWidget->count() == 0 )
    {
        deleteSchedule->hide();
        configureSchedule->hide();
    }

    HLayout->addWidget(addSchedule);
    HLayout->addWidget(deleteSchedule);
    HLayout->addWidget(configureSchedule);
    HLayout->addStretch();
    HLayout->addWidget(closeButton);

    VLayout->addWidget(ScheduleItemWidget);
    VLayout->addLayout(HLayout);

    widget->setLayout(VLayout);
    widget->show();
}

void Dialog::compoundDataTransItem()
{
    addressType = ui->AddressTypeComobox->currentIndex();
    timeInterval = ui->TimeIinterval->currentText();
    transDataSize = ui->TransDataSize->text().toInt();

    isExecCode = ui->ExecCodeWhenOpenSpecialWin->checkState();
    codeStr = ui->SpecialExecCodeCombox->currentText();
    codeIndex = ui->SpecialExecCodeCombox->currentIndex();

    sourceDev = ui->SouceDeviceCombox->currentText();
    sourceAddr = ui->SourceAddressCombox->currentText();
    sourceShiftStr = ui->SourceAddrShift->text();

    targetDev = ui->TargetDeviceCombox->currentText();
    targetAddr = ui->TargetAddressCombox->currentText();
    targetShiftAddr = ui->TargetAddressShift->text();

    QString itemText = "["+sourceDev+"："+sourceAddr+"-"+sourceShiftStr+"]->["+targetDev+"："+targetAddr+"-"+targetShiftAddr+"],";
    if(addressType == 0)
    {
        itemText += "模式：位,";
        itemText += "频率："+timeInterval+",传输数据大小："+QString::number(transDataSize)+"位";
    }
    else if(addressType == 1)
    {
       itemText += "模式：字,";
       itemText += "频率："+timeInterval+",传输数据大小："+QString::number(transDataSize)+"字";
    }
    if(isExecCode == 2)         //如果勾选了在执行特定命令
    {
        itemText += "(执行：窗口"+codeStr.split(".").first()+")";
    }
    TransBackground->addItem(itemText);
    if(TransBackground->count() > 0)
    {
        settingButton->show();
        deleteButton->show();
    }
}

void Dialog::compoundScheduleItem()
{
    compoundSchText = "";
    if( ui->ExplainLineEdit->text() != "")            //获取当前排程的名称
        compoundSchText += ui->ExplainLineEdit->text()+":[";
    //获取模式状态
    if(ui->BitSaveAsOn->isChecked())
        compoundSchText+="位设为ON]->[";
    else if(ui->BitSaveAsOff->isChecked())
        compoundSchText += "位设为OFF]->[";
    else if(ui->wordWWriteRadio->isChecked())
    {
        if(ui->ConstNumberRadio->isChecked())
        {
            compoundSchText += "字写入("+ui->TextWriteConstValue->text()+")]->["+ ui->ScheduleTargetDeviceCombox->currentText()+":"+ui->ScheduleTargetAddrCombox->currentText()+"-"+ui->ScheduleTargetShiftCombox->text()+"],时间:SUN";
        }
        else if(ui->AddressRadio->isChecked())
        {
            compoundSchText += "字写入[" + ui->ScheduleTargetDeviceCombox->currentText()+":"+ui->ScheduleTargetAddrCombox->currentText()+"-"+ui->ScheduleTargetShiftCombox->text()+"]]->[";
            compoundSchText += ui->TextInputValueAddrDevice->currentText()+":"+ui->TextWriteAddrCombox->currentText()+"-"+ui->TextInputValueShiftAddr->text()+"],时间:SUN;";
        }
    }
     if(ui->BitSaveAsOn->isChecked() || ui->BitSaveAsOff->isChecked())
     {
         compoundSchText += ui->ScheduleTargetDeviceCombox->currentText()+":"+ui->ScheduleTargetAddrCombox->currentText()+"-"+ui->ScheduleTargetShiftCombox->text()+"],时间:SUN;";
     }


     QString scheduleName = compoundSchText.split(":").first();
     int i=0;
     for(i;i<ScheduleItemWidget->count();i++)
     {
         if(ScheduleItemWidget->item(i)->text().contains(scheduleName))         //就是进行了修改
         {
            ScheduleItemWidget->item(i)->setText(compoundSchText);  //更换内容
            break;
         }
     }
     if(i == ScheduleItemWidget->count())
     {
         ScheduleItemWidget->addItem(compoundSchText);          //作为新的插入到list中
     }
     if(ScheduleItemWidget->count() > 0)
     {
         deleteSchedule->show();
         configureSchedule->show();
     }

}

void Dialog::configureLBWidget(bool wordCombox, bool addrTips, bool indexCombox, bool systemRegister, bool userCustom,bool hideIndexCheck)
{
    subDlg->setAddrWidgetType(1);
    if(hideIndexCheck == false)
        subDlg->setSubControlEnable(wordCombox,addrTips,indexCombox,systemRegister,userCustom,hideIndexCheck);
    else
        subDlg->setSubControlEnable(wordCombox,addrTips,indexCombox,systemRegister,userCustom);

    subDlg->showSubDialog(WatchNeedleAddrPage);
    if(subDlg->exec() == QDialog::Rejected)
        return;
}

void Dialog::configureLWWidget(bool wordCombox, bool addrTips, bool indexCombox, bool systemRegister, bool userCustom,bool hideIndexCheck)
{
    subDlg->setAddrWidgetType(0);
    if(hideIndexCheck == false)
        subDlg->setSubControlEnable(wordCombox,addrTips,indexCombox,systemRegister,userCustom,hideIndexCheck);
    else
        subDlg->setSubControlEnable(wordCombox,addrTips,indexCombox,systemRegister,userCustom);
    subDlg->showSubDialog(WatchNeedleAddrPage);
    if(subDlg->exec() == QDialog::Rejected)
        return;
}

void Dialog::initFontControl(QComboBox *combox)
{
    QFontDatabase base;
    QStringList fontName = base.families();
    combox->clear();
    combox->addItems(fontName);
}

void Dialog::initSystemPataTable()
{
    QStringList strHeaderList;
    strHeaderList<<"编号"<<"启用"<<"隐藏用户"<<"用户名称"<<"密码"<<"类别A"<<"类别B"<<"类别C"<<"类别D"<<"类别E"<<"类别F"<<"类别G"<<"类别H"<<"类别I"<<"类别J"<<"类别K"<<"类别L";
    ui->UserInfoTableWidget->setColumnCount(17);
    ui->UserInfoTableWidget->setHorizontalHeaderLabels(strHeaderList);
    ui->UserInfoTableWidget->verticalHeader()->setVisible(false);
    ui->UserInfoTableWidget->setRowCount(11);
    for(int i=1;i<12;i++)
    {
        ui->UserInfoTableWidget->setItem(i-1,0,new QTableWidgetItem(QString::number(i)));
        ui->UserInfoTableWidget->item(i-1,0)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
        ui->UserInfoTableWidget->setItem(i-1,3,new QTableWidgetItem("User"+QString::number(i)));
        ui->UserInfoTableWidget->item(i-1,3)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
        ui->UserInfoTableWidget->setItem(i-1,4,new QTableWidgetItem(QString::number(i)));
        ui->UserInfoTableWidget->item(i-1,4)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
    }
    for(int i=0;i<12;i++)
    {
        for(int j=0;j<17;j++)
        {
            if(j!= 0 && j != 3 && j!= 4)
            {
                QCheckBox *check = new QCheckBox;
                check->setProperty("row",i);
                check->setProperty("column",j);
                QWidget *widget = new QWidget();
                QHBoxLayout *layout = new QHBoxLayout;
                layout->setMargin(0);
                layout->addStretch();
                layout->addWidget(check);
                layout->addStretch();
                widget->setLayout(layout);
                ui->UserInfoTableWidget->setCellWidget(i,j,widget);
                connect(check,SIGNAL(stateChanged(int)),this,SLOT(doTableCheck(int)));
            }
        }
    }

    QStringList  userList;
    userList<<"类别"<<"描述";
    ui->UserTypeTable->setColumnCount(2);
    ui->UserTypeTable->setHorizontalHeaderLabels(userList);
    ui->UserTypeTable->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->UserTypeTable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->UserTypeTable->verticalHeader()->setVisible(false);
    ui->UserTypeTable->setRowCount(12);

    QStringList charList{"A","B","C","D","E","F","G","H","I","J","K","L"};
    for(int i=0;i<12;i++)
    {
        ui->UserTypeTable->setItem(i,0,new QTableWidgetItem("类别"+charList.at(i)));
        ui->UserTypeTable->item(i,0)->setTextAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    }

    //初始化数据库配方表
    QStringList dataHeader{"项目名称","数据类型","大小","显示宽度","小数点","对齐"};
    dataModel = new QStandardItemModel(0,6);
    dataModel->setHorizontalHeaderLabels(dataHeader);
    ui->DatabaseTableView->setModel(dataModel);
    ui->DatabaseTableView->verticalHeader()->setVisible(false);
    ui->DatabaseTableView->horizontalHeader()->setStretchLastSection(true);

    //为每一列都添加委托
    ui->DatabaseTableView->setItemDelegateForColumn(0,new ProNameDelegate(this));
    //数据类型
    ui->DatabaseTableView->setItemDelegateForColumn(1,new DataTypeDelegate(this));
    //大小
    ui->DatabaseTableView->setItemDelegateForColumn(2,new SizeDelegate(this));
    //显示宽度
    ui->DatabaseTableView->setItemDelegateForColumn(3,new WidthDelegate(this));
    //小数点
    ui->DatabaseTableView->setItemDelegateForColumn(4,new pointDeletgate(this));
    //对齐
    ui->DatabaseTableView->setItemDelegateForColumn(5,new TextAlignmentDelegate(this));

    connect(dataModel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(doTableViewTextChanged(QStandardItem*)));
    connect(ui->DatabaseTableView,SIGNAL(clicked(QModelIndex)),this,SLOT(doItemClicked(QModelIndex)));
}

bool Dialog::checkIllegalChara(QString arg)
{
    QByteArray ba = arg.toLatin1();
    const char *s = ba.data();
    bool bret = true;
    while(*s)
    {
        if((*s>='A' && *s<='Z') || (*s>='a' && *s<='z') || (*s>='0' && *s<='9'))
            s++;
        else
        {
            bret = false;
            break;
        }
    }
    return bret;
}

bool Dialog::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->DynamicScalrRadiusSlider )
    {
        if(event->type() == QEvent::MouseMove && ui->DynamicScalrRadiusSlider->underMouse())
        {
            int value = ui->DynamicScalrRadiusSlider->value();
            ((QLabel*)DynamicScaleTipWidget->children().at(1))->setText(QString::number(value));
            QMouseEvent *mouseEvent = (QMouseEvent*)event;
            if(mouseEvent->windowPos().x() - ((QSlider*)obj)->geometry().x() <180 && mouseEvent->windowPos().x() - ((QSlider*)obj)->geometry().x()>30)
                DynamicScaleTipWidget->move(mouseEvent->windowPos().x()-15,335);
            DynamicScaleTipWidget->show();

            qDebug()<<"Slider左上角的窗口坐标是： "<<((QSlider*)obj)->geometry().x()<<" the y is: "<<((QSlider*)obj)->geometry().y()-20;
            qDebug()<<"鼠标点击的位置相对于窗口而言，坐标是："<<mouseEvent->windowPos();
            qDebug()<<"鼠标点击的位置相对于屏幕而言，坐标是："<<mouseEvent->screenPos();
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            DynamicScaleTipWidget->hide();
        }
        return QDialog::eventFilter(obj,event);
    }
    else
        return QDialog::eventFilter(obj,event);
}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"the mouseevent was clicked";
    if(event->buttons() == Qt::LeftButton)
    {
        qDebug()<<"mouse left button was pressed";

        if(ui->DynamicScalrRadiusSlider->underMouse())
        {
            qDebug()<<"mouse is above the slider";
        }
    }

}

void Dialog::on_BitStatusLightRadio_clicked()
{

}

/*
void Dialog::on_BitStatusSwitRadio_clicked()
{

}
*/

//多状态切换开关
void Dialog::on_MultStatusSwitchRadio_clicked()
{
    initMultStatusSwitchPage();
}

//多状态指示灯
void Dialog::on_MultStatusLightRadio_clicked()
{
    initMultStatusLightPage();
}

//弹出窗口
void Dialog::on_EjectWindowsRadio_clicked()
{
    initFuncKeyPage(9);
}

void Dialog::on_SwitchPublicWindowsRadio_clicked()
{
    initFuncKeyPage(1);
}

void Dialog::on_SwitchBaBaseWindowsRadio_clicked()
{
    initFuncKeyPage(2);
}
//宏指令触发
void Dialog::on_TriggerMacroinstructionRadio_clicked()
{
   initFuncKeyPage(3);
}
//窗口控制条
void Dialog::on_WindowControlItemRadio_clicked()
{
   initFuncKeyPage(4);
}
//画面截取
void Dialog::on_PictureInterceptionRadio_clicked()
{
    initFuncKeyPage(5);
}
//通知box中的启用按钮
void Dialog::on_EnableCheckBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
        initFuncKeyPage(6);         //启用按钮被点击
    else if(arg1 == Qt::Unchecked)
        initFuncKeyPage(7);         //启用按钮被取消
}

void Dialog::on_closeWindowRadio_clicked()
{
   initFuncKeyPage(8);
}

void Dialog::on_returnPreWindwosRadio_clicked()
{
    hideFuncKeyButton();
}

void Dialog::on_EnterKeyRadio_clicked()
{
   hideFuncKeyButton();
}

//复合式多功能添加按钮菜单
void Dialog::on_MultipleFunctionsAddAction_clicked()
{
    multipleFunctionsMenu->exec(QCursor::pos());
}

//滑动
void Dialog::on_radioButton_clicked()
{
    ui->numberLimitPage->setCurrentIndex(0);
}

void Dialog::on_radioButton_2_clicked()
{
    ui->numberLimitPage->setCurrentIndex(1);
}

//滚动模式
void Dialog::on_rollModelCheckBox_clicked()
{
    if(ui->rollModelCheckBox->checkState() == Qt::Checked )
    {
        ui->rollValueLabel->show();
        ui->rollValueLineEdit->show();
    }
    else if(ui->rollModelCheckBox->checkState() == Qt::Unchecked )
    {
        ui->rollValueLabel->hide();
        ui->rollValueLineEdit->hide();
    }
}

//滑动开关通知GroupBox启动
void Dialog::on_SliderSwitchEnableCheckBox_clicked()
{
    if(ui->SliderSwitchEnableCheckBox->checkState() == Qt::Checked )
    {
        ui->SetAsOFFRadio->show();
        ui->SetAsONRadio->show();
        ui->sliderSwitchNoticeGroupWidget->show();
    }
    else if(ui->SliderSwitchEnableCheckBox->checkState() == Qt::Unchecked)
    {
        ui->SetAsOFFRadio->hide();
        ui->SetAsONRadio->hide();
        ui->sliderSwitchNoticeGroupWidget->hide();
    }
}

//监看地址GroupBox启动
void Dialog::on_WatchEnableCheckBox_clicked()
{
    if(ui->WatchEnableCheckBox->checkState() == Qt::Checked )
    {
      ui->PrisonWatchGroupWidget->show();
    }
    else if(ui->WatchEnableCheckBox->checkState() == Qt::Unchecked)
    {
       ui->PrisonWatchGroupWidget->hide();
    }
}

//项目选单中的资料来源
void Dialog::on_ProjectDataSouceCombox_currentIndexChanged(int index)
{
    if(index == 0)          //预设
    {
        ui->ProjectDataSourceHistory->hide();
        ui->ProjectAddrGroupBox->hide();
        ui->ControlAddrGroupBox->hide();
        ui->enableConfirmAfterOpened->hide();
    }
    else if(index == 1)     //历史数据日期
    {
        //显示取自历史资源数据GroupBox
        ui->EnableDelHistoryFileCheckBox->show();
        ui->ProjectDataSourceHistory->show();
        ui->ProjectAddrGroupBox->hide();
        ui->ControlAddrGroupBox->hide();
        ui->enableConfirmAfterOpened->hide();
    }
    else if(index == 2)     //项目地址
    {
        //显示项目地址、控制地址、写入成功开启通知
        ui->ProjectDataSourceHistory->hide();
        ui->ControlAddrGroupBox->show();
        ui->ProjectAddrGroupBox->show();
        ui->enableConfirmAfterOpened->show();
    }
}

//启用删除历史文件功能
void Dialog::on_EnableDelHistoryFileCheckBox_clicked()
{
    if(ui->EnableDelHistoryFileCheckBox->checkState() == Qt::Checked)
    {
        ui->ControlAddrGroupBox->show();
    }
    else
        ui->ControlAddrGroupBox->hide();
}

//资料取样
void Dialog::on_ProjectDataTypeCombox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "资料取样")
    {
        ui->ItemIndexCombox->show();
        ui->ItemIndexLabel->show();
    }
    else
    {
        ui->ItemIndexCombox->hide();
        ui->ItemIndexLabel->hide();
    }
}

//写入成功后开启通知
void Dialog::on_WatchAddrEnable_clicked()
{
    if(ui->WatchAddrEnable->checkState() == Qt::Checked)
    {
        ui->enableConfirmSaveAsOn->show();
        ui->enableConfirmSaveAsOff->show();
        ui->enableConfirmSubWidget->show();
    }
    else
    {
        ui->enableConfirmSaveAsOn->hide();
        ui->enableConfirmSaveAsOff->hide();
        ui->enableConfirmSubWidget->hide();
    }
}

void Dialog::on_ValueItemEnableCheckBox_clicked(bool checked)
{
    ui->ValueEnableConfirmSubWidget->setHidden(!checked);
    ui->ValueNoticeRadioWidgte->setHidden(!checked);
}

//数值元件读取/写入使用不同的地址
void Dialog::on_useDiffAddrInRW_clicked(bool checked)
{
    ui->NumberItemWriteAddr->setHidden(!checked);
    if(checked)
        ui->NumberItemReadAddr->setTitle("读取地址");
    else
        ui->NumberItemReadAddr->setTitle("读取/写入地址");
}

void Dialog::on_enableInputFcuntion_clicked(bool checked)
{
    ui->useDiffAddrInRW->setHidden(!checked);
    ui->InputInvalidNotice->setHidden(!checked);
    ui->NumberItemNotice->setHidden(!checked);
}

void Dialog::on_InputInvalidEnable_clicked(bool checked)
{
    ui->SaveAsOn->setHidden(!checked);
    ui->SaveAsOff->setHidden(!checked);
    ui->ValuePageEnableWidget->setHidden(!checked);
}

void Dialog::on_MultipleLinesShowCheckbox_clicked(bool checked)
{
    ui->VerticalAlignmentLabel->setHidden(!checked);
    ui->VerticalAlignmentCombox->setHidden(!checked);
    ui->CharacterItemNotice->hide();
}

void Dialog::on_checkBox_4_clicked(bool checked)
{
    ui->CharacterItemNotice->setHidden(!checked);
    if(checked)
        ui->CharacterItemWriteAddr->setTitle("读取/写入地址");
    else
        ui->CharacterItemWriteAddr->setTitle("读取地址");
}

//原型图中心开始位置
void Dialog::on_circularPointSizeSlider_valueChanged(int value)
{
    ui->PartternPaintWidget->setWidgetSubRingRadius(value);
    update();           //重绘
}

//圆形图不等拆分
void Dialog::on_channelNumberCount_currentTextChanged(const QString &arg1)
{
    ui->ChannelChooseComBox->clear();
    for(int i=1;i<=ui->channelNumberCount->currentText().toInt();i++)
    {
        ui->ChannelChooseComBox->addItem(QString::number(i));
    }
    ui->PartternPaintWidget->setWidgetRingCount(arg1.toInt());
    update();           //重绘
}

//更改指定通道上百分比字体的颜色
void Dialog::on_PieChartFontColor_currentIndexChanged(int arg1)
{
    update();
}

//更改指定通道上背景颜色
void Dialog::on_PieChartPaPatternCombox_currentIndexChanged(int arg1)
{
    update();
}

//更换指定通道上的背景样式
//void Dialog::on_comboBox_15_currentIndexChanged(int arg1)
//{
//    update();
//}

//改变通道上字体的显示样式，数据Or百分比
void Dialog::on_dataShowStyle_currentTextChanged(const QString& arg1)
{
    ui->PartternPaintWidget->setWidgetRingTextProperty(ui->PieChartFontComBox->currentText(),ui->FontSizeComBox->currentText().toInt(),ui->dataShowStyle->currentText());
    update();
}

//改变通道上显示的数据的字体
void Dialog::on_PieChartFontComBox_currentTextChanged(const QString& )
{
    ui->PartternPaintWidget->setWidgetRingTextProperty(ui->PieChartFontComBox->currentText(),ui->FontSizeComBox->currentText().toInt(),ui->dataShowStyle->currentText());
    update();
}

//改变通道上显示的数据的字体大小
void Dialog::on_FontSizeComBox_currentTextChanged(const QString& )
{
    ui->PartternPaintWidget->setWidgetRingTextProperty(ui->PieChartFontComBox->currentText(),ui->FontSizeComBox->currentText().toInt(),ui->dataShowStyle->currentText());
    update();
}

void Dialog::on_RotateDirectionButton_clicked()
{
    subDlg->showSubDialog(PartternRotateSettting);
    if(subDlg->exec() == QDialog::Accepted )
    {
        subDlg->getRotateParameter(m_rotateDirection,m_startPos,m_endPos);
        if(m_endPos == -1)
            m_endPos = 360;
        if(m_endPos> 0)
        {
            ui->RotateDirectionButton->setText(QString("%1° ~ %2°").arg(m_startPos).arg(m_endPos));
            ui->PartternPaintWidget->setWidgetRingDrawDirection(m_rotateDirection,m_startPos,m_endPos);
        }
    }
}

void Dialog::on_DynamicCalibrationStyleCombox_currentTextChanged(const QString &arg1)
{
    if(arg1 != "圆形")
    {
        ui->DCRotateDirectionButton->hide();
        ui->DCRotateDirectionLabel->hide();
    }
    else
    {
        ui->DCRotateDirectionButton->show();
        ui->DCRotateDirectionLabel->show();
    }
}

void Dialog::on_DynamicScalrRadiusSlider_valueChanged(int value)
{

    ui->DynamicScalrRadiusSlider->setToolTip(QString::number(value));
}


void Dialog::on_UseScaleChartCheckBox_stateChanged(int arg1)
{
    if(ui->UseScaleChartCheckBox->checkState() == Qt::Checked)
    {
        ui->ScaleChartSubWidget->show();
    }
    else
        ui->ScaleChartSubWidget->hide();

}


void Dialog::on_UseRegisterData_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(arg1 == 2)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void Dialog::on_DataGroupUseShiftAddrCheckBox_stateChanged(int arg1)
{
    if(arg1 == 0)               //未选中
    {
        ui->DataGroupShiftAddrStackWidget->setCurrentIndex(0);
    }
    else if(arg1 == 2)          //选中
    {
        ui->DataGroupShiftAddrStackWidget->setCurrentIndex(1);
    }
}


void Dialog::on_DataGroupTotalChannelCombox_currentTextChanged(const QString &arg1)
{
    ui->DataGroupSingleChannel->clear();
    int totalChannel = arg1.toInt();
    if(totalChannel > 1)
    {
        for(int i=0;i<totalChannel;i++)
        {
            ui->DataGroupSingleChannel->addItem(QString::number(i));
        }
    }
    else
    {
        ui->DataGroupSingleChannel->addItem("1");
    }
}

void Dialog::on_enableWatchCheckBox_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->DataGroupWatchSubWidget->setHidden(true);
    }
    else if(arg1 == 2)
    {
        ui->DataGroupWatchSubWidget->setHidden(false);
    }

}

void Dialog::on_DataLimitSourceFromRegister_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->X_Group->hide();
        ui->Y_Group->hide();
    }
    else if(arg1 == 2)
    {
        ui->X_Group->show();
        ui->Y_Group->show();
    }
}

void Dialog::on_XYCurveChannelCountSpinbox_valueChanged(int arg1)
{
    ui->XYCurveChannelNumber->clear();
    if(arg1>1)
    {
        for(int i=0;i<arg1;i++)
        {
            ui->XYCurveChannelNumber->addItem(QString::number(i));
        }
    }
    else
    {
        ui->XYCurveChannelNumber->addItem("0");
    }
}

void Dialog::on_XYCuroveDataLimitDesc_clicked()
{
     subDlg->showSubDialog(XYCuroveUseInformation);
     if(subDlg->exec() == QDialog::Rejected)
         return;
}

void Dialog::on_XYCurveControlAddrSettingBtn_clicked()
{
    subDlg->setAddrWidgetType(0);  //LW
    subDlg->setSubControlEnable(false,false,false,false,true);
    subDlg->showSubDialog(WatchNeedleAddrPage);
    if(subDlg->exec() == QDialog::Rejected)
        return;
}

void Dialog::on_CancelBtn_clicked()
{
    this->close();
}

void Dialog::on_UseValueFromRegister_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->ValueLimitSubWidget->hide();
        ui->RegisterEquipmentInfoamtion->show();
    }
    else if(arg1 == 0)
    {
        ui->ValueLimitSubWidget->show();
        ui->RegisterEquipmentInfoamtion->hide();
    }
}

void Dialog::on_WatchNeedleSettingBtn_clicked()
{
    subDlg->setWidgetCaller("WatchNeedle");
    configureLWWidget(false,false,true,true,true);

}

void Dialog::on_BarGraphControlSettingBtn_clicked()
{
    subDlg->setWidgetCaller("BarGraph");
    configureLWWidget(false,true,true,true,true);

}

void Dialog::on_ClearAddrSetting_clicked()
{
    subDlg->setWidgetCaller("DynamicPaint");
    configureLWWidget(false,false,false,true,true);
}

void Dialog::on_MoreInformation1_clicked()
{
    subDlg->setWidgetCaller("DynamicPaint");
    subDlg->showSubDialog(MoreInformationOne);
    if(subDlg->exec() == QDialog::Rejected)
        return;

}

void Dialog::on_MoreInfomation2_clicked()
{
    subDlg->setWidgetCaller("DynamicPaint");
    subDlg->showSubDialog(MoreInformationTwo);
    if(subDlg->exec() == QDialog::Rejected)
        return;

}

void Dialog::on_LimitValueFromRegister_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->MoveGraphLimitValueWidget->hide();
        ui->MoveGraphPropertyCoordinate->hide();
    }
    else if(arg1 == 2)
    {
        ui->MoveGraphLimitValueWidget->show();
        ui->MoveGraphPropertyCoordinate->show();
    }
}

void Dialog::on_LimitValueAddiDescBtn_clicked()
{
    subDlg->setWidgetCaller("MoveGraph");
    subDlg->showSubDialog(MoveGraphLimitValueDesc);
    if(subDlg->exec() == QDialog::Rejected)
        return;

}

void Dialog::on_UseWindowShift_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->ShiftValueLabel->show();
        ui->ShiftValueCombox->show();
    }
    else if(arg1 == 0)
    {
        ui->ShiftValueLabel->hide();
        ui->ShiftValueCombox->hide();
    }

}

void Dialog::on_SourceAddrSettingBtn_clicked()
{
    subDlg->setWidgetCaller("dataTransBackground");
    configureLWWidget(false,false,false,true,true);
}

void Dialog::on_AddressTypeComobox_currentTextChanged(const QString &arg1)
{
    if( arg1 == "Word")
    {
        ui->SourceAddressCombox->clear();
        ui->SourceAddressCombox->addItems(LWlist);

        ui->TargetAddressCombox->clear();
        ui->TargetAddressCombox->addItems(LWlist);
    }
    else if(arg1 == "Bit")
    {
        ui->SourceAddressCombox->clear();
        ui->SourceAddressCombox->addItems(LBlist);

        ui->TargetAddressCombox->clear();
        ui->TargetAddressCombox->addItems(LBlist);
    }
}

void Dialog::on_OKBtn_clicked()
{
    if(ui->generalProStack->currentIndex() == 21)       //如果当前属性页面是 资料传输背景 界面
        compoundDataTransItem();
    else if(ui->generalProStack->currentIndex() == 27)
        compoundScheduleItem();
    this->hide();
}

//资料传输背景  --目标地址  --设置
void Dialog::on_TargetAddrSettingBtn_clicked()
{
    subDlg->setWidgetCaller("dataTransBackground");
    subDlg->setAddrWidgetType(1);
    subDlg->setSubControlEnable(false,false,false,true,true);
    subDlg->showSubDialog(WatchNeedleAddrPage);
    if(subDlg->exec() == QDialog::Rejected)
        return;

}

//资料传输背景  --通知  --设置
void Dialog::on_ConfirmSettingBtn_clicked()
{
    subDlg->setWidgetCaller("dataTransBackground");
    configureLBWidget(false,false,false,true,true);
}

//图片检视 --目录  --设置按钮
void Dialog::on_DirAddrSettingBtn_clicked()
{
    subDlg->setWidgetCaller("ImageCheckPage");
    configureLWWidget(true,false,false,true,true);
}

//资料传输来源地址 设置按钮
void Dialog::on_DataTransSourceAddrBtn_clicked()
{
    subDlg->setWidgetCaller("ImageCheckPage");
    configureLWWidget(false,false,false,true,true);
}

//资料传输目的地址 设置按钮
void Dialog::on_DataTransTargetAddrBtn_clicked()
{
    subDlg->setWidgetCaller("ImageCheckPage");
    configureLWWidget(false,false,false,true,true);
}

//动态绘图属性 设置按钮
void Dialog::on_PropertyAddrSetting_clicked()
{
    subDlg->setWidgetCaller("DynamicPaint");
    configureLWWidget(false,false,false,true,true);
}

//移动图形 --读取地址  --设置按钮
void Dialog::on_ControlAddrSettingBtn_clicked()
{
    subDlg->setWidgetCaller("MoveGraphicsPage");
    configureLWWidget(false,false,false,true,true);
}

//移动图形 --限制值地址  --设置按钮
void Dialog::on_LimitDataAddrOfMoveGraphics_clicked()
{
    subDlg->setWidgetCaller("MoveGraphicsPage");
    configureLWWidget(false,false,false,true,true);
}

void Dialog::on_ConfigureButton_clicked()
{
    showStatus = !showStatus;
    ui->ConfirmAddrWidget->setHidden(!showStatus);
}

void Dialog::on_ChooseFileAddrSettingBtn_clicked()
{
    configureLWWidget(true,false,false,true,true);
}

//VNC Viewer  -- 文字库按钮
void Dialog::on_TextBaseBtn_clicked()
{
    btnWdg->showIndexWidget(TextLibraryPage);
    btnWdg->exec();
}

void Dialog::on_QRCodeDeviceSettingBtn_clicked()
{
    configureLWWidget(true,false,false,true,true);
}

void Dialog::on_QRCodeModeCombox_currentTextChanged(const QString &arg1)
{
    ui->QRCodeCorrectStandard->clear();
    QStringList standarnPrecent;
    if(arg1 == "QR code")
    {
        standarnPrecent<<"L(7%)"<<"M(15%)"<<"Q(25%)"<<"H(30%)-预设";
        ui->QRCodeCorrectStandard->addItems(standarnPrecent);
        ui->QRCodeCorrectStandard->setCurrentIndex(3);
    }
    else if(arg1 == "Aztec code")
    {
        QString itemText= "";
        for(int i = 5;i<96;i++)
        {
            if(i == 23)
            {
                itemText = "23%-预设";
            }
            else
                itemText = QString::number(i)+"%";
            ui->QRCodeCorrectStandard->addItem(itemText);
        }
         ui->QRCodeCorrectStandard->setCurrentText("23%-预设");
    }
}

//12小时制，标签设置按钮
void Dialog::on_HourseTagSettingButton_clicked()
{

}

void Dialog::on_comboBox_14_currentTextChanged(const QString &arg1)
{
    if(arg1 == "累加式开关(ON)" || arg1 == "累加式开关(OFF)")
    {
        ui->ResetGroupBox->show();
    }
    else
        ui->ResetGroupBox->hide();
}

void Dialog::on_InputBitSettingButton_clicked()
{
    configureLBWidget(false,false,false,true,true);
}

void Dialog::on_ExportBitButton_clicked()
{
   configureLBWidget(false,false,false,true,true);
}

void Dialog::on_TimerBitSettingButton_clicked()
{
   configureLBWidget(false,false,false,true,true);
}

void Dialog::on_PresetTimeButton_clicked()
{
    configureLWWidget(false,false,false,true,true);
}

void Dialog::on_ResetBitButton_clicked()
{
    configureLBWidget(false,false,false,true,true);
}

void Dialog::on_RecordBitButton_clicked()
{
    configureLWWidget(false,false,false,true,true);
}

void Dialog::on_ConstNumberRadio_clicked()
{
    ui->WriteValueStackWidget->setCurrentIndex(0);
}

void Dialog::on_AddressRadio_clicked()
{
    ui->WriteValueStackWidget->setCurrentIndex(1);
}

void Dialog::on_ShceduleTargetAddrSettingBtn_clicked()
{
    configureLWWidget(false,false,true,true,true);
}

void Dialog::on_TextWriteAddrSettingBtn_clicked()
{
    configureLWWidget(false,false,false,true,true);
}

void Dialog::on_BitSaveAsOn_clicked()
{
    ui->ScheduleTargetAddrCombox->clear();
    ui->ScheduleTargetAddrCombox->addItems(LBlist);
    ui->ScheduleTargetAddrCombox->setCurrentIndex(0);
}

void Dialog::on_BitSaveAsOff_clicked()
{
    ui->ScheduleTargetAddrCombox->clear();
    ui->ScheduleTargetAddrCombox->addItems(LBlist);
    ui->ScheduleTargetAddrCombox->setCurrentIndex(0);
}

void Dialog::on_wordWWriteRadio_clicked()
{
    ui->ScheduleTargetAddrCombox->clear();
    ui->ScheduleTargetAddrCombox->addItems(LWlist);
    ui->ScheduleTargetAddrCombox->setCurrentIndex(0);
}

void Dialog::on_ReadAndWriteUseDiff_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
       ui->BitStatusLightReadAddr->setTitle("读取地址");
       ui->BitStatusLightWriteAddr->setTitle("写入地址");
    }
    else if(arg1 == 2)
    {
        ui->BitStatusLightReadAddr->setTitle("读取/写入地址");
        ui->BitStatusLightWriteAddr->setTitle("");
    }
}

//选中位状态切换开关
void Dialog::on_BitStatusSwitch_clicked()
{
    ui->BitStatusLightReadAddr->setTitle("读取/写入地址");
    ui->BitStatusLightWriteAddr->setTitle("");
}

void Dialog::on_BitStatusReadAddrSettingBtn_clicked()
{
    configureLBWidget(false,false,false,true,true);
}

void Dialog::on_BitStatusWriteAddrSettingBtn_clicked()
{
    configureLBWidget(false,false,false,true,true);
}

void Dialog::on_UserOperatorLimitCombox_activated(const QString &arg1)
{

}


void Dialog::on_ConfirmBeforeOperator_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->LeastKeyTime->setEnabled(true);
        ui->ConfirmWaitTimeLineEdit->setEnabled(true);
    }
    else if(arg1 == 2)
    {
        ui->LeastKeyTime->setEnabled(false);
        ui->ConfirmWaitTimeLineEdit->setEnabled(false);
    }
}

void Dialog::on_EnabelKeySoundSetting_stateChanged(int arg1)
{
    if(arg1 == 2)           //选中
    {
        ui->KeySoundPreSetting->show();
        ui->SoundLibraryButton->setEnabled(true);
        ui->PlaySoundButton->setEnabled(true);
    }
    else if(arg1 == 0)
    {
        ui->KeySoundPreSetting->hide();
        ui->SoundLibraryButton->setEnabled(false);
        ui->PlaySoundButton->setEnabled(false);
    }
}

void Dialog::on_UserOperatorLimitCombox_currentTextChanged(const QString &arg1)
{
    if(currentBitStatus == 0)       //指示灯
    {
        if(arg1 == "无")
            ui->UseLimitSubWidget->hide();
        else
        {
            ui->UseLimitSubWidget->show();
            ui->HideControlWhenNoRoot->show();
            ui->HideControlWhenNoRoot->setEnabled(false);
            ui->RecoverWhenFinishOPerator->hide();
            ui->ShowTipsWinWhenNoRoot->hide();
            ui->UserLimitTipsLabel->hide();
         }
    }
    else if(currentBitStatus == 1)
    {
        if(arg1 == "无")
        {
            ui->UseLimitSubWidget->hide();
        }
         else
        {
            ui->UseLimitSubWidget->show();
            ui->HideControlWhenNoRoot->setEnabled(true);
            ui->RecoverWhenFinishOPerator->show();
            ui->ShowTipsWinWhenNoRoot->show();
            ui->UserLimitTipsLabel->show();
        }
    }
}

void Dialog::on_MoreImageBtnLibrary_clicked()
{

}

//切换第0张图片
void Dialog::on_TurnOnWith0_clicked()
{

}

//切换第1张图片
void Dialog::on_TurnOnWith1_clicked()
{

}

//切换第2张图片
void Dialog::on_TurnOnWith2_clicked()
{

}

//切换第3张图片
void Dialog::on_TurnOnWith3_clicked()
{

}

//切换第4张图片
void Dialog::on_TurnOnWith4_clicked()
{

}

//切换第5张图片
void Dialog::on_TurnOnWith5_clicked()
{

}







void Dialog::on_GalleryButton_clicked()
{

}

//图片--复制当前配置
void Dialog::on_ImageCopyCurrentConfigure_clicked()
{

}


//图案--复制当前配置
void Dialog::on_PartternCopyCurrentConfigure_clicked()
{

}


void Dialog::on_UseVectorGraph_stateChanged(int arg1)
{
    if(arg1 == 2)
        ui->PartternGalleryButton->setEnabled(true);
    else if(arg1 == 0)
        ui->PartternGalleryButton->setEnabled(false);
}

void Dialog::on_UseImageCheckbox_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        if(currentBitStatus == 0 )
        {
            ui->ImageSizeLineEdit->setText("72x72");
            ui->ImageNameLineEdit->setText("Lamp-Standard");
        }
        else if(currentBitStatus == 1)
        {
            ui->ImageSizeLineEdit->setText("56x91");
            ui->ImageNameLineEdit->setText("SWITCH-Flat");
        }
        ui->ImageFromLineEdit->setText("SYSTEM");
        ui->GalleryButton->setEnabled(true);
        ui->UseImageOldSize->setEnabled(true);
        ui->ImageColorCombox->show();
        ui->ImageCopyCurrentConfigure->show();
    }
    else if(arg1 == 0)
    {
        ui->ImageNameLineEdit->setText("");
        ui->ImageFromLineEdit->setText("");
        ui->ImageSizeLineEdit->setText("");
        ui->GalleryButton->setEnabled(false);
        ui->UseImageOldSize->setEnabled(false);
        ui->ImageColorCombox->hide();
        ui->ImageCopyCurrentConfigure->hide();
    }
}

void Dialog::on_InnerCheckBox_stateChanged(int arg1)
{
    if(ui->OutsideCheckBox->checkState() == Qt::Checked)     //如果外框被选中
    {
        if(arg1== 2)
            ui->InnerColorCombox->show();
        else if(arg1 == 0)
            ui->InnerColorCombox->hide();
    }
    else if(ui->OutsideCheckBox->checkState() == Qt::Unchecked)
    {
        ui->InnerCheckBox->setChecked(true);        //如果外框没选中，则内框必须被选中
        ui->InnerColorCombox->show();
    }
}

void Dialog::on_OutsideCheckBox_stateChanged(int arg1)
{
    if(ui->InnerCheckBox->checkState() == Qt::Checked)     //如果外框被选中
    {
        if(arg1== 2)
            ui->OutsideColorCombox->show();
        else if(arg1 == 0)
            ui->OutsideColorCombox->hide();
    }
    else if(ui->InnerCheckBox->checkState() == Qt::Unchecked)
    {
        ui->OutsideCheckBox->setChecked(true);        //如果外框没选中，则内框必须被选中
        ui->OutsideColorCombox->show();
    }
}

void Dialog::on_InnerCheckBox_clicked()
{
    if(ui->OutsideCheckBox->checkState() == Qt::Unchecked)
    {
        ui->InnerCheckBox->setChecked(true);        //如果外框没选中，则内框必须被选中
        ui->InnerColorCombox->show();
    }
}

void Dialog::on_OutsideCheckBox_clicked()
{
    if(ui->InnerCheckBox->checkState() == Qt::Unchecked)
    {
        ui->OutsideCheckBox->setChecked(true);        //如果外框没选中，则内框必须被选中
        ui->OutsideColorCombox->show();
    }
}

void Dialog::on_BitStatusTagFlashSpeedSlider_valueChanged(int value)
{
    ui->BitStatusTagFlashSpeedSpin->setValue(value);
}

void Dialog::on_BitStatusTagFlashSpeedSpin_valueChanged(int arg1)
{
    ui->BitStatusTagFlashSpeedSlider->setValue(arg1);
}

void Dialog::on_TextLibraryButton_clicked()
{
    btnWdg->showIndexWidget(TextLibraryPage);
    btnWdg->exec();
}

void Dialog::on_StatusPreviousButton_clicked()
{
    int currentIndex = ui->StatusIndexCombox->currentIndex();
    if(currentIndex>0)
    {
        ui->StatusIndexCombox->setCurrentIndex(currentIndex-1);
    }

    currentIndex = ui->StatusIndexCombox->currentIndex();
    if(currentIndex == 0)
    {
        ui->StatusPreviousButton->setEnabled(false);
        ui->StatusNextButton->setEnabled(true);
    }
    else if(currentIndex == ui->StatusIndexCombox->count()-1 )
    {
        ui->StatusPreviousButton->setEnabled(true);
        ui->StatusNextButton->setEnabled(false);
    }
}

void Dialog::on_StatusNextButton_clicked()
{
    int currentIndex = ui->StatusIndexCombox->currentIndex();
    if(currentIndex < ui->StatusIndexCombox->count()-1)
    {
        ui->StatusIndexCombox->setCurrentIndex(currentIndex+1);
    }
    currentIndex = ui->StatusIndexCombox->currentIndex();
    if(currentIndex == 0)
    {
        ui->StatusPreviousButton->setEnabled(false);
        ui->StatusNextButton->setEnabled(true);
    }
    else if(currentIndex == ui->StatusIndexCombox->count()-1 )
    {
        ui->StatusPreviousButton->setEnabled(true);
        ui->StatusNextButton->setEnabled(false);
    }
}

void Dialog::on_StatusOneButton_clicked()
{
    ui->StatusIndexCombox->setCurrentIndex(0);
}

void Dialog::on_StatusTwoButton_clicked()
{
    ui->StatusIndexCombox->setCurrentIndex(1);
}

void Dialog::on_MultStatusReadWriteCheck_stateChanged(int arg1)
{
    if(arg1 == 2)           //选中
    {
        ui->MultStatusReadAddrGroup->setTitle("读取地址");
        ui->MultStatusWriteAddrGroup->show();
        ui->MultStatusWriteAddrGroup->setTitle("写入地址");
        ui->MultStatusWriteSubWidget->show();
    }
    else if(arg1 == 0)      //未选中
    {
        ui->MultStatusReadAddrGroup->setTitle("读取/写入地址");
        ui->MultStatusWriteAddrGroup->show();
        ui->MultStatusWriteAddrGroup->setTitle("");
        ui->MultStatusWriteSubWidget->hide();
    }
}


//决定模式数量
void Dialog::on_MultStatusNumberCombox_currentIndexChanged(int index)
{

    ui->StatusIndexCombox->clear();
    int currentIndex = ui->MultStatusNumberCombox->currentText().toInt();
    initNumberComBox(ui->StatusIndexCombox,0,currentIndex);

    if(index >= 6)
    {
        ui->TurnOnWith0->show();
        ui->TurnOnWith1->show();
        ui->TurnOnWith2->show();
        ui->TurnOnWith3->show();
        ui->TurnOnWith4->show();
        ui->TurnOnWith5->show();
    }
    else if(index == 0)
    {
        ui->TurnOnWith0->show();
        ui->TurnOnWith1->hide();
        ui->TurnOnWith2->hide();
        ui->TurnOnWith3->hide();
        ui->TurnOnWith4->hide();
        ui->TurnOnWith5->hide();

        ui->StatusOneButton->show();
        ui->StatusTwoButton->hide();
        ui->StatusThreeButton->hide();
        ui->StatusFourButton->hide();
    }
    else if(index == 1)
    {
        ui->TurnOnWith0->show();
        ui->TurnOnWith1->show();
        ui->TurnOnWith2->hide();
        ui->TurnOnWith3->hide();
        ui->TurnOnWith4->hide();
        ui->TurnOnWith5->hide();

        ui->StatusOneButton->show();
        ui->StatusTwoButton->show();
        ui->StatusThreeButton->hide();
        ui->StatusFourButton->hide();
    }
    else if(index == 2)
    {
        ui->TurnOnWith0->show();
        ui->TurnOnWith1->show();
        ui->TurnOnWith2->show();
        ui->TurnOnWith3->hide();
        ui->TurnOnWith4->hide();
        ui->TurnOnWith5->hide();

        ui->StatusOneButton->show();
        ui->StatusTwoButton->show();
        ui->StatusThreeButton->show();
        ui->StatusFourButton->hide();

    }
    else if(index == 3)
    {
        ui->TurnOnWith0->show();
        ui->TurnOnWith1->show();
        ui->TurnOnWith2->show();
        ui->TurnOnWith3->show();
        ui->TurnOnWith4->hide();
        ui->TurnOnWith5->hide();

        ui->StatusOneButton->show();
        ui->StatusTwoButton->show();
        ui->StatusThreeButton->show();
        ui->StatusFourButton->show();
    }
    else if(index == 4)
    {
        ui->TurnOnWith0->show();
        ui->TurnOnWith1->show();
        ui->TurnOnWith2->show();
        ui->TurnOnWith3->show();
        ui->TurnOnWith4->show();
        ui->TurnOnWith5->hide();
    }
    else if(index == 5)
    {
        ui->TurnOnWith0->show();
        ui->TurnOnWith1->show();
        ui->TurnOnWith2->show();
        ui->TurnOnWith3->show();
        ui->TurnOnWith4->show();
        ui->TurnOnWith5->show();
    }

}

void Dialog::on_MoveGridButton_clicked()
{
    ui->SystemParameterStackWidget->setCurrentIndex(7);
}

void Dialog::on_PrintBackupsServiceButton_clicked()
{
    ui->SystemParameterStackWidget->setCurrentIndex(8);
}

void Dialog::on_TimeSynButton_clicked()
{
    ui->SystemParameterStackWidget->setCurrentIndex(9);
}

void Dialog::on_EmailButton_clicked()
{
    ui->SystemParameterStackWidget->setCurrentIndex(10);
}

void Dialog::on_FormulaDataBaseButton_clicked()
{
    ui->SystemParameterStackWidget->setCurrentIndex(11);
}

void Dialog::on_DevicePageButton_clicked()
{
    ui->SystemParameterStackWidget->setCurrentIndex(0);
}

void Dialog::on_HMIPropertyButton_clicked()
{
    ui->SystemParameterStackWidget->setCurrentIndex(1);
}

void Dialog::on_GeneralPropertyButton_clicked()
{
    ui->SystemParameterStackWidget->setCurrentIndex(2);
}

void Dialog::on_SystemSettingButton_clicked()
{
    ui->SystemParameterStackWidget->setCurrentIndex(3);
}

void Dialog::on_RemoteButton_clicked()
{
    ui->SystemParameterStackWidget->setCurrentIndex(4);
}

void Dialog::on_UsePasswordButton_clicked()
{
    ui->SystemParameterStackWidget->setCurrentIndex(5);
}

void Dialog::on_ExtendMemoryButton_clicked()
{
    ui->SystemParameterStackWidget->setCurrentIndex(6);
}

void Dialog::on_addNewHMIDevice_clicked()
{
    qDebug()<<"系统参数界面的新增HMI按钮";
    subDlg->showSubDialog(AddNewHMIDevicePage);
    if(subDlg->exec() == QDialog::Accepted)
    {

    }
}

void Dialog::on_addNewDevice_clicked()
{
    qDebug()<<"系统参数界面的新增设备按钮";
    subDlg->showSubDialog(AddNewDeivceSubPage);
    if(subDlg->exec() == QDialog::Accepted)
    {
        QString deviceName,name,position,deviceType,screenType,commProtocal,stationID;
        subDlg->getDeivceProperty(deviceName,name,position,deviceType,screenType,commProtocal,stationID);
        //判断设备名称是否存在
        QMap<int,DevProperty>::iterator iter = devData.begin();
        for(iter;iter!=devData.end();++iter)
        {
            if(name == iter.value().getDevName())
            {
                QMessageBox::warning(NULL,"提示","设备["+name+"]已经存在",QMessageBox::Yes);
                return;
            }
        }
        deviceName = deviceName+" "+ screenType.mid(4,1);

        //设置界面已使用的协议标注为不可在使用
        QString text = screenType.mid(0,5);
        subDlg->setWidgetInfoDisable(text);

        //保存设备信息
        DevProperty dev;
        dev.setDevFull(deviceName);
        dev.setDevName(name);
        dev.setDevLoca(position);
        dev.setDevType(deviceType);
        dev.setDevScre(screenType);
        dev.setDevProt(commProtocal);
        dev.setDevStID(stationID);
        int row = ui->SystemParameterDevTable->rowCount();
        devData.insert(row,dev);

        //不存在，则将数据插入到表格中
        ui->SystemParameterDevTable->insertRow(row);
        ui->SystemParameterDevTable->setItem(row,0,new QTableWidgetItem(deviceName));
        ui->SystemParameterDevTable->item(row,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
        ui->SystemParameterDevTable->setItem(row,1,new QTableWidgetItem(name));
        ui->SystemParameterDevTable->item(row,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
        ui->SystemParameterDevTable->setItem(row,2,new QTableWidgetItem(position));
        ui->SystemParameterDevTable->item(row,2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
        ui->SystemParameterDevTable->setItem(row,3,new QTableWidgetItem(deviceType));
        ui->SystemParameterDevTable->item(row,3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
        ui->SystemParameterDevTable->setItem(row,4,new QTableWidgetItem(screenType));
        ui->SystemParameterDevTable->item(row,4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
        ui->SystemParameterDevTable->setItem(row,5,new QTableWidgetItem(commProtocal));
        ui->SystemParameterDevTable->item(row,5)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
        ui->SystemParameterDevTable->setItem(row,6,new QTableWidgetItem(stationID));
        ui->SystemParameterDevTable->item(row,6)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    }
}

void Dialog::on_DeleteDevTableItem_clicked()
{
    qDebug()<<"系统参数界面的删除第"<<currentDevRow<<"  行";
    ui->SystemParameterDevTable->removeRow(currentDevRow);
    //将devData中的对应数据删除
   QMap<int,DevProperty>::iterator iter = devData.begin();
   for(iter;iter!=devData.end();++iter)
   {
       if(iter.key() == currentDevRow)
       {
           devData.erase(iter);
           break;
       }
   }
   QMap<int,DevProperty> tempDevData;
   for(iter = devData.begin();iter!=devData.end();)
   {
       if(iter.key() > currentDevRow) //将后面的数据重新调整key值
       {
           DevProperty dev;
           dev.setDevFull(iter.value().getDevFull());
           dev.setDevLoca(iter.value().getDevLoca());
           dev.setDevName(iter.value().getDevName());
           dev.setDevProt(iter.value().getDevProt());
           dev.setDevScre(iter.value().getDevScre());
           dev.setDevStID(iter.value().getDevStID());
           dev.setDevType(iter.value().getDevType());
           tempDevData.insert(iter.key()-1,dev);
           iter = devData.erase(iter);
       }
       else
           iter++;
   }
   QMap<int,DevProperty>::iterator it = tempDevData.begin();
   for(it;it!=tempDevData.end();++it)
   {
       devData.insert(it.key(),it.value());
   }
}

void Dialog::on_ProtectOrSetting_clicked()
{
    qDebug()<<"系统参数界面的保护/设置按钮";
    DevProperty tempPro = devData.value(currentDevRow);

    subDlg->showSubDialog(AddNewDeivceSubPage);
    subDlg->setCurrentDevPro(tempPro);
    subDlg->setAddNewDeviceFalg(false);
    if(subDlg->exec() == QDialog::Accepted)
    {
        DevProperty dev;
        dev = devData.value(currentDevRow);

        QString deviceName,name,position,deviceType,screenType,commProtocal,stationID;
        subDlg->getDeivceProperty(deviceName,name,position,deviceType,screenType,commProtocal,stationID);
        //判断设备名称是否存在
        if(name != dev.getDevName())
        {
            QMap<int,DevProperty>::iterator iter = devData.begin();
            for(iter;iter!=devData.end();++iter)
            {
                if(name == iter.value().getDevName())
                {
                    QMessageBox::warning(NULL,"提示","设备["+name+"]已经存在",QMessageBox::Yes);
                    return;
                }
            }
        }

        deviceName = deviceName+" "+ screenType.mid(4,1);

        //设置界面已使用的协议标注为不可再使用
        QString text = screenType.mid(0,5);
        subDlg->setWidgetInfoDisable(text);

        //修改之前保存的设备信息
        dev.setDevFull(deviceName);
        dev.setDevName(name);
        dev.setDevLoca(position);
        dev.setDevType(deviceType);
        dev.setDevScre(screenType);
        dev.setDevProt(commProtocal);
        dev.setDevStID(stationID);
        devData.insert(currentDevRow,dev);

        qDebug()<<"要修改的信息是第："<<currentDevRow<<" 行";
        ui->SystemParameterDevTable->item(currentDevRow,0)->setText(deviceName);
        ui->SystemParameterDevTable->item(currentDevRow,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
        ui->SystemParameterDevTable->item(currentDevRow,1)->setText(name);
        ui->SystemParameterDevTable->item(currentDevRow,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
        ui->SystemParameterDevTable->item(currentDevRow,2)->setText(position);
        ui->SystemParameterDevTable->item(currentDevRow,2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
        ui->SystemParameterDevTable->item(currentDevRow,3)->setText(deviceType);
        ui->SystemParameterDevTable->item(currentDevRow,3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
        ui->SystemParameterDevTable->item(currentDevRow,4)->setText(screenType);
        ui->SystemParameterDevTable->item(currentDevRow,4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
        ui->SystemParameterDevTable->item(currentDevRow,5)->setText(commProtocal);
        ui->SystemParameterDevTable->item(currentDevRow,5)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
        ui->SystemParameterDevTable->item(currentDevRow,6)->setText(stationID);
        ui->SystemParameterDevTable->item(currentDevRow,6)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    }
}



void Dialog::on_ClockFromCombox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "外部设备")
        ui->ClockSubWidget->show();
    else
        ui->ClockSubWidget->hide();
}

void Dialog::on_ClockType_currentTextChanged(const QString &arg1)
{
    qDebug()<<"the arg1 is : 0"<<arg1;
    ui->HMIPopertySubStackWidget->show();
    bool flag = false;
    bool isBit = false;
    bool isHidden = false;
    bool isTipsFlag = false;
    bool isRowSpacing = false;
    bool isMeetHidden = false;
    if(arg1 == "HP PCL  系列(USB)")
    {
        ui->HMIPopertySubStackWidget->show();
        ui->HMIPopertySubStackWidget->setCurrentIndex(0);
        flag = true;
        isBit = false;
        isHidden = false;
        isTipsFlag = true;
        isRowSpacing = true;
        isMeetHidden = true;
    }
    else if(arg1 == "EPSON ESC/P2 系列" || arg1 == "Axiohm A630")
    {
       ui->HMIPopertySubStackWidget->setCurrentIndex(1);
       isBit = true;
       flag = true;
       isTipsFlag = true;
       isHidden = false;
       isRowSpacing = true;
       isMeetHidden = true;
    }
    else if(arg1 == "START(SP-DIII,DIV,D5,D6,A,DN,T)")
    {
        ui->HMIPopertySubStackWidget->setCurrentIndex(1);
        isBit = true;
        flag = false;
        isTipsFlag = true;
        isHidden = false;
        isRowSpacing = true;
        isMeetHidden = true;
    }
    else if(arg1 == "SP-M,D,E,F")
    {
        ui->HMIPopertySubStackWidget->setCurrentIndex(1);
        isBit = true;
        flag = false;
        isTipsFlag = false;
        isHidden = false;
        isRowSpacing = true;
        isMeetHidden = true;
    }
    else if(arg1 == "EPSON TM-L90")
    {
        ui->HMIPopertySubStackWidget->setCurrentIndex(1);
        isBit = true;
        flag = false;
        isTipsFlag = true;
        isHidden = false;
        isRowSpacing = false;
        isMeetHidden = true;
    }
    else if(arg1 == "EPSON TM-T70")
    {
        ui->HMIPopertySubStackWidget->setCurrentIndex(1);
        isBit = true;
        flag = false;
        isTipsFlag = true;
        isHidden = false;
        isRowSpacing = false;
        isMeetHidden = false;
    }
    else if(arg1 == "BRIGHTEK WH-E19")
    {
        ui->HMIPopertySubStackWidget->setCurrentIndex(1);
        isBit = true;
        flag = true;
        isTipsFlag = true;
        isHidden = false;
        isRowSpacing = true;
        isMeetHidden = true;
    }
    else if(arg1 == "BRIGHTEK WH-C1/C2")
    {
        ui->HMIPopertySubStackWidget->setCurrentIndex(1);
        isBit = true;
        flag = true;
        isTipsFlag = true;
        isHidden = false;
        isRowSpacing = true;
        isMeetHidden = false;
    }
    ui->OnlySupportUSBLabel->setHidden(isBit);
    ui->ClockWidth->setHidden(flag);
    ui->WidthLabel->setHidden(flag);
    ui->PixelLabel->setHidden(flag);
    ui->PixelTipsLabel->setHidden(isTipsFlag);
    ui->ScreenCaptureRatio->setHidden(isHidden);
    ui->ScreenCaptureLabel->setHidden(isHidden);
    ui->RowSpacingAfterSwitch->setHidden(isRowSpacing);
    ui->RowSapceingNumber->setHidden(isRowSpacing);
    ui->MeetType->setHidden(isMeetHidden);
}

void Dialog::on_PrsetStyleSheet_currentIndexChanged(int index)
{

}

void Dialog::on_DirectLoginWithoutPassword_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->ConfigurePasswordFromProFile->show();
    }
    else
    {
        ui->ConfigurePasswordFromProFile->hide();
    }
}

void Dialog::on_EditUserPassword_clicked()
{
    subDlg->showSubDialog(ConfigureReadOnly);
    if(subDlg->exec() == QDialog::Rejected)
        return;
    QString password;
    int isHidden ;
    subDlg->getConfigurePassword(password,isHidden);
}

//系统参数--用户密码 --状态地址
void Dialog::on_StateAdderConfigreBtn_clicked()
{
    subDlg->setWidgetCaller("SystemParameter");
    configureLWWidget(false,false,true,false,true);
}
//系统参数 --用户密码--控制地址
void Dialog::on_ControlAddrConfigureBtn_clicked()
{
    configureLWWidget(false,false,false,false,true,false);
}

//打开联系人设置
void Dialog::on_OpenContactsConfig_clicked()
{
    btnWdg->showIndexWidget(ContactsConfigPage);
    btnWdg->exec();
}

//配方数据库--新增条目
void Dialog::on_addFormulaItem_clicked()
{
    int row = ui->FormulaListWidget->count();
    QListWidgetItem *item = new QListWidgetItem(ui->FormulaListWidget,0);
    QWidget *itemWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    QLineEdit *itemText = new QLineEdit;
    QLabel *index = new QLabel;

    itemText->setStyleSheet("border:none;");            //没有边框
    itemText->setProperty("listRow",ui->FormulaListWidget->count());
    connect(itemText,SIGNAL(editingFinished()),this,SLOT(doLineEditTextChanged()));
    layout->addWidget(index);
    layout->addWidget(itemText);
    layout->addStretch();
    layout->setMargin(0);
    itemWidget->setLayout(layout);
    ui->FormulaListWidget->setItemWidget(item,itemWidget);
    itemWidget->show();
    if(row == 0)
        itemText->setText("new");
    else
        itemText->setText("new"+QString::number(row));
    int count = ui->FormulaListWidget->count();
    index->setText(QString::number(count)+".");
}

//配方数据--删除条目
void Dialog::on_deleteFormulaItem_clicked()
{
    if(formulaListRow != -1)
    {
        if(formulaListRow == ui->FormulaListWidget->count())
        {
            formulaListRow -= 1;
        }
        QListWidgetItem* item= ui->FormulaListWidget->item(formulaListRow);
        QObject* obj = ui->FormulaListWidget->itemWidget(item)->children().at(2);
        QString formulaName = ((QLineEdit*)(obj))->text();

        ui->FormulaListWidget->removeItemWidget(ui->FormulaListWidget->item(formulaListRow));
        ui->FormulaListWidget->takeItem(formulaListRow);            //删除某一行
        //调整剩下的数据中的序号
        if(formulaListRow != 0)
        {
            for(int i= formulaListRow-1;i<ui->FormulaListWidget->count();i++)
            {
              qDebug()<<"the i is: "<<i;
              ((QLabel*)(ui->FormulaListWidget->itemWidget(ui->FormulaListWidget->item(i))->children().at(1)))->setText(QString::number(i+1)+".");
            }
        }

        //删除右侧表中的所有数据
        for(int i= dataModel->rowCount()-1;i>= 0;i--)
        {
            dataModel->removeRow(i);
        }

        //从m_allData中删除对应配方的数据
        QMap<QString,QVector<FormulaItem>>::iterator iter = m_allData.find(formulaName);
        if(iter!=m_allData.end())
        {
          m_allData.erase(iter);
        }
    }
}

//配方数据库--导入
void Dialog::on_importDataBaseFile_clicked()
{

}

//配方数据库--导出
void Dialog::on_exportDataBaseFile_clicked()
{

}

//配方数据库右侧表--新增条目
void Dialog::on_AddNewItem_clicked()
{
    QListWidgetItem* item = ui->FormulaListWidget->currentItem();
    QString formulaIndexStr = ((QLabel*)(ui->FormulaListWidget->itemWidget(item)->children().at(1)))->text();
    if(ui->FormulaListWidget->count() == 0)
    {
        qDebug()<<"不存在对应的配方名称";
        return;
    }

    isNewAddItem = true;
    int row = dataModel->rowCount();
    QString textStr;
    if(row!= 0)
       textStr = "newItem"+QString::number(row);
    else
       textStr = "newItem";
    dataModel->insertRow(dataModel->rowCount());
    dataModel->setData(dataModel->index(row,0,QModelIndex()),textStr);
    dataModel->item(row,0)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    dataModel->setData(dataModel->index(row,1,QModelIndex()),QVariant("16-bit BCD"));
    dataModel->item(row,1)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    dataModel->setData(dataModel->index(row,2,QModelIndex()),QVariant("1"));
    dataModel->item(row,2)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    dataModel->setData(dataModel->index(row,3,QModelIndex()),QVariant("5"));
    dataModel->item(row,3)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    dataModel->setData(dataModel->index(row,4,QModelIndex()),QVariant("0"));
    dataModel->item(row,4)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    dataModel->setData(dataModel->index(row,5,QModelIndex()),QVariant("左对齐"));
    dataModel->item(row,5)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    ui->DatabaseTableView->show();
    if(dataModel->rowCount() > 0)
    {
        ui->deleteOneItem->setEnabled(true);
        ui->ConfigureTableView->setEnabled(true);
    }

    FormulaItem itemSt;
    itemSt.row = row;           //数据表中的行号
    itemSt.proName = textStr;
    itemSt.dataType = "16-bit BCD";
    itemSt.size = "1";
    itemSt.pointNumber = "0";
    itemSt.showWidth = "5";
    itemSt.alignType = "左对齐";

    QVector<FormulaItem>  vec;
    vec.push_back(itemSt);

     QString formulaStr = ((QLineEdit*)(ui->FormulaListWidget->itemWidget(item)->children().at(2)))->text();
    if(!m_allData.contains(formulaStr))
    {
        m_allData.insert(formulaStr,vec);
    }
    else
    {
        QVector<FormulaItem>  tempVec = m_allData.value(formulaStr);
        tempVec.push_back(itemSt);
        m_allData.insert(formulaStr,tempVec);
     }
    isNewAddItem = false;
}

//配方数据库右侧表--删除条目
void Dialog::on_deleteOneItem_clicked()
{
    if(currentFormulaRow != -1)
    {
        dataModel->removeRow(currentFormulaRow);
        if(dataModel->rowCount()  == 0)
        {
            ui->deleteOneItem->setEnabled(false);
            ui->ConfigureTableView->setEnabled(false);
        }
    }
}

//配方数据库右侧表--配置条目
void Dialog::on_ConfigureTableView_clicked()
{
    int row = ui->DatabaseTableView->currentIndex().row();
    QListWidgetItem* item= ui->FormulaListWidget->item(formulaListRow);
    QObject* obj = ui->FormulaListWidget->itemWidget(item)->children().at(2);
    QString formulaName = ((QLineEdit*)(obj))->text();

    FormulaItem *formulaItem;
    QVector<FormulaItem> tempVec = m_allData.value(formulaName);
    for(QVector<FormulaItem>::iterator iter = tempVec.begin();iter!=tempVec.end();++iter)
    {
        if(iter->row == row)
        {
            formulaItem = iter;
        }
    }
    subDlg->showSubDialog(FormulaDatabasePage);
    subDlg->setDataBasePage(formulaItem);  
    subDlg->getDataBaseResult(*formulaItem);
    if(subDlg->exec() == QDialog::Rejected)
        return;
    int resetRow = formulaItem->row;
    qDebug()<<"配置的数据是第： "<<resetRow<<" 行";
    dataModel->setData(dataModel->index(resetRow,0),formulaItem->proName);
    dataModel->setData(dataModel->index(resetRow,1),formulaItem->dataType);
    dataModel->setData(dataModel->index(resetRow,2),formulaItem->size);
    dataModel->setData(dataModel->index(resetRow,3),formulaItem->showWidth);
    dataModel->setData(dataModel->index(resetRow,4),formulaItem->pointNumber);
    dataModel->setData(dataModel->index(resetRow,5),formulaItem->alignType);
}


