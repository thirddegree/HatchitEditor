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

#include <ht_editor_viewmenu.h>

namespace Hatchit {

    namespace Editor {

        ViewMenu::ViewMenu(QWidget* widget /* = 0 */)
            : QMenu(tr("View"), widget)
        {
            QMenu* _rendererSelection = addMenu(tr("Renderer"));

            m_dxRenderer = new QAction(tr("DirectX"), nullptr);
            m_dxRenderer->setCheckable(true);
            m_vkRenderer = new QAction(tr("Vulkan"), nullptr);
            m_vkRenderer->setCheckable(true);

            _rendererSelection->addAction(m_dxRenderer);
            _rendererSelection->addAction(m_vkRenderer);

            QActionGroup* renderGroup = new QActionGroup(_rendererSelection);
            renderGroup->addAction(m_dxRenderer);
            renderGroup->addAction(m_vkRenderer);

            addMenu(_rendererSelection);
        }

        QAction* ViewMenu::DirectXRenderer()
        {
            return m_dxRenderer;
        }

        QAction* ViewMenu::VulkanRenderer()
        {
            return m_vkRenderer;
        }
    }

}