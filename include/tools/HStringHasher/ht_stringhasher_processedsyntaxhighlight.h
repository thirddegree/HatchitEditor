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

#include <QSyntaxHighlighter>
#include <QRegularExpression>

namespace Hatchit
{
    namespace StringHasher
    {
        class ProcessedSyntaxHighlight : public QSyntaxHighlighter
        {
        Q_OBJECT
        public:
            ProcessedSyntaxHighlight(QTextDocument* document);

        protected:
            void highlightBlock(const QString& text) override;

        private:
            struct HighlightRule
            {
                QRegularExpression pattern;
                QTextCharFormat    format;
            };

            QVector<HighlightRule> m_rules;

            QTextCharFormat m_keywordFormat;

            HighlightRule   m_hashMacroRule;
            HighlightRule   m_stringRule;

            QList<QString>  m_selectList;
        };
    }
}