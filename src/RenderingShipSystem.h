#pragma once


struct RenderingShipSystem : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::child_update<RenderingSystem, RenderingSystem::update>
    {
        .m_pName = "render_ships"
    };

    using query = std::tuple
        <
        xecs::query::one_of<entity>
        >;

    void OnPreUpdate(void) noexcept
    {
        glBegin(GL_QUADS);
    }

    void OnPostUpdate(void) noexcept
    {
        glEnd();
    }

    __inline
        void operator()(const Position& _position, const Timer* _pTimer) const noexcept
    {
        constexpr auto Size = 3;
        if (_pTimer) glColor3f(0, 1.0, 0.0);
        else       glColor3f(0.5, 1.0, 0.5);
        glVertex2i(_position.m_value.m_X - Size, _position.m_value.m_Y - Size);
        glVertex2i(_position.m_value.m_X - Size, _position.m_value.m_Y + Size);
        glVertex2i(_position.m_value.m_X + Size, _position.m_value.m_Y + Size);
        glVertex2i(_position.m_value.m_X + Size, _position.m_value.m_Y - Size);
    }
};