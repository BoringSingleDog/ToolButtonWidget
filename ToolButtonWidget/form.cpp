#include "form.h"
#include "ui_form.h"
#include "datatype.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    m_dialog = new Dialog;
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    m_dialog->showComfirm(BitStatusPointLight);
    m_dialog->show();
}

void Form::on_pushButton_2_clicked()
{
    m_dialog->showComfirm(MultStatsPointLight);
    m_dialog->show();
}

//位状态设置
void Form::on_pushButton_3_clicked()
{
    m_dialog->showComfirm(BitStatusConfigure);
    m_dialog->show();
}
//多状态设置
void Form::on_pushButton_4_clicked()
{
    m_dialog->showComfirm(MultStatusConfigure);
    m_dialog->show();
}
//滑动开关
void Form::on_pushButton_5_clicked()
{
    m_dialog->showComfirm(SliderSwitch);
    m_dialog->show();
}
//位状态切换开关
void Form::on_pushButton_6_clicked()
{
    m_dialog->showComfirm(BitStatusSelectSwitch);
    m_dialog->show();
}
//多状态切换开关
void Form::on_pushButton_7_clicked()
{
    m_dialog->showComfirm(MultStatusSelectSwitch);
    m_dialog->show();
}

void Form::on_pushButton_8_clicked()
{
    m_dialog->showComfirm(FunctionKeyTool);
    m_dialog->show();
}

void Form::on_pushButton_9_clicked()
{
    m_dialog->showComfirm(CompMultFuncButton);
    m_dialog->show();
}

void Form::on_pushButton_10_clicked()
{
    m_dialog->showComfirm(ProjectChooseList);
    m_dialog->show();
}

void Form::on_pushButton_12_clicked()
{
    m_dialog->showComfirm(NumberShowButton);
    m_dialog->show();
}

void Form::on_pushButton_14_clicked()
{
    m_dialog->showComfirm(CharacterShowButton);
    m_dialog->show();
}

void Form::on_pushButton_21_clicked()
{
    m_dialog->showComfirm(PieChartItem);
    m_dialog->show();
}

void Form::on_DynamicClibrationBtn_clicked()
{
    m_dialog->showComfirm(DynamicClibration);
    m_dialog->show();
}

void Form::on_DataGroupBtn_clicked()
{
    m_dialog->showComfirm(DataGroupItem);
    m_dialog->show();
}

void Form::on_pushButton_22_clicked()
{
    m_dialog->showComfirm(XYEllispImage);
    m_dialog->show();
}

void Form::on_HistogramButton_clicked()
{
    m_dialog->showComfirm(HistogramPage);
    m_dialog->show();
}

void Form::on_WatchNeedleBtn_clicked()
{
    m_dialog->showComfirm(WatchNeedlePage);
    m_dialog->show();
}

void Form::on_DynamicPaint_clicked()
{
    m_dialog->showComfirm(DynamicPainttingPage);
    m_dialog->show();
}

void Form::on_pushButton_23_clicked()
{
    m_dialog->showComfirm(MoveGrapgicalPage);
    m_dialog->show();
}

void Form::on_pushButton_24_clicked()
{
    m_dialog->showComfirm(PLCControlPage);
}
