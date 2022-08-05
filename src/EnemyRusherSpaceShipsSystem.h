struct EnemyRusherSpaceShipsSystem : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "EnemyRusherSpaceShipsSystem"
    };

    using query = std::tuple
        <
        xecs::query::must<EnemyRusherSpaceShips>
        >;

    _inline void operator()(entity& Entity,  Position& position, const EnemyRusherSpaceShips& speedster, Velocity& velocity, Timer& _timer) const noexcept
    {
        static float spawner = 0.0f;
        static int  killCounter = 5;
        xecs::query::instance playerquery;
        playerquery.m_Must.AddFromComponents<Player>();
        xecs::query::instance enemyquery;
        enemyquery.m_Must.AddFromComponents<Enemy>();
        xecs::query::instance plyerbullet;
        plyerbullet.m_Must.AddFromComponents<PlayerBullet>();
        Foreach(Search(playerquery), [&](entity& entplyer, Position& pos, Player& plyer)noexcept
            {
                if (constexpr auto distance_v = 10; (plyer.playerPos - position.m_value).getLengthSquared() < distance_v * distance_v)
                {
                    if (plyer.health != -1)
                    {
                        --plyer.health;
                        bulletSpawnRate *= 2.f;
                    }
                    else
                    {
                        entplyer.setZombie();
                        DeleteEntity(entplyer);
                    }
                    Entity.setZombie();
                    DeleteEntity(Entity);
                }
            });

        Foreach(Search(plyerbullet), [&](entity& bullet, Position& pos, PlayerBullet& playerBullet)noexcept
            {
                if (constexpr auto distance_v = 10; (pos.m_value - position.m_value).getLengthSquared() < distance_v * distance_v)
                {

                    getOrCreateArchetype< Position, Velocity, Timer, EnemyRusherSpaceShips>()
                        .CreateEntities(2, [&](Position& position, Velocity& velocity, Timer& timer, EnemyRusherSpaceShips& enemyEnt) noexcept
                            {

                                position.m_value = xcore::vector2{ static_cast<float>(std::rand() % 1024)
                                                                     , static_cast<float>(std::rand() % 800 / (2))
                                };

                                velocity.m_value.m_X = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
                                velocity.m_value.m_Y = std::rand() / static_cast<float>(RAND_MAX) + 0.5f;
                                velocity.m_value.Normalize();

                                timer.m_value = std::rand() / static_cast<float>(RAND_MAX) * 8;
                            });
                    bullet.setZombie();
                    Entity.setZombie();
                    DeleteEntity(Entity);
                    DeleteEntity(bullet);
                    
                    killCounter--;

                    if (killCounter == 0)
                    {
                        killCounter = 5;
                        if (bulletSpawnRate >= 50.0f)
                        {
                            bulletSpawnRate -= 10.0f;
                        }

                    }
                }
            });
        spawner += 0.5f;
        if (spawner >= 5000.0f)
        {
            spawner = 0.0f;
            getOrCreateArchetype< Position, Velocity, Timer, EnemyRusherSpaceShips>()
                .CreateEntities(3, [&](Position& position, Velocity& velocity, Timer& timer, EnemyRusherSpaceShips& enemyEnt) noexcept
                    {

                        position.m_value = xcore::vector2{ static_cast<float>(std::rand() % 1024)
                                                             , static_cast<float>(std::rand() % 800 / (2))
                        };

                        velocity.m_value.m_X = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
                        velocity.m_value.m_Y = std::rand() / static_cast<float>(RAND_MAX) + 0.5f;
                        velocity.m_value.Normalize();

                        timer.m_value = std::rand() / static_cast<float>(RAND_MAX) * 8;
                    });

        }


            position.m_value += velocity.m_value;

            if (position.m_value.m_X < 0)
            {
                position.m_value.m_X = 0;
                velocity.m_value.m_X = -velocity.m_value.m_X;
            }
            else if (position.m_value.m_X >= grid::max_resolution_width_v)
            {
                position.m_value.m_X = grid::max_resolution_width_v - 1;
                velocity.m_value.m_X = -velocity.m_value.m_X;
            }

            if (position.m_value.m_Y < grid::max_resolution_height_v/3)
            {
                position.m_value.m_Y = grid::max_resolution_height_v / 3;
                velocity.m_value.m_Y = -velocity.m_value.m_Y;
            }
            else if (position.m_value.m_Y >= grid::max_resolution_height_v)
            {
                position.m_value.m_Y = grid::max_resolution_height_v - 1;
                velocity.m_value.m_Y = -velocity.m_value.m_Y;
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
