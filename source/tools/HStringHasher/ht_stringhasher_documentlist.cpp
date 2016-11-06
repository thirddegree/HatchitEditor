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

#include <ht_stringhasher_documentlist.h>

namespace Hatchit
{
    namespace StringHasher
    {
        DocumentList::DocumentList(QWidget *parent)
            : QListView(parent)
        {
            m_model = new QFileSystemModel;
            m_model->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);
            m_model->setNameFilters(QStringList() << "*.cpp" << "*.cxx" << "*.h" <<
                                                  "*.hpp");
            m_model->setNameFilterDisables(false);

            setModel(m_model);
        }

        DocumentList::~DocumentList()
        {

        }

        void DocumentList::OnFileTreeItemFound(const QFileInfo &file)
        {
            /**
             * Check to make sure the fileinfo doesn't already exist
             * in our list
             */
//            auto it = std::find(m_files.begin(), m_files.end(), file);
//            if(it == m_files.end())
//            {
//                this->addItem(file.fileName());
//            }
        }
    }
}