#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QColorDialog>
#include <QFontDatabase>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QTime>
#include <QVBoxLayout>
#include <QListWidget>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    subDlg = new subDialog;
    setWindowTitle(QStringLiteral("新增 滑动开关 原件"));
    ui->ElementPropertyTab->removeTab(1);
    initWindowPage();
    initControlCode();
    initSliderSwitchPage();
    initProjectMenuPage();
    initValueItemPage();
    initCharaItemPage();
    initPieCharacterPage();
    initDynamicClibrationPage();
    initDataGroupPage();
    initXYCurveImagePage();
    initWatchNeedlePage();
    initMoveGraphicalPage();
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
        ui->generalProStack->setCurrentIndex(1);
        setWindowTitle("新增 位状态指示灯/位状态切换开关 元件");
        break;
    case MultStatsPointLight:
        ui->generalProStack->setCurrentIndex(0);
        ui->MultStatusLightRadio->setChecked(true);
        initMultStatusLightPage();
        setWindowTitle("新增 多状态指示灯/多状态切换开关 元件");
        break;
    case BitStatusConfigure:
        ui->generalProStack->setCurrentIndex(2);
        setWindowTitle("新增 位状态设置 元件");
        break;
    case MultStatusConfigure:
        ui->generalProStack->setCurrentIndex(3);
        setWindowTitle("新增 多状态设置 元件");
        break;
    case BitStatusSelectSwitch:
        setWindowTitle("新增 位状态切换开关/位状态指示灯 元件");
        ui->generalProStack->setCurrentIndex(1);
        break;
    case MultStatusSelectSwitch:
        ui->MultStatusSwitchRadio->setChecked(true);
        initMultStatusSwitchPage();
        setWindowTitle("新增 多状态切换开关/多状态指示灯 元件");
        ui->generalProStack->setCurrentIndex(0);
        break;
    case FunctionKeyTool:
        setWindowTitle("新增 功能键 元件");
        initFuncKeyPage(0);
        ui->generalProStack->setCurrentIndex(4);
        break;
    case CompMultFuncButton:
        setWindowTitle("新增 复合式多功能 元件");
        ui->generalProStack->setCurrentIndex(5);
        break;
    case SliderSwitch:
        setWindowTitle("新增 滑动开关 元件");
        ui->generalProStack->setCurrentIndex(6);
        break;
    case ProjectChooseList:
        setWindowTitle("新增 项目选单 元件");
        ui->generalProStack->setCurrentIndex(7);
        break;
    case NumberShowButton:
        setWindowTitle("新增 数值 元件");
        ui->generalProStack->setCurrentIndex(8);
        break;
    case CharacterShowButton:
        setWindowTitle("新增 字符 元件");
        ui->generalProStack->setCurrentIndex(9);
        break;
    case PieChartItem:
        setWindowTitle("新增 圆饼图 元件");
        ui->generalProStack->setCurrentIndex(10);
        break;
    case DynamicClibration:
        setWindowTitle("新增 动态刻度 元件");
        ui->generalProStack->setCurrentIndex(11);
        break;
    case DataGroupItem:
        setWindowTitle("新增 数据群组 元件");
        ui->generalProStack->setCurrentIndex(12);
        break;
    case XYEllispImage:
        setWindowTitle("新增 XY曲线图 元件");
        ui->generalProStack->setCurrentIndex(13);
        break;
    case HistogramPage:
        setWindowTitle("新增 棒图 元件");
        ui->generalProStack->setCurrentIndex(14);
        break;
    case WatchNeedlePage:
        setWindowTitle("新增 表针 元件");
        ui->generalProStack->setCurrentIndex(15);
        break;
    case DynamicPainttingPage:
        setWindowTitle("新增 动态绘图 元件");
        ui->generalProStack->setCurrentIndex(16);
        break;
    case MoveGrapgicalPage:
        setWindowTitle("新增 移动图形 元件");
        ui->generalProStack->setCurrentIndex(17);
        break;
    case PLCControlPage:
        showPLCControlWidget();
        break;
    case IndirectWidgetPage:
        setWindowTitle("新增 间接窗口 元件");
        initIndirectWindowPage();
        ui->generalProStack->setCurrentIndex(18);
        break;
     case DirectWidgetPage:
        setWindowTitle("新增 直接窗口 元件");
        initDirectWidgetPage();
        ui->generalProStack->setCurrentIndex(19);
        break;
     case DataTransportPage:
        setWindowTitle("新增 数据资料传输窗口 元件");
        initDataTranportPage();
        ui->generalProStack->setCurrentIndex(20);
        break;
     case DataTransportBackground:
        showDataTransBackground();
        break;
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

