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

#include <ht_editor_collapsepane.h>

#include <QDialog>
#include <QTextBrowser>
#include <QWebView>
#include <QScrollArea>
#include <QLabel>
#include <QEvent>

namespace Hatchit {

    namespace Editor {

        class AboutDialog : public QDialog
        {
            Q_OBJECT
        public:
            AboutDialog(QWidget* parent);

        private slots:
            void OnLoadLicense(bool);

        protected:
            void keyPressEvent(QKeyEvent* e);

        private:
            QScrollArea*    m_scrollArea;
            QLabel*         m_info;
            QWebView*       m_webView;
            CollapsePane*   m_collapsePane;
            CollapsePane*   m_aboutPane;
            CollapsePane*   m_versionInfo;
            QVBoxLayout*    m_mainLayout;
            bool            m_firstLoad;
        };

    }

}