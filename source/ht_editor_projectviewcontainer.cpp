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

#include <include/ht_editor_projectviewcontainer.h>
#include <QBoxLayout>
#include <QStyle>
#include <QApplication>

namespace Hatchit
{

    namespace Editor
    {
        ProjectViewContainer::ProjectViewContainer(QWidget* parent)
            : QWidget(parent)
        {
            m_projView = new ProjectView;

            m_activeDirectory = new QLabel;
            m_activeDirectory->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            QVBoxLayout* layout = new QVBoxLayout;
            QHBoxLayout* buttonLayout = new QHBoxLayout;
            m_moveToParentDir = new QPushButton;
            m_moveToParentDir->setIcon(QApplication::style()->standardIcon(QStyle::SP_FileDialogToParent));
            m_moveToParentDir->setMaximumSize(20,20);
            m_moveToParentDir->setEnabled(false);

            buttonLayout->addWidget(m_moveToParentDir);
            buttonLayout->addWidget(m_activeDirectory);
            layout->addLayout(buttonLayout);

            layout->addWidget(m_projView);

            setLayout(layout);

            connect(m_projView, SIGNAL(ActiveDirectoryChanged(const QString&)), this, SLOT(OnActiveDirectoryChanged(const QString&)));
            connect(m_moveToParentDir, SIGNAL(clicked()), this, SLOT(OnMoveToParentDirectory()));

        }

        ProjectView* ProjectViewContainer::View()
        {
            return m_projView;
        }

        void ProjectViewContainer::OnActiveDirectoryChanged(const QString& dir)
        {
            m_activeDirectory->setText(dir);
            if(dir == m_projView->RootDirectoryPath())
                m_moveToParentDir->setEnabled(false);
            else
                m_moveToParentDir->setEnabled(true);
            
        }

        void ProjectViewContainer::OnMoveToParentDirectory()
        {
            m_projView->MoveToParentDirectory();          
        }
    }
}
