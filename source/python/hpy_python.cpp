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

#include <hpy_python.h>
#include <Python.h>
#include <ht_os.h>
#include <ht_string.h>

namespace hpy
{
    Python& Python::instance()
    {
        static Python _instance;

        return _instance;
    }

    void Python::Init(int argc, char **argv)
    {
        using namespace Hatchit;
        using namespace Hatchit::Core;

        Py_SetProgramName(reinterpret_cast<wchar_t*>(argv[0]));
        Py_Initialize();
        Py_SetPath(string_to_wstring(os_exec_dir()).c_str());

    }

    void Python::ShutDown()
    {
        Py_Finalize();
    }
}