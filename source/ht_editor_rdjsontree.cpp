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


#include <ht_editor_rdjsontree.h>

namespace Hatchit
{
    namespace Editor
    {
        ResourceDatabaseJsonTree::ResourceDatabaseJsonTree(QWidget* parent)
            : QTreeView(parent)
        {
            m_model = new QJsonModel;

            this->setModel(m_model);
        }

        void ResourceDatabaseJsonTree::loadJson(const QString& text)
        {
            m_model->loadJson(text.toUtf8());
        }

        void ResourceDatabaseJsonTree::load(const QString& filePath)
        {
            m_model->load(filePath);
        }
    }
}