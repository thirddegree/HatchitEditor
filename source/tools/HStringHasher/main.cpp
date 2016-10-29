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

#include <QApplication>
#include <QFile>
#include <QIcon>
#include <QStyleFactory>

#include <ht_stringhasher_dialog.h>
#include <ht_os.h>

using namespace Hatchit;
using namespace Hatchit::StringHasher;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("fusion"));

    QFile stylesheet(QString::fromStdString(Core::os_exec_dir() + "HatchitEditor.qss"));
    Dialog dlg;
    if (stylesheet.open(QIODevice::ReadOnly))
        dlg.setStyleSheet(stylesheet.readAll());
    dlg.setWindowIcon(QIcon(":icons/hatchit.png"));
    dlg.show();

    return app.exec();
}