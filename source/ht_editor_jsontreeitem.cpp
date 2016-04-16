/**
**    Hatchit Editor
**    Copyright(c) 2015 Third-Degree
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

#include <ht_editor_jsontreeitem.h>

namespace Hatchit
{
    namespace Editor
    {
        JsonTreeItem::JsonTreeItem(JsonTreeItem* parent)
        {

        }

        JsonTreeItem::~JsonTreeItem()
        {

        }

        JsonTreeItem* JsonTreeItem::GetParent()
        {
            return m_parent;
        }

        std::string JsonTreeItem::GetKey()
        {
            return m_key;
        }

        std::string JsonTreeItem::GetValue()
        {
            return m_value;
        }

        int JsonTreeItem::GetChildCount()
        {
            return static_cast<int>(m_children.size());
        }

        bool JsonTreeItem::IsEditable()
        {
            return m_editable;
        }

        void JsonTreeItem::SetKey(std::string key)
        {
            m_key = key;
        }

        void JsonTreeItem::SetValue(std::string value)
        {
            m_value = value;
        }

        void JsonTreeItem::SetEditable(bool edit)
        {
            m_editable = edit;
        }

        void JsonTreeItem::AppendChild(JsonTreeItem* child)
        {
            m_children.push_back(child);
        }

    }
}
