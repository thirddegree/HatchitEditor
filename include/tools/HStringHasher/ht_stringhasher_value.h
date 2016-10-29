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

#include <ht_jsonhelper.h>
#include <ht_string.h>

namespace Hatchit
{
    namespace StringHasher
    {
        class Value
        {
        public:
            Value();
            Value(Core::JSON j);

            ~Value();

            const std::string& GetText() const;
            uint32_t           GetHash() const;

            void SetText(const std::string& text);
            void Hash();

            std::string Serialize() const;

        private:
            std::string m_text;
            uint32_t    m_hash;
        };
    }
}