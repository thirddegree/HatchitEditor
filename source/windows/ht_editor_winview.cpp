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

#include <ht_editor_winview.h>
#include <ht_window_singleton.h>
#include <ht_renderer_singleton.h>
#include <ht_time_singleton.h>
#include <ht_renderer.h>
#include <ht_debug.h>
#include <thread>

#include <QResizeEvent>
#include <QTimer>
#include <QApplication>

namespace Hatchit {

    namespace Editor {

        WinView::WinView(Graphics::RendererType type, QWidget* parent)
            : QWidget(parent)
        {
            /*setAttribute(Qt::WA_PaintOnScreen);
            setAttribute(Qt::WA_NativeWindow);*/
            setUpdatesEnabled(false);


            Graphics::RendererParams params;
            params.renderer = type;
            params.clearColor = Graphics::Colors::CornflowerBlue;
            params.window = (HWND)this->winId();
            params.viewportWidth = this->width();
            params.viewportHeight = this->height();
            m_thread = new RenderThread(params);


            /*connect(this, SIGNAL(Resize(uint32_t, uint32_t)),
                m_thread, SLOT(resize(uint32_t, uint32_t)));*/
        }

        WinView::~WinView()
        {
            delete m_thread;
        }

        void WinView::Start()
        {
            m_thread->Start();
        }

        void WinView::paintEvent(QPaintEvent* e)
        {
            Q_UNUSED(e);
        }

        void WinView::resizeEvent(QResizeEvent* e)
        {
            Q_UNUSED(e);
            
            m_thread->resize(this->width(), this->height());
        }

    }

}