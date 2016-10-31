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

#include <ht_stringhasher_valuetree.h>
#include <ht_stringhasher_jsonmodel.h>
#include <ht_stringhasher_document.h>

namespace Hatchit
{
    namespace StringHasher
    {
        ValueTree::ValueTree(QWidget* parent)
            : QTreeView(parent)
        {
            m_model = new JsonModel;
            setModel(m_model);

        }

        ValueTree::~ValueTree()
        {
            
        }

        void ValueTree::SetDocument(const Document& document)
        {
            Core::JSON json = Core::JSON::parse(document.Serialize());
            m_model->read(json);
        }
    }
}