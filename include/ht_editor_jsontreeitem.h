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

#pragma once

#include <ht_string.h>
#include <ht_jsonhelper.h>
#include <vector>

namespace Hatchit
{
    namespace Editor
    {
        using JSON = nlohmann::json;
        class JsonTreeItem
        {
        public:
            JsonTreeItem(JsonTreeItem* parent = 0);

            ~JsonTreeItem();
       
            JsonTreeItem*   GetParent();
            int             GetChildCount();
            std::string     GetValue();
            std::string     GetKey();
            bool            IsEditable();
         
            void            SetKey(std::string key);
            void            SetValue(std::string value);
            void            SetEditable(bool edit);
            
            void            AppendChild(JsonTreeItem* item);
        private:
            std::string                 m_key;
            std::string                 m_value;
            JSON                        m_object;
            bool                        m_editable;

            std::vector<JsonTreeItem*>  m_children;
            JsonTreeItem*               m_parent;
        };
    }
}
