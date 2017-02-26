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

#include <ht_editor_filemenu.h>
#include <ht_editor_viewmenu.h>
#include <ht_editor_helpmenu.h>

#include <QMenuBar>

namespace Hatchit {

    namespace Editor {

        class MenuBar : public QMenuBar
        {
            Q_OBJECT
        public:
            MenuBar(QWidget* parent = 0);

            FileMenu* GetFileMenu() const;
            ViewMenu* GetViewMenu() const;
            HelpMenu* GetHelpMenu() const;

        private:
            FileMenu*  m_fileMenu;
            ViewMenu*  m_viewMenu;
            HelpMenu*  m_helpMenu;
        };
    }

}