
#include <include/unused/ht_editor_rootlayoutmodel.h>
#include <ht_debug.h>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QIcon>
#include <QFont>

RootLayoutModel::RootLayoutModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    mRootItem = new QJsonTreeItem;
    mHeaders.append("key");
    mHeaders.append("value");
}

Qt::ItemFlags RootLayoutModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return 0;

    QModelIndex _index = index;
    QJsonTreeItem* item = static_cast<QJsonTreeItem*>(index.internalPointer());
    if (item)
    {
        if (item->type() != QJsonValue::Array)
        {
            if (index.column() == 1 && item->isEditable())
                return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
        }
    }
   
    

    return QAbstractItemModel::flags(index);
}

QJsonTreeItem * RootLayoutModel::root() const
{
    return mRootItem;
}

bool RootLayoutModel::load(const QString &fileName)
{
    QFile file(fileName);
    bool success = false;
    if (file.open(QIODevice::ReadOnly)) {
        success = load(&file);
        file.close();
    }
    else success = false;

    return success;
}

bool RootLayoutModel::load(QIODevice *device)
{
    return loadJson(device->readAll());
}

QJsonTreeItem* recursiveItemBuild(const QJsonValue& value, QJsonTreeItem* parent)
{
    QJsonTreeItem * rootItem = new QJsonTreeItem(parent);
    rootItem->setKey("root");
   
    if ( value.isObject())
    {

        //Get all QJsonValue childs
        foreach (QString key , value.toObject().keys()){
            QJsonValue v = value.toObject().value(key);
            QJsonTreeItem * child = recursiveItemBuild(v,rootItem);
            child->setKey(key);
            child->setType(v.type());
            rootItem->appendChild(child);

        }

    }

    else if ( value.isArray())
    {
        //Get all QJsonValue childs
        int index = 0;
        foreach (QJsonValue v , value.toArray()){

            QJsonTreeItem * child = recursiveItemBuild(v,rootItem);
            child->setKey(QString::number(index));
            child->setType(v.type());
            rootItem->appendChild(child);
            ++index;
        }
    }
    else
    {
        rootItem->setValue(value.toVariant().toString());
        rootItem->setType(value.type());
    }

    return rootItem;
 
}

QJsonTreeItem* RootLayoutModel::loadItem(const QJsonValue& value, QJsonTreeItem* parent)
{
 

    QJsonTreeItem * rootItem = new QJsonTreeItem(parent);
    rootItem->setKey("root");
   
    /*The root layout format is well defined, and therefore I can make assumptions*/
    /*For one, I know the overall contained data is within a json object*/

    QJsonTreeItem* flagsItem = nullptr;
    QJsonTreeItem* samplersItem = nullptr;
    for(QString key : value.toObject().keys())
    {
        if(key == "Flags")
        {
            //Load flags
            QJsonValue v = value.toObject().value(key);
            flagsItem = recursiveItemBuild(v,rootItem);
            flagsItem->setKey(key);
            flagsItem->setType(v.type());        
        }

        if(key == "Samplers")
        {
            //Load Samplers
            QJsonValue v = value.toObject().value(key);
            samplersItem = recursiveItemBuild(v, rootItem);
            samplersItem->setKey(key);
            samplersItem->setType(v.type());
        }
    }

    rootItem->appendChild(flagsItem);
    rootItem->appendChild(samplersItem);

    return rootItem;
   
}

bool RootLayoutModel::loadJson(const QByteArray &json)
{
    mDocument = QJsonDocument::fromJson(json);

    if (!mDocument.isNull())
    {
        beginResetModel();
        if (mDocument.isArray()) {
            mRootItem = RootLayoutModel::loadItem(QJsonValue(mDocument.array()));
        } else {
            mRootItem = RootLayoutModel::loadItem(QJsonValue(mDocument.object()));
        }
        endResetModel();
        return true;
    }
    return false;
}

bool RootLayoutModel::write(const QString & fileName)
{
    /*Need to build a QJsonDocument containing the modified data*/
    QJsonDocument document;
    
    QJsonTreeItem* parent = mRootItem->child(0);
    if (mDocument.isObject())
    {
        document.setObject(buildObject(parent));
    }
    else if (mDocument.isArray())
    {
        document.setArray(buildArray(parent));
    }

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(document.toJson());
        file.close();
        return true;
    }

    return false;
}

QJsonObject RootLayoutModel::buildObject(QJsonTreeItem * item)
{
    QJsonObject obj;
    obj.insert(item->key(), item->value());
    
    return obj;
}

QJsonArray RootLayoutModel::buildArray(QJsonTreeItem * item)
{
    QJsonArray array;
    
    array.append(buildObject(item));
    int childCount = item->childCount();
    for (int i = 0; i < childCount; i++)
    {
        array.append(buildArray(item->child(i)));
    }

    return array;
}


QVariant RootLayoutModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();


    QJsonTreeItem *item = static_cast<QJsonTreeItem*>(index.internalPointer());
    

    if ((role == Qt::DecorationRole) && (index.column() == 0)){

        return mTypeIcons.value(item->type());
    }


    if (role == Qt::DisplayRole) {

        if (index.column() == 0)
            return QString("%1").arg(item->key());

        if (index.column() == 1)
            return QString("%1").arg(item->value());
    }



    return QVariant();

}

QVariant RootLayoutModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {

        return mHeaders.value(section);
    }
    else
        return QVariant();
}

QModelIndex RootLayoutModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    QJsonTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<QJsonTreeItem*>(parent.internalPointer());

    

    QJsonTreeItem *childItem = parentItem->child(row);
    if (childItem)
    {
        if (column == 1)
        {
            if(!childItem->value().isEmpty())
                childItem->setEditable(true);
        }
       
        childItem->setModelRow(row);
        return createIndex(row, column, childItem);
    }
    else
        return QModelIndex();
}

QModelIndex RootLayoutModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    QJsonTreeItem *childItem = static_cast<QJsonTreeItem*>(index.internalPointer());
    QJsonTreeItem *parentItem = childItem->parent();

    if (parentItem == mRootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int RootLayoutModel::rowCount(const QModelIndex &parent) const
{
    QJsonTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<QJsonTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int RootLayoutModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

void RootLayoutModel::setIcon(const QJsonValue::Type &type, const QIcon &icon)
{
    mTypeIcons.insert(type,icon);
}

bool RootLayoutModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (role != Qt::EditRole)
        return false;

    if (value.toString().isEmpty())
        return false;

    QJsonTreeItem* item = static_cast<QJsonTreeItem*>(index.internalPointer());
    if (item)
    {
        if (index.column() == 0)
            item->setKey(value.toString());
        if (index.column() == 1)
            item->setValue(value.toString());

        emit dataChanged(index, index);
        
        return true;
    }

    return false;
}

