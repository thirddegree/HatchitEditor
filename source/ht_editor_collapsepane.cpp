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

#include <ht_editor_collapsepane.h>
#include <QBoxLayout>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QSizePolicy>

namespace Hatchit {

    namespace Editor {

        CollapsePaneHeader::CollapsePaneHeader(const QString& title,
                                               CollapsePane* parent,
                                               CollapseState state /* = CollapseState::Collapsed */)
            : QWidget(parent)
        {
            setObjectName(tr("CollapsePaneHeader"));

            this->setAttribute(Qt::WA_Hover);
            m_title = new QLabel(title);
            m_title->setObjectName("CollapsePaneHeaderTitle");
            m_toggle = new QCheckBox;
            m_toggle->setObjectName(tr("CollapseCheck"));

            QHBoxLayout* layout = new QHBoxLayout;
            layout->addSpacing(5);
            layout->addWidget(m_toggle);
            layout->addWidget(m_title);
            layout->addStretch();
            layout->setSpacing(0);
            layout->setMargin(0);


            connect(m_toggle, SIGNAL(stateChanged(int)), parent, SLOT(onToggle(int)));

            setCollapseState(state);

            setLayout(layout);
        }

        void CollapsePaneHeader::paintEvent(QPaintEvent* e)
        {
            QStyleOption opt;
            opt.init(this);
            QPainter p(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
        }

        void CollapsePaneHeader::enterEvent(QEvent* e)
        {
            QWidget::enterEvent(e);
        }

        void CollapsePaneHeader::leaveEvent(QEvent* e)
        {
            QWidget::leaveEvent(e);
        }

        void CollapsePaneHeader::mousePressEvent(QMouseEvent* e)
        {
            if (m_state == CollapseState::CollapsedDisabled ||
                m_state == CollapseState::ExpandedDisabled)
                return;

            if (e->button() == Qt::LeftButton)
                m_toggle->toggle();
        }

        void CollapsePaneHeader::setCollapseState(CollapseState state)
        {
            m_state = state;
            switch (m_state)
            {
            case CollapseState::Collapsed:
                m_toggle->setChecked(true);
                break;
            case CollapseState::Expanded:
                m_toggle->setChecked(false);
                break;
            case CollapseState::CollapsedDisabled:
                m_toggle->setChecked(true);
                m_toggle->setDisabled(true);
                break;
            case CollapseState::ExpandedDisabled:
                m_toggle->setChecked(false);
                m_toggle->setDisabled(true);
                break;

            default:
                break;
            }
        }


        CollapsePane::CollapsePane(const QString& title, QWidget* contents, QWidget* parent /* = 0 */)
            : QWidget(parent)
        {
            setObjectName(tr("CollapsePane"));

            m_layout = new QVBoxLayout;
            m_contents = contents;
            m_header = new CollapsePaneHeader(title, this);


            m_layout->setContentsMargins(4, 4, 4, 4);
            m_layout->addWidget(m_header);
            m_layout->addWidget(m_contents);


            setLayout(m_layout);

        }

        void CollapsePane::onToggle(int state)
        {
            if (state == Qt::Checked) {
                m_contents->setVisible(false);
            }
            else {
                m_contents->setVisible(true);
            }

        }

        void CollapsePane::paintEvent(QPaintEvent* e)
        {
            QStyleOption opt;
            opt.init(this);
            QPainter p(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
        }

        void CollapsePane::setCollapseState(CollapseState state)
        {
            m_header->setCollapseState(state);
        }

    }

}
