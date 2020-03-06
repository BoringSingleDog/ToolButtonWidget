#ifndef FORM_H
#define FORM_H
#include "dialog.h"
#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_21_clicked();

    void on_DynamicClibrationBtn_clicked();

    void on_DataGroupBtn_clicked();

    void on_pushButton_22_clicked();

    void on_HistogramButton_clicked();

    void on_WatchNeedleBtn_clicked();

    void on_DynamicPaint_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_DirectWidget_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

private:
    Ui::Form *ui;
    Dialog *m_dialog;
};

#endif // FORM_H
