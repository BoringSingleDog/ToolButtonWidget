#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

//自定义代理，向QTableView中加入lineEdit和combox


#include <QObject>
#include <QItemDelegate>
#include <QComboBox>
#include <QLineEdit>
#include <QStandardItemModel>

//项目名称代理列
class ProNameDelegate:public QItemDelegate
{
    Q_OBJECT
public:
    ProNameDelegate(QObject *parent = 0):QItemDelegate(parent){}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
       QLineEdit *editor = new QLineEdit(parent);
       QRegExp regx("[a-zA-Z0-9]+$");
       editor->setValidator(new QRegExpValidator(regx,parent));
       return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QString text = index.model()->data(index,Qt::EditRole).toString();
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        lineEdit->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        lineEdit->setText(text);
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        QString text = lineEdit->text();
        model->setData(index,text,Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
};

//数据类型代理列-- 使用QCombox
class DataTypeDelegate:public QItemDelegate
{
    Q_OBJECT
 public:
    DataTypeDelegate(QObject *parent = 0):QItemDelegate(parent){}

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QComboBox *combox = new QComboBox(parent);
        combox->addItem("16-bit BCD");
        combox->addItem("32-bit BCD");
        combox->addItem("16-bit Hex");
        combox->addItem("32-bit Hex");
        combox->addItem("16-bit Binary");
        combox->addItem("32-bit Binary");
        combox->addItem("16-bit Unsigned");
        combox->addItem("32-bit Unsigned");
        combox->addItem("32-bit Signed");
        combox->addItem("16-bit Signed");
        combox->addItem("32-bit Float");
        combox->addItem("ASCII");
        combox->addItem("Unicode");
        combox->addItem("高/低互换");
        combox->setCurrentIndex(0);
        return combox;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QString text = index.model()->data(index,Qt::EditRole).toString();
        QComboBox *combox = static_cast<QComboBox*>(editor);
        int comIndex = combox->findText(text);
        combox->setCurrentIndex(comIndex);
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        QComboBox* combox = static_cast<QComboBox*>(editor);
        QString text = combox->currentText();
        model->setData(index,text,Qt::EditRole);
    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }

};

//大小--使用只读lineEdit
class SizeDelegate:public QItemDelegate
{
    Q_OBJECT
 public:
    SizeDelegate(QObject *parent =0):QItemDelegate(parent){}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        return NULL;
    }
};

//显示宽度代理列
class WidthDelegate:public QItemDelegate
{
    Q_OBJECT
public:

    WidthDelegate(QObject *parent = 0):QItemDelegate(parent){}

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QLineEdit *lineEdit = new QLineEdit(parent);
        QRegExp regx("[0-9]+$");
        lineEdit->setValidator(new QRegExpValidator(regx));
        return lineEdit;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QString text = index.model()->data(index,Qt::EditRole).toString();
        QLineEdit *line = static_cast<QLineEdit*>(editor);
        line->setText(text);
        line->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        //先获取控件中的文字信息
        QLineEdit *line = static_cast<QLineEdit*>(editor);
        QString text = line->text();
        model->setData(index,text,Qt::EditRole);
    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
};

//小数点代理列
class pointDeletgate:public QItemDelegate
{
    Q_OBJECT
 public:
    pointDeletgate(QObject *parent = 0):QItemDelegate(parent){}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QLineEdit *line = new QLineEdit(parent);
        line->setValidator(new QIntValidator(0,11));      //只允许输入0~11的数字
        return line;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QString text = index.model()->data(index,Qt::EditRole).toString();
        QLineEdit *line = static_cast<QLineEdit*>(editor);
        line->setText(text);
        line->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        //先获取控件中的文字信息
        QLineEdit *line = static_cast<QLineEdit*>(editor);
        QString text = line->text();
        model->setData(index,text,Qt::EditRole);
    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
};

//对齐代理列
class  TextAlignmentDelegate: public QItemDelegate
{
    Q_OBJECT
 public:
    TextAlignmentDelegate(QObject *parent = 0):QItemDelegate(parent){}

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QComboBox *combox = new QComboBox(parent);
        QStringList list{"左对齐","居中对齐","右对齐"};
        combox->addItems(list);
        combox->setCurrentIndex(0);
        return combox;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QComboBox *combox = static_cast<QComboBox*>(editor);
        QString text = index.model()->data(index,Qt::EditRole).toString();  //获取模型中的数据
        int comIndex = combox->findText(text);             //更改控件中对应的信息
        combox->setCurrentIndex(comIndex);

    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        QComboBox *combox = static_cast<QComboBox*>(editor);
        QString text = combox->currentText();
        model->setData(index,text,Qt::EditRole);
    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
};


#endif // CUSTOMDELEGATE_H
