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

namespace Hatchit {

    namespace Editor {

        CollapsePane::CollapsePane(const QString& title, QWidget* contents, bool collapsed /* = true */, QWidget* parent /* = 0 */)
            : QWidget(parent)
        {
            setObjectName(tr("CollapsePane"));

            m_layout = new QVBoxLayout;
            m_title = title;
            m_contents = contents;

            m_collapsed = collapsed;
            m_contents->setVisible(!m_collapsed);

            m_button = new QCheckBox;
            m_button->setChecked(m_collapsed);
            m_button->setObjectName(tr("CollapseCheck"));

            QHBoxLayout* titleLayout = new QHBoxLayout;
            titleLayout->addWidget(m_button); 
            titleLayout->addWidget(new QLabel(m_title));
            titleLayout->addStretch();
            titleLayout->setSpacing(0);
            
            
            m_layout->addLayout(titleLayout);
            m_layout->addWidget(m_contents);

            setLayout(m_layout);


            connect(m_button, SIGNAL(stateChanged(int)), this, SLOT(OnToggle(int)));
        }

        void CollapsePane::OnToggle(int state)
        {
            m_collapsed = m_button->isChecked();

            m_contents->setVisible(!m_collapsed);

        }

        void CollapsePane::paintEvent(QPaintEvent* e)
        {
            QStyleOption opt;
            opt.init(this);
            QPainter p(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
        }

    }

}