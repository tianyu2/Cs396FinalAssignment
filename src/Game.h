#pragma once


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


    void Initialize() noexcept
    {
        RenderingSystem::renderingInfo = &m_renderingInfo;
        m_GameMgr->RegisterComponents<Position, Scale, Velocity,Timer>();
        m_GameMgr->RegisterSystems<RenderingSystem,RenderingShipSystem>();
    }
    void InitializeGame() noexcept
    {
        s_Game.m_GameMgr->getOrCreateArchetype< Position, Velocity, Timer>()
            .CreateEntities(1, [&](Position& position, Velocity& velocity, Timer& timer) noexcept
                {
                    position.m_value = xcore::vector2{ static_cast<float>(std::rand() % s_Game.m_renderingInfo.m_W)
                                                         , static_cast<float>(std::rand() % s_Game.m_renderingInfo.m_H)
                    };

                    //Cell = grid::ComputeGridCellFromWorldPosition(Position.m_Value);

                    velocity.m_value.m_X = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
                    velocity.m_value.m_Y = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
                    velocity.m_value.Normalize();

                    timer.m_value = std::rand() / static_cast<float>(RAND_MAX) * 8;
                });
    }

} s_Game;