
struct RenderingPlayer : xecs::system::instance
{
    constexpr static auto typedef_v =
        xecs::system::type::child_update<RenderingSystem, RenderingSystem::update>
    {
        .m_pName = "RenderingPlayerSystem"
    };

    using query = std::tuple< xecs::query::one_of<entity>>;

    void OnPreUpdate(void) noexcept
    {
        glBegin(GL_QUADS);
    }

    void OnPostUpdate(void) noexcept
    {
        glEnd();
    }

    void operator()(const Player& _entity, const Position& _position, const Timer* _timer) const noexcept
    {

        constexpr auto Size = 3;

        glColor3f(1.0, 1.0, 1.0);
        glVertex2i(_position.m_value.m_X - Size, _position.m_value.m_Y - Size);
        glVertex2i(_position.m_value.m_X - Size, _position.m_value.m_Y + Size);
        glVertex2i(_position.m_value.m_X + Size, _position.m_value.m_Y + Size);
        glVertex2i(_position.m_value.m_X + Size, _position.m_value.m_Y - Size);
    }
};