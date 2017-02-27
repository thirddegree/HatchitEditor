
#include <hpy_debug.h>
#include <hpy_os.h>

namespace py = pybind11;

PYBIND11_PLUGIN(hpy)
{
    py::module m("hpy", "editor python module");

    py::class_<hpy::Console>(m, "console")
            .def("log", &hpy::Console::Log);

    py::class_<hpy::OS>(m, "os")
            .def("exec_dir", &hpy::OS::exec_dir);

    return m.ptr();

}