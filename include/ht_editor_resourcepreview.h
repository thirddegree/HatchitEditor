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

#pragma once

#include <QStackedWidget>

#include <ht_editor_imagepreview.h>

namespace Hatchit
{
    namespace Editor
    {
        class ResourcePreview : public QStackedWidget
        {
            Q_OBJECT
        public:
            ResourcePreview(QWidget* parent = 0);

        public slots:
            void OnImageResourceSelected(const QString& path);

        private:
            ImagePreview* m_imagePreview;
        };
    }
}
