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

#include <ht_editor_menubar.h>
#include <ht_editor_filemenu.h>

namespace Hatchit {

    namespace Editor {

        MenuBar::MenuBar(QWidget* parent /* = 0 */)
            : QMenuBar(parent)
        {
            m_fileMenu = new FileMenu;
            m_viewMenu = new ViewMenu;
            m_helpMenu = new HelpMenu;



            /**
             * The following code is necessary to force the menubar submenus
             * to have the correct styling to match the rest of the editor
             *
             * NOTE:
             *      If anyone figures out a way to correctly apply
             *      this styling through the editor's stylesheet, this code
             *      should then be removed in favor of styling from the stylesheet
             */
            QPalette p = this->palette();
            p.setColor(QPalette::Highlight, QColor(148, 100, 229));
            p.setColor(QPalette::Base, QColor(35, 43, 43));
            p.setColor(QPalette::Text, Qt::white);
            p.setColor(QPalette::Disabled, QPalette::Text, Qt::gray);
            p.setColor(QPalette::Disabled, QPalette::Light, Qt::gray);
            p.setColor(QPalette::Background, QColor(35, 43, 43));
            m_fileMenu->setPalette(p);
            m_viewMenu->setPalette(p);
            m_helpMenu->setPalette(p);

            addMenu(m_fileMenu);
            addMenu(m_viewMenu);
            addMenu(m_helpMenu);

            /**
             * Attempt to set menu text color from appstyle
             */


            setPalette(p);
        }

        FileMenu* MenuBar::GetFileMenu()
        {
            return m_fileMenu;
        }

        ViewMenu* MenuBar::GetViewMenu()
        {
            return m_viewMenu;
        }

        HelpMenu* MenuBar::GetHelpMenu()
        {
            return m_helpMenu;
        }
    }
}