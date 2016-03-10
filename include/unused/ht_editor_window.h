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

#include <ht_editor_menubar.h>

#include <QMainWindow>

namespace Hatchit {

    namespace Editor {

        class Window : public QMainWindow
        {
            Q_OBJECT
        public:
            Window(QWidget* parent = 0);

        protected slots:
            void OnFileNew();
            void OnFileOpen();
            void OnFileSave();
            void OnFileExit();

            void OnHelpAbout();

        private:
            MenuBar* m_menuBar;
            QWidget* m_view;

        private:
            void ConnectMenuSlots();
        };

    }
}