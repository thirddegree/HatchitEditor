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

#include <ht_editor_window.h>
#include <ht_os.h>
#include <QApplication>
#include <QFile>
#include <QStyleFactory>

using namespace Hatchit;
using namespace Hatchit::Editor;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("fusion"));

    /*UPDATE PALETTE FOR USE WITH FUSION STYLE*/
    QPalette palette;
    palette.setColor(QPalette::Highlight, QColor(255, 153, 0));
    palette.setColor(QPalette::Base, QColor(39, 40, 34));
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Disabled, QPalette::Text, Qt::gray);
    palette.setColor(QPalette::Disabled, QPalette::Light, Qt::gray);
    app.setPalette(palette);

    Window window;

    QFile stylesheet(QString::fromStdString(Hatchit::Core::os_exec_dir()) + "HatchitEditor.qss");
    if (stylesheet.open(QIODevice::ReadOnly))
        window.setStyleSheet(stylesheet.readAll());

    window.showMaximized();
    return app.exec();
}
