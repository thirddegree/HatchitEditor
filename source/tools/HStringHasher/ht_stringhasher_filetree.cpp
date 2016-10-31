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

#include <ht_stringhasher_filetree.h>
#include <ht_os.h>

namespace Hatchit
{
    namespace StringHasher
    {
        FileTree::FileTree(QWidget* parent)
            : QTreeView(parent)
        {
            m_model = new QFileSystemModel;
            m_model->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);
            m_model->setNameFilters(QStringList() << "*.cpp" << "*.cxx" << "*.h" <<
                "*.hpp");
            m_model->setNameFilterDisables(false);
            
            setModel(m_model);
            this->resizeColumnToContents(0);
            this->resizeColumnToContents(1);
            this->resizeColumnToContents(2);
            this->resizeColumnToContents(3);

            connect(this, SIGNAL(doubleClicked(const QModelIndex&)),
                this, SLOT(OnItemDoubleClicked(const QModelIndex&)));
        }

        FileTree::~FileTree()
        {
            
        }

        void FileTree::OnDirectorySelected(const QString& path)
        {
            setRootIndex(m_model->setRootPath(path));
        }

        void FileTree::OnItemDoubleClicked(const QModelIndex& index)
        {
            QFileInfo info(m_model->filePath(index));
            if(info.isFile())
                emit FileSelected(info.absoluteFilePath());
        }




    }
}