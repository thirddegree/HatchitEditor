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
           
            setAttribute(Qt::WA_PaintOnScreen);
            setAttribute(Qt::WA_NativeWindow);
            setUpdatesEnabled(false);

            m_destroyed = false;
        }

        WinView::~WinView()
        {
            m_destroyed = true;
        }

        void WinView::Start()
        {
            m_render = std::thread([](std::atomic_bool& dead, HWND wnd) {

                Graphics::RendererParams params;
                params.renderer = Graphics::RendererType::DIRECTX12;
                params.clearColor = Graphics::Colors::CornflowerBlue;
                params.window = wnd;
                params.viewportWidth = 500;
                params.viewportHeight = 500;

                Game::Renderer::Initialize(params);
                Game::Time::Start();

                while (!dead)
                {
                    Game::Time::Tick();

                    Game::Renderer::ClearBuffer(Graphics::ClearArgs::ColorDepthStencil);

                    Game::Renderer::Render();

                    Game::Renderer::Present();
                }

                Game::Renderer::DeInitialize();

            }, std::ref(m_destroyed), (HWND)this->winId());

            m_render.detach();
        }

        void WinView::OnFrameUpdate()
        {
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
            //Game::Renderer::ResizeBuffers(width(), height());
        }

        bool WinView::nativeEvent(const QByteArray& eventType, void* message, long* result)
        {
            switch (((MSG*)message)->message)
            {
            case WM_PAINT:
                
                break;
            }

            return QWidget::nativeEvent(eventType, message, result);
        }

        void WinView::render()
        {
           

            
        }
    }

}