#include "ConfigDialog.h"
#include "ui_ConfigDialog.h"
#include <QMessageBox>
#include <QDebug>
ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    this->setModal(true);
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::showConfigDialog(ConfigDialogType type)
{
    switch(type)
    {
        case AddAddressConfigPage:
        case ConfigAddressConfigPage:
            ui->stackedWidget->setCurrentIndex(0);
            this->setWindowTitle("0x/1x地址范围");
            this->setFixedSize(QSize(480,200));
            initAddAddrPage();
            break;
        case NetAddressConfigPage:
            initDeviceNetInfoPage();
            ui->stackedWidget->setCurrentIndex(1);
            this->setWindowTitle("IP地址设置");
            this->setFixedSize(QSize(480,200));
            break;
        default:
            break;
    }
}

void ConfigDialog::getAddrConfigValue(QString& stationID, QString& addrType, QString& minValue, QString& maxValue)
{
    stationID = ui->StationIDCombox->currentText();
    addrType = ui->AddrTypeCombox->currentText();
    minValue = ui->MinizeAddrLineEdit->text();
    maxValue = ui->MaxizeLineEdit->text();
}

void ConfigDialog::setAddrConfigShowValue(AddrRangeItem &item)
{
    qDebug()<<item.addrType<<item.stationID<<item.minValue<<item.maxValue;
    ui->MinizeAddrLineEdit->setText(item.minValue);
    ui->MaxizeLineEdit->setText(item.maxValue);
    ui->AddrTypeCombox->setCurrentText(item.addrType);
    ui->StationIDCombox->setCurrentText(item.stationID);
}

void ConfigDialog::getDeviceNetInfo(QString &ipStr, QString &portStr)
{
    ipStr = ui->IP_LineEdit1->text()+"."+ui->IP_LineEdit2->text()+"."+ui->IP_LineEdit3->text()+"."+ui->IP_LineEdit4->text();
    portStr = ui->DevicePortLineEdit->text();
}

void ConfigDialog::setCurrentStationID(int value)
{
    ui->StationIDCombox->setCurrentText(QString::number(value));
}


void ConfigDialog::initAddAddrPage()
{
    if(ui->StationIDCombox->count() >2)         //如果存在数据就不在重复初始化
        return;
    for(int i=0;i<256;i++)
    {
        ui->StationIDCombox->addItem(QString::number(i));
    }
    ui->StationIDCombox->setCurrentIndex(1);

    QStringList list;
    list<<"0x"<<"1x"<<"0x_multi_coils"<<"0x_1"<<"0x_2"<<"0x_3"<<"0x_4"<<"0x_5"<<"0x_6"<<"0x_7"<<"0x_8"<<"0x_9"
        <<"1x_1"<<"1x_2"<<"1x_3"<<"1x_4"<<"1x_5"<<"1x_6"<<"1x_7"<<"1x_8"<<"1x_9";
    ui->AddrTypeCombox->addItems(list);
    ui->AddrTypeCombox->setCurrentIndex(2);

    ui->MinizeAddrLineEdit->setValidator(new QIntValidator(0,65535));
    ui->MaxizeLineEdit->setValidator(new QIntValidator(0,65535));
}

void ConfigDialog::initDeviceNetInfoPage()
{
    ui->InterNetRadio->setChecked(true);
    ui->IP_LineEdit1->setValidator(new QIntValidator(0,255));
    ui->IP_LineEdit2->setValidator(new QIntValidator(0,255));
    ui->IP_LineEdit3->setValidator(new QIntValidator(0,255));
    ui->IP_LineEdit4->setValidator(new QIntValidator(0,255));
    ui->DevicePortLineEdit->setPlaceholderText("0~65535");
    ui->DevicePortLineEdit->setValidator(new QIntValidator(0,65535));
}

void ConfigDialog::on_OKButton_clicked()
{
    if(ui->stackedWidget->currentIndex() == 0)
    {
        if(ui->MinizeAddrLineEdit->text() == "" || ui->MaxizeLineEdit->text() == "")
        {
            QMessageBox::warning(NULL,"提示","请完善最小值和最大值信息",QMessageBox::Yes);
            return;
        }
        else if(ui->MaxizeLineEdit->text().toInt() < ui->MinizeAddrLineEdit->text().toInt())
        {
            QMessageBox::warning(NULL,"提示","请输入正确的最小值和最大值",QMessageBox::Yes);
            return;
        }
        else
            this->accept();
    }
    else
        this->accept();
}

void ConfigDialog::on_CancelButton_clicked()
{
    this->reject();
}
