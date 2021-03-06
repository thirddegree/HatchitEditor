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

#pragma once

#include <QTreeView>
#include <QFileSystemModel>

namespace Hatchit
{
    namespace StringHasher
    {
        class FileTreeProxyFilter;

        class FileTree : public QTreeView
        {
            Q_OBJECT
        public:
            explicit FileTree(QWidget* parent = nullptr);
            
            ~FileTree();

        public slots:
            void OnDirectorySelected(const QString& path);
            void OnItemDoubleClicked(const QModelIndex& index);
            void OnFileAccepted(const QFileInfo& info);

        signals:
            void FileSelected(const QString& path);
            void FilterFileAccepted(const QFileInfo& info);

        private:
            QFileSystemModel*    m_model;
            FileTreeProxyFilter* m_filter;
        };
    }
}