//隐藏多状态指示灯中部分控件来实现多状态切换开关页面
void Dialog::initMultStatusSwitchPage()
{
    ui->MultStatusReadAddrGroup->setTitle(QStringLiteral("读取/写入地址"));
    ui->MultStatusProperLabel->setText(QStringLiteral("使用状态设置"));
    ui->MultStatusWriteGroupBox->setTitle(QStringLiteral(" "));
    ui->MultStatusWriteSetButton->hide();
    ui->MultStatusWriteDev->hide();
    ui->MultStatusWriteAddr->hide();
    ui->MultStatusWriteAddrLabel->hide();
    ui->MultStatusWriteDevLabel->hide();
    ui->lineEdit_12->hide();
    ui->lineEdit_13->hide();
    ui->MultStatusSendGroup->show();

    ui->MultStatusReadWriteCheck->show();
    ui->MultStatusWriteGroupBox->show();
    ui->MultStatusOperatorModeCombox->show();
    ui->MultStatusOperatorLabel->show();
    ui->MultStatusCrycleLabel->show();
    ui->MultStatusCrycleCombox->show();
    ui->MultStatusSendCmdCheck->show();

}
//更改多状态指示灯中的部分控件
void Dialog::initMultStatusLightPage()
{
    ui->MultStatusReadAddrGroup->setTitle(QStringLiteral("读取地址"));
    ui->MultStatusProperLabel->setText(QStringLiteral("若当前状态无对应的图片时，不显示图片"));
    ui->MultStatusReadWriteCheck->hide();
    ui->MultStatusWriteGroupBox->hide();
    ui->MultStatusOperatorModeCombox->hide();
    ui->MultStatusOperatorLabel->hide();
    ui->MultStatusCrycleLabel->hide();
    ui->MultStatusCrycleCombox->hide();
    ui->MultStatusSendCmdCheck->hide();
    ui->MultStatusSendGroup->hide();
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
    QFontDatabase fontBase;
    QStringList fontList = fontBase.families();
    foreach (QString fontStr, fontList)
    {
        ui->PieChartFontComBox->addItem(fontStr);
        ui->PieChartFontComBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
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
    for(int i=startValue; i <= endValue;i++)
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
    PieChartPatternStyle->setMinimumSize(QSize(400,700));
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
    for(int i=1;i<=100;i++)
    {
        ui->MainScaleCombox->addItem(QString::number(i));
        ui->viceScaleCombox->addItem(QString::number(i));
    }

    for(int i=5;i<=255;i++)
        ui->ScaleChartSizeCombox->addItem(QString::number(i));

    QFontDatabase fontBase;
    QStringList fontNames = fontBase.families();

    for(int i=0;i<fontNames.size();i++)
    {
        ui->ScaleChartFontCombox->addItem(fontNames.at(i));
    }


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
    QFontDatabase fontBase;
    QStringList fontList = fontBase.families();
    foreach (QString fontStr, fontList)
    {
        ui->WatchNeedlFontCombox->addItem(fontStr);
        ui->WatchNeedlFontCombox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
    ui->WatchNeedlFontCombox->setCurrentIndex(0);

    //字体颜色
    WatchNeedleFontColor = new QTableWidget(8,8);
    WatchNeedleFontColor->setProperty("tableName","WatchNeedleFontColor");
    WatchNeedleFontLineEdit = new QLineEdit();
    initColorChooseComBox(WatchNeedleFontColor,WatchNeedleFontLineEdit,ui->WatchNedlFontColor);

    //字体大小
    for(int i=5;i<=255;i++)
    {
        ui->WatchNeedleFontSizeCombox->addItem(QString::number(i));
    }



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
    ui->ConfigureSwitchSubWidget_2->hide();
    ui->DataTransportAddrSubWidget_2->hide();
    establishConnectRelation(ui->DataTransportEnableCheckBox_2,ui->ConfigureSwitchSubWidget_2);
    establishConnectRelation(ui->DataTransportEnableCheckBox_2,ui->DataTransportAddrSubWidget_2);
}

void Dialog::establishConnectRelation(QCheckBox *checkbox, QWidget *widget)
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
    subDlg->exec();

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
    ui->generalProStack->setCurrentIndex(21);
    initDataTransBackground();
    this->show();
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
    dialog->setFixedSize(QSize(700,600));
    TransBackground = new QListWidget();
    TransBackground->addItem("1：[local HMI：RW-300]->[local HMI:RW-300],模式：字，频率=3.0秒，传输数据大小=1字");

    QHBoxLayout *hLayout = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout();

    QTabWidget  *tabWidget = new QTabWidget();
    tabWidget->addTab(TransBackground,"定时式");

    QPushButton *addButton = new QPushButton("新增");
    QPushButton *deleteButton = new QPushButton("删除");
    QPushButton *settingButton = new QPushButton("设置");
    QPushButton *closeButton = new QPushButton("关闭");


    connect(closeButton,&QPushButton::clicked,dialog,&QDialog::close);
    connect(addButton,&QPushButton::clicked,this,&Dialog::doShowDataTransBackground);


    hLayout->addWidget(addButton);
    hLayout->addWidget(deleteButton);
    hLayout->addWidget(settingButton);
    hLayout->addStretch();
    hLayout->addWidget(closeButton);

    vLayout->addWidget(tabWidget);
    vLayout->addLayout(hLayout);

    dialog->setLayout(vLayout);
    dialog->show();
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

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{

}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{

}

void Dialog::on_BitStatusLightRadio_clicked()
{
     ui->BitStatusSubWidget->setCurrentIndex(0);
}

void Dialog::on_BitStatusSwitRadio_clicked()
{
    ui->BitStatusSubWidget->setCurrentIndex(1);
}

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
     subDlg->show();
}

void Dialog::on_XYCurveControlAddrSettingBtn_clicked()
{
    subDlg->showSubDialog(AddressSubDialogPage);
    subDlg->show();
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
    subDlg->showSubDialog(WatchNeedleAddrPage);
    subDlg->show();
}

void Dialog::on_BarGraphControlSettingBtn_clicked()
{
    subDlg->setWidgetCaller("BarGraph");
    subDlg->showSubDialog(WatchNeedleAddrPage);
    subDlg->show();
}

void Dialog::on_ClearAddrSetting_clicked()
{
    subDlg->setWidgetCaller("DynamicPaint");
    subDlg->showSubDialog(WatchNeedleAddrPage);
    subDlg->show();
}

void Dialog::on_MoreInformation1_clicked()
{
    subDlg->setWidgetCaller("DynamicPaint");
    subDlg->showSubDialog(MoreInformationOne);
    subDlg->show();
}

void Dialog::on_MoreInfomation2_clicked()
{
    subDlg->setWidgetCaller("DynamicPaint");
    subDlg->showSubDialog(MoreInformationTwo);
    subDlg->show();
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
    subDlg->show();
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
