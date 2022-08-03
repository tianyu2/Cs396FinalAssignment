struct UpdateEnemy : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "Update_Enemy"
    };

   xecs::archetype::instance* m_pBulletArchetype{};
    _inline void operator()(Position& pos, Velocity& velocity, Enemy& ent)const noexcept
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

        if(ent.canShoot)
        {
           m_pBulletArchetype< Position, Velocity, Timer, Bullet>()
                .CreateEntities(1, [&](Position& position, Velocity& velocity, Timer& timer, Bullet& bullet)
                    {
                        position.m_value = pos.m_value;
                        velocity.m_value.m_Y = 5;
                        velocity.m_value.Normalize();
                        timer.m_value = std::rand() / static_cast<float>(RAND_MAX) * 8;
                    });
        }
       //if (pos.m_value.m_Y < 0)
       //{
       //    pos.m_value.m_Y = 0;
       //    velocity.m_value.m_Y = -velocity.m_value.m_Y;
       //}
       //else if (pos.m_value.m_Y >= grid::max_resolution_height_v)
       //{
       //    pos.m_value.m_Y = grid::max_resolution_height_v - 1;
       //    velocity.m_value.m_Y = -velocity.m_value.m_Y;
       //}
    }
};
