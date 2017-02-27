/**
**    Hatchit Editor
**    Copyright(c) 2015-2017 Third-Degree
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

#include <hpy_os.h>
#include <ht_os.h>

namespace hpy
{
    std::string OS::exec_dir()
    {
        return Hatchit::Core::os_exec_dir();
    }
}