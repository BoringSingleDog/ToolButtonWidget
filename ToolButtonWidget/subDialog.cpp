#include "subDialog.h"
#include "ui_subDialog.h"
#include <QDebug>
#include <QMessageBox>

subDialog::subDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::subDialog)
{

    ui->setupUi(this);
    //this->setWindowFlags(Qt::Window|Qt::WindowStaysOnTopHint);
    this->setModal(true);
    configDlg = new ConfigDialog(this);
    btnWdg = new BtnWidget(this);
    connect(btnWdg,SIGNAL(listItemChanged(int)),this,SLOT(doListItemChanged(int)));
    initWidgetControl();
}

subDialog::~subDialog()
{
    delete ui;
}

void subDialog::showSubDialog(subWidgetType type)
{
    switch(type)
    {
        case PartternRotateSettting:
            ui->stackedWidget->setCurrentIndex(0);
            break;
        case XYCuroveUseInformation:
            this->setWindowTitle("地址使用方式");
            ui->AddrTagBaseBtn->show();
            ui->stackedWidget->setCurrentIndex(1);
            break;      
        case WatchNeedleAddrPage:
            initWatchNeedlePage();
            this->setWindowTitle("地址");
            this->setFixedSize(QSize(585,400));
            ui->IndexRegisterCheckbox_2->setChecked(true);
            ui->AddrTagBaseBtn->show();
            ui->stackedWidget->setCurrentIndex(2);
            break;
       case MoreInformationOne:
            this->setWindowTitle("箭头/形状样式");
            ui->AddrTagBaseBtn->hide();
            ui->stackedWidget->setCurrentIndex(3);
            break;
       case MoreInformationTwo:
            this->setWindowTitle("线/填充样式");
            ui->AddrTagBaseBtn->hide();
            ui->stackedWidget->setCurrentIndex(4);
            break;
       case MoveGraphLimitValueDesc:
            this->setWindowTitle("地址使用方式");
            ui->AddrTagBaseBtn->hide();
            ui->stackedWidget->setCurrentIndex(5);
            break;
       case PLCControlSubWidget:
            this->setWindowTitle("PLC控制");
            initPLCControlSubPage();
            ui->stackedWidget->setCurrentIndex(6);
            break;
       case ConfigureReadOnly:
            this->setWindowTitle("只读设置");
            ui->AddrTagBaseBtn->hide();
            ui->EnableReadOnly->setCheckable(true);
            ui->stackedWidget->setCurrentIndex(7);
            this->setFixedSize(QSize(586,200));
            break;
       case FormulaDatabasePage:
            this->setWindowTitle("数据库配方");
            initDataBaseSubPage();
            ui->AddrTagBaseBtn->hide();
            ui->stackedWidget->setCurrentIndex(8);
            this->setFixedSize(QSize(589,400));
            break;
       case AddNewDeivceSubPage:
            this->setWindowTitle("设备属性");
            initNewDeicePropertyPage();
            ui->NewDeviceRadioBtn->setChecked(true);
            ui->AddrTagBaseBtn->hide();
            ui->stackedWidget->setCurrentIndex(9);
            break;
       case AddNewHMIDevicePage:
            this->setWindowTitle("设备属性");
            initNewDeicePropertyPage();
            initAddHMIDevicePage();
            ui->AddNewHMIDeviceRadio->setChecked(true) ;
            ui->AddrTagBaseBtn->hide();
            ui->stackedWidget->setCurrentIndex(9);
            break;
    }
}

void subDialog::getRotateParameter(int &ClockWise, int &startPos, int &endPos)
{
    if(ui->ClockWise->isChecked())
        ClockWise = 1;
    else
        ClockWise = 0;
    if(ui->wholeCircular->checkState() == Qt::Checked)
        endPos = -1;
    else
        endPos = ui->endLineEdit->text().toInt();
    startPos = ui->startLineEdit->text().toInt();
}

//参数1：控制类型
//参数2：是否勾选 【在指定窗口打开时才执行】； 0-勾选 1-未勾选
//参数3：执行的命令编号
//参数4：是否勾选【打开背光灯】 0-勾选，1-未勾选
//参数5：是否勾选【地址清零】  0-勾选，1-未勾选
//参数6：是否否选【窗口地址偏移】  0-勾选，1-未勾选
//参数7：窗口地址偏移 ID,
//参数8：设备类型； 0-local HMI ,1-MODBUS TCP/IP
//参数9：设备地址：3x,4x,4x-Double
//参数10：地址后紧跟的偏移地址数
void subDialog::getPLCChooseResult(QString &windowType, int &isExecCom, int &commandID, int &useBackLight, int &addClear, int &useWindIDShift, int &windowIDShift, QString &devType, QString &AddrType, int &addrNumber)
{
    windowType = ui->ControlTypeCombox->currentText();
    isExecCom = ui->ExecSpecialCommand->checkState();
    commandID = ui->CommanderCombox->currentText().split(".").first().toInt();
    useBackLight = ui->OpenBackGroundLight->checkState();
    addClear = ui->ClearAddrValueAfterSwitchPage->checkState();
    useWindIDShift = ui->UseWindowIDCheckBox->checkState();
    windowIDShift = ui->windowIDCombox->currentText().toInt();
    devType = ui->PLCAddrDevType->currentText();
    AddrType = ui->PLCAddrTypeCombox->currentText();
    addrNumber = ui->PLCADdrShiftLineEidt->text().toInt();

}

void subDialog::setAddrWidgetType(int bit)
{
    subAddrWidgetType = bit;
}

//参数1：字数量窗口是否显示
//参数2：地址提示窗口是否显示
//参数1：额外索引窗口是否显示
//参数1：系统寄存器窗口是否显示
//参数1：用户自定义标签窗口是否显示

void subDialog::setSubControlEnable(bool wordCombox, bool addTips, bool indexCombox, bool systemRegister, bool userCustomTag, bool isHideIndexCheckbox)
{
    isEnableWordWidget = wordCombox;
    isEnableTips = addTips;
    isEnableIndexCombox = indexCombox;
    isEnableStstemRegister = systemRegister;
    isEnableUseCustom = userCustomTag;
    isEnableIndexCheck = isHideIndexCheckbox;
}

void subDialog::getConfigurePassword(QString &password, int &isHidden)
{
    password = ui->PasswordLineEdit->text();
    isHidden = ui->HiddenPassword->checkState();
}

void subDialog::setDataBasePage(FormulaItem *item)
{
    ui->ProFileName->setText(item->proName);
    int index = ui->DataTypeCombox->findText(item->dataType);
    qDebug()<<"要设置的文字信息是： "<<item->dataType<<" ; the index is : "<<index;
    //ui->DataTypeCombox->setCurrentIndex(index);
    ui->SizeLineEdit->setText(item->size);
    ui->ShowWidthLineEdit->setText(item->showWidth);
    ui->AlignmentCombox->setCurrentIndex(ui->AlignmentCombox->findText(item->alignType));
    ui->PointNumberLineEdit->setText(item->pointNumber);
}

void subDialog::getDataBaseResult(FormulaItem &item)
{
    item.proName = ui->ProFileName->text();
    item.dataType = ui->DataTypeCombox->currentText();
    item.size = ui->SizeLineEdit->text();
    item.pointNumber = ui->PointNumberLineEdit->text();
    item.showWidth = ui->ShowWidthLineEdit->text();
    item.alignType = ui->AlignmentCombox->currentText();
}

void subDialog::getDeivceProperty(QString &deviceName, QString &addrType, QString &position, QString &deviceType, QString &screenType, QString &commProtocal, QString &stationID)
{
    deviceName = ui->DeviceLocationCombox->currentText()+" 设备";
    addrType = ui->DeviceNameLineEdit->text();
    if(ui->DeviceLocationCombox->currentText() == "远端")
        position = ui->DeviceLocationCombox->currentText()+"("+ui->DeviceNetInfoLineEdit->text().replace("(",",").replace(")",",")+ui->ComValueLineEdit->text().mid(0,5)+")";
    else
        position = "本机";

    deviceType = "MODBUS RTU";
    screenType = ui->ComValueLineEdit->text();             //屏幕
    commProtocal = ui->CommunicationProtocalCombox->currentText();      //通讯协议

    if(ui->PresetStationUseStationVaraiable->checkState() == Qt::Checked)
        stationID = ui->DevicePresetStationIDCombox->currentText();
    else
        stationID = ui->DevicePresetStationIDLineEdit->text();              //站号

}

void subDialog::setWidgetInfoDisable(QString &text)
{
    qDebug()<<"修正的数据是： "<<text;
    btnWdg->setComInfoDisable(text);
}

void subDialog::setWidgetInfoEnable(QString &text)
{
    btnWdg->setComInfoVisiable(text);
}

void subDialog::setCurrentDevPro(DevProperty &dev)
{
    if(dev.getDevLoca().contains("远端"))
    {
        ui->DeviceNetInfoLineEdit->show();
        ui->DeviceNetInfoLineEdit->setText(dev.getDevLoca().split("(").last().remove(')'));         //设置远端后面的Ip地址信息
        btnWdg->setComWidgetType(1);
    }
    else
    {
        ui->DeviceNetInfoLineEdit->hide();
        btnWdg->setComWidgetType(0);
    }
    ui->DeviceNameLineEdit->setText(dev.getDevName());          //设备名称

    qDebug()<<"当前的设备    位置是： "<<dev.getDevLoca();
    if(dev.getDevLoca().contains("本机"))
         ui->DeviceLocationCombox->setCurrentText("本机");
    else
        ui->DeviceLocationCombox->setCurrentText("远端");
    ui->ComValueLineEdit->setText(dev.getDevScre());                //Com口信息,本机附有全部信息，远端只保留COM口
    QString str = dev.getDevScre();
    btnWdg->setCurrentComIndex(str);

    ui->DevicePresetStationIDLineEdit->setText(dev.getDevStID());           //预设ID
    currentComInfoStr = dev.getDevScre();
}


void subDialog::initWidgetControl()
{
    ui->endLabel->hide();
    ui->endLineEdit->hide();
    ui->endLineEdit->setValidator(new QIntValidator(0,360,this));
    ui->startLineEdit->setValidator(new QIntValidator(0,360,this));
    ui->endLineEdit->setPlaceholderText("0~360");
    ui->startLineEdit->setPlaceholderText("0~360");

}

void subDialog::initWatchNeedlePage()
{
    ui->WatchNeedleDevTypeCombox->installEventFilter(this);
    ui->WatchNeedleIndexLabel->hide();
    ui->WatchNeedleIndexCombox->hide();
    ui->WatchNeedleIndexCombox->clear();
    ui->WatchNeedleAddrFormat->setEnabled(false);

    QString itemString = "";
    for(int i=0;i<32;i++)
    {
        if(i<=15)
        {
            itemString = "INDEX"+QString::number(i)+" (16-bit)";
        }
        else
        {
            itemString = "INDEX"+QString::number(i)+" (32-bit)";
        }
        ui->WatchNeedleIndexCombox->addItem(itemString);
    }

    ui->WatchNeedleIndexType->setHidden(!isEnableIndexCombox);
    ui->AddressSettingTips->setHidden(!isEnableTips);
    ui->WordNumberWdg->setHidden(!isEnableWordWidget);
    ui->WatchNeedleSystemRegister->setHidden(!isEnableStstemRegister);
    ui->UserCustomTagCheckbox->setHidden(!isEnableUseCustom);
    ui->IndexRegisterCheckbox_2->setHidden(!isEnableIndexCheck);
    ui->WatchNeedleIndexCombox->setHidden(!isEnableIndexCheck);
    ui->WatchNeedleIndexLabel->setHidden(!isEnableIndexCheck);


    QStringList addList;
    if(subAddrWidgetType == 0)          //采用LW
    {
        addList<<"LW"<<"RW"<<"RW_A"<<"RWI"<<"EM0"<<"EM1"<<"EM2"<<"EM3"<<"EM4"<<"EM5"<<"EM6"<<"EM7"<<"EM8"<<"EM9";
        ui->WatchNeedleDevTypeCombox->clear();
        ui->WatchNeedleDevTypeCombox->addItems(addList);
    }
    else if(subAddrWidgetType == 1)     //采用LB
    {
        addList<<"LB"<<"RW_Bit"<<"RW_A_Bit"<<"LW_Bit"<<"RBI"<<"RECIPE-Bit";
        ui->WatchNeedleDevTypeCombox->clear();
        ui->WatchNeedleDevTypeCombox->addItems(addList);
    }
    ui->WatchNeedleDevTypeCombox->setCurrentIndex(0);
    ui->WatchNeedleAddressLineEdit->setText("0");
}

void subDialog::initPLCControlSubPage()
{
    ui->CommanderCombox->hide();
    ui->windowIDCombox->hide();
    ui->AddrTagBaseBtn->hide();
    for(int i = -1024;i<=1024;i++)
    {
        ui->windowIDCombox->addItem(QString::number(i));
    }
}

void subDialog::initDataBaseSubPage()
{
    QRegExp regx("[a-zA-Z0-9]+$");
    ui->ProFileName->setValidator(new QRegExpValidator(regx,ui->ProFileName));

    ui->SizeLineEdit->setReadOnly(true);
    ui->PointNumberLineEdit->setValidator(new QIntValidator(0,11));
    ui->ShowWidthLineEdit->setValidator(new QIntValidator(0,255));
}

void subDialog::initNewDeicePropertyPage()
{
    initWidgetNumber(ui->AddWholeIntervalCombox,0,513);
    initWidgetNumber(ui->MaxReadIntervalCombox,0,513);
    initWidgetNumber(ui->MaxWriteIntervalCombox,0,513);
    ui->DeviceLocationTipsLabel->show();
    ui->AddNewDevicePropertyGroupbox->show();
    ui->AddNewDeviceAddrGroupBox->show();

    ui->DeviceNetInfoLineEdit->hide();

    ui->DevicePresetStationIDCombox->hide();
    ui->UseRadioBroadcastLabel->hide();
    ui->RadioBordcaseUseStationID->hide();
    establishConnectRelation(ui->UseRadioBroadcastCheckbox,ui->UseRadioBroadcastLabel);
    establishConnectRelation(ui->UseRadioBroadcastCheckbox,ui->RadioBordcaseUseStationID);

    QStringList list{"LW-1000(16bit):var0","LW-1001(16bit):var1","LW-1002(16bit):var2","LW-1003(16bit):var3","LW-1003(16bit):var4","LW-1005(16bit):var5","LW-1006(16bit):var6","LW-1007(16bit):var7","LW-1008(16bit):var8","LW-1009(16bit):var9","LW-1010(16bit):var10","LW-1011(16bit):var11","LW-1012(16bit):var12","LW-1013(16bit):var13","LW-1014(16bit):var14","LW-1015(16bit):var15"};
    ui->DevicePresetStationIDCombox->addItems(list);

    initWidgetNumber(ui->RadioBordcaseUseStationID,0,256);
    ui->RadioBordcaseUseStationID->setCurrentIndex(1);

    ui->DevicePresetStationIDLineEdit->setPlaceholderText("0~256");
    ui->DevicePresetStationIDLineEdit->setValidator(new QIntValidator(0,256));

    ui->ComValueLineEdit->setText("COM 1(1200,None,7 Bits,1 Bit)");
    currentComInfoStr = "COM 1(1200,None,7 Bits,1 Bit)";
}

void subDialog::initAddHMIDevicePage()
{
    ui->DeviceLocationTipsLabel->hide();
    ui->AddNewDevicePropertyGroupbox->hide();
    ui->AddNewDeviceAddrGroupBox->hide();
}

void subDialog::initWidgetNumber(QComboBox *box, int startNumber, int endNumber)
{
    box->clear();
    for(int i=startNumber;i<endNumber;i++)
    {
        box->addItem(QString::number(i));
    }
}

void subDialog::establishConnectRelation(QCheckBox *checkbox, QWidget *widget, int bit)
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


void subDialog::on_wholeCircular_clicked(bool checked)
{
    ui->endLabel->setHidden(checked);
    ui->endLineEdit->setHidden(checked);
}

//地址标签库按钮被点击
void subDialog::on_AddrTagBaseBtn_clicked()
{
    btnWdg->showIndexWidget(AddressTagBasePage);
    btnWdg->exec();
}

void subDialog::on_ExitBtn_clicked()
{
    this->reject();
}

void subDialog::on_ConfirmBtn_clicked()
{
    if(ui->stackedWidget->currentIndex() == 9 )
    {
        //校验设备名称是否为空
        if( ui->DeviceNameLineEdit->text() == "")
        {
            QMessageBox::warning(NULL,"提示","请输入有效的设备名称",QMessageBox::Yes);
            return;
        }
        //校验设备ID是否为空
        if(ui->DevicePresetStationIDLineEdit->text() == "")
        {
            QMessageBox::warning(NULL,"提示","请指定有效的设备站号ID",QMessageBox::Yes);
            return;
        }
        //校验设备IP是否为空
        if(ui->DeviceLocationCombox->currentText() == "远端")
        {
            QString str = ui->DeviceNetInfoLineEdit->text();
            if(str.contains("0.0.0.0"))
            {
                QMessageBox::warning(NULL,"提示","IP地址不能为空",QMessageBox::Yes);
                return;
            }
        }
        //校验COM信息是否已被占用
        QString comText = ui->ComValueLineEdit->text().mid(0,5);
        if(comInfo.contains(comText))
        {
            if(isNewAddDevice)      //是新增加设备提示
            {
                QMessageBox::warning(NULL,"提示",comText+"已经被定义",QMessageBox::Yes);
                return;
            }
            else                    //否则不提示
                this->accept();
        }
        else
            comInfo.push_back(comText);
        this->accept();
    }
    else
        this->accept();
}

//系统寄存器
void subDialog::on_WatchNeedleSystemRegister_stateChanged(int arg1)
{
    if(widgetCaller != "DynamicPaint")
    {
        if(arg1 == 2)
        {
            if(ui->UserCustomTagCheckbox->checkState() == Qt::Checked)   //如果选中的时候，用户自定义标签也被选中该，
                ui->UserCustomTagCheckbox->setChecked(false);

            currentDevTypeStr = ui->WatchNeedleAddressLineEdit->text();
            ui->WatchNeedleAddressLineEdit->setEnabled(false);
            ui->WatchNeedleDevTypeCombox->clear();
            if(widgetCaller == "dataTransBackground")
            {
                ui->WatchNeedleDevTypeCombox->addItem("LB-9000：重新开机时状态为ON");
                ui->WatchNeedleAddressLineEdit->setText("LW-9000");
                ui->WatchNeedleAddrFormat->setText("DDDDD [范围： 0~12799]");
            }
            else
            {
                ui->WatchNeedleDevTypeCombox->addItem("LW-9002(32bit-float):数值输入元件允许输入上限");
                ui->WatchNeedleAddressLineEdit->setText("LW-9002");
                ui->WatchNeedleAddrFormat->setText("DDDDD [范围： 0~12799]");
            }
            ui->WatchNeedleDevTypeCombox->setCurrentIndex(0);
        }
        else if(arg1 == 0)
        {
            ui->WatchNeedleAddressLineEdit->setEnabled(true);
            ui->WatchNeedleDevTypeCombox->clear();
            if(widgetCaller == "dataTransBackground" )
            {
                ui->WatchNeedleDevTypeCombox->addItem("LB");
                ui->WatchNeedleDevTypeCombox->addItem("RW-Bit");
                ui->WatchNeedleDevTypeCombox->addItem("RW_A-Bit");
                ui->WatchNeedleDevTypeCombox->addItem("LW-Bit");
                ui->WatchNeedleDevTypeCombox->addItem("RBI");
                ui->WatchNeedleDevTypeCombox->addItem("RECIPE-Bit");
            }
             else
            {
                ui->WatchNeedleDevTypeCombox->addItem("LW");
                ui->WatchNeedleDevTypeCombox->addItem("RW");
                ui->WatchNeedleDevTypeCombox->addItem("RW_A");
                ui->WatchNeedleDevTypeCombox->addItem("RWI");
                ui->WatchNeedleDevTypeCombox->addItem("EM0");
                ui->WatchNeedleDevTypeCombox->addItem("EM1");
                ui->WatchNeedleDevTypeCombox->addItem("EM2");
                ui->WatchNeedleDevTypeCombox->addItem("EM3");
                ui->WatchNeedleDevTypeCombox->addItem("EM4");
                ui->WatchNeedleDevTypeCombox->addItem("EM5");
                ui->WatchNeedleDevTypeCombox->addItem("EM6");
                ui->WatchNeedleDevTypeCombox->addItem("EM7");
                ui->WatchNeedleDevTypeCombox->addItem("EM8");
                ui->WatchNeedleDevTypeCombox->addItem("EM9");
            }
           ui->WatchNeedleAddressLineEdit->setText(currentDevTypeStr);
           ui->WatchNeedleDevTypeCombox->setCurrentIndex(0);
           if(ui->UserCustomTagCheckbox->checkState() == Qt::Unchecked)
           {
               ui->WatchNeedleAddrFormat->setText("DDDDD 范围[0~12000]");
           }
        }
    }
    else
    {
        if(arg1 == 0)               //如果未选中
        {
            ui->WatchNeedleAddressLineEdit->setEnabled(true);
            ui->WatchNeedleDevTypeCombox->clear();
            ui->WatchNeedleDevTypeCombox->addItem("LB");
            ui->WatchNeedleDevTypeCombox->addItem("RW-Bit");
            ui->WatchNeedleDevTypeCombox->addItem("RW_A-Bit");
            ui->WatchNeedleDevTypeCombox->addItem("LW-Bit");
            ui->WatchNeedleDevTypeCombox->addItem("RBI");
            ui->WatchNeedleDevTypeCombox->addItem("RECIPE-Bit");
            ui->WatchNeedleDevTypeCombox->setCurrentIndex(0);
            ui->WatchNeedleAddressLineEdit->setText(currentDevTypeStr);
            if(ui->UserCustomTagCheckbox->checkState() == Qt::Unchecked)
            {
                ui->WatchNeedleAddrFormat->setText("DDDDD 范围[0~12000]");
            }
        }
        else if(arg1 == 2)          //如果选中
        {
            if(ui->UserCustomTagCheckbox->checkState() == Qt::Checked)   //如果选中的时候，用户自定义标签也被选中该，
                ui->UserCustomTagCheckbox->setChecked(false);
            currentDevTypeStr = ui->WatchNeedleAddressLineEdit->text();
            ui->WatchNeedleAddressLineEdit->setText("LB-9000");
            ui->WatchNeedleAddressLineEdit->setEnabled(false);
            ui->WatchNeedleDevTypeCombox->clear();
            ui->WatchNeedleDevTypeCombox->addItem("LB-9000：重新开机时状态为ON");
            ui->WatchNeedleDevTypeCombox->setCurrentIndex(0);
        }
    }


}

