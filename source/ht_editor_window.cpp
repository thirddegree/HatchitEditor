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

#ifdef HT_SYS_WINDOWS
#include <ht_editor_dxview.h>
#endif

#include <ht_editor_glview.h>


namespace Hatchit {

    namespace Editor {

        Window::Window(QWidget* parent /* = 0 */)
            : QMainWindow(parent)
        {
            m_menuBar = new MenuBar;
            setMenuBar(m_menuBar);

#ifdef HT_SYS_WINDOWS
            m_view = new DXView;
#else
            m_view = new GLView;
#endif
            QWidget* w = new QWidget;
            QHBoxLayout* layout = new QHBoxLayout;
            layout->addWidget(m_view);
            w->setLayout(layout);
            setCentralWidget(w);

            ConnectMenuSlots();
        }

        void Window::OnFileNew()
        {

        }

        void Window::OnFileOpen()
        {

        }

        void Window::OnFileSave()
        {

        }

        void Window::OnFileExit()
        {
            close();
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

            connect(m_menuBar->GetHelpMenu()->About(), SIGNAL(triggered()),
                this, SLOT(OnHelpAbout()));
        }
    }

}
