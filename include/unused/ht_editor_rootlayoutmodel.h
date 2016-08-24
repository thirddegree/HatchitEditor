

#pragma once

#include <QAbstractItemModel>
#include "qjsonitem.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QIcon>

class RootLayoutModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit RootLayoutModel(QObject *parent = 0);
    
    virtual ~RootLayoutModel() { };

    bool load(const QString& fileName);
    bool load(QIODevice * device);
    bool loadJson(const QByteArray& json);
    bool write(const QString& fileName);
    
    QJsonObject buildObject(QJsonTreeItem* item);
    QJsonArray  buildArray(QJsonTreeItem* item);
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    void setIcon(const QJsonValue::Type& type, const QIcon& icon);

    bool setData(const QModelIndex &index, const QVariant &value,
        int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex& index) const;

    QJsonTreeItem* root() const;
private:
    QJsonTreeItem * mRootItem;
    std::vector<QModelIndex> mFlagItems;
    QJsonDocument mDocument;
    QStringList mHeaders;
    QHash<QJsonValue::Type, QIcon> mTypeIcons;


    static QJsonTreeItem* loadItem(const QJsonValue& value, QJsonTreeItem* parent = 0);
};
