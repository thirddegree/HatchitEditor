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
#include <QDir>

#include <ht_stringhasher_dialog.h>
#include <ht_os.h>
#include <ht_debug.h>
#include <ht_stringhasher_jsonitem.h>
#include <ht_stringhasher_document.h>
#include <ht_stringhasher_processor.h>

using namespace Hatchit;
using namespace Hatchit::StringHasher;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    /**
     * Determine if stringhasher has been run with command line user arguments,
     * if no arguments specified then the application GUI is executed.
     */
    QStringList _args = app.arguments();
    if(_args.size() > 1)
    {
        /**
         * We will check for specific command line arguments.
         * Options:
         *
         * -i -- the input directory to recursively search, and process files
         * -o -- the output directory to write processed files
         * --dump -- dump the processed files (i.e don't match directory structure)
         *           NOTE: this could result in file name clashes which will NOT be handled.
         */

        QString inDir;
        QString outDir;
        auto it = std::find(_args.begin(), _args.end(), "-i");
        if(it != _args.end())
            inDir = *(++it);

        it = std::find(_args.begin(), _args.end(), "-o");
        if(it != _args.end())
            outDir = *(++it);

        bool shouldDump = false;
        it = std::find(_args.begin(), _args.end(), "--dump");
        if(it != _args.end())
            shouldDump = true;
        shouldDump = true; //for now, this will always be true

        /**
         * We should first check the arguments of the input and output
         * to make sure they are valid arguments.
         *
         * Check Input Directory
         * Check Output Directory
         */
        QFileInfo _in(inDir);
        if(!_in.isDir()) {
            HT_ERROR_PRINTF("Invalid input directory.\n");
            return -1;
        }

        QFileInfo _out(outDir);
        if(!_out.isDir()) {
            HT_ERROR_PRINTF("Invalid output directory.\n");
            return -1;
        }


        /**
         * Now, we instantiate a processor object with the parsed information.
         * It will then process recursively the files multi-threaded and output
         * the results.
         */
        Processor processor(inDir, outDir, shouldDump);

        if(!processor.Execute())
            return -1;

        return 0;
    }
    else
    {
        app.setStyle(QStyleFactory::create("fusion"));
        QFile stylesheet(QString::fromStdString(Core::os_exec_dir() + "HatchitEditor.qss"));
        if (stylesheet.open(QIODevice::ReadOnly))
            app.setStyleSheet(stylesheet.readAll());

        Dialog dlg;
        dlg.setWindowIcon(QIcon(":icons/hatchit.png"));
        dlg.show();

        return app.exec();
    }
}