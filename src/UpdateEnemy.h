struct UpdateEnemy : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "Update_Enemy"
    };

   xecs::archetype::instance* m_pBulletArchetype{};

    _inline void operator()(Position& pos, Velocity& velocity, Enemy& ent, entity& ship)const noexcept
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

        if(ent.canShoot && !ent.bulletisShot)
        {

            getOrCreateArchetype< Position, Velocity, Timer, Bullet>()
                .CreateEntities(1, [&](Position& position, Velocity& bulvel, Timer& timer, Bullet& bullet)
                    {
                        position.m_value = pos.m_value;
                        bulvel.m_value = bullet.bulletSpeed;
                        bulvel.m_value.Normalize();
                        position.m_value = position.m_value + bulvel.m_value;
                        timer.m_value = std::rand() / static_cast<float>(RAND_MAX) * 8;
                        bullet.m_ShipOwner = ship;
                    });

            ent.bulletisShot = true;
        }
    }
};
