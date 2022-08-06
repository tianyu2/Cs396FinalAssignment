static struct Game
{
    using game_mgr_uptr = std::unique_ptr<xecs::game_mgr::instance>;

    RenderingInfo   m_renderingInfo;
    game_mgr_uptr   m_GameMgr = nullptr;
    int             m_MouseX{};
    int             m_MouseY{};
    bool            m_MouseLeft{};
    bool            m_MouseRight{};
    Keys            m_Keys{};
    int             m_DisplayGridInfo{ 0 };
    Enemy           enemyArray[5][5];
    void Initialize() noexcept
    {
        RenderingSystem::renderingInfo = &m_renderingInfo;
        m_GameMgr->RegisterComponents<Position, Scale, Velocity,Timer, GridCells,Player,Enemy, EnemyRusherSpaceShips, PlayerBullet>();
        m_GameMgr->RegisterSystems<RenderingSystem,RenderingGridSystem, RenderingShipSystem,UpdatePlayerMovement,
            RenderingPlayer,UpdateEnemy, RenderBullets, EnemyRusherSpaceShipsSystem, UpdatePlayerBullet, RenderPlayerBullets>();
       
    }


    void InitializeGame() noexcept
    {

        for (unsigned int i = 0; i < 5; ++i)
        {
            for (unsigned int j = 0; j < 5; ++j)
            {
                if (i != 0 && j != 0)
                {
                    enemyArray[i][j].enemyPos = enemyArray[i][j - 1].enemyPos + enemyArray[i][j].offsetPos;
                } 
                else
                {
                    if (i != 0)
                    {
                        enemyArray[i][j].enemyPos = enemyArray[i - 1][j].enemyPos + xcore::vector2{ 0,50 };
                    }
                    else
                        if( i == 0)
                        {
                            if (j == 0)
                            {
                                enemyArray[i][j].enemyPos = xcore::vector2{ 0,20 };
                            }
                            else
                            {
                                enemyArray[i][j].enemyPos = enemyArray[i][j-1].enemyPos + enemyArray[i][j].offsetPos;
                            }
                        }
                }

                if (i == 0)
                {
                    enemyArray[i][j].canShoot = true;
                    enemyArray[i][j].shooter = true;
                }

                m_GameMgr->getOrCreateArchetype< Position, Velocity, Timer, Enemy>()
                    .CreateEntities(1, [&](Position& position, Velocity& velocity, Timer& timer, Enemy& enemyEnt)
                        {
                            enemyEnt.canShoot = enemyArray[i][j].canShoot;
                            enemyEnt.shooter = enemyArray[i][j].shooter;
                            position.m_value = enemyArray[i][j].enemyPos;
                            velocity.m_value.m_X = 2;
                            velocity.m_value.Normalize();

                            timer.m_value = std::rand() / static_cast<float>(RAND_MAX) * 8;
                        });
            }
        }



        m_GameMgr->getOrCreateArchetype< Position, Velocity, Timer,Player>()
            .CreateEntities(1, [&](Position& position, Velocity& velocity, Timer& timer, Player& player) noexcept
                {
                    position.m_value = {500 , 700};
                    player.playerPos = position.m_value;
                    ///cells = grid::ComputeGridCellFromWorldPosition(position.m_value);

                    velocity.m_value.m_X = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
                    velocity.m_value.m_Y = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
                    velocity.m_value.Normalize();

                    timer.m_value = std::rand() / static_cast<float>(RAND_MAX) * 8;
                });
    }

} s_Game;