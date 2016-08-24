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

#include <ht_editor_imagepreview.h>

#include <QBoxLayout>

namespace Hatchit
{
    namespace Editor
    {
        ImagePreview::ImagePreview(QWidget* parent)
            : QWidget(parent)
        {
//            setMinimumSize(150,150);            
//            setMaximumSize(400,400);

            QVBoxLayout* layout = new QVBoxLayout;
            m_imageDisplay = new QLabel;
            layout->addWidget(m_imageDisplay);

            setLayout(layout);
        }

        void ImagePreview::SetImageFromPath(const QString& path)
        {
            QPixmap pixmap(path);

            m_imageDisplay->setPixmap(pixmap);
        }
             
    }
}
