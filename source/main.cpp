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


/* Qt includes */
#include <QApplication>
#include <QFile>
#include <QStyleFactory>
#include <QPalette>
#include <QMainWindow>
#include <QStyle>
#include <QDesktopWidget>

#include <ht_os.h>
#include <ht_debug.h>
#include <ht_editor_window.h>
#include <ht_editor_launcher.h>
#include <ht_editor_version.h>

using namespace Hatchit;
using namespace Hatchit::Core;
using namespace Hatchit::Editor;

#include <ht_jsonhelper.h>
#include <unordered_map>


int main(int argc, char* argv[])
{

    QApplication app(argc, argv);
	app.setStyle(QStyleFactory::create("fusion"));
    app.setApplicationName(HatchitEditor_TITLE);

    /**
     * Check command line arguments.
     * For now, just check if project path was passed to be
     * opened.
     *
     * TODO:
     *      Implement command-line parse logic to handle
     *      other editor settings passed as parameters.
     */
    QStringList _args = app.arguments();
    if(_args.size() >= 2)
    {
        std::string projectPath = _args[1].toStdString();
    }


	QFile stylesheet(QString::fromStdString(Core::os_exec_dir() + "HatchitEditor.qss"));
	Editor::Window window;
	if (stylesheet.open(QIODevice::ReadOnly))
		window.setStyleSheet(stylesheet.readAll());
    window.setWindowIcon(QIcon(":icons/hatchit.png"));

    /*Create Launcher window and exec first to prompt user for project selection/creation.*/
    Launcher* dlg = new Launcher(&window);
    dlg->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            dlg->size(),
            qApp->desktop()->availableGeometry()
            )
        );
    int result = dlg->exec();
    if(result == QDialog::Rejected)
        return -1;
    dlg->SaveRecent();
    window.showMaximized();



    return app.exec();
}
