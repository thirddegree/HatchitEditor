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

#include <ht_platform.h>
#include <include/ht_editor_viewport.h>

#ifdef HT_SYS_WINDOWS
//#include <ht_editor_dxview.h>
#endif

//#include <ht_editor_glview.h>

namespace Hatchit {

    namespace Editor {

        Viewport::Viewport(QWidget* parent)
            : QWidget(parent)
        {

        }

    }

}
