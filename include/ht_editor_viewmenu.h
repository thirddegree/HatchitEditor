

#pragma once

#include <QMenu>

namespace Hatchit {

    namespace Editor {

        class ViewMenu : public QMenu
        {
        public:
            ViewMenu(QWidget* parent = 0);

            QAction* DirectXRenderer();
            QAction* VulkanRenderer();

        private:
            QAction*    m_dxRenderer;
            QAction*    m_vkRenderer;
       
        };

    }
}