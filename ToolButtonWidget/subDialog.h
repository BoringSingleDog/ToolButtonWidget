#ifndef SUBDIALOG_H
#define SUBDIALOG_H

#include <QDialog>
#include "datatype.h"

namespace Ui {
class subDialog;
}

class subDialog : public QDialog
{
    Q_OBJECT

public:
    explicit subDialog(QWidget *parent = 0);
    ~subDialog();

    void showSubDialog(subWidgetType type);
    void getRotateParameter(int &ClockWise,int &startPos,int &endPos);

private:
    initWidgetControl();


private slots:
    void on_wholeCircular_clicked(bool checked);

private:
    Ui::subDialog *ui;
};

#endif // SUBDIALOG_H
