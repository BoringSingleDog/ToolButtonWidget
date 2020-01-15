#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QColorDialog>
#include <QFontDatabase>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QTime>


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
    initColorChooseComBox(PieChartBorderColor,PieChartBorderLineEdit,ui->PieChartBorderColor);

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

bool Dialog::eventFilter(QObject *obj, QEvent *event)
{
     return QDialog::eventFilter(obj,event);
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
void Dialog::on_PieChartFontColor_currentIndexChanged(int )
{
    update();
}

//更改指定通道上背景颜色
void Dialog::on_PieChartPaPatternCombox_currentIndexChanged(int )
{
    update();
}

//更换指定通道上的背景样式
void Dialog::on_comboBox_15_currentIndexChanged(int )
{
    update();
}

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
