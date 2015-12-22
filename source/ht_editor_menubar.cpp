/**
**    Hatchit Engine
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

            addMenu(m_fileMenu);
        }

        FileMenu* MenuBar::GetFileMenu()
        {
            return m_fileMenu;
        }
    }
}