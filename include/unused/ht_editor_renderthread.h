#pragma once

#include <QObject>
#include <thread>

#include <ht_renderer.h>
#include <ht_timer.h>

namespace Hatchit
{
    namespace Editor
    {
        class RenderThread : public QObject
        {
            Q_OBJECT
        public:
            RenderThread(Graphics::RendererParams params);

            ~RenderThread();

            void Start();

        public slots:
            void resize(uint32_t width, uint32_t height);

        private:
            Core::Timer                 m_timer;
            Graphics::RendererParams    m_params;
            std::thread                 m_thread;
            bool                        m_stop;
            bool                        m_completed;
            bool                        m_resizing;
            Graphics::IRenderer*        m_renderer;
            uint32_t                    m_width;
            uint32_t                    m_height;

            void thread_main();
        };
    }
}