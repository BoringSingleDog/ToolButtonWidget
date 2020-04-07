#include "BtnWidget.h"
#include "ui_BtnWidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
BtnWidget::BtnWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BtnWidget)
{
    ui->setupUi(this);
    this->setModal(true);
 //   this->setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint);
    ConfigDlg = new ConfigDialog(this);
    initContactsPage();         //界面的部分信息只能初始化一次，所以放在构造函数中
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
             initAddrTagPage();
             this->setWindowTitle("地址标签库");
             break;
        case WatchNeedleRegisterType:
             ui->stackedWidget->setCurrentIndex(1);
             initDevTypeListWidget();
             this->setWindowTitle("");
             break;
        case TextLibraryPage:
             setWindowTitle("文字库");
             this->setFixedSize(QSize(1117,657));
             initTextLibrary();
             ui->stackedWidget->setCurrentIndex(2);
             break;
        case ContactsConfigPage:
             this->setWindowTitle("联系人");
             ui->stackedWidget->setCurrentIndex(3);
             this->setFixedSize(QSize(1117,400));
             break;
        case ConfigComDataPage:
             initComfigComPage();
             ui->stackedWidget->setCurrentIndex(4);
             this->setWindowTitle("通讯端口设置");
             this->setFixedSize(QSize(540,270));
             break;
        case AddTransformPage:
            ui->stackedWidget->setCurrentIndex(5);
            this->setWindowTitle("地址转换方式");
            this->setFixedSize(QSize(400,400));
            break;
        case AddRangeLimitPage:
            ui->stackedWidget->setCurrentIndex(6);
            initAddRangLimitPage();
            this->setWindowTitle("地址范围限制");
            this->setFixedSize(QSize(520,400));
            break;
        default:break;
    }
}

void BtnWidget::getComConfigValue(QString &comName, QString &bounRate, QString &dataBit, QString &checkTimes, QString &stopBit, QString &overTime, QString &commDelay, int reSendTimes)
{
    comName = ui->CommunicationPort->currentText();
    bounRate = ui->BaudRateCombox->currentText();
    dataBit = ui->DataBitCombox->currentText();
    checkTimes = ui->CheckBitCombox->currentText();
    stopBit = ui->StopBitCombox->currentText();
    overTime = ui->OvertimeCombox->currentText();
    commDelay = ui->CommunicateDelayTime->text();
    reSendTimes = ui->CommandResendTimes->currentText().toInt();
}

void BtnWidget::setComInfoVisiable(QString &text)
{
    int index = ui->CommunicationPort->findText(text);
    ui->CommunicationPort->setItemText(index,text.remove("*"));
}

void BtnWidget::setComInfoDisable(QString &text)
{
    int index = ui->CommunicationPort->findText(text);
    ui->CommunicationPort->setItemText(index,text+"*");
    qDebug()<<"修正的数据是： "<<text<<"the index is: "<<index<<" 修正后的数据是： "<<ui->CommunicationPort->itemText(index);
}

void BtnWidget::setComWidgetType(int type)
{
    bool isHidd = true;
    if(type == 1)
    {
        isHidd = true;
    }
    else if(type == 0)
    {
        isHidd = false;
    }
    ui->CommOverTimeGroupbox->setHidden(isHidd);
    ui->ComInfoConfigWidget->setHidden(isHidd);
}

void BtnWidget::setCurrentComIndex(QString &str)
{
    str = str.mid(0,5);
    int count = ui->CommunicationPort->count();
    for(int i=0;i<count;i++)
    {
        if(ui->CommunicationPort->itemText(i).contains(str))
        {
            if(!str.contains("*"))
                str =str+"*";
            ui->CommunicationPort->setItemText(i,str);
        }
    }
}

void BtnWidget::initAddrTagPage()
{

    //初始化表头以及相关的控件界面文字信息
    QStringList list;
    list<<" 编号"<<" 标签名称"<<" 分类"<<" 设备名称"<<" 地址"<<" 类型"<<" 转换"<<" 资料格式"<<" 原始格式";
    headerList = list;

    for(int i=0;i<=8;i++)
    {
        m_columnSort.insert(i,-1);
    }
    m_tableModel = new QStandardItemModel();
    m_tableModel->setHorizontalHeaderLabels(list);

    ui->AddrTagTable->setModel(m_tableModel);
    ui->AddrTagTable->horizontalHeader()->setStretchLastSection(true);
    ui->AddrTagTable->verticalHeader()->setVisible(false);
    ui->AddrTagTable->setSelectionBehavior(QAbstractItemView::SelectRows);          //整行选中， QAbstractItemView::SelectColumn---整列选中

    m_headerView = ui->AddrTagTable->horizontalHeader();
    connect(m_headerView,SIGNAL(sectionClicked(int)),this,SLOT(doColumnSortBtnClicked(int)));

    if(m_tableModel->rowCount() == 0 )
    {
        ui->ExportAsCSVFile->setEnabled(false);
        ui->ExportAsExeclFile->setEnabled(false);
        ui->ImportFromCSVFile->setEnabled(false);
        ui->ImportFromExeclFile->setEnabled(false);
    }
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
       else if(callerName == "DynamicPaint" ||  callerName == "dataTransBackground")
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
           ui->listWidget->addItem(new QListWidgetItem("LB-9022：删除HMI内存里日期最早的时间记录文件(设置为ON)"));

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
        else if( callerName == "dataTransBackground")
        {
            ui->listWidget->addItem(new QListWidgetItem("UAC command execution result: succeeds"));
            ui->listWidget->addItem(new QListWidgetItem("UAC command execution result: invalid command"));
            ui->listWidget->addItem(new QListWidgetItem("UAC command execution result: account exists"));
            ui->listWidget->addItem(new QListWidgetItem("UAC command execution result: password error"));
            ui->listWidget->addItem(new QListWidgetItem("UAC command execution result: deny command"));
            ui->listWidget->addItem(new QListWidgetItem("UAC command execution result: invalid namne"));
            ui->listWidget->addItem(new QListWidgetItem("UAC command execution result: invalid password character exists"));
            ui->listWidget->addItem(new QListWidgetItem("UAC command execution result: invalid import data"));
            ui->listWidget->addItem(new QListWidgetItem("UAC command execution result: invalid out of validity range"));
            ui->listWidget->addItem(new QListWidgetItem("UAC privilege (Class A)"));
            ui->listWidget->addItem(new QListWidgetItem("UAC privilege (Class B)"));
            ui->listWidget->addItem(new QListWidgetItem("UAC privilege (Class C)"));
            ui->listWidget->addItem(new QListWidgetItem("UAC privilege (Class D)"));
            ui->listWidget->addItem(new QListWidgetItem("UAC privilege (Class E)"));
            ui->listWidget->addItem(new QListWidgetItem("UAC privilege (Class F)"));
            ui->listWidget->addItem(new QListWidgetItem("UAC privilege (Class G)"));
            ui->listWidget->addItem(new QListWidgetItem("UAC privilege (Class H)"));
            ui->listWidget->addItem(new QListWidgetItem("UAC privilege (Class I)"));
            ui->listWidget->addItem(new QListWidgetItem("UAC privilege (Class J)"));
            ui->listWidget->addItem(new QListWidgetItem("UAC privilege (Class K)"));
            ui->listWidget->addItem(new QListWidgetItem("UAC privilege (Class L)"));
        }
        ui->listWidget->setCurrentRow(0);
    }
}


//初始化文字标签库界面
void BtnWidget::initTextLibrary()
{
    ui->CurrentStatusCombox->clear();
    for(int i=0;i<96;i++)
    {
        ui->CurrentStatusCombox->addItem(QString::number(i));
    }
    ui->CurrentStatusCombox->setCurrentIndex(1);
    ui->NextButton->setEnabled(true);
    ui->PreviousButton->setEnabled(true);

    QStringList strHeader;
    strHeader<<"编号"<<"文字标签名称"<<"状态数"<<"Language1"<<"Language2"<<"Language3"<<"Language4"<<"Language5"<<"Language6"<<"Language7"<<"Language8";
    textLibraryModel = new QStandardItemModel();
    textLibraryModel->setHorizontalHeaderLabels(strHeader);
    textLibraryModel->horizontalHeaderItem(0)->setEditable(false);          //不可编辑
    textLibraryModel->horizontalHeaderItem(1)->setEditable(false);
    textLibraryModel->horizontalHeaderItem(2)->setEditable(false);

    textLibraryModel->horizontalHeaderItem(0)->setSelectable(false);        //不可选中
    textLibraryModel->horizontalHeaderItem(1)->setSelectable(false);
    textLibraryModel->horizontalHeaderItem(2)->setSelectable(false);

   // ui->tableView->horizontalHeader()->setVisible(false);               //隐藏默认表头
    ui->tableView->verticalHeader()->setVisible(false);

    textLibraryModel->setRowCount(5);
    ui->tableView->setModel(textLibraryModel);

    if(textLibraryModel->rowCount() == 0)
        enableTextLibraryButn(false);
}

void BtnWidget::initContactsPage()
{
    QStringList str{"联络人名称","邮件地址"};
    ui->ContartsLeftTable->setColumnCount(2);
    ui->ContartsLeftTable->setHorizontalHeaderLabels(str);
    ui->ContartsLeftTable->verticalHeader()->setVisible(false);
    ui->ContartsLeftTable->setColumnWidth(0,100);
    ui->ContartsLeftTable->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->ContartsLeftTable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->ContartsLeftTable->setRowCount(0);
    ui->ContartsLeftTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->ContartsLeftTable,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(doDealItemClicked(QTableWidgetItem*)));
    connect(ui->ContartsLeftTable,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(doNameItemChanged(QTableWidgetItem*)));

    ui->ContartsRightTable->setColumnCount(2);
    ui->ContartsRightTable->setHorizontalHeaderLabels(str);
    ui->ContartsRightTable->verticalHeader()->setVisible(false);
    ui->ContartsRightTable->setRowCount(0);
    ui->ContartsRightTable->setColumnWidth(0,100);
    ui->ContartsRightTable->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->ContartsRightTable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->ContartsRightTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->ContartsRightTable,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(doDealRightItemClicked(QTableWidgetItem*)));

    isAddGroupCombox = true;
    ui->ContactsGroupNumber->setValue(1);
    ui->CurrentGroupCombox->addItem("群组A");
    ui->CurrentGroupCombox->setCurrentIndex(0);
    isAddGroupCombox = false;
}

void BtnWidget::initComfigComPage()
{
    if(ui->OvertimeCombox->count() > 2)         //不重复初始化
        return;

    ui->OvertimeCombox->clear();
    for(int i=0;i<=25;i++)
    {
        for(int j=0;j<=9;j++)
        {
            QString text = QString::number(i)+"."+QString::number(j);
            ui->OvertimeCombox->addItem(text);
        }
    }
    ui->OvertimeCombox->setCurrentIndex(10);

    ui->CommunicateDelayTime->setPlaceholderText("0~65535");
    ui->CommunicateDelayTime->setValidator(new QIntValidator(0,65535));
}

void BtnWidget::initAddRangLimitPage()
{
    if(ui->AddLimitTable->columnCount() == 5)
        return;
    QStringList list;
    ui->AddLimitTable->setColumnCount(5);
    list<<"编号"<<"站号"<<"地址类型"<<"最小地址"<<"最大地址";
    ui->AddLimitTable->setHorizontalHeaderLabels(list);
    ui->AddLimitTable->verticalHeader()->setVisible(false);
    ui->AddLimitTable->horizontalHeader()->setStretchLastSection(true);
    connect(ui->AddLimitTable,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(doAddrTableItemClicked(QTableWidgetItem*)));
}

//执行对表中的数据进行排序
void BtnWidget::execAddTagSort(int column, int sortType)
{
    QMessageBox::information(this,"Tips","地址标签库排序功能暂未实现",QMessageBox::Yes);
}

void BtnWidget::enableTextLibraryButn(bool enable)
{
    ui->SettingButton->setEnabled(enable);
    ui->DeleteButton->setEnabled(enable);
    ui->DeleteAllButton->setEnabled(enable);
    ui->CopyButton->setEnabled(enable);
    ui->PasterButton->setEnabled(enable);
    ui->ExportTextBaseFile->setEnabled(enable);
    ui->ImportTextBaseFile->setEnabled(enable);
    ui->ExportAsExclFile->setEnabled(enable);
    ui->ImportFromExclFile->setEnabled(enable);
}

bool BtnWidget::exportContarterInfo(QString fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly ))
    {
        QTextStream in(&file);
        QString groupStr = ",Group";
        QString groupSescStr = ",Group Description";
        for(int i=0;i< ui->CurrentGroupCombox->count();i++)
        {
            QString groupName = ui->CurrentGroupCombox->itemText(i);
            groupStr = groupStr+ ","+groupName;
            if(m_allGroupDesc.contains(groupName))
                groupSescStr = groupSescStr+","+m_allGroupDesc.value(groupName);
        }
        in<<groupStr<<"\r\n";
        in<<groupSescStr<<"\r\n";

        //导出分组对应的描述信息；
        for(int i=0;i<ui->ContartsLeftTable->rowCount();i++)
        {
            QString name = ui->ContartsLeftTable->item(i,0)->text();
            QString email = ui->ContartsLeftTable->item(i,1)->text();
            QString textStr = name+","+email;
            for(QMap<QString,QMap<QString,int>>::iterator iter = m_allGroupName.begin();iter != m_allGroupName.end();++iter)
            {
                QMap<QString,int> tempName = iter.value();
                //如果找到了就设置一个V
                qDebug()<<tempName;
                if(tempName.contains(name) && tempName.value(name) == 1)
                {
                    textStr +=",V";
                }
            }
            in<<textStr<<"\r\n";
        }
        file.close();
        return true;
    }
    else
        return false;
}

bool BtnWidget::importContarterInfo(QString fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        m_allGroupName.clear();
        m_allName.clear();
        m_AllIndex.clear();
        m_allGroupDesc.clear();
        m_allGroupName.clear();

        QString textLine;
        QTextStream in(&file);
        while(!in.atEnd())
        {
            textLine = in.readLine();
            if(textLine.contains(",Group,"))
            {
                 QStringList textList = textLine.remove(",Group").split(",");
                 for(int i = 0;i<textList.size();i++)
                 {
                     QString text = textList.at(i);
                     if(text!="")
                     {
                         m_allGroupDesc.insert(text,"");
                         QMap<QString,int> tempData;
                         m_allGroupName.insert(text,tempData);
                     }
                 }
            }
            else if(textLine.contains(",Group Description"))
            {
                QStringList textList = textLine.remove(",Group Description").split(",");
                QMap<QString,QString> ::iterator iter = m_allGroupDesc.begin();
                for(int i = 0;i<textList.size();i++)
                {
                    QString text = textList.at(i);
                    if(text!="")
                    {
                        iter.value() = text;
                        ++iter;
                    }
                }
            }
            else
            {
                QStringList textList = textLine.split(",");
                if(textList.first() == "" )
                {
                    textList.removeFirst();
                }
                QString name = textList.at(0);
                QString email = textList.at(1);
                m_allName.insert(name,email);
                QMap<QString,QMap<QString,int>> tempMap = m_allGroupName;
                QMap<QString,QMap<QString,int>>::iterator iter = m_allGroupName.begin();
                for(int i = 0;i<textList.size()-2;i++)
                {
                    iter.value().insert(name,1);
                    ++iter;
                }
            }
        }
        //数据解析完成，清空左侧联系人信息
        isAddEdit = true;
        for(int i=0;i<ui->ContartsLeftTable->rowCount();i++)
        {
            ui->ContartsLeftTable->removeRow(0);
        }



        //利用解析后的数据重新恢复
        isAddGroupCombox = true;
        ui->CurrentGroupCombox->clear();
        for(QMap<QString,QString>::iterator iter = m_allGroupDesc.begin();iter!=m_allGroupDesc.end();++iter)
        {
            ui->CurrentGroupCombox->addItem(iter.key());
        }
        ui->CurrentGroupCombox->setCurrentIndex(0);
        isAddGroupCombox = false;
        qDebug()<<"当前要设置的群组是: "<<ui->CurrentGroupCombox->currentText();
        ui->GroupDescription->setText(m_allGroupDesc.value(ui->CurrentGroupCombox->currentText()));
        ui->ContactsGroupNumber->setValue(m_allGroupDesc.size());

        qDebug()<<"the group description has "<<m_allGroupDesc.size();


        qDebug()<<"清空右侧表格中的数据";
        for(int i=0;i<ui->ContartsRightTable->rowCount();i++)
            ui->ContartsRightTable->removeRow(0);

        qDebug()<<"向左侧数据表中添加数据,一共有： "<<m_allName.size()<<"  个" ;
        QMap<QString,QString>::iterator iter =  m_allName.begin();
        int row = 0;
        ui->ContartsLeftTable->setRowCount(m_allName.size());
        for(iter;iter!=m_allName.end();++iter)
        {
            ui->ContartsLeftTable->setItem(row,0,new QTableWidgetItem(iter.key()));
            ui->ContartsLeftTable->setItem(row,1,new QTableWidgetItem(iter.value()));
            m_AllIndex.insert(row,iter.key());
            row++;
        }

        //向右侧数据表中添加数据
        qDebug()<<"向右侧数据表中添加数据";
        int rightRow = ui->ContartsRightTable->rowCount();
        int i=0;
        QMap<QString,int> tempRightData = m_allGroupName.value(ui->CurrentGroupCombox->currentText());
        for(QMap<QString,int>::const_iterator iter = tempRightData.begin();iter!=tempRightData.end();++iter)
        {
            if(iter.value() == 1)
            {
                QString Rightname = iter.key();
                QString Rightemial = m_allName.value(Rightname);
                ui->ContartsRightTable->insertRow(rightRow);
                ui->ContartsRightTable->setItem(i,0,new QTableWidgetItem(Rightname));
                ui->ContartsRightTable->setItem(i,1,new QTableWidgetItem(Rightemial));
                rightRow++;
                i++;
                int leftRow = m_AllIndex.key(Rightname);
                ui->ContartsLeftTable->item(leftRow,0)->setTextColor(Qt::red);
                ui->ContartsLeftTable->item(leftRow,1)->setTextColor(Qt::red);
            }
        }
        return true;
    }
    else
        return false;
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

void BtnWidget::on_listWidget_currentRowChanged(int currentRow)
{
    emit listItemChanged(currentRow);
}


void BtnWidget::doColumnSortBtnClicked(int logicIndex)
{
    int sortBit =  m_columnSort.value(logicIndex);
    //默认第一次是降序，第二次与第一次相反
    if(sortBit == -1 || sortBit == 1 )
    {
        sortBit = 0;                //升序
        m_tableModel->horizontalHeaderItem(logicIndex)->setText("↑"+headerList.at(logicIndex));
        execAddTagSort(logicIndex,sortBit);
    }
    else if(sortBit == 0)
    {
        sortBit = 1;                //降序
        m_columnSort.insert(logicIndex,sortBit);
        m_tableModel->horizontalHeaderItem(logicIndex)->setText("↓"+headerList.at(logicIndex));
    }
     m_columnSort.insert(logicIndex,sortBit);
}

//导出表中的数据存储到CSV文件中
void BtnWidget::on_ExportAsCSVFile_clicked()
{
    QMessageBox::information(this,"Tips","导出表中的数据存储到CSV文件中功能暂未实现",QMessageBox::Yes);
}

//从CSV文件中导入数据
void BtnWidget::on_ImportFromCSVFile_clicked()
{
    QMessageBox::information(this,"Tips","从CSV文件中导入数据功能暂未实现",QMessageBox::Yes);
}

//导出表中数据到Execl文件中
void BtnWidget::on_ExportAsExeclFile_clicked()
{
    QMessageBox::information(this,"Tips","导出表中数据到Execl文件中功能暂未实现",QMessageBox::Yes);
}

//从Execl文件中导入数据
void BtnWidget::on_ImportFromExeclFile_clicked()
{
    QMessageBox::information(this,"Tips","从从Execl文件中导入数据功能暂未实现",QMessageBox::Yes);
}

//从所有数据中进行相关数据筛选功能
void BtnWidget::on_SearchByKeyWordBtn_clicked()
{
    QMessageBox::information(this,"Tips","从所有数据中进行相关数据筛选功能功能暂未实现",QMessageBox::Yes);
}

//文字库--新增按钮
void BtnWidget::on_NewAddButton_clicked()
{
    if(textLibraryModel->rowCount() >= 0)
        enableTextLibraryButn(true);
}

//文字库--设置按钮
void BtnWidget::on_SettingButton_clicked()
{
    QMessageBox::information(this,"Tips","文字库--设置按钮功能功能暂未实现",QMessageBox::Yes);
}

//文字库--删除按钮
void BtnWidget::on_DeleteButton_clicked()
{
    if(textLibraryModel->rowCount() == 0)
        enableTextLibraryButn(false);
}

//文字库--删除全部按钮
void BtnWidget::on_DeleteAllButton_clicked()
{
    enableTextLibraryButn(false);
}

//文字库--复制按钮
void BtnWidget::on_CopyButton_clicked()
{
     QMessageBox::information(this,"Tips","文字库--复制按钮功能功能暂未实现",QMessageBox::Yes);
}

//文字库--粘贴按钮
void BtnWidget::on_PasterButton_clicked()
{
    QMessageBox::information(this,"Tips","文字库--粘贴功能功能暂未实现",QMessageBox::Yes);
}

//文字库--导出文字库文件按钮
void BtnWidget::on_ExportTextBaseFile_clicked()
{
    QMessageBox::information(this,"Tips","文字库--导出文字功能功能暂未实现",QMessageBox::Yes);
}

//文字库--导入文字库文件按钮
void BtnWidget::on_ImportTextBaseFile_clicked()
{
    QMessageBox::information(this,"Tips","文字库--导入文字库文件功能功能暂未实现",QMessageBox::Yes);
}

//文字库--导出文字库为EXECL文件按钮
void BtnWidget::on_ExportAsExclFile_clicked()
{
    QMessageBox::information(this,"Tips","文字库--导出文字库为EXECL文件功能功能暂未实现",QMessageBox::Yes);
}

//文字库--导入文字库EXECL文件按钮
void BtnWidget::on_ImportFromExclFile_clicked()
{
    QMessageBox::information(this,"Tips","文字库--导入文字库EXECL文件按钮功能功能暂未实现",QMessageBox::Yes);
}

//文字库--确定按钮
void BtnWidget::on_OKButton_clicked()
{
    this->hide();
}

//文字库--取消按钮
void BtnWidget::on_CancelBtn_clicked()
{
    this->close();
}

//文字库--说明按钮
void BtnWidget::on_ExplainButton_clicked()
{
    QMessageBox::information(this,"Tips","文字库--说明按钮功能功能暂未实现",QMessageBox::Yes);
}

//文字库--后退按钮
void BtnWidget::on_PreviousButton_clicked()
{
    int index = ui->CurrentStatusCombox->currentIndex();
    if(ui->CurrentStatusCombox->currentIndex() > 0)
    {
        index -= 1;
        ui->CurrentStatusCombox->setCurrentIndex(index);
        if(index == 0 )
            ui->PreviousButton->setEnabled(false);
        else if(index != 95)
            ui->NextButton->setEnabled(true);
    }
}

void BtnWidget::on_NextButton_clicked()
{
    int index = ui->CurrentStatusCombox->currentIndex();
    if(ui->CurrentStatusCombox->currentIndex() < ui->CurrentStatusCombox->count() )
    {
        index += 1;
        ui->CurrentStatusCombox->setCurrentIndex(index);
        if(index > 0 )
            ui->PreviousButton->setEnabled(true);
        else if(index == 95)
            ui->NextButton->setEnabled(false);
    }
}

void BtnWidget::on_ZeroPageButton_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int number = button->text().toInt();
    ui->CurrentStatusCombox->setCurrentIndex(number);
}

void BtnWidget::on_CurrentStatusCombox_currentIndexChanged(int index)
{
    if(index>2 && index <= 91)
    {
        int currentIndex = ui->CurrentStatusCombox->currentIndex();
        ui->ZeroPageButton->setText(QString::number(currentIndex-2));
        ui->FirstPageButton->setText(QString::number(currentIndex-1));
        ui->SecibdPageButton->setText(QString::number(currentIndex));
        ui->ThirdPageButton->setText(QString::number(currentIndex+1));
        ui->FourthPageButton->setText(QString::number(currentIndex+2));
        ui->FifthPageButton->setText(QString::number(currentIndex+3));
        ui->SixthPageButton->setText(QString::number(currentIndex+4));
    }
    else  if(index <= 2 && index >= 0)
    {
        ui->ZeroPageButton->setText("0");
        ui->FirstPageButton->setText("1");
        ui->SecibdPageButton->setText("2");
        ui->ThirdPageButton->setText("3");
        ui->FourthPageButton->setText("4");
        ui->FifthPageButton->setText("5");
        ui->SixthPageButton->setText("6");
    }
    else
    {
        ui->ZeroPageButton->setText("89");
        ui->FirstPageButton->setText("90");
        ui->SecibdPageButton->setText("91");
        ui->ThirdPageButton->setText("92");
        ui->FourthPageButton->setText("93");
        ui->FifthPageButton->setText("94");
        ui->SixthPageButton->setText("95");
    }

    if(index == 0)
    {
        ui->PreviousButton->setEnabled(false);
        ui->NextButton->setEnabled(true);
    }
    else if(index == 95)
    {
        ui->PreviousButton->setEnabled(true);
        ui->NextButton->setEnabled(false);
    }
    else
    {
        ui->PreviousButton->setEnabled(true);
        ui->NextButton->setEnabled(true);
    }
}

void BtnWidget::on_FirstPageButton_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int number = button->text().toInt();
    ui->CurrentStatusCombox->setCurrentIndex(number);
}

void BtnWidget::on_SecibdPageButton_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int number = button->text().toInt();
    ui->CurrentStatusCombox->setCurrentIndex(number);
}

void BtnWidget::on_ThirdPageButton_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int number = button->text().toInt();
    ui->CurrentStatusCombox->setCurrentIndex(number);
}

void BtnWidget::on_FourthPageButton_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int number = button->text().toInt();
    ui->CurrentStatusCombox->setCurrentIndex(number);
}

void BtnWidget::on_FifthPageButton_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int number = button->text().toInt();
    ui->CurrentStatusCombox->setCurrentIndex(number);
}

void BtnWidget::on_SixthPageButton_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int number = button->text().toInt();
    ui->CurrentStatusCombox->setCurrentIndex(number);
}

void BtnWidget::on_ContactsGroupNumber_valueChanged(int arg1)
{
    isAddGroupCombox = true;
    ui->CurrentGroupCombox->clear();
    QStringList group{"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P"};
    for(int i=0;i<arg1;i++)
    {
      ui->CurrentGroupCombox->addItem("群组"+group.at(i));
    }
    ui->CurrentGroupCombox->setCurrentIndex(ui->CurrentGroupCombox->count()-1);
    isAddGroupCombox = false;
 }

//导入
void BtnWidget::on_ImportContansFromFile_clicked()
{
    QFileDialog *fDialog = new QFileDialog();
    QString dir = QCoreApplication::applicationDirPath();
    QString fileName = fDialog->getOpenFileName(this,tr("选择导入的csv文件"),dir,tr("*.csv"));
    qDebug()<<"选择的文件是： "<<fileName;

    //执行导入操作
    if(importContarterInfo(fileName))
        QMessageBox::warning(NULL,"提示","数据导入成功",QMessageBox::Yes);
    else
        QMessageBox::warning(NULL,"提示","数据导入失败",QMessageBox::Yes);
}

//导出
void BtnWidget::on_ExportContansToFile_clicked()
{
    QString fileName = QDateTime::currentDateTime().toString("yyyyMMddhhmmss")+QStringLiteral(".csv");
    QString filePath = QFileDialog::getExistingDirectory(this, "选择目标文件夹","./");
    fileName = filePath+"/"+fileName;
    qDebug()<<"数据要保存到的文件位置是： "<<fileName;
    if( exportContarterInfo(fileName) )
        QMessageBox::information(NULL,"提示","数据导出成功",QMessageBox::Yes);
}

void BtnWidget::on_ContansConfirmButton_clicked()
{
    this->hide();
}

void BtnWidget::on_ContactsCancelButton_clicked()
{
    this->hide();
}

//新增
void BtnWidget::on_AddNewContans_clicked()
{
    isAddEdit = true;
    m_allName.clear();
    m_AllIndex.clear();
    QMap<QString,int> nameStatue;
    for(int i=0;i<ui->ContartsLeftTable->rowCount();i++)
    {
        QString name,email;
        name = ui->ContartsLeftTable->item(i,0)->text();
        email = ui->ContartsLeftTable->item(i,1)->text();
        m_AllIndex.insert(i,name);
        m_allName.insert(name,email);
        nameStatue.insert(name,0);
    }
    QString newName ;
    for(int i = 0;i<1024;i++)
    {
        newName = "新联系人"+QString::number(i+1);
        if(!m_allName.contains(newName))
            break;
    }

    int row = ui->ContartsLeftTable->rowCount();
    ui->ContartsLeftTable->insertRow(row);
    ui->ContartsLeftTable->setItem(row,0,new QTableWidgetItem(newName));
    ui->ContartsLeftTable->setItem(row,1,new QTableWidgetItem(newName+"@admin.com"));

    m_AllIndex.insert(row,newName);
    m_allName.insert(newName,newName+"@admin.com");
    nameStatue.insert(newName,0);
    m_allGroupName.insert(ui->CurrentGroupCombox->currentText(),nameStatue);
    isAddEdit = false;

}

//系统参数--联系人列表--联系人删除
void BtnWidget::on_DeleteContans_clicked()
{
    int column = clickItem->column();
    int row = clickItem->row();
    QString name = "";
    if(column == 1)
        name = ui->ContartsLeftTable->item(row,0)->text();
    else if(column == 0)
        name = clickItem->text();

    //待删除的联系人只有左侧表存在
    QMap<QString,QMap<QString,int>>::iterator iter = m_allGroupName.begin();
    for(;iter!=m_allGroupName.end();++iter)
    {
        QMap<QString,int> tempGroup = iter.value();
        for(QMap<QString,int>::iterator it = tempGroup.begin();it!=tempGroup.end();++it)
        {
            if(it.key() == name )
            {
               tempGroup.erase(it);
               break;
            }
        }
    }

    //删除左侧表中的数据项
    if(row >= 0)
        ui->ContartsLeftTable->removeRow(row);

    //删除右侧表格中的数据
    for(int i=0;i<ui->ContartsRightTable->rowCount();i++)
    {
        QString nameStr  = ui->ContartsRightTable->item(i,0)->text();
        if(name == nameStr)
        {
            ui->ContartsRightTable->removeRow(i);
            break;
        }
    } 
}

void BtnWidget::doDealItemClicked(QTableWidgetItem *item)
{
    currentLeftRow = item->row();
    clickItem = item;
}

void BtnWidget::doDealRightItemClicked(QTableWidgetItem *item)
{
    currentRightRow = item->row();
}

void BtnWidget::doNameItemChanged(QTableWidgetItem *item)
{
    int row = item->row();

   if(item->column() == 1 && isAddEdit != true)
   {
       QString name = ui->ContartsLeftTable->item(row,0)->text();
       QString email = item->text();
       if(!email.contains("@admin.com"))
       {
            QMessageBox::warning(NULL,"Tips","此字段格式无法被接受",QMessageBox::Yes);
            ui->ContartsLeftTable->item(row,1)->setText(m_allName.value(name));
            return;
       }
       else
           m_allName.insert(name,email);
   }
   else if(item->column() == 0 && isAddEdit != true && ui->ContartsLeftTable->rowCount() > 0)
   {
       QString name = item->text();
       QString email = ui->ContartsLeftTable->item(row,1)->text();
       qDebug()<<"the name is:"<<name<<"the email is: "<<email<<"the m_allName size is: "<<m_allName;
       QMap<QString,QString> tempName = m_allName;
       if(m_allName.contains(name) && ui->ContartsRightTable->rowCount() > 0)
       {
           QMessageBox::warning(NULL,"提示","该用户名已经存在",QMessageBox::Yes);
           return;
       }

       for(QMap<QString,QString>::iterator iter = m_allName.begin();iter!=m_allName.end();++iter)
       {
           if(iter.value() == email && iter.key() != name)
           {
               m_allName.erase(iter);
               m_allName.insert(name,email);
               qDebug()<<"the "<<email<<" 对应的联系人名称发生了变化";
               break;
           }
       }
   }

}

void BtnWidget::doAddrTableItemClicked(QTableWidgetItem *item)
{
     addrRow = item->row();
}

void BtnWidget::on_LeftMoveToRight_clicked()
{
    if(ui->ContartsLeftTable->rowCount() == 0)
        return;

    if(currentLeftRow == -1)
    {
        QMessageBox::warning(NULL,"提示","请选中要移动的数据项",QMessageBox::Yes);
        return;
    }

    QString name = ui->ContartsLeftTable->item(currentLeftRow,0)->text();
    QString emailAddress = ui->ContartsLeftTable->item(currentLeftRow,1)->text();

    QString groupName = ui->CurrentGroupCombox->currentText();
    QMap<QString,int> tempData = m_allGroupName.value(groupName);
    if(tempData.value(name) == 1)
    {
        QMessageBox::warning(NULL,"提示","该用户名已经存在",QMessageBox::Yes);
        return;
    }
    tempData.insert(name,1);
    m_allGroupName.insert(groupName,tempData);
    int row = ui->ContartsRightTable->rowCount();
    ui->ContartsRightTable->insertRow(row);
    ui->ContartsRightTable->setItem(row,0,new QTableWidgetItem(name));
    ui->ContartsRightTable->setItem(row,1,new QTableWidgetItem(emailAddress));

    isAddEdit = true;
    ui->ContartsLeftTable->item(currentLeftRow,0)->setForeground(QBrush(QColor(255, 0, 0)));
    ui->ContartsLeftTable->item(currentLeftRow,1)->setForeground(QBrush(QColor(255, 0, 0)));
    m_allRightName.push_back(name);
    ui->ContartsLeftTable->setFocus();
    repaint();
}

void BtnWidget::on_RightMoveToLeft_clicked()
{
    if(ui->ContartsRightTable->rowCount() == 0)     //右侧表中没有数据时，禁用
        return;

    if(currentRightRow == -1 || currentRightRow == ui->ContartsRightTable->rowCount())
        currentRightRow = ui->ContartsRightTable->rowCount()-1;
    QString name = ui->ContartsRightTable->item(currentRightRow,0)->text(); 
    int row = m_AllIndex.key(name);
    ui->ContartsLeftTable->item(row,0)->setTextColor(Qt::black);
    ui->ContartsLeftTable->item(row,1)->setTextColor(Qt::black);

    ui->ContartsRightTable->removeRow(currentRightRow);
    m_allRightName.removeOne(name);


    QString groupName = ui->CurrentGroupCombox->currentText();
    QMap<QString,int> tempData = m_allGroupName.value(groupName);//状态重置为 未添加
    tempData.insert(name,0);
    m_allGroupName.insert(groupName,tempData);
}

void BtnWidget::on_CurrentGroupCombox_currentIndexChanged(const QString &arg1)
{
       int row = ui->ContartsRightTable->rowCount();
       if(row > 0 )
       {
           //清空右侧表中的所有数据
           for(int i=0;i<row;i++)
               ui->ContartsRightTable->removeRow(0);
           row = ui->ContartsRightTable->rowCount();

           //左侧表的所有数据颜色恢复为黑色
           for(int i=0;i<ui->ContartsLeftTable->rowCount();i++)
           {
               ui->ContartsLeftTable->item(i,0)->setTextColor(Qt::black);
               ui->ContartsLeftTable->item(i,1)->setTextColor(Qt::black);
           }
       }

       if(isAddGroupCombox)
           return;

       QMap<QString,int> tempName = m_allGroupName.value(arg1);
       qDebug()<<"新分组中包含： "<<tempName<<"  个数据";
       for(QMap<QString,int>::const_iterator iter = tempName.begin();iter!=tempName.end();++iter)
       {
           if(iter.value() == 1)        //表示在右侧表格中已经有这个数据
           {
               QString name = iter.key();
               QString email = m_allName.value(name);
               ui->ContartsRightTable->insertRow(row);
               ui->ContartsRightTable->setItem(row,0,new QTableWidgetItem(name));
               ui->ContartsRightTable->setItem(row,1,new QTableWidgetItem(email));
               int row = m_AllIndex.key(name);
               ui->ContartsLeftTable->item(row,0)->setTextColor(Qt::red);
               ui->ContartsLeftTable->item(row,1)->setTextColor(Qt::red);
           }
       }
       QString groupDesc = m_allGroupDesc.value(ui->CurrentGroupCombox->currentText());
       ui->GroupDescription->setText(groupDesc);
}

void BtnWidget::on_GroupDescription_textChanged(const QString &arg1)
{
    m_allGroupDesc.insert(ui->CurrentGroupCombox->currentText(),arg1);
}

void BtnWidget::on_ConfigComDataOKBtn_clicked()
{
    if(ui->stackedWidget->currentIndex() == 4)
    {
        //需要判断COM口是否已经被占用了
        if(ui->CommunicationPort->currentText().contains("*"))
        {
            QMessageBox::warning(NULL,"提示",ui->CommunicationPort->currentText()+"已经被占用",QMessageBox::Yes);
            return;
        }
        else
            this->accept();
    }
    else
        this->accept();
}

void BtnWidget::on_ConfigComDataCancelBtn_clicked()
{
    this->reject();
}

void BtnWidget::on_AddTransWayOKBtn_clicked()
{
    this->accept();
}

void BtnWidget::on_AddTransWayCancelBtn_clicked()
{
    this->reject();
}

void BtnWidget::on_CloseAddrTableBtn_clicked()
{
    this->reject();
}

//新增地址标签Item
void BtnWidget::on_AddNewAddrItem_clicked()
{
    ConfigDlg->showConfigDialog(AddAddressConfigPage);
    ConfigDlg->setCurrentStationID(currentStationID);
    if( ConfigDlg->exec() == QDialog::Rejected)     //用户以退出方式结束窗口
       return;
    QString stationID,addrType,minValue,maxValue;
    ConfigDlg->getAddrConfigValue(stationID,addrType,minValue,maxValue);
    AddrRangeItem *Item = new AddrRangeItem;
    Item->stationID = stationID;
    Item->addrType = addrType;
    Item->minValue = minValue;
    Item->maxValue = maxValue;
    for(QMap<int,AddrRangeItem>::iterator iter = m_allAddrRange.begin();iter!=m_allAddrRange.end();++iter)
    {
        if(iter.value().stationID == Item->stationID && iter.value().addrType == Item->addrType)
        {
            QMessageBox::warning(NULL,"提示","站号"+Item->stationID+"("+Item->addrType+")已经定义",QMessageBox::Yes);
            return;
        }
    }
    int row = ui->AddLimitTable->rowCount();
    ui->AddLimitTable->insertRow(row);
    m_allAddrRange.insert(ui->AddLimitTable->rowCount(),*Item);
    ui->AddLimitTable->setItem(row,0,new QTableWidgetItem(QString::number(row+1)));
    ui->AddLimitTable->item(row,0)->setTextAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    ui->AddLimitTable->setItem(row,1,new QTableWidgetItem(Item->stationID));
    ui->AddLimitTable->item(row,1)->setTextAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    ui->AddLimitTable->setItem(row,2,new QTableWidgetItem(Item->addrType));
    ui->AddLimitTable->item(row,2)->setTextAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    ui->AddLimitTable->setItem(row,3,new QTableWidgetItem(Item->minValue));
    ui->AddLimitTable->item(row,3)->setTextAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    ui->AddLimitTable->setItem(row,4,new QTableWidgetItem(Item->maxValue));
    ui->AddLimitTable->item(row,4)->setTextAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    row = ui->AddLimitTable->rowCount();
    if(row > 0)
    {
        ui->DelAddrItemBtn->setEnabled(true);
        ui->ConfigAddrItem->setEnabled(true);
    }
}
//删除地址标签Item
void BtnWidget::on_DelAddrItemBtn_clicked()
{
    if(addrRow >=0 )
        ui->AddLimitTable->removeRow(addrRow);
    int row = ui->AddLimitTable->rowCount();
    if(row == 0)
    {
        ui->DelAddrItemBtn->setEnabled(false);
        ui->ConfigAddrItem->setEnabled(false);
    }
    m_allAddrRange.remove(addrRow);

    //移动表格中改行的后续属性
    if(addrRow != row)          //表示删除的不是最后一行或第一行
    {
        for(int i = addrRow;i<row;i++)
        {
            qDebug()<<"要修正的是第： "<<i<<" 行的编号";
            ui->AddLimitTable->item(i,0)->setText(QString::number(i+1));
        }
    }
}
//配置地址标签Item
void BtnWidget::on_ConfigAddrItem_clicked()
{
    qDebug()<<"要配置的是第： "<<addrRow<<" 行数据";
    AddrRangeItem item = m_allAddrRange.value(addrRow+1);
    ConfigDlg->setAddrConfigShowValue(item);
    ConfigDlg->showConfigDialog(ConfigAddressConfigPage);
    if( ConfigDlg->exec() == QDialog::Accepted)
    {
        QString stationID,addrType,minValue,maxValue;
        ConfigDlg->getAddrConfigValue(stationID,addrType,minValue,maxValue);
        AddrRangeItem Item;
        Item.stationID = stationID;
        Item.addrType = addrType;
        Item.minValue = minValue;
        Item.maxValue = maxValue;
        for(QMap<int,AddrRangeItem>::iterator iter = m_allAddrRange.begin();iter!=m_allAddrRange.end();++iter)
        {
            if(iter.value().stationID == Item.stationID && iter.value().addrType == Item.addrType)
            {
                QMessageBox::warning(NULL,"提示","站号"+Item.stationID+"("+Item.addrType+")已经定义",QMessageBox::Yes);
                return;
            }
        }
        m_allAddrRange.insert(addrRow,Item);
        ui->AddLimitTable->item(addrRow,1)->setText(Item.stationID);
        ui->AddLimitTable->item(addrRow,2)->setText(Item.addrType);
        ui->AddLimitTable->item(addrRow,3)->setText(Item.minValue);
        ui->AddLimitTable->item(addrRow,4)->setText(Item.maxValue);
    }
}
