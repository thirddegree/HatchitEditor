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

#include <QWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPropertyAnimation>

namespace Hatchit {

    namespace Editor {

        class CollapsePane : public QWidget
        {
            Q_OBJECT
        public:
            CollapsePane(const QString& title, QWidget* contents, bool collapsed = true, QWidget* parent = 0);


        protected:
            void paintEvent(QPaintEvent* e);

        private slots:
            void OnToggle(int);

        private:
            QWidget*        m_contents;
            QString         m_title;
            QCheckBox*      m_button;
            QVBoxLayout*    m_layout;
            QPropertyAnimation* m_collapseAnimation;
            bool            m_collapsed;
        };

    }

}