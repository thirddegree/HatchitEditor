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

#include <ht_stringhasher_filemenu.h>

namespace Hatchit
{
    namespace StringHasher
    {
        FileMenu::FileMenu(QWidget* parent)
            : QMenu(tr("File"), parent)
        {
            m_open = new QAction(tr("Open"));

            addAction(m_open);
        }

        FileMenu::~FileMenu()
        {
            
        }

        QAction* FileMenu::GetOpen() const
        {
            return m_open;
        }
    }
}