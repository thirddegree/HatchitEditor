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

#include <QTreeView>
#include <QFileSystemModel>
#include <QDirModel>
#include <QPushButton>
#include <include/ht_editor_projectviewmodel.h>

namespace Hatchit
{
    namespace Editor
    {
        class ProjectView : public QTreeView
        {
          Q_OBJECT
        public:
            ProjectView(QWidget* parent = 0);

            void SetViewDirectory(const QString& path);
            void SetRootDirectory(const QString& path);

            QString RootDirectoryPath();
            QString ActiveDirectoryPath();

            void MoveToParentDirectory();

        signals:
            void ActiveDirectoryChanged(const QString&);
            void ImageFileSelected(const QString&);
    
        public slots:
            void OnItemClicked(const QModelIndex& index);
            void OnItemDoubleClicked(const QModelIndex& index);

        private:
            ProjectViewModel*   m_dirModel;    
            QString             m_activeDirectory;
            QString             m_rootDirectory;      
        };
    }
}
