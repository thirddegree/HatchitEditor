/**
**    Hatchit Editor
**    Copyright(c) 2015-2016 Third-Degree
**
**    GNU General Public License
**    This file may be used under the terms of
**    the GNU General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.GPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU General Public License requirements
**    will be met: https://www.gnu.org/licenses/gpl.html
**
**/

#include <ht_stringhasher_jsonmodel.h>
#include <ht_stringhasher_jsonitem.h>
#include <QFile>

namespace Hatchit
{
    namespace StringHasher
    {
        JsonModel::JsonModel(QObject *parent)
            : QAbstractItemModel(parent)
        {
            m_root = new JsonItem;
        }

        Qt::ItemFlags JsonModel::flags(const QModelIndex &index) const
        {
            if(!index.isValid())
                return 0;

            JsonItem* item = static_cast<JsonItem*>(index.internalPointer());
            if (item)
            {
                /**
                 * Here we could add optional
                 * flag checking to determine if
                 * the model item should be editable.
                 */
                if (index.column() == 1)
                    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
            }

            return QAbstractItemModel::flags(index);
        }

        bool JsonModel::load(const QString& fileName)
        {
            QFile file(fileName);
            if(file.open(QIODevice::ReadOnly)) {
                return load(&file);
            }

            return false;
        }

        bool JsonModel::load(QIODevice* device)
        {
            auto j = Core::JSON::parse(static_cast<const char*>(device->readAll()));

            return read(j);
        }

        bool JsonModel::read(Core::JSON &json)
        {
            if(json.is_null())
                return false;


            beginResetModel();

            /**
             * Load json document into tree
             * structure.
             */
            m_root = JsonItem::load(json);


            endResetModel();

            return true;
        }

        QVariant JsonModel::data(const QModelIndex &index, int role) const
        {
            if(!index.isValid())
                return QVariant();

            JsonItem* item = static_cast<JsonItem*>(index.internalPointer());

            if(role == Qt::DisplayRole)
            {
                if(index.column() == 0)
                    return item->GetKey();
                if(index.column() == 1)
                    return item->GetValue();
            }

            if(role == Qt::EditRole)
            {
                if (index.column() == 1)
                    return item->GetValue();
            }

            return QVariant();
        }

        QVariant JsonModel::headerData(int section, Qt::Orientation orientation, int role) const
        {
            if (role != Qt::DisplayRole)
                return QVariant();

            if(orientation == Qt::Horizontal)
            {
                if (section == 0)
                    return "Key";
                else
                    return "Value";
            }

            return QVariant();
        }

        QModelIndex JsonModel::index(int row, int column, const QModelIndex &parent) const
        {
            if(!hasIndex(row, column, parent))
                return QModelIndex();

            JsonItem* parentItem;
            if(!parent.isValid())
                parentItem = m_root;
            else
                parentItem = static_cast<JsonItem*>(parent.internalPointer());


            JsonItem* child = parentItem->GetChild(row);
            if(child)
            {
                /**
                 * Here we could set it an item is editable based
                 * on column
                 */

                return createIndex(row, column, child);
            }
            else
                return QModelIndex();
        }

        QModelIndex JsonModel::parent(const QModelIndex &index) const
        {
            if(!index.isValid())
                return QModelIndex();

            JsonItem* child = static_cast<JsonItem*>(index.internalPointer());
            JsonItem* parent = child->GetParent();

            if(parent == m_root)
                return QModelIndex();

            return createIndex(parent->GetRow(), 0, parent);
        }

        int JsonModel::rowCount(const QModelIndex &parent) const
        {
            JsonItem* parentItem;
            if(parent.column() > 0)
                return 0;

            if(!parent.isValid())
                parentItem = m_root;
            else
                parentItem = static_cast<JsonItem*>(parent.internalPointer());

            return parentItem->GetChildCount();
        }

        int JsonModel::columnCount(const QModelIndex &parent) const
        {
            Q_UNUSED(parent);

            return 2;
        }

        bool JsonModel::setData(const QModelIndex &index, const QVariant &value, int role)
        {
            if(role != Qt::EditRole)
                return false;

            if(value.toString().isEmpty())
                return false;

            JsonItem* item = static_cast<JsonItem*>(index.internalPointer());
            if(item)
            {
                if(index.column() == 0)
                    item->SetKey(value.toString());
                if(index.column() == 1)
                    item->SetValue(value.toString());

                emit dataChanged(index, index);

                return true;
            }

            return false;
        }

    }
}