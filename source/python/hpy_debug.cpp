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

#include <hpy_debug.h>

#include <pybind11/cast.h>

using namespace Hatchit::Core;

namespace hpy
{
    void Console::Log(int severity, py::args arguments)
    {
        auto strings = py::tuple(arguments.size());
        for (size_t i = 0; i < arguments.size(); ++i) {
            strings[i] = py::str(arguments[i]);
        }
        auto sep = py::cast(" ");
        auto line = sep.attr("join")(strings);

        HT_DEBUG_PRINTF("%s\n", line.cast<std::string>());
    }

}
