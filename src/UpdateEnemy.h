struct UpdateEnemy : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "Update_Enemy"
    };

   xecs::archetype::instance* m_pBulletArchetype{};

    _inline void operator()(Position& pos, Velocity& velocity, Enemy& ent, entity& ship, Timer& _timer)const noexcept
    {
        pos.m_value.m_X += velocity.m_value.m_X;

        // Bounce on edges
        if (pos.m_value.m_X < 0)
        {
            pos.m_value.m_X = 0;
            velocity.m_value.m_X = -velocity.m_value.m_X;
        }
        else if (pos.m_value.m_X >= grid::max_resolution_width_v)
        {
            pos.m_value.m_X = grid::max_resolution_width_v - 1;
            velocity.m_value.m_X = -velocity.m_value.m_X;
        }
    
    }
};
