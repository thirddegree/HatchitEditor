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
            m_dirModel = new ProjectViewModel;

            this->setUniformItemSizes(true);
            this->setModel(m_dirModel);

            connect(this, SIGNAL(clicked(const QModelIndex&)), SLOT(OnItemClicked(const QModelIndex&)));
            connect(this, SIGNAL(doubleClicked(const QModelIndex&)), SLOT(OnItemDoubleClicked(const QModelIndex&)));
        }

        void ProjectView::SetViewDirectory(const QString& path)
        {
            m_activeDirectory = path;

            this->setRootIndex(m_dirModel->index(path));

            emit ActiveDirectoryChanged(m_activeDirectory);
        }


        void ProjectView::SetRootDirectory(const QString& path)
        {
            m_rootDirectory = path;
        }

        void ProjectView::MoveToParentDirectory()
        {
            QDir dir(m_activeDirectory);
            dir.cdUp();
            m_activeDirectory = dir.absolutePath();

            this->setRootIndex(m_dirModel->index(m_activeDirectory));

            emit ActiveDirectoryChanged(m_activeDirectory);
        }


        void ProjectView::OnItemClicked(const QModelIndex& index)
        {
            QFileInfo info(m_dirModel->filePath(index));
            if(info.isFile())
            {
                /*Handle each type of file*/
                if(info.completeSuffix() == "png")
                {
                    emit ImageFileSelected(info.absoluteFilePath());
                }               
            }
        }

        void ProjectView::OnItemDoubleClicked(const QModelIndex& index)
        {
            QFileInfo info(m_dirModel->filePath(index));
            if(info.isDir())
            {
                m_activeDirectory = m_dirModel->filePath(index);
                this->setRootIndex(m_dirModel->index(m_activeDirectory));
            
                emit ActiveDirectoryChanged(m_activeDirectory);
            }
        }

        QString ProjectView::ActiveDirectoryPath()
        {
            return m_activeDirectory;
        }

        QString ProjectView::RootDirectoryPath()
        {
            return m_rootDirectory;
        }
    }
}
