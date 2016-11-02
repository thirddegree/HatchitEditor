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

#include <ht_stringhasher_processor.h>
#include <ht_stringhasher_document.h>
#include <QDir>
#include <QFile>
#include <QtCore/QDirIterator>

#include <thread>

namespace Hatchit
{
    namespace StringHasher
    {
        Processor::Processor(const QString& input, const QString& output, bool dump)
            : m_inputDirectory(input), m_outputDirectory(output), m_shouldDump(dump)
        {

        }

        Processor::~Processor()
        {

        }

        bool Processor::Execute()
        {
            /**
             * First, we should check to see if we recieved a valid
             * input directory. If so, then we will use that directory as
             * the start point for the recursive processing.
             */
            QList<QFileInfo> m_files;
            if(!m_inputDirectory.isEmpty())
            {
                QDir inputDir(m_inputDirectory);
                inputDir.setNameFilters(QStringList() << "*.h" << "*.hpp" << "*.cpp" << "*.cxx");

                QDirIterator iter(inputDir, QDirIterator::Subdirectories);
                while(iter.hasNext()) {
                    iter.next();
                    m_files.push_back(iter.fileInfo());
                }
            }

            /**
             * Now we should have a list of all the files we want to process
             * We should spawn a few thread to process them in parallel
             */

            std::thread processors[2];
            auto processFunc = [](const QList<QFileInfo>& files)
            {
                /**
                 * Here we need to process the files. But first,
                 * we need to check if the file actually has HID values
                 * to process. If it fails this check, we should skip processing that file.
                 */
                for(auto info : files)
                {
                    QFile file(info.absoluteFilePath());
                    Document document;
                    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                        document.Load(file);

                        /**
                        * If the document post-process has values.
                        */
                        if(document.GetValueCount() > 0)
                        {
                            HT_DEBUG_PRINTF("File: %s\n", info.filePath().toStdString());
                        }
                    }
                }
            };

            QList<QFileInfo> left = m_files.mid(0, m_files.size()/2);
            QFile fileLeft("/home/debunez/left.txt");
            if(fileLeft.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
                for(auto info : left) {
                    fileLeft.write(info.filePath().toLocal8Bit());
                    fileLeft.write("\n");
                }
                fileLeft.close();
            }
            int val = m_files.size()/2;
            QList<QFileInfo> right = m_files.mid((m_files.size()/2)+1, m_files.size());
            QFile fileRight("/home/debunez/right.txt");
            if(fileRight.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
                for(auto info : right) {
                    fileRight.write(info.filePath().toLocal8Bit());
                    fileRight.write("\n");
                }
                fileRight.close();
            }
            processors[0] = std::thread(processFunc, std::ref(left));
            processors[1] = std::thread(processFunc, std::ref(right));
            for(int i = 0; i < 2; i++)
                processors[i].join();

            return true;
        }
    }
}