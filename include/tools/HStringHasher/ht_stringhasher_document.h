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

#include <ht_stringhasher_value.h>

#include <vector>
#include <QString>
#include <QFile>
#include <QTemporaryFile>

namespace Hatchit
{
    namespace StringHasher
    {
        class Document
        {
        public:
            Document();

            ~Document();

            bool Load(QFile& file);
                
            void Deserialize(const Core::JSON& json);

            std::string Serialize() const;

        private:
            std::string        m_filePath;
            std::string        m_fileName;
            std::vector<Value> m_values;
            QString            m_original;
            QTemporaryFile     m_modified;

            bool Load(const QString& text);
        };
    }
}
