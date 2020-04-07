#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include "datatype.h"

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();
    void showConfigDialog(ConfigDialogType type);
    void getAddrConfigValue(QString& stationID, QString& addrType, QString& minValue, QString& maxValue);
    void setAddrConfigShowValue(AddrRangeItem &item);
    void getDeviceNetInfo(QString& ipStr,QString& portStr);
    void setCurrentStationID(int value);
private slots:
    void on_OKButton_clicked();
    void on_CancelButton_clicked();

private:
    void initAddAddrPage();
    void initDeviceNetInfoPage();

private:
    Ui::ConfigDialog *ui;
};

#endif // CONFIGDIALOG_H
