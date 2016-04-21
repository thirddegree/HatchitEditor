/**
**    Hatchit Editor
**    Copyright(c) 2015 Third-Degree
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
#include <QPushButton>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QCheckBox>
namespace Hatchit
{
    namespace Editor
    {
        class Launcher : public QDialog
        {
            Q_OBJECT
        public:
            Launcher(QWidget* parent = 0);


            QString ProjectPath();

        protected slots:
            void OnCreateNew();
            void OnOpenExisting();
            void OnAccepted();

        private:
           
            QString             m_projectPath;

            QLineEdit*          m_directoryEdit;            
            QPushButton*        m_createNew;
            QPushButton*        m_openExisting;
            QDialogButtonBox*   m_buttonBox;
            QCheckBox*          m_defaultCheckBox;
        };
    }
}
