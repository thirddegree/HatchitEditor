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

#include <ht_stringhasher_value.h>
#include <ht_hash.h>

namespace Hatchit
{
    namespace StringHasher
    {
        Value::Value()
            : m_text(L""),
              m_hash(0)
        {
            
        }

        Value::~Value()
        {
            
        }

        const std::wstring & Value::GetText() const
        {
            return m_text;
        }

        uint64_t Value::GetHash() const
        {
            return m_hash;
        }

        void Value::SetText(const std::wstring& text)
        {
            m_text = text;
        }

        void Value::Hash()
        {
            m_hash = Core::Hash::FNV1A(m_text);//std::_Fnv_hash_impl::hash(m_text);
        }

        bool Value::operator==(const Value& other) const
        {
            return (m_hash == other.m_hash);
        }

    }
}