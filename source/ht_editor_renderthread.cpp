
#include <ht_editor_renderthread.h>
#include <ht_time_singleton.h>

namespace Hatchit
{
    namespace Editor
    {
        using namespace Graphics;

        RenderThread::RenderThread(RendererParams params)
            : QObject(nullptr)
        {
            m_params = params;
            m_stop = false;
            m_thread = std::thread(&RenderThread::thread_main, this);
            m_renderer = nullptr;
            m_completed = false;
            m_resizing = false;
        }

        RenderThread::~RenderThread()
        {
            m_stop = true; //flag thread to start cleanup
            
            /*Wait for thead to complete before exiting*/
            do {} while (!m_completed);
        }

        void RenderThread::Start()
        {
            m_thread.detach();
        }

        void RenderThread::resize(uint32_t width, uint32_t height)
        {
            m_resizing = true;
            
            m_width = width;
            m_height = height;
        }

        void RenderThread::thread_main()
        { 
            Game::Time::Start();

            m_renderer = IRenderer::FromType(m_params.renderer);
            if (!m_renderer->VInitialize(m_params))
                return;

            while (!m_stop)
            {
                Game::Time::Tick();

                if (m_resizing)
                {
                    m_renderer->VResizeBuffers(m_width, m_height);
                    m_resizing = false;
                }

                m_renderer->VRender(Game::Time::DeltaTime());

                m_renderer->VPresent();
            }

            m_renderer->VDeInitialize();
            delete m_renderer;

            m_completed = true;
        }
    }
}