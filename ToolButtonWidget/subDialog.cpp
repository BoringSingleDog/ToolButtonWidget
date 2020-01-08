#include "subDialog.h"
#include "ui_subDialog.h"

subDialog::subDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::subDialog)
{
    ui->setupUi(this);
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

subDialog::initWidgetControl()
{
    ui->endLabel->hide();
    ui->endLineEdit->hide();
    ui->endLineEdit->setValidator(new QIntValidator(0,360,this));
    ui->startLineEdit->setValidator(new QIntValidator(0,360,this));
    ui->endLineEdit->setPlaceholderText("0~360");
    ui->startLineEdit->setPlaceholderText("0~360");
}

void subDialog::on_wholeCircular_clicked(bool checked)
{
    ui->endLabel->setHidden(checked);
    ui->endLineEdit->setHidden(checked);
}

