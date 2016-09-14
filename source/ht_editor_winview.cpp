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

#include <include/ht_editor_winview.h>
#include <ht_debug.h>
#include <thread>

#include <QResizeEvent>
#include <QTimer>
#include <QApplication>

namespace Hatchit {

    namespace Editor {

        WinView::WinView(QWidget* parent)
            : QWidget(parent)
        {
            setAttribute(Qt::WA_PaintOnScreen);
            setAttribute(Qt::WA_NativeWindow);
            setUpdatesEnabled(false);




        }

        WinView::~WinView()
        {

        }

        void WinView::Start()
        {

        }

        void WinView::paintEvent(QPaintEvent* e)
        {
            Q_UNUSED(e);
        }

        void WinView::resizeEvent(QResizeEvent* e)
        {
            Q_UNUSED(e);
            
            emit Resize(width(), height());
        }

    }

}
