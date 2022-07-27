#pragma once

struct RenderingSystem : xecs::system::instance
{
    inline static RenderingInfo* renderingInfo = nullptr;
    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "RenderingSystem"
    };

    using update = xecs::event::instance<>;

    using events = std::tuple
        < update
        >;
    __inline void OnPreUpdate(void) noexcept
    {
        //
        // Begin of the rendering
        //
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
       // glColor3f(0.0f, 1.0f, 0.0f);
        glViewport(0, 0, renderingInfo->m_W, renderingInfo->m_H);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, renderingInfo->m_W, 0, renderingInfo->m_H, -1, 1);
        glScalef(1, -1, 1);
        glTranslatef(0, -renderingInfo->m_H, 0);

    }
    __inline
        void OnUpdate(void) noexcept
    {

        //
        // Let all the system that depends on me
        //
        SendEventFrom<update>(this);
       // std::cout << x << std::endl;
        //
        // Page Flip
        //
//        glFlush();
        
    }
    __inline void OnPostUpdate(void) noexcept
    {
        glutSwapBuffers();
    }
};