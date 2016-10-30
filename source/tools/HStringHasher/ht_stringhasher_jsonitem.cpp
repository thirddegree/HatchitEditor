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

#include <ht_stringhasher_jsonitem.h>

namespace Hatchit
{
    namespace StringHasher
    {
        JsonItem::JsonItem(JsonItem *parent)
            : m_key(""),
              m_value(""),
              m_editable(true),
              m_parent(parent)
        {

        }

        JsonItem::~JsonItem()
        {

        }

        void JsonItem::SetKey(const QString &key)
        {
            m_key = key;
        }

        void JsonItem::SetValue(const QString &value)
        {
            m_value = value;
        }

        void JsonItem::SetEditable(bool edit)
        {
            m_editable = edit;
        }


        JsonItem* JsonItem::GetChild(int row) const
        {
            return m_children[row];
        }

        JsonItem* JsonItem::GetParent() const
        {
            return m_parent;
        }

        int JsonItem::GetChildCount() const
        {
            return m_children.size();
        }

        QString JsonItem::GetKey() const
        {
            return m_key;
        }

        int JsonItem::GetRow() const
        {
            if(m_parent)
                return m_parent->m_children.indexOf(const_cast<JsonItem*>(this));
            return 0;
        }

        QString JsonItem::GetValue() const
        {
            return m_value;
        }

        bool JsonItem::IsEditable() const
        {
            return m_editable;
        }

        void JsonItem::AppendChild(JsonItem* child)
        {
            m_children.push_back(child);
        }

        JsonItem* JsonItem::load(const Core::JSON &value, JsonItem *parent)
        {
            using namespace Core;

            JsonItem* root = new JsonItem(parent);
            root->SetKey("Root");

            if(value.is_object())
            {
                for(auto it = value.begin(); it != value.end(); it++)
                {
                    JSON v = it.value();
                    JsonItem* child = load(v, root);
                    std::string k = it.key();
                    child->SetKey(QString::fromStdString(k));
                    root->AppendChild(child);
                }
            }
            else if(value.is_array())
            {
                int index = 0;
                for(auto val : value)
                {
                    JsonItem* child = load(val, root);
                    child->SetKey(QString::number(index));
                    root->AppendChild(child);
                    index++;
                }
            }
            else
            {
                std::stringstream ss;
                ss << value;
                root->SetValue(QString::fromStdString(ss.str()));
            }

            return root;
        }

        void JsonItem::Print()
        {
            HT_DEBUG_PRINTF("Key: %s Val: %s\n", m_key.toStdString(), m_value.toStdString());
            if(m_children.size() > 0)
            {
                HT_DEBUG_PRINTF("Children...\n");
                for(int i = 0; i < m_children.size(); i++)
                {
                    m_children[i]->Print();
                }
            }
        }
    }
}