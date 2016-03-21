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

#include <ht_editor_projectview.h>

#include <QFileSystemModel>

namespace Hatchit
{
    namespace Editor
    {
        ProjectView::ProjectView(QWidget* parent)
            : QListView(parent)
        {
            m_model = new QFileSystemModel;
            m_model->setRootPath(QDir::currentPath());
                        
            this->setViewMode(QListView::IconMode);            
            this->setFlow(QListView::LeftToRight);
            this->setWrapping(false);
            this->setUniformItemSizes(true);
            this->setModel(m_model);
        }

        void ProjectView::SetViewDirectory(const QString& path)
        {
            this->setRootIndex(m_model->setRootPath(path));
        }
    }
}
