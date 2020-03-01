#ifndef DATATYPE_H
#define DATATYPE_H

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
};


//子窗口类型
enum subWidgetType
{
    PartternRotateSettting = 2001,             //图案旋转角度
    XYCuroveUseInformation = 2002,             //XY曲线图形中的数据上下限的使用说明
    AddressSubDialogPage = 2003,               //XY曲线图中的地址格式子页面
    WatchNeedleAddrPage = 2004,
    MoreInformationOne = 2005,
    MoreInformationTwo = 2006,
    MoveGraphLimitValueDesc = 2007,
    PLCControlSubWidget = 2008,

};



//在子窗口中调用显示的界面
enum BtnWidgetType
{
    AddressTagBasePage = 4001,
    WatchNeedleRegisterType = 4002,
};

#endif // DATATYPE_H
