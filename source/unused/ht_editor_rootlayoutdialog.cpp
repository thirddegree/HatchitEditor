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
#include <ht_path_singleton.h>
#include <QBoxLayout>
#include <QFile>
#include <QMenuBar>

namespace Hatchit
{
    namespace Editor
    {
        class RootLayoutMenuBar : public QMenuBar
        {
        public:
            RootLayoutMenuBar(QWidget* parent = 0);

            QAction* OpenAction();
            QAction* SaveAction();
        private:
            QAction* m_open;
            QAction* m_save;
        };

        RootLayoutMenuBar::RootLayoutMenuBar(QWidget* parent)
            : QMenuBar(parent)
        {
            QMenu* fileMenu = new QMenu(tr("File"));

            m_open = new QAction(tr("Open"), nullptr);
            m_save = new QAction(tr("Save"), nullptr);

            fileMenu->addAction(m_open);
            fileMenu->addAction(m_save);

            addMenu(fileMenu);
        }

        QAction* RootLayoutMenuBar::OpenAction()
        {
            return m_open;
        }

        QAction* RootLayoutMenuBar::SaveAction()
        {
            return m_save;
        }

        RootLayoutDialog::RootLayoutDialog(QWidget* parent)
            : QDialog(parent)
        {
            setWindowTitle(tr("RootLayout"));
            
            resize(800, 600); 

            RootLayoutMenuBar* menuBar = new RootLayoutMenuBar;

            QVBoxLayout* mainLayout = new QVBoxLayout;

            m_tree = new RootLayoutTree;
            m_textEdit = new QTextEdit;
            m_textEdit->setReadOnly(true);

            QFile rootLayout(QString::fromStdString(Core::Path::Value(Core::Path::Directory::Assets) + "TestRootDescriptor.json"));
            if(rootLayout.open(QIODevice::ReadOnly))
                m_textEdit->setText(rootLayout.readAll());

            
            m_tabs = new QTabWidget;
            m_tabs->addTab(m_tree, tr("Layout"));
            m_tabs->addTab(m_textEdit, tr("Raw"));

            mainLayout->addWidget(m_tabs);
            mainLayout->setMenuBar(menuBar);
            
            setLayout(mainLayout);          


            
        }

        void RootLayoutDialog::OnFileOpen()
        {

        }

        void RootLayoutDialog::OnFileSave()
        {

        }

    }
}
