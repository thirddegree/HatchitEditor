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

#pragma once

#include <QDialog>
#include <QTextEdit>
#include <QLabel>
#include <QTabWidget>

namespace Hatchit
{
    namespace StringHasher
    {
        class MenuBar;
        class SourceSyntaxHighlight;
        class ProcessedSyntaxHighlight;
        class ValueTree;
        class FileTree;

        class Dialog : public QDialog
        {
            Q_OBJECT
        public:
            Dialog(QWidget* parent = 0);

            ~Dialog();

        protected slots:
            void OnDirectoryOpen() const;
            void OnFileSelected(const QString& path) const;
        
        private:
            MenuBar*                    m_menuBar;
            SourceSyntaxHighlight*      m_sourceHighlight;
            ProcessedSyntaxHighlight*   m_processedHighlight;
            ValueTree*                  m_valueTree;
            FileTree*                   m_fileTree;
            QTabWidget*                 m_documentTabs;
            QTextEdit*                  m_processedView;
            QTextEdit*                  m_textEdit;
            QLabel*                     m_activeDocText;
        };
    }
}