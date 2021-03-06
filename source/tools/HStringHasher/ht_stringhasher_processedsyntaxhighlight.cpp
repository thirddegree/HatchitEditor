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

#include <ht_stringhasher_processedsyntaxhighlight.h>
#include <ht_debug.h>

#include <QBrush>
#include <QColor>
#include <QTextDocument>

namespace Hatchit
{
    namespace StringHasher
    {
        ProcessedSyntaxHighlight::ProcessedSyntaxHighlight(QTextDocument* document)
                : QSyntaxHighlighter(document)
        {
            /**
             * HATCHIT Hash ID Macro
             */
            m_hashMacroRule.format.setForeground(Qt::magenta);
            m_hashMacroRule.format.setFontWeight(QFont::Bold);
            m_hashMacroRule.pattern = QRegularExpression("HID");// \\(([^]]+?)\\)");

            m_stringRule.format.setForeground(QColor(255, 153, 102));
            m_stringRule.format.setFontWeight(QFont::Bold);
            m_stringRule.pattern = QRegularExpression("(?<=HID\\()[0-9]+");

        }

        void ProcessedSyntaxHighlight::highlightBlock(const QString& text)
        {
            /**
             * HashID Macro Rule
             */
            auto exp(m_hashMacroRule.pattern);
            auto iter = exp.globalMatch(text);
            while(iter.hasNext())
            {
                auto match = iter.next();
                int index = match.capturedStart();
                int length = match.capturedLength();
                setFormat(index, length, m_hashMacroRule.format);
            }

            /**
             * HashID String Rule
             */
            exp = QRegularExpression(m_stringRule.pattern);
            iter = exp.globalMatch(text);
            while (iter.hasNext())
            {
                auto match = iter.next();
                int index = match.capturedStart();
                int length = match.capturedLength();
                setFormat(index, length, m_stringRule.format);
            }

        }
    }
}