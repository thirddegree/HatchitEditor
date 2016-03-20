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

#include <QMenu>

namespace Hatchit {

    namespace Editor {

        class FileMenu : public QMenu
        {
        public:
            FileMenu(QWidget* parent = 0);

            QAction* NewProject();
            QAction* OpenProject();
            QAction* SaveProject();
            QAction* ProjectSettings();
            QAction* Exit();

        private:
            QAction*    m_newProject;
            QAction*    m_openProject;
            QAction*    m_saveProject;
            QAction*    m_projectSettings;
            QAction*    m_exit;
        };

    }
}