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

#include <ht_editor_projectviewmodel.h>

#include <QFileInfo>
#include <QApplication>
#include <QStyle>
#include <QDebug>

namespace Hatchit
{

    namespace Editor
    {
        ProjectViewModel::ProjectViewModel(QObject* parent)
            : QDirModel(parent)
        {
            m_texExtensionList << "png" << "jpg" << "tga";
        }

        QVariant ProjectViewModel::data(const QModelIndex& index, int role) const
        {
            QFileInfo info = this->fileInfo(index);
                       
            if(role == Qt::DecorationRole)
            {
                if(m_texExtensionList.contains(info.completeSuffix()))
                {              
                    /*We want to return icon of the texture*/
                    QPixmap image(info.absoluteFilePath());
                
                    return QIcon(image);
                }
              
                return QDirModel::data(index, role);
            }
            
            return QDirModel::data(index, role);

        }
    }
}
