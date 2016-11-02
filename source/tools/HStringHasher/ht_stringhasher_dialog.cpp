/**
**    Hatchit Editor
**    Copyright(c) 2015-2016 Third-Degree
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

#include <ht_stringhasher_dialog.h>
#include <ht_stringhasher_menubar.h>
#include <ht_stringhasher_sourcesyntaxhighlight.h>
#include <ht_stringhasher_processedsyntaxhighlight.h>
#include <ht_stringhasher_valuetree.h>
#include <ht_stringhasher_filemenu.h>
#include <ht_stringhasher_filetree.h>
#include <ht_stringhasher_document.h>
#include <ht_debug.h>
#include <ht_os.h>
#include <QBoxLayout>
#include <QSplitter>
#include <QFileDialog>
#include <QStatusBar>

namespace Hatchit
{
    namespace StringHasher
    {
        Dialog::Dialog(QWidget* parent)
            : QDialog(parent)
        {
            setObjectName("StringHasher");

            resize(1280, 720);
            m_menuBar = new MenuBar(this);
            m_textEdit = new QTextEdit;
            m_textEdit->setWordWrapMode(QTextOption::NoWrap);
            m_textEdit->setReadOnly(true);

            m_processedView = new QTextEdit;
            m_processedView->setWordWrapMode(QTextOption::NoWrap);
            m_processedView->setReadOnly(true);

            m_documentTabs = new QTabWidget;
            m_documentTabs->addTab(m_textEdit, tr("Source"));
            m_documentTabs->addTab(m_processedView, tr("Processed"));

            m_valueTree = new ValueTree;
            m_fileTree = new FileTree;

            m_sourceHighlight = new SourceSyntaxHighlight(m_textEdit->document());
            m_processedHighlight = new ProcessedSyntaxHighlight(m_processedView->document());

            m_activeDocText = new QLabel;

            auto mainLayout = new QVBoxLayout;
            auto splitter = new QSplitter;
            splitter->addWidget(m_fileTree);
            splitter->addWidget(m_documentTabs);
            splitter->addWidget(m_valueTree);
            splitter->setSizes({250, 600, 225});
            mainLayout->setMenuBar(m_menuBar);
            mainLayout->addWidget(splitter);

            

            this->setLayout(mainLayout);

            connect(m_menuBar->GetFileMenu()->GetOpen(), SIGNAL(triggered()),
                this, SLOT(OnDirectoryOpen()));
            connect(m_fileTree, SIGNAL(FileSelected(const QString&)),
                this, SLOT(OnFileSelected(const QString&)));
        }

        Dialog::~Dialog()
        {
            
        }

        void Dialog::OnDirectoryOpen() const
        {
            QString directory = QFileDialog::getExistingDirectory();
            if(!directory.isEmpty())
            {
                m_fileTree->OnDirectorySelected(directory);
            }
        }

        void Dialog::OnFileSelected(const QString& path) const
        {
            QFile file(path);
            QFileInfo info(path);
            if (file.open(QFile::ReadOnly | QFile::Text))
            {
                QString text = file.readAll();
                m_textEdit->setPlainText(text);
                file.reset();

                Document d;
                d.Load(file);
                m_processedView->setPlainText(d.GetModified());
                m_valueTree->SetDocument(d);
            }
        }
    }
}