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

#pragma once

#include <ht_jsonhelper.h>

#include <QAbstractItemModel>
#include <QIODevice>

namespace Hatchit
{
    namespace StringHasher
    {
        class JsonItem;

        class JsonModel : public QAbstractItemModel
        {
        public:
            explicit JsonModel(QObject* parent = nullptr);

            virtual ~JsonModel() {};

            bool load(const QString& fileName);
            bool load(QIODevice* device);
            bool read(Core::JSON& json);

            QVariant data(const QModelIndex& index, int role) const;
//            QVariant headerData(int section, Qt::Orientation orientation, int role) const;
            QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
            QModelIndex parent(const QModelIndex& index) const;
            int rowCount(const QModelIndex& parent = QModelIndex()) const;
            int columnCount(const QModelIndex& parent = QModelIndex()) const;
            bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);

            Qt::ItemFlags flags(const QModelIndex& index) const;


        private:
            JsonItem*   m_root;
        };
    }
}