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

#include <ht_editor_rdtreeview.h>

namespace Hatchit
{
    namespace Editor
    {
        ResourceDatabaseTreeView::ResourceDatabaseTreeView(QWidget* parent)
            : QTreeView(parent)
        {
            m_model = new QFileSystemModel;
            m_model->setNameFilters(QStringList() << "*.json");

            setModel(m_model);

            this->hideColumn(1);
            this->hideColumn(2);
            
            
        }

        void ResourceDatabaseTreeView::setDirectory(const QDir& directory)
        {
            /*if (m_model)
                delete m_model;*/
            QString path = directory.absolutePath();

            setRootIndex(m_model->setRootPath(path));
        }
    }
}