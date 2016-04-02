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
#include <ht_renderer_singleton.h>
#include <ht_time_singleton.h>
#include <ht_renderer.h>
#include <ht_debug.h>

#include <QResizeEvent>
#include <QTimer>
#include <QApplication>

namespace Hatchit {

    namespace Editor {

        WinView::WinView(Graphics::RendererType type, QWidget* parent)
            : QWidget(parent)
        {
           
            Graphics::RendererParams params;
            params.renderer = type;
            params.clearColor = Graphics::Colors::CornflowerBlue;
            params.window = (HWND)winId();
            params.viewportWidth = this->width();
            params.viewportHeight = this->height();
            Game::Renderer::Initialize(params);

            setAttribute(Qt::WA_PaintOnScreen);
            setAttribute(Qt::WA_NativeWindow);
            setUpdatesEnabled(false);

            connect(&timer, SIGNAL(timeout()), this, SLOT(OnFrameUpdate()));

            Game::Time::Start();
            timer.start(1);
        }

        WinView::~WinView()
        {
            Game::Renderer::DeInitialize();
        }

        void WinView::OnFrameUpdate()
        {
            Game::Time::Tick();
            
            render();

            /*Emit WM_PAINT message to repaint each frame*/
            SendMessage((HWND)winId(), WM_PAINT, NULL, NULL);
        }

        void WinView::paintEvent(QPaintEvent* e)
        {
            Q_UNUSED(e);
        }

        void WinView::resizeEvent(QResizeEvent* e)
        {
            Q_UNUSED(e);
            Game::Renderer::ResizeBuffers(width(), height());
        }

        bool WinView::nativeEvent(const QByteArray& eventType, void* message, long* result)
        {
            switch (((MSG*)message)->message)
            {
            case WM_PAINT:
                render();
                break;
            }

            return QWidget::nativeEvent(eventType, message, result);
        }

        void WinView::render()
        {
            Game::Time::Tick();

            Game::Renderer::ClearBuffer(Graphics::ClearArgs::ColorDepthStencil);

            Game::Renderer::Render();

            Game::Renderer::Present();
        }
    }

}