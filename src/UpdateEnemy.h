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
        float temp = _timer.m_value;

        //if (static_cast<int>(temp) % 10 > 1)
        //{
        int random = rand() % 5;
        if (ent.canShoot && random % 5 == 0 && !ent.bulletisShot)
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
           // if (ent.shooter && ent.canShoot && !ent.bulletisShot)
           // {
           //     getOrCreateArchetype< Position, Velocity, Timer, Bullet>()
           //         .CreateEntities(1, [&](Position& position, Velocity& bulvel, Timer& timer, Bullet& bullet)
           //             {
           //                 position.m_value.m_X = pos.m_value.m_X + std::rand() / static_cast<float>(RAND_MAX) * 100;
           //                 position.m_value.m_Y = pos.m_value.m_Y;
           //                 bulvel.m_value = bullet.bulletSpeed;
           //                 bulvel.m_value.Normalize();
           //                 position.m_value = position.m_value + bulvel.m_value;
           //                 timer.m_value = std::rand() / static_cast<float>(RAND_MAX) * 8;
           //                 bullet.m_ShipOwner = ship;
           //             });
           //
           //     ent.bulletisShot = true;
           // }
        //}
    }
};
