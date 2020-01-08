#ifndef DATATYPE_H
#define DATATYPE_H

enum ToolButtonType
{
    BitStatusPointLight = 1001,                //位状态指示灯
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

};


//子窗口类型
enum subWidgetType
{
    PartternRotateSettting = 2001,             //图案旋转角度


};


#endif // DATATYPE_H
