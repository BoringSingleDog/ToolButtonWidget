#include "BtnWidget.h"
#include "ui_BtnWidget.h"
#include <QDebug>
BtnWidget::BtnWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BtnWidget)
{
    ui->setupUi(this);
    initAddrTagPage();

}



BtnWidget::~BtnWidget()
{
    delete ui;
}

void BtnWidget::showIndexWidget(BtnWidgetType type)
{
    switch(type)
    {
        case AddressTagBasePage:               //地址标签库界面
             ui->stackedWidget->setCurrentIndex(0);
             this->setWindowTitle("地址标签库");
             break;
        case WatchNeedleRegisterType:
             ui->stackedWidget->setCurrentIndex(1);
             initDevTypeListWidget();
             this->setWindowTitle("");
             break;
        default:break;
    }

}

void BtnWidget::initAddrTagPage()
{

    //初始化表头以及相关的控件界面文字信息




}

void BtnWidget::initDevTypeListWidget()
{
    if(devType == 0)
    {
       ui->listWidget->clear();
       if(callerName == "WatchNeedle" || callerName == "BarGraph")
       {
           ui->listWidget->addItem(new QListWidgetItem("LW-9002 (32bit-float):数值输入元件允许输入的上限值"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9004 (32bit-float):数值输入元件允许输入的下限值"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9006 (16bit):连接到本机远端的HMI项目"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9007 (16bit):硬件索引编号"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9010 (16bit-BCD):本机时间(秒)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9011 (16bit-BCD):本机时间(分)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9012 (16bit-BCD):本机时间(时)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9013 (16bit-BCD):本机时间(日)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9014 (16bit-BCD):本机时间(月)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9015 (16bit-BCD):本机时间(年)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9016 (16bit-BCD):本机时间(星期)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9017 (16bit):本机时间(秒)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9018 (16bit):本机时间(分)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9019 (16bit):本机时间(时)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9020 (16bit):本机时间(日)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9021 (16bit):本机时间(月)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9022 (16bit):本机时间(年)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9023 (16bit):本机时间(星期)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9024 (16bit):memory link 系统寄存器"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9025 (16bit):CPU使用率"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9026 (16bit):OS版本(年)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9027 (16bit):OS版本(月)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9028 (16bit):OS版本(日)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9030 (32bit):系统时间(单位：0.1秒)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9032 (8 words):备份历史记录到SD卡，U盘的文件夹名称"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9040 (16bit):背景灯亮度值"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9041 (16bit):触控状态(bit0=on 正在触控屏幕)"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9042 (16bit):触控时X的位置"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9043 (16bit):触控时Y的位置"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9044 (16bit):离开时X的位置"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9045 (16bit):离开时Y的位置"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9046 (32bit):HMI识别码"));
           ui->listWidget->addItem(new QListWidgetItem("LW-9048 (16bit):时间(0：AM,1:PM)"));
       }
       else if(callerName == "DynamicPaint")
       {
           ui->listWidget->addItem(new QListWidgetItem("LB-9000：重新开机时状态为ON"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9001：重新开机时状态为ON"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9002：重新开机时状态为ON"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9003：重新开机时状态为ON"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9004：重新开机时状态为ON"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9005：重新开机时状态为ON"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9006：重新开机时状态为ON"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9007：重新开机时状态为ON"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9008：重新开机时状态为ON"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9009：重新开机时状态为ON"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9010：数据传输写入指令"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9011：数据传输读取指令"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9012：数据传输执行指令"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9013：隐藏(设ON)/显示(设OFF)快选窗口"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9014：隐藏(设ON)/显示(设OFF)快选窗口"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9015：隐藏(设ON)/显示(设OFF)快选窗口"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9016：远端HMI连接到本机HMI(当状态为ON)"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9017：取消PLC控制元件[切换窗口]的[写回]功能"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9018：隐藏(设ON)/显示(设OFF)鼠标光标"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9019：取消(设ON)/显示(设OFF)声音输出"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9020：显示(设ON)/隐藏(设OFF)系统设置列"));
           ui->listWidget->addItem(new QListWidgetItem("LB-9021：重置当前的系统记录事件(OFF->ON)"));
       }
        ui->listWidget->setCurrentRow(0);
    }
    else if(devType == 1)
    {
        ui->listWidget->clear();
        if(callerName == "WatchNeedle" || callerName == "BarGraph")
        {
            ui->listWidget->addItem(new QListWidgetItem("UAC command"));
            ui->listWidget->addItem(new QListWidgetItem("UAC command execution result"));
            ui->listWidget->addItem(new QListWidgetItem("UAC user index"));
            ui->listWidget->addItem(new QListWidgetItem("UAC user private"));
            ui->listWidget->addItem(new QListWidgetItem("UAC user name"));
            ui->listWidget->addItem(new QListWidgetItem("UAC password"));
        }
        else if(callerName == "DynamicPaint")
        {

        }
        ui->listWidget->setCurrentRow(0);
    }
}

void BtnWidget::on_closeBtn_clicked()
{
    this->close();
}

void BtnWidget::on_ConfirmButton_clicked()
{
   QString textStr = ui->listWidget->currentItem()->text();
   chooseItemText = textStr;
   this->close();
}

void BtnWidget::on_CancelButton_clicked()
{
    this->close();
}

void BtnWidget::on_listWidget_currentTextChanged(const QString &currentText)
{
    chooseItemText = currentText;
}
