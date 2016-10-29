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

#include <ht_stringhasher_menubar.h>
#include <ht_stringhasher_filemenu.h>

namespace Hatchit
{
    namespace StringHasher
    {
        MenuBar::MenuBar(QWidget* parent)
            : QMenuBar(parent)
        {
            m_fileMenu = new FileMenu(this);

            addMenu(m_fileMenu);
        }

        MenuBar::~MenuBar()
        {
            
        }


    }
}