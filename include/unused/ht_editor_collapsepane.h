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
#include <QLabel>
#include <QEvent>

namespace Hatchit {

    namespace Editor {

        enum class CollapseState
        {
            Collapsed,
            Expanded,
            CollapsedDisabled,
            ExpandedDisabled
        };

        class CollapsePane;
        class CollapsePaneHeader : public QWidget
        {
            Q_OBJECT
        public:
            CollapsePaneHeader(const QString& title, CollapsePane* parent, CollapseState state = CollapseState::Collapsed);

            void setCollapseState(CollapseState state);

        protected:
            void paintEvent(QPaintEvent* e);
            void enterEvent(QEvent* e);
            void leaveEvent(QEvent* e);
            void mousePressEvent(QMouseEvent* e);

        private:
            QLabel*         m_title;
            QCheckBox*      m_toggle;
            CollapseState   m_state;
        };

        class CollapsePane : public QWidget
        {
            Q_OBJECT
        public:
            CollapsePane(const QString& title, QWidget* contents, QWidget* parent = 0);

            void setCollapseState(CollapseState state);

        protected:
            void paintEvent(QPaintEvent* e);

        private slots:
            void onToggle(int);

        private:
            CollapsePaneHeader* m_header;
            QWidget*            m_contents;
            QVBoxLayout*        m_layout;
        };

    }

}