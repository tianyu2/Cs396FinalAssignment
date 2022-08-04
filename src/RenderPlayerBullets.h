struct RenderPlayerBullets : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::child_update<RenderingSystem, RenderingSystem::update>
    {
        .m_pName = "render_player_bullets"
    };

    using query = std::tuple<xecs::query::must<PlayerBullet>>;

    void OnPreUpdate(void) noexcept
    {
        glBegin(GL_QUADS);
    }

    void OnPostUpdate(void) noexcept
    {
        glEnd();
    }

    __inline
        void operator()(const Position& position, const Velocity& velocity) const noexcept
    {
        constexpr auto Size = 10;

        glColor3f(1.0, 0.0, 1.0);
        glVertex2i(position.m_value.m_X - Size,position.m_value.m_Y - Size);
        glVertex2i(position.m_value.m_X - Size,position.m_value.m_Y + Size);
        glVertex2i(position.m_value.m_X + Size,position.m_value.m_Y + Size);
        glVertex2i(position.m_value.m_X + Size,position.m_value.m_Y - Size);
    }
};