#include "form.h"
#include  <QCoreApplication>
#include  <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Form W;
    W.show();
    return a.exec();
}
