struct RenderBullets : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::child_update<RenderingSystem, RenderingSystem::update>
    {
        .m_pName = "render_bullets"
    };

    using query = std::tuple<xecs::query::must<Bullet>>;

    void OnPreUpdate(void) noexcept
    {
        glBegin(GL_TRIANGLES);
    }

    void OnPostUpdate(void) noexcept
    {
        glEnd();
    }

    __inline
        void operator()(const Position& position, const Velocity& velocity) const noexcept
    {
        constexpr auto SizeX = 1;
        constexpr auto SizeY = SizeX * 3;
        glColor3f(1.0, 0.5, 0.0);
        glVertex2i(position.m_value.m_X + velocity.m_value.m_X * SizeY, position.m_value.m_Y + velocity.m_value.m_Y * SizeY);
        glVertex2i(position.m_value.m_X + velocity.m_value.m_Y * SizeX, position.m_value.m_Y - velocity.m_value.m_X * SizeX);
        glVertex2i(position.m_value.m_X - velocity.m_value.m_Y * SizeX, position.m_value.m_Y + velocity.m_value.m_X * SizeX);
    }
};
