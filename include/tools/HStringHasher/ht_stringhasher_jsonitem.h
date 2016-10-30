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
#include <QString>
#include <QList>
#include <QVariant>

namespace Hatchit
{
    namespace StringHasher
    {
        class JsonItem
        {
        public:
            JsonItem(JsonItem* parent = nullptr);

            ~JsonItem();

            JsonItem* GetChild(int row) const;
            JsonItem* GetParent() const;
            int       GetRow() const;
            int       GetChildCount() const;
            void      AppendChild(JsonItem* child);

            void SetKey(const QString& key);
            void SetValue(const QString& value);

            QString GetKey() const;
            QString GetValue() const;

            static JsonItem* load(const Core::JSON& value,
                                  JsonItem* parent = nullptr);

            void Print();

        private:
            QString             m_key;
            QString             m_value;

            QList<JsonItem*>    m_children;
            JsonItem*           m_parent;
        };
    }
}