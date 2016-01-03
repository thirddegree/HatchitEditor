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

#include <ht_editor_dxview.h>
#include <ht_renderer_singleton.h>
#include <ht_renderer.h>
#include <ht_debug.h>

#include <QResizeEvent>
#include <QTimer>

namespace Hatchit {

    namespace Editor {

        DXView::DXView(QWidget* parent)
            : QWidget(parent)
        {
            

            Graphics::RendererParams params;
            params.renderer = Graphics::RendererType::DIRECTX;
            params.clearColor = Graphics::Colors::CornflowerBlue;
            params.window = (HWND)winId();
            Game::Renderer::Initialize(params);
            
            setAttribute(Qt::WA_PaintOnScreen);
            setAttribute(Qt::WA_NativeWindow);
            setUpdatesEnabled(false);
        }

        DXView::~DXView()
        {
            Game::Renderer::DeInitialize();
        }

        void DXView::paintEvent(QPaintEvent* e)
        {
            Q_UNUSED(e);
        }

        void DXView::resizeEvent(QResizeEvent* e)
        {
            Game::Renderer::ResizeBuffers(width(), height());
        }

        bool DXView::nativeEvent(const QByteArray& eventType, void* message, long* result)
        {
            switch (((MSG*)message)->message)
            {
            case WM_PAINT:
                render();
                break;
            }

            return QWidget::nativeEvent(eventType, message, result);
        }

        void DXView::render()
        {
            Game::Renderer::ClearBuffer(Graphics::ClearArgs::ColorDepthStencil);

            Game::Renderer::Present();
        }
    }

}