bool subDialog::eventFilter(QObject *obj, QEvent *ev)
{
    if(ui->WatchNeedleDevTypeCombox->underMouse() && obj->objectName() == "WatchNeedleDevTypeCombox" && ev->type() == QEvent::MouseButtonPress)
    {
        if(ui->WatchNeedleSystemRegister->checkState() == Qt::Checked || ui->UserCustomTagCheckbox->checkState() == Qt::Checked)
        {
            if(ui->WatchNeedleSystemRegister->checkState() == Qt::Checked)
                btnWdg->setCurrentDevType(0);
            else if(ui->UserCustomTagCheckbox->checkState() == Qt::Checked)
                btnWdg->setCurrentDevType(1);

            btnWdg->setWidgetCallerName(widgetCaller);
            btnWdg->showIndexWidget(WatchNeedleRegisterType);
            if( btnWdg->exec() == QDialog::Rejected )
                return QDialog::eventFilter(obj,ev);
            QString devtypeStr = btnWdg->getChooseItemText();
            if(devtypeStr!="")
            {
                ui->WatchNeedleDevTypeCombox->clear();
                ui->WatchNeedleDevTypeCombox->addItem(devtypeStr);
                ui->WatchNeedleDevTypeCombox->setCurrentIndex(0);
            }
            return true;
        }
    }
    return QDialog::eventFilter(obj,ev);
}

//用户自定义标签
void subDialog::on_UserCustomTagCheckbox_stateChanged(int arg1)
{

    if(widgetCaller != "DynamicPaint" )
    {
        if(arg1 == 2)
        {
            if( ui->WatchNeedleSystemRegister->checkState() == Qt::Checked )
                ui->WatchNeedleSystemRegister->setChecked(false);
            currentDevTypeStr = ui->WatchNeedleAddressLineEdit->text();
            ui->WatchNeedleDevTypeCombox->clear();
            if( widgetCaller == "dataTransBackground")
            {
                ui->WatchNeedleDevTypeCombox->addItem("UAC command execution result: succeeds");
                ui->WatchNeedleAddressLineEdit->setText("LW_Bit 895100");
                ui->WatchNeedleAddrFormat->setText("DDDDDdd [范围： 0~1200015,dd(位地址):00~15]");
            }
            else
            {
                 ui->WatchNeedleDevTypeCombox->addItem("UAC command");
                 ui->WatchNeedleAddressLineEdit->setText("LW-500");
                 ui->WatchNeedleAddrFormat->setText("DDDDDdd [范围： 0~1200015,dd(位地址):00~15]");

            }

            ui->WatchNeedleDevTypeCombox->setCurrentIndex(0);
            ui->WatchNeedleAddressLineEdit->setEnabled(false);
        }
        else if(arg1 == 0  )      //两种状态都没有选中
        {
            if(widgetCaller == "dataTransBackground")
            {
                ui->WatchNeedleAddressLineEdit->setEnabled(true);
                ui->WatchNeedleDevTypeCombox->clear();
                ui->WatchNeedleDevTypeCombox->addItem("LB");
                ui->WatchNeedleDevTypeCombox->addItem("RW-Bit");
                ui->WatchNeedleDevTypeCombox->addItem("RW_A-Bit");
                ui->WatchNeedleDevTypeCombox->addItem("LW-Bit");
                ui->WatchNeedleDevTypeCombox->addItem("RBI");
                ui->WatchNeedleDevTypeCombox->addItem("RECIPE-Bit");
                ui->WatchNeedleDevTypeCombox->setCurrentIndex(0);
            }
            else
            {
                ui->WatchNeedleAddressLineEdit->setEnabled(true);
                ui->WatchNeedleDevTypeCombox->clear();
                ui->WatchNeedleDevTypeCombox->addItem("LW");
                ui->WatchNeedleDevTypeCombox->addItem("RW");
                ui->WatchNeedleDevTypeCombox->addItem("RW_A");
                ui->WatchNeedleDevTypeCombox->addItem("RWI");
                ui->WatchNeedleDevTypeCombox->addItem("EM0");
                ui->WatchNeedleDevTypeCombox->addItem("EM1");
                ui->WatchNeedleDevTypeCombox->addItem("EM2");
                ui->WatchNeedleDevTypeCombox->addItem("EM3");
                ui->WatchNeedleDevTypeCombox->addItem("EM4");
                ui->WatchNeedleDevTypeCombox->addItem("EM5");
                ui->WatchNeedleDevTypeCombox->addItem("EM6");
                ui->WatchNeedleDevTypeCombox->addItem("EM7");
                ui->WatchNeedleDevTypeCombox->addItem("EM8");
                ui->WatchNeedleDevTypeCombox->addItem("EM9");
                ui->WatchNeedleDevTypeCombox->setCurrentIndex(0);
            }
             ui->WatchNeedleAddressLineEdit->setText(currentDevTypeStr);
             if(ui->WatchNeedleSystemRegister->checkState() == Qt::Unchecked)
             {
                 //两种都未选中
                 ui->WatchNeedleAddrFormat->setText("DDDDD 范围[0~12000]");
             }
        }
    }
    else
    {
        if(arg1 == 2)
        {
            if( ui->WatchNeedleSystemRegister->checkState() == Qt::Checked )
                ui->WatchNeedleSystemRegister->setChecked(false);
            currentDevTypeStr = ui->WatchNeedleAddressLineEdit->text();
            ui->WatchNeedleDevTypeCombox->clear();
            ui->WatchNeedleDevTypeCombox->addItem("LW-9000：重新开机时状态设置为ON");
            ui->WatchNeedleDevTypeCombox->setCurrentIndex(0);
            ui->WatchNeedleAddressLineEdit->setText("LW-9000");
            ui->WatchNeedleAddrFormat->setText("DDDDDdd [范围： 0~1200015,dd(位地址):00~15]");
            ui->WatchNeedleAddressLineEdit->setEnabled(false);
        }
        else if(arg1 == 0)   //两种状态都未选中
        {
            ui->WatchNeedleAddressLineEdit->setEnabled(true);
            ui->WatchNeedleDevTypeCombox->clear();
            ui->WatchNeedleDevTypeCombox->addItem("LB");
            ui->WatchNeedleDevTypeCombox->addItem("RW-Bit");
            ui->WatchNeedleDevTypeCombox->addItem("RW_A-Bit");
            ui->WatchNeedleDevTypeCombox->addItem("LW-Bit");
            ui->WatchNeedleDevTypeCombox->addItem("RBI");
            ui->WatchNeedleDevTypeCombox->addItem("RECIPE-Bit");
            ui->WatchNeedleDevTypeCombox->setCurrentIndex(0);
            ui->WatchNeedleAddressLineEdit->setText(currentDevTypeStr);

            if(ui->WatchNeedleSystemRegister->checkState() == Qt::Unchecked)
            {
                //两种都未选中
                ui->WatchNeedleAddrFormat->setText("DDDDD 范围[0~12000]");
            }
        }
    }
}

void subDialog::on_IndexRegisterCheckbox_2_stateChanged(int arg1)
{
    if(arg1 == 2)           //选中
    {
        ui->WatchNeedleIndexLabel->show();
        ui->WatchNeedleIndexCombox->show();

    }
    else if(arg1 == 0)      //未选中
    {
        ui->WatchNeedleIndexLabel->hide();
        ui->WatchNeedleIndexCombox->hide();
    }
}

void subDialog::on_ExecSpecialCommand_stateChanged(int arg1)
{
    if(arg1 == 2)
        ui->CommanderCombox->show();
    else if (arg1 == 0)
        ui->CommanderCombox->hide();
}

void subDialog::on_UseWindowIDCheckBox_stateChanged(int arg1)
{
    if(arg1 == 2)
        ui->windowIDCombox->show();
    else if(arg1 == 0)
        ui->windowIDCombox->hide();
}

void subDialog::doListItemChanged(int index)
{
    QString text = "LW_Bit 89510"+QString::number(index);
    ui->WatchNeedleAddressLineEdit->setText(text);
}


void subDialog::on_EnableReadOnly_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->PasswordGroupbox->hide();
    }
    else
        ui->PasswordGroupbox->show();
}

//com 地址配置按钮
void subDialog::on_ComConfigBtn_clicked()
{
    btnWdg->showIndexWidget(ConfigComDataPage);
    if(btnWdg->exec() == QDialog::Accepted )
    {
        QString comName,bounRate,dataBit,checkTimes,stopBit,overTime,commDelay;
        int reSendTimes = 3;
        btnWdg->getComConfigValue(comName,bounRate,dataBit,checkTimes,stopBit,overTime,commDelay,reSendTimes);
        QString text;
        if(ui->DeviceLocationCombox->currentText() == "本机")
           text = comName.remove("*")+"("+bounRate+","+checkTimes+","+dataBit+","+stopBit+")";
        else
           text = comName.remove("*");
        ui->ComValueLineEdit->setText(text);
    }
}

//所属位置
void subDialog::on_ConfigLocationBtn_clicked()
{
    configDlg->showConfigDialog(NetAddressConfigPage);
    if(configDlg->exec() == QDialog::Accepted)
    {
        QString ipStr,portStr;
        configDlg->getDeviceNetInfo(ipStr,portStr);
        ui->DeviceNetInfoLineEdit->setText("IP:"+ipStr+"(端口号="+portStr+")");
    }
}

//数据转换方式
void subDialog::on_DataTransformWayBtn_clicked()
{
    btnWdg->showIndexWidget(AddTransformPage);
    if( btnWdg->exec() == QDialog::Rejected )
        return;
}

//地址整段范围
void subDialog::on_AddScropLimitBtn_clicked()
{
    btnWdg->setAddrRangeInfo(ui->DevicePresetStationIDLineEdit->text().toInt());
    btnWdg->showIndexWidget(AddRangeLimitPage);
    if( btnWdg->exec() == QDialog::Rejected )
        return;
}

void subDialog::on_PresetStationUseStationVaraiable_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->DevicePresetStationIDCombox->hide();
        ui->DevicePresetStationIDLineEdit->show();
    }
    else if(arg1 == 2)
    {
        ui->DevicePresetStationIDCombox->show();
        ui->DevicePresetStationIDLineEdit->hide();
    }
}

void subDialog::on_DeviceLocationCombox_currentTextChanged(const QString &arg1)
{
    bool isHidden = true;
    if(arg1 == "远端"  )
    {
        ui->DeviceNetInfoLineEdit->show();
        isHidden = true;
        if(ui->NewDeviceRadioBtn->isChecked() == true)
        {
            btnWdg->setComWidgetType(1);
            ui->ComValueLineEdit->setText(currentComInfoStr.mid(0,5));
        }
    }
    else if(arg1 != "远端" && ui->NewDeviceRadioBtn->isChecked() == true)
    {
        ui->DeviceNetInfoLineEdit->hide();
        isHidden = false;
        btnWdg->setComWidgetType(0);
        ui->ComValueLineEdit->setText(currentComInfoStr);
    }
    ui->SuportOutlineLabel->setHidden(isHidden);
    ui->SupportCommWithHMIDev->setHidden(isHidden);
    ui->ImproveTransSpeed->setHidden(isHidden);
    ui->UseRadioBroadcastCheckbox->setHidden(isHidden);
    ui->AddScropLimitBtn->setHidden(isHidden);
    ui->DataTransformWayBtn->setHidden(isHidden);
}

void subDialog::on_NewDeviceRadioBtn_clicked()
{
    if(ui->DeviceLocationCombox->currentText() == "本机")
        ui->DeviceNetInfoLineEdit->hide();
    else
        ui->DeviceNetInfoLineEdit->show();
}
