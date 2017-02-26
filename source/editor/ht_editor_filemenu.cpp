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

#include <ht_editor_filemenu.h>

namespace Hatchit {

    namespace Editor {

        FileMenu::FileMenu(QWidget* parent /* = 0 */)
            : QMenu(tr("File"), parent)
        {
            m_newProject = new QAction(tr("New"), nullptr);
            m_openProject = new QAction(tr("Open"), nullptr);
            m_saveProject = new QAction(tr("Save"), nullptr);
            m_projectSettings = new QAction(tr("Project Settings"), nullptr);
            m_exit = new QAction(tr("Exit"), nullptr);

            addAction(m_newProject);
            addAction(m_openProject);
            addAction(m_saveProject);
            addSeparator();
            addAction(m_projectSettings);
            addSeparator();
            addAction(m_exit);
        }

        QAction* FileMenu::NewProject() const
        {
            return m_newProject;
        }

        QAction* FileMenu::OpenProject() const
        {
            return m_openProject;
        }

        QAction* FileMenu::SaveProject() const
        {
            return m_saveProject;
        }

        QAction* FileMenu::ProjectSettings() const
        {
            return m_projectSettings;
        }

        QAction* FileMenu::Exit() const
        {
            return m_exit;
        }

    }
}