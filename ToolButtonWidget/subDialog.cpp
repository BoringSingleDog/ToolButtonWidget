#include "subDialog.h"
#include "ui_subDialog.h"
#include <QDebug>

subDialog::subDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::subDialog)
{

    ui->setupUi(this);
    btnWdg = new BtnWidget();
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
        case AddressSubDialogPage:
            this->setWindowTitle("地址");
            ui->AddrTagBaseBtn->show();
            ui->stackedWidget->setCurrentIndex(2);
            break;
        case WatchNeedleAddrPage:
            initWatchNeedlePage();
            this->setWindowTitle("地址");
            ui->AddrTagBaseBtn->show();
            ui->stackedWidget->setCurrentIndex(3);
            break;
       case MoreInformationOne:
            this->setWindowTitle("箭头/形状样式");
            ui->AddrTagBaseBtn->hide();
            ui->stackedWidget->setCurrentIndex(4);
            break;
       case MoreInformationTwo:
            this->setWindowTitle("线/填充样式");
            ui->AddrTagBaseBtn->hide();
            ui->stackedWidget->setCurrentIndex(5);
            break;
       case MoveGraphLimitValueDesc:
            this->setWindowTitle("地址使用方式");
            ui->AddrTagBaseBtn->hide();
            ui->stackedWidget->setCurrentIndex(6);
            break;
       case PLCControlSubWidget:
            this->setWindowTitle("PLC控制");
            ui->AddrTagBaseBtn->hide();
            ui->stackedWidget->setCurrentIndex(7);
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

void subDialog::initWidgetControl()
{
    ui->endLabel->hide();
    ui->endLineEdit->hide();
    ui->endLineEdit->setValidator(new QIntValidator(0,360,this));
    ui->startLineEdit->setValidator(new QIntValidator(0,360,this));
    ui->endLineEdit->setPlaceholderText("0~360");
    ui->startLineEdit->setPlaceholderText("0~360");

    ui->IndexRegisterCombox->hide();
    ui->IndexRegisterLabel->hide();
    ui->IndexRegisterCombox->clear();
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
        ui->IndexRegisterCombox->addItem(itemString);
    }
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

    if(widgetCaller == "BarGraph")
        ui->AddressSettingTips->show();
    else if(widgetCaller == "DynamicPaint")
    {
       ui->WatchNeedleIndexType->hide();
       ui->AddressSettingTips->hide();
    }
    else
        ui->AddressSettingTips->hide();

}

void subDialog::on_wholeCircular_clicked(bool checked)
{
    ui->endLabel->setHidden(checked);
    ui->endLineEdit->setHidden(checked);
}

void subDialog::on_IndexRegisterCheckbox_stateChanged(int arg1)
{
    if(arg1 == 2)           //如果用户选择了使用索引寄存器中的索引值
    {
        ui->IndexRegisterCombox->show();
        ui->IndexRegisterLabel->show();
    }
    else if(arg1 == 0)      //未选中
    {
        ui->IndexRegisterCombox->hide();
        ui->IndexRegisterLabel->hide();
    }
}

//地址标签库按钮被点击
void subDialog::on_AddrTagBaseBtn_clicked()
{
    btnWdg->showIndexWidget(AddressTagBasePage);
    btnWdg->show();
}

void subDialog::on_ExitBtn_clicked()
{
    this->close();
}

void subDialog::on_ConfirmBtn_clicked()
{
    this->close();
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
            ui->WatchNeedleAddressLineEdit->setText("LW-9002");
            ui->WatchNeedleAddressLineEdit->setEnabled(false);
            ui->WatchNeedleDevTypeCombox->clear();
            ui->WatchNeedleDevTypeCombox->addItem("LW-9002(32bit-float):数值输入元件允许输入上限");
            ui->WatchNeedleDevTypeCombox->setCurrentIndex(0);
        }
        else if(arg1 == 0)
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
            ui->WatchNeedleAddressLineEdit->setText(currentDevTypeStr);
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
        }
        else if(arg1 == 2)          //如果选中
        {
            if(ui->UserCustomTagCheckbox->checkState() == Qt::Checked)   //如果选中的时候，用户自定义标签也被选中该，
                ui->UserCustomTagCheckbox->setChecked(false);
            currentDevTypeStr = ui->WatchNeedleAddressLineEdit->text();
            ui->WatchNeedleAddressLineEdit->setText("LB-900");
            ui->WatchNeedleAddressLineEdit->setEnabled(false);
            ui->WatchNeedleDevTypeCombox->clear();
            ui->WatchNeedleDevTypeCombox->addItem("LB-900：重新开机时状态为ON");
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
            btnWdg->exec();

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
    if(widgetCaller != "DynamicPaint")
    {
        if(arg1 == 2)
        {
            if( ui->WatchNeedleSystemRegister->checkState() == Qt::Checked )
                ui->WatchNeedleSystemRegister->setChecked(false);
            currentDevTypeStr = ui->WatchNeedleAddressLineEdit->text();
            ui->WatchNeedleDevTypeCombox->clear();
            ui->WatchNeedleDevTypeCombox->addItem("UAC command");
            ui->WatchNeedleDevTypeCombox->setCurrentIndex(0);
            ui->WatchNeedleAddressLineEdit->setText("LW-500");
            ui->WatchNeedleAddressLineEdit->setEnabled(false);
        }
        else if(arg1 == 0)      //两种状态都没有选中
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
            ui->WatchNeedleAddressLineEdit->setText(currentDevTypeStr);
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
            ui->WatchNeedleDevTypeCombox->addItem("LW-900：重新开机时状态设置为ON");
            ui->WatchNeedleDevTypeCombox->setCurrentIndex(0);
            ui->WatchNeedleAddressLineEdit->setText("LW-900");
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
