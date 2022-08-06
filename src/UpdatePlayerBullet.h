struct UpdatePlayerBullet : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "UpdatePlayerBullet"
    };

    using query = std::tuple
        <
        xecs::query::must<PlayerBullet>
        >;

    _inline void operator()(entity& Entity,  Position& position, const PlayerBullet& Bullet) const noexcept
    {

        xecs::query::instance enemyquery;
        enemyquery.m_Must.AddFromComponents<Enemy>();
        position.m_value -= Bullet.bulletSpeed;

        Foreach(Search(enemyquery), [&](entity& enemy, Position& pos, Enemy& enemyent)noexcept
            {
                if (constexpr auto distance_v = 10; (pos.m_value - position.m_value).getLengthSquared() < distance_v * distance_v)
                {  
                    //enemyent.enemyHp -= 10.0f;
                    if (totalSpeedster < 50)
                    {
                        getOrCreateArchetype< Position, Velocity, Timer, EnemyRusherSpaceShips>()
                            .CreateEntities(2, [&](Position& position, Velocity& velocity, Timer& timer, EnemyRusherSpaceShips& enemyEnt) noexcept
                                {

                                    position.m_value = xcore::vector2{ static_cast<float>(std::rand() % 1024)
                                                                         , static_cast<float>(std::rand() % 800 / (2))
                                    };

                                    velocity.m_value.m_X = std::rand() / 1024 / 2 - 0.5f;
                                    velocity.m_value.m_Y = std::rand() / 800 / (2) + 0.5f;
                                    velocity.m_value.Normalize();

                                    timer.m_value = std::rand() / static_cast<float>(RAND_MAX) * 8;
                                });
                        totalSpeedster += 2;
                    }
                    if (bulletSpawnRate >= 90.0f)
                    {
                        bulletSpawnRate -= 10.0f;
                    }

                    --spaceshipHP;
                    enemy.setZombie();
                    DeleteEntity(enemy);
                    Entity.setZombie();
                    DeleteEntity(Entity);
                }
            });
    }
};
