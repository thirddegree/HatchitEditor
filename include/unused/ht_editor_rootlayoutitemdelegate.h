
#pragma once

#include <QItemDelegate>

class RootLayoutItemDelegate : public QItemDelegate
{
public:
    RootLayoutItemDelegate(QObject* parent = 0);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
        const QModelIndex& index) const;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
    void setEditorData(QWidget* editor, const QModelIndex& index) const;
};