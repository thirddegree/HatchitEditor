#include "ht_editor_rootlayoutitemdelegate.h"
#include <QComboBox>
#include <QSpinBox>
#include <qjsonitem.h>

RootLayoutItemDelegate::RootLayoutItemDelegate(QObject * parent)
    : QItemDelegate(parent)
{

}

QWidget * RootLayoutItemDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    
    if (index.column() == 1)
    {
        QJsonTreeItem* item = static_cast<QJsonTreeItem*>(index.internalPointer());
        if (item)
        {
            QJsonTreeItem* parentItem = item->parent();
            if (parentItem)
            {
                /*Handle Flags*/
                if (parentItem->key() == "Flags")
                {
                    QComboBox* editor = new QComboBox(parent);
                    editor->addItem("LAYOUT_ALLOW_INPUT_ASSEMLBER_INPUT_LAYOUT");
                    editor->addItem("LAYOUT_DENY_VERTEX_SHADER_ROOT_ACCESS");
                    editor->addItem("LAYOUT_DENY_TESS_CONTROL_SHADER_ROOT_ACCESS");
                    editor->addItem("LAYOUT_DENY_TESS_EVAL_SHADER_ROOT_ACCESS");
                    editor->addItem("LAYOUT_DENY_GEOMETRY_SHADER_ROOT_ACCESS");
                    editor->addItem("LAYOUT_DENY_FRAGMENT_SHADER_ROOT_ACCESS");
                    editor->addItem("LAYOUT_ALLOW_STREAM_OUTPUT");

                    return editor;
                }

                /*Handle Sampler Address Mode*/
                if (parentItem->key() == "Address")
                {
                    QComboBox* editor = new QComboBox(parent);
                    editor->addItem("WRAP");
                    editor->addItem("CLAMP");
                    editor->addItem("BORDER");
                    editor->addItem("MIRROR");
                    editor->addItem("MIRROR_ONCE");

                    return editor;
                }

                /*Handle visibility value*/
                if (item->key() == "Visibility")
                {
                    QComboBox* editor = new QComboBox(parent);
                    editor->addItem("ALL");
                    editor->addItem("VERTEX");
                    editor->addItem("TESS_CONTROL");
                    editor->addItem("TESS_EVAL");
                    editor->addItem("GEOMETRY");
                    editor->addItem("FRAGMENT");
                    
                    return editor;
                }

                /*Handle filter modes*/
                if (parentItem->key() == "Filter")
                {
                    QComboBox* editor = new QComboBox(parent);
                    editor->addItem("NEAREST");
                    editor->addItem("BILINEAR");

                    return editor;
                }

                /*Handle Border Color*/
                if (item->key() == "BorderColor")
                {
                    QComboBox* editor = new QComboBox(parent);
                    editor->addItem("COLOR_TRANSPARENT_BLACK");
                    editor->addItem("COLOR_OPAQUE_BLACK");
                    editor->addItem("COLOR_OPAQUE_WHITE");

                    return editor;
                }

                /*Handle Compare Op*/
                if (item->key() == "CompareOp")
                {
                    QComboBox* editor = new QComboBox(parent);
                    editor->addItem("COMPARE_OP_NEVER");
                    editor->addItem("COMPARE_OP_LESS");
                    editor->addItem("COMPARE_OP_EQUAL");
                    editor->addItem("COMPARE_OP_LESS_EQUAL");
                    editor->addItem("COMPARE_OP_GREATER");
                    editor->addItem("COMPARE_OP_NOT_EQUAL");
                    editor->addItem("COMPARE_OP_GREATER_EQUAL");
                    editor->addItem("COMPARE_OP_ALWAYS");

                    return editor;
                }

                /*Handle all integer based items*/
                bool intCheck;
                item->value().toInt(&intCheck);
                if (intCheck)
                {
                    QSpinBox* editor = new QSpinBox(parent);
                    editor->setMinimum(0);
                    editor->setButtonSymbols(QAbstractSpinBox::NoButtons);
                    return editor;
                }
            }
        }
    }

    return QItemDelegate::createEditor(parent, option, index);
}

void RootLayoutItemDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
    QSpinBox* spinBox = qobject_cast<QSpinBox*>(editor);
    if (spinBox)
    {
        QJsonTreeItem* item = static_cast<QJsonTreeItem*>(index.internalPointer());
        if (item)
        {
            spinBox->interpretText();
            int value = spinBox->value();
            model->setData(index, value, Qt::EditRole);
        }
    }

    QComboBox* editorCombo = qobject_cast<QComboBox*>(editor);
    if (editorCombo)
    {
        QJsonTreeItem* item = static_cast<QJsonTreeItem*>(index.internalPointer());
        if (item)
        {
            item->setValue(editorCombo->currentText());
        }
    }
}

void RootLayoutItemDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
    QSpinBox* spinBox = qobject_cast<QSpinBox*>(editor);
    if (spinBox)
    {
        QJsonTreeItem* item = static_cast<QJsonTreeItem*>(index.internalPointer());
        if (item)
        {
            spinBox->setValue(item->value().toInt());
        }
    }
}
