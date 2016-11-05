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

#include <QSortFilterProxyModel>

namespace Hatchit
{
    namespace StringHasher
    {
        class FileTreeProxyFilter : public QSortFilterProxyModel
        {
        public:
            FileTreeProxyFilter(QObject* parent = nullptr);

            ~FileTreeProxyFilter();

        protected:
            bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceIndex) const override;

        private:

        };
    }
}