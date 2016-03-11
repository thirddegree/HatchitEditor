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

#include <QDialog>
#include <QMenuBar>
#include <QMenu>
#include <QBoxLayout>
#include <QSplitter>

#include <ht_editor_rdtreeview.h>
#include <ht_editor_rdtextview.h>
#include <ht_editor_rdjsontree.h>

namespace Hatchit
{
    namespace Editor
    {
        class ResourceDatabase : public QDialog
        {
            Q_OBJECT
        public:
            ResourceDatabase(QWidget* parent = 0);

        protected slots:
            void OnFileMenuOpen();

            void OnFileSelection(const QItemSelection& selected,
                                 const QItemSelection& deselected);

        private:
            QMenuBar*                   m_menuBar;
            QMenu*                      m_fileMenu;
            QVBoxLayout*                m_layout;
            QSplitter*                  m_splitter;
            ResourceDatabaseTreeView*   m_treeView;
            ResourceDatabaseTextView*   m_textView;
            ResourceDatabaseJsonTree*   m_jsonTree;


            static const QString ASSET_DIRECTORY_CHECK;
        };
    }
}