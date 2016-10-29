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
#include <ht_stringhasher_syntaxhighlighter.h>
#include <ht_stringhasher_valuetree.h>
#include <ht_debug.h>
#include <ht_os.h>
#include <QBoxLayout>
#include <QSplitter>

namespace Hatchit
{
    namespace StringHasher
    {
        Dialog::Dialog(QWidget* parent)
            : QDialog(parent)
        {
            m_menuBar = new MenuBar(this);
            m_textEdit = new QTextEdit;
            m_textEdit->setReadOnly(true);

            m_valueTree = new ValueTree;

            m_highlighter = new SyntaxHighlighter(m_textEdit->document());

            auto mainLayout = new QVBoxLayout;
            auto splitter = new QSplitter;
            splitter->addWidget(m_textEdit);
            splitter->addWidget(m_valueTree);
            mainLayout->setMenuBar(m_menuBar);
            mainLayout->addWidget(splitter);

            QFile file("E:/GitHub/HatchitEditor/Hatchit/HatchitTest/app_test/apptest.cpp");
            if (file.open(QFile::ReadOnly | QFile::Text))
                m_textEdit->setPlainText(file.readAll());

            this->setLayout(mainLayout);

            
        }

        Dialog::~Dialog()
        {
            
        }
        
    }
}