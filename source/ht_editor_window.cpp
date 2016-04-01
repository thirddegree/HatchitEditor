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

#include <ht_editor_window.h>
#include <ht_debug.h>
#include <ht_editor_about.h>

#include <ht_renderer_singleton.h>

#ifdef HT_SYS_WINDOWS
#include <ht_editor_winview.h>
#endif

#include <ht_editor_glview.h>

#include <QDockWidget>
#include <QFileDialog>
#include <QApplication>
#include <QStyle>
namespace Hatchit {

    namespace Editor {

        Window::Window(QWidget* parent /* = 0 */)
            : QMainWindow(parent)
        {
            m_menuBar = new MenuBar;
            setMenuBar(m_menuBar);

#ifdef HT_SYS_WINDOWS
            m_view = new WinView(Graphics::RendererType::DIRECTX12);
#else
            m_view = new GLView;
#endif
            QDockWidget* sceneDock = new QDockWidget(tr("Scene View"));
            m_sceneTree = new SceneTree;
            sceneDock->setWidget(m_sceneTree);
            addDockWidget(Qt::LeftDockWidgetArea, sceneDock);

            QDockWidget* projViewDock = new QDockWidget(tr("Project View"));
            m_projViewCont = new ProjectViewContainer;
            projViewDock->setWidget(m_projViewCont);
            projViewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
            projViewDock->setAllowedAreas(Qt::BottomDockWidgetArea);
            addDockWidget(Qt::BottomDockWidgetArea, projViewDock);


            QDockWidget* resourcePrevDock = new QDockWidget(tr("Resource Preview"));
            m_resourcePreview = new ResourcePreview;
            resourcePrevDock->setWidget(m_resourcePreview);
            addDockWidget(Qt::RightDockWidgetArea, resourcePrevDock);


            /*QWidget* w = new QWidget;
            QHBoxLayout* layout = new QHBoxLayout;
            layout->addWidget(m_view);
            w->setLayout(layout);*/
            setCentralWidget(m_view);

            ConnectMenuSlots();

            connect(m_projViewCont->View(), SIGNAL(ImageFileSelected(const QString&)),
                    m_resourcePreview, SLOT(OnImageResourceSelected(const QString&)));
            
        }

        void Window::OnFileNew()
        {

        }

        void Window::OnFileOpen()
        {
            QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                    "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
            if(!dir.isEmpty())
            {
                m_projViewCont->View()->SetViewDirectory(dir);
            }
        }

        void Window::OnFileSave()
        {

        }

        void Window::OnFileExit()
        {
            close();
        }

        void Window::OnViewDirectX()
        {
            int w = m_view->width();
            int h = m_view->height();
            Game::Renderer::DeInitialize();
            Graphics::RendererParams params;
            params.renderer = Graphics::RendererType::DIRECTX12;
            params.clearColor = Graphics::Colors::CornflowerBlue;
            params.window = (HWND)m_view->winId();
            params.viewportWidth = w;
            params.viewportHeight = h;
            Game::Renderer::Initialize(params);
           /* if (m_view)
                delete m_view;
            QWidget* placeHolder = new QWidget;
            placeHolder->resize(w, h);
            setCentralWidget(placeHolder);

            m_view = new WinView(Graphics::RendererType::DIRECTX12);
            delete placeHolder;
            m_view->resize(w, h);
            setCentralWidget(m_view);*/
        }

        void Window::OnViewVulkan()
        {
            int w = m_view->width();
            int h = m_view->height();
            Game::Renderer::DeInitialize();
            Graphics::RendererParams params;
            params.renderer = Graphics::RendererType::VULKAN;
            params.clearColor = Graphics::Colors::CornflowerBlue;
            params.window = (HWND)m_view->winId();
            params.viewportWidth = w;
            params.viewportHeight = h;
            Game::Renderer::Initialize(params);
            /*if (m_view)
                delete m_view;
            QWidget* placeHolder = new QWidget;
            placeHolder->resize(w, h);
            setCentralWidget(placeHolder);

            m_view = new WinView(Graphics::RendererType::VULKAN);
            m_view->resize(w, h);
            delete placeHolder;
            setCentralWidget(m_view);*/
        }

        void Window::OnHelpAbout()
        {
            AboutDialog dialog(this);

            dialog.exec();
        }

        void Window::ConnectMenuSlots()
        {
            connect(m_menuBar->GetFileMenu()->NewProject(), SIGNAL(triggered()),
                this, SLOT(OnFileNew()));
            connect(m_menuBar->GetFileMenu()->OpenProject(), SIGNAL(triggered()),
                this, SLOT(OnFileOpen()));
            connect(m_menuBar->GetFileMenu()->SaveProject(), SIGNAL(triggered()),
                this, SLOT(OnFileSave()));
            connect(m_menuBar->GetFileMenu()->Exit(), SIGNAL(triggered()),
                this, SLOT(OnFileExit()));

            connect(m_menuBar->GetViewMenu()->DirectXRenderer(), SIGNAL(triggered()),
                this, SLOT(OnViewDirectX()));
            connect(m_menuBar->GetViewMenu()->VulkanRenderer(), SIGNAL(triggered()),
                this, SLOT(OnViewVulkan()));

            connect(m_menuBar->GetHelpMenu()->About(), SIGNAL(triggered()),
                this, SLOT(OnHelpAbout()));
        }

        void Window::setProjectPath(QString path)
        {
            m_projPath = path;
            m_projViewCont->View()->SetRootDirectory(m_projPath);
            m_projViewCont->View()->SetViewDirectory(m_projPath);
        }
    }

}
