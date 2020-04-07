#ifndef BTNWIDGET_H
#define BTNWIDGET_H

#include <QDialog>
#include "datatype.h"
#include <QString>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QLabel>
#include <QTableWidgetItem>
#include "ConfigDialog.h"

namespace Ui {
class BtnWidget;
}

class BtnWidget : public QDialog
{
    Q_OBJECT

public:
    explicit BtnWidget(QWidget *parent = 0);
    ~BtnWidget();

    void showIndexWidget(BtnWidgetType type);
    QString getChooseItemText(){return chooseItemText;}
    void setCurrentDevType(int key){devType = key;}            //key--0--系统寄存器；  key--0--用户自定义标签
    void setWidgetCallerName(QString Name){callerName = Name;}
    void getComConfigValue(QString& comName,QString& bounRate,QString& dataBit,QString& checkTimes,QString& stopBit,QString& overTime,QString& commDelay,int reSendTimes = 3);
    void setAddrRangeInfo(int value){currentStationID = value;}
    void setComInfoVisiable(QString& text);         //将某项Item设置为 未使用
    void setComInfoDisable(QString& text);          //将某项Item设置为 已使用
    void setComWidgetType(int type);                //type:0表示本机，1表示远端
    void setCurrentComIndex(QString &str);          //指定当前的COM口信息
private slots:
    void on_closeBtn_clicked();
    void on_ConfirmButton_clicked();
    void on_CancelButton_clicked();
    void on_listWidget_currentRowChanged(int currentRow);
    void doColumnSortBtnClicked(int logicIndex);
    void on_ExportAsCSVFile_clicked();                  //--未实现
    void on_ImportFromCSVFile_clicked();                //--未实现
    void on_ExportAsExeclFile_clicked();                //--未实现
    void on_ImportFromExeclFile_clicked();              //--未实现
    void on_SearchByKeyWordBtn_clicked();
    void on_NewAddButton_clicked();
    void on_SettingButton_clicked();
    void on_DeleteButton_clicked();
    void on_DeleteAllButton_clicked();
    void on_CopyButton_clicked();
    void on_PasterButton_clicked();
    void on_ExportTextBaseFile_clicked();               //--未实现
    void on_ImportTextBaseFile_clicked();               //--未实现
    void on_ExportAsExclFile_clicked();                 //--未实现
    void on_ImportFromExclFile_clicked();               //--未实现
    void on_OKButton_clicked();
    void on_CancelBtn_clicked();
    void on_ExplainButton_clicked();
    void on_PreviousButton_clicked();
    void on_NextButton_clicked();
    void on_ZeroPageButton_clicked();
    void on_CurrentStatusCombox_currentIndexChanged(int index);
    void on_FirstPageButton_clicked();
    void on_SecibdPageButton_clicked();
    void on_ThirdPageButton_clicked();
    void on_FourthPageButton_clicked();
    void on_FifthPageButton_clicked();
    void on_SixthPageButton_clicked();
    void on_ContactsGroupNumber_valueChanged(int arg1);
    void on_ImportContansFromFile_clicked();
    void on_ExportContansToFile_clicked();
    void on_ContansConfirmButton_clicked();
    void on_ContactsCancelButton_clicked();
    void on_AddNewContans_clicked();
    void on_DeleteContans_clicked();
    void on_LeftMoveToRight_clicked();
    void on_RightMoveToLeft_clicked();
    void on_CurrentGroupCombox_currentIndexChanged(const QString &arg1);
    void on_GroupDescription_textChanged(const QString &arg1);
    void on_ConfigComDataOKBtn_clicked();
    void on_ConfigComDataCancelBtn_clicked();
    void on_AddTransWayOKBtn_clicked();
    void on_AddTransWayCancelBtn_clicked();
    void on_CloseAddrTableBtn_clicked();
    void on_AddNewAddrItem_clicked();
    void on_DelAddrItemBtn_clicked();
    void on_ConfigAddrItem_clicked();

    void doDealItemClicked(QTableWidgetItem* itm);
    void doDealRightItemClicked(QTableWidgetItem* item);
    void doNameItemChanged(QTableWidgetItem*item);
    void doAddrTableItemClicked(QTableWidgetItem*);

signals:
    void listItemChanged (int index);

private:
    void initAddrTagPage();         //初始化地址标签界面
    void initDevTypeListWidget();   //初始化地址标签列表
    void initTextLibrary();         //初始化文字库界面
    void initContactsPage();
    void initComfigComPage();
    void initAddRangLimitPage();    //初始化地址范围限制界面

    void execAddTagSort(int column,int sortType);           //排序依据，排序顺序   --未实现
    void enableTextLibraryButn(bool enable);
    bool exportContarterInfo(QString fileName);
    bool importContarterInfo(QString fileName);
private:
    Ui::BtnWidget *ui;
    ConfigDialog *ConfigDlg = NULL;
    QString chooseItemText = "";
    QString callerName = "";
    int devType = -1;
    int currentRow = -1;
    int currentLeftRow = -1;
    int currentRightRow = -1;
    int addrRow = -1;               //新增设备当前选中的Item行号
    int currentStationID = -1;      //设备当前ID

    bool isAddEdit = false;
    bool isAddGroupCombox = true;

    QStandardItemModel *m_tableModel = NULL;
    QHeaderView  *m_headerView;
    QMap<int,int> m_columnSort;  //列号，排序标志(0 -升序， 1-降序)
    QMap<int,QString> m_AllIndex;   //左侧表Index,左侧表Name
    QMap<QString,QString> m_allName;
    QMap<QString,QMap<QString,int>> m_allGroupName;  //群组名，(设备名，映射关系)
    QMap<QString,QString>           m_allGroupDesc;  //设备分组的对应描述
    QMap<int,AddrRangeItem>         m_allAddrRange;      //编号(从1开始)，单元格数据

    QVector<QString> m_allRightName;

    QStringList headerList;
    QStandardItemModel *textLibraryModel = NULL;
    QTableWidgetItem *clickItem;


};

#endif // BTNWIDGET_H
