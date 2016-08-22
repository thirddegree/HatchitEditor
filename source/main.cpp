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
#include <QDialog>
#include <QStyle>
#include <QDesktopWidget>


#include <ht_os.h>
#include <ht_file.h>
//#include <ht_editor_window.h>
//#include <ht_editor_launcher.h>
#include <ht_inisettings.h>
#include <ht_path_singleton.h>

using namespace Hatchit;
//using namespace Hatchit::Editor;
using namespace Hatchit::Core;
//using namespace Hatchit::Game;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
	app.setStyle(QStyleFactory::create("fusion"));

	QPalette palette;
	palette.setColor(QPalette::Highlight, QColor(148, 100, 229));
	palette.setColor(QPalette::Base, QColor(35, 43, 43));
	palette.setColor(QPalette::Text, Qt::white);
	palette.setColor(QPalette::Disabled, QPalette::Text, Qt::gray);
	palette.setColor(QPalette::Disabled, QPalette::Light, Qt::gray);
    palette.setColor(QPalette::Background, QColor(35, 43, 43));

	app.setPalette(palette);

	QFile stylesheet("stylesheets/HatchitEditor.qss");
	QMainWindow window;
	if (stylesheet.open(QIODevice::ReadOnly))
		window.setStyleSheet(stylesheet.readAll());


    //*Create Launcher window and exec first to prompt user for project selection/creation.*//
    /*Launcher* dlg = new Launcher(&window);
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

    window.setProjectPath(dlg->ProjectPath());
    window.showMaximized();
	delete dlg;
    */

    window.showMaximized();

    return app.exec();
}