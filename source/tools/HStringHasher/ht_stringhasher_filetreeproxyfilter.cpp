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

#include <ht_stringhasher_filetreeproxyfilter.h>
#include <QFileSystemModel>
#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>

namespace Hatchit
{
    namespace StringHasher
    {
        FileTreeProxyFilter::FileTreeProxyFilter(QObject* parent)
            : QSortFilterProxyModel(parent)
        {
            
        }

        FileTreeProxyFilter::~FileTreeProxyFilter()
        {
            
        }

        bool FileTreeProxyFilter::filterAcceptsRow(int sourceRow, const QModelIndex& sourceIndex) const
        {
            /**
             * Filter out all files that don't
             * actually have any HID usages.
             */
            QFileSystemModel* model = static_cast<QFileSystemModel*>(sourceModel());
            if (model)
            {
                const QModelIndex index = model->index(sourceRow, 0, sourceIndex);
                QFileInfo info = model->fileInfo(index);
                QFile file(info.absoluteFilePath());
                std::string name = info.fileName().toStdString();
                if (file.open(QIODevice::ReadOnly))
                {
                    QString text = file.readAll();
                    QRegularExpression pattern("(?<=HID\\()\".*\"|(?<=HID\\()\'.*\'");
                    auto iter = pattern.globalMatch(text);
                    if (iter.hasNext())
                        return true;
                    else
                        return false;
                }
            }

            return true;
        }


    }
}