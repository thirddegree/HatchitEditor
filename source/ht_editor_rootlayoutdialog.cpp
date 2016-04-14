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

#include <ht_editor_rootlayoutdialog.h>
#include <QBoxLayout>
#include <QFile>

namespace Hatchit
{
    namespace Editor
    {
        RootLayoutDialog::RootLayoutDialog(QWidget* parent)
            : QDialog(parent)
        {
            setWindowTitle(tr("RootLayout"));   
            resize(800, 600); 

            QVBoxLayout* mainLayout = new QVBoxLayout;

            m_tree = new RootLayoutTree;
            m_textEdit = new QTextEdit;
            m_textEdit->setReadOnly(true);

            QFile rootLayout("TestRootDescriptor.json");
            if(rootLayout.open(QIODevice::ReadOnly))
                m_textEdit->setText(rootLayout.readAll());

            
            m_tabs = new QTabWidget;
            m_tabs->addTab(m_tree, tr("Layout"));
            m_tabs->addTab(m_textEdit, tr("Raw"));

            mainLayout->addWidget(m_tabs);
            
            setLayout(mainLayout);            
        }

    }
}
