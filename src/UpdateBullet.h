struct UpdateBullet : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "UpdateBullet"
    };

    using query = std::tuple
        <
        xecs::query::must<Bullet>
        >;

    _inline void operator()(entity& Entity,  Position& position, const Bullet& Bullet) const noexcept
    {
        xecs::query::instance playerquery;
        playerquery.m_Must.AddFromComponents<Player>();
        xecs::query::instance enemyquery;
        enemyquery.m_Must.AddFromComponents<Enemy>();
        Foreach(Search(playerquery), [&](entity& entplyer, Position& pos, Player& plyer)noexcept
            {
                if (constexpr auto distance_v = 10; (plyer.playerPos - position.m_value).getLengthSquared() < distance_v * distance_v)
                {
                    if (plyer.health != -1)
                    {
                        --plyer.health;
                    }
                    else
                    {
                        DeleteEntity(entplyer);
                    }
                    DeleteEntity(Entity);
                    Foreach(Search(enemyquery), [&](Enemy& enemy)noexcept
                        {
                            enemy.bulletisShot = false;
                        });
                }
            });

            position.m_value -= Bullet.bulletSpeed;

            if (position.m_value.m_Y < 0)
            {
                DeleteEntity(Entity);
                Foreach(Search(enemyquery), [&](Enemy& enemy)noexcept
                    {
                        enemy.bulletisShot = false;
                    });
            }
            else if (position.m_value.m_Y >= grid::max_resolution_height_v)
            {
                DeleteEntity(Entity);
                Foreach(Search(enemyquery), [&](Enemy& enemy)noexcept
                    {
                        enemy.bulletisShot = false;
                    });
            }
       // if (!Entity.isZombie())
       // {
       //     if (constexpr auto distance_v = 3; (plyer.playerPos - position.m_value).getLengthSquared() < distance_v * distance_v)
       //     {
       //         if (plyer.health != -1)
       //         {
       //             --plyer.health;
       //         }
       //         else
       //         {         
       //             //DeleteEntity(plyer)
       //         }
       //         DeleteEntity(Entity);
       //     }
       // }
    }
};
