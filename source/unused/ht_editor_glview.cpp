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

#include <ht_editor_glview.h>
#include <ht_renderer_singleton.h>

namespace Hatchit {

    namespace Editor {

        GLView::GLView(QWidget* parent)
            : QOpenGLWidget(parent)
        {

        }

        void GLView::initializeGL()
        {
            Graphics::RendererParams params;
            params.renderer = Graphics::RendererType::OPENGL;
            params.clearColor = Graphics::Colors::CornflowerBlue;
            Game::Renderer::Initialize(params);
        }

        void GLView::paintGL()
        {
            Game::Renderer::ClearBuffer(Graphics::ClearArgs::ColorDepthStencil);


            Game::Renderer::Present();
        }

        void GLView::resizeGL(int w, int h)
        {
            Game::Renderer::ResizeBuffers(w, h);
        }

    }

}