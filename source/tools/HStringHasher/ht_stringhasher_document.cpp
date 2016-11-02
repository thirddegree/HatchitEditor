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

#include <ht_stringhasher_document.h>
#include <QRegularExpression>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextBlock>
#include <QFileInfo>

#include <ht_os.h>

namespace Hatchit
{
    namespace StringHasher
    {
        Document::Document()
        {
            
        }

        Document::~Document()
        {
            
        }

        bool Document::Load(QFile & file)
        {
            QFileInfo info(file);
            m_fileName = info.fileName().toStdString();
            m_filePath = info.filePath().toStdString();

            m_original = file.readAll();
            
            return Load(m_original);
        }

        bool Document::Load(const QString& text)
        {
            QRegularExpression pattern("(?<=HID\\()\".*\"|(?<=HID\\()\'.*\'");
            auto iter = pattern.globalMatch(text);
            while(iter.hasNext())
            {
                /**
                 * Process each word match into
                 * a value and append it to the document list.
                 */
                auto match = iter.next();
                int index = match.capturedStart();
                int length = match.capturedLength();
                
                /**
                * We need to build a list of all the string values
                * that were matched with information about them
                * such as the line number in the document.
                */
                std::wstring _text = match.capturedTexts()[0].trimmed().toStdWString();
                QTextDocument document(text);
                QTextCursor cursor = document.find(QString::fromStdWString(_text),
                    index);
                int lineNumber = cursor.block().firstLineNumber();

                /**
                 * We want to remove the actual quote characters that surround
                 * the text, as they will be turned into string values anyway.
                 */
                _text.erase(std::remove(_text.begin(), _text.end(), '\''), _text.end());
                _text.erase(std::remove(_text.begin(), _text.end(), '"'), _text.end());

                Value v;
                v.SetText(_text);
                v.Hash();

                auto res = std::find(m_values.begin(), m_values.end(), v);
                if(res == m_values.end())
                    m_values.push_back(v);
                
            }


            /**
             * Create the temporary file from replaced text values with the
             * calculated hash value, to show how the source file
             * will look post-processing
             */
            m_modified = m_original;
            for(auto val : m_values)
            {
                QString text = QString::fromStdWString(val.GetText());
                QString hash = QString::number(val.GetHash());

                QRegularExpression exp("(?<=HID\\()\"" + text + "\"|(?<=HID\\()\'" + text + "'");

                m_modified = m_modified.replace(exp, hash);
            }



            return true;
        }

        void Document::Deserialize(const Core::JSON& json)
        {
            Core::JsonExtract(json, "Name", m_fileName);
            Core::JsonExtract(json, "Path", m_filePath);

            Core::JSON values = json["Values"];
            for(auto v : values)
            {
                Value _val;
                std::wstring text;
                Core::JsonExtract(v, "Text", text);

                _val.SetText(text);
                _val.Hash();

                m_values.push_back(_val);
            }
        }

        std::string Document::Serialize() const
        {
            Core::JSON arr;
            for(auto val : m_values)
                arr.push_back({ {"Hash", val.GetHash()}, {"Text", val.GetText()} });
            Core::JSON j;
            j["Name"] = m_fileName;
            j["Path"] = m_filePath;
            j["Values"] = arr;

            std::string text = j.dump(4);

            return text;
        }

        QString Document::GetModified() const
        {
            return m_modified;
        }


    }
}
