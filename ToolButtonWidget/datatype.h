#ifndef DATATYPE_H
#define DATATYPE_H
#include <QString>

enum ToolButtonType
{
    BitStatusPointLight = 1001,         //位状态指示灯
    MultStatsPointLight,                //多状态指示灯
    BitStatusConfigure,                 //位状态设置
    MultStatusConfigure,                //多状态设置
    BitStatusSelectSwitch,              //位状态切换开关
    MultStatusSelectSwitch,             //多状态切换开关
    FunctionKeyTool,                    //功能键
    CompMultFuncButton,                 //复合式多功能按钮
    SliderSwitch,                       //滑动开关
    ProjectChooseList,                  //项目选单
    NumberShowButton,                   //数值显示按钮
    CharacterShowButton,                //字符显示按钮
    PieChartItem,                       //圆饼图
    DynamicClibration,                  //动态刻度
    DataGroupItem,                      //数据群组
    XYEllispImage,                      //XY曲线图
    HistogramPage,                      //柱状图
    WatchNeedlePage,                    //表针
    DynamicPainttingPage,               //动态绘图
    MoveGrapgicalPage,                  //移动图形
    PLCControlPage,                     //PLC控制
    IndirectWidgetPage,                 //间接窗口
    DirectWidgetPage,                   //直接窗口
    DataTransportPage,                  //数据传输窗口
    DataTransportBackground,            //资料传输背景
    PhotoCheckPage,                     //图片检视窗口
    VNCViewerPage,                      //VNC Viewer
    QRCodePage,                         //二维码
    WeChatQRCodePage,                   //微信二维码
    DateAndTimePage,                    //日期/时间窗口
    TimerControlPage,                   //计时器窗口
    ScheduleControlPage,                //排程窗口
    SystemParamterPage,                 //系统参数界面
};

//子窗口类型
enum subWidgetType
{
    PartternRotateSettting = 2001,             //图案旋转角度
    XYCuroveUseInformation = 2002,             //XY曲线图形中的数据上下限的使用说明
    WatchNeedleAddrPage = 2003,
    MoreInformationOne = 2004,
    MoreInformationTwo = 2005,
    MoveGraphLimitValueDesc = 2006,
    PLCControlSubWidget = 2007,
    ConfigureReadOnly = 2008,
    FormulaDatabasePage = 2009,
    AddNewDeivceSubPage = 2010,                 //系统参数--设备--新增设备界面
    AddNewHMIDevicePage = 2011,                 //系统参数--设备--新增HMI设备界面

};

//在子窗口中调用显示的界面
enum BtnWidgetType
{
    AddressTagBasePage = 4001,              //地址标签库
    WatchNeedleRegisterType = 4002,
    TextLibraryPage = 4003,                 //文字库
    ContactsConfigPage = 4004,
    ConfigComDataPage = 4005,
    AddTransformPage = 4006,                //地址转换界面
    AddRangeLimitPage = 4007,               //地址范围限制
};

//在子窗口中按钮触发显示的界面
enum ConfigDialogType
{
    AddAddressConfigPage = 5001,            //系统参数界面-->设备属性-->新增-->地址范围限制-->新增
    ConfigAddressConfigPage = 5002,
    NetAddressConfigPage = 5003,            //系统参数界面-->设备属性-->所在位置-->设置
};

//配方数据库右侧表数据结构体
typedef struct
{
    int row;                    //数据所在行
    QString proName;            //项目名称
    QString dataType;           //数据类型
    QString size;                   //大小
    QString showWidth;              //显示宽度
    QString pointNumber;            //小数点
    QString alignType;          //对齐方式

}FormulaItem;

//系统参数--设备--新增设备/HMI--地址范围限制--地址表结构体
typedef struct
{
    QString stationID;
    QString addrType;
    QString minValue;
    QString maxValue;
}AddrRangeItem;

//系统参数--设备--设备表
class DevProperty
{
private:
    QString devFull;    //设备全称  本机？远端？
    QString devName;    //设备名称
    QString devLoca;    //设备位置  本机？远端(IP?PORT?COM?)
    QString devType;    //设备地址
    QString devScre;    //设备界面  COM?
    QString devProt;    //设备协议
    QString devStID;    //设备站号
public:
    DevProperty()
    {
        devFull = "本机";
        devName = "-";
        devLoca = "-";
        devType = "-";
        devScre = "-";
        devProt = "-";
        devStID = "0";
    }
    void setDevFull(QString type){devFull = type;}
    QString getDevFull(){return devFull;}

    void setDevName(QString name){devName = name;}
    QString getDevName(){return devName;}

    void setDevLoca(QString location){devLoca = location;}
    QString getDevLoca(){return devLoca;}

    void setDevType(QString type){devType = type;}
    QString getDevType(){return devType;}

    void setDevScre(QString screen){devScre = screen;}
    QString getDevScre(){return devScre;}

    void setDevProt(QString protocal){devProt = protocal;}
    QString getDevProt(){return devProt;}

    void setDevStID(QString stationID){devStID = stationID;}
    QString getDevStID(){return devStID;}
};

#endif // DATATYPE_H
