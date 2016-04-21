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
#include <QDesktopServices>
#include <QUrl>

namespace Hatchit
{
    namespace Editor
    {
        ProjectView::ProjectView(QWidget* parent)
            : QTreeView(parent)
        {
            m_dirModel = new ProjectViewModel;

            //this->setUniformItemSizes(true);
            this->setModel(m_dirModel);
            this->setContextMenuPolicy(Qt::CustomContextMenu);

            //Build file context menu
            m_fileContext = new QMenu(tr("File Context"));
            QAction* fileContextOpen = m_fileContext->addAction(tr("Open"));

            connect(this, SIGNAL(clicked(const QModelIndex&)), SLOT(OnItemClicked(const QModelIndex&)));
            connect(this, SIGNAL(doubleClicked(const QModelIndex&)), SLOT(OnItemDoubleClicked(const QModelIndex&)));
            connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), SLOT(OnCustomContextMenu(const QPoint&)));
            connect(fileContextOpen, SIGNAL(triggered()), this, SLOT(OnFileContextOpen()));
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

        void ProjectView::OnCustomContextMenu(const QPoint & point)
        {
            QModelIndex index = this->indexAt(point);
            if (index.isValid())
            {
                m_activeRightClickIndex = index;
                if(!m_dirModel->isDir(index))
                    m_fileContext->exec(this->mapToGlobal(point));
            }
        }

        void ProjectView::OnFileContextOpen()
        {
            QString filePath = m_dirModel->filePath(m_activeRightClickIndex);
            if (!filePath.isEmpty())
            {
                //Attempt to open file using DesktopServices
                QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
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
