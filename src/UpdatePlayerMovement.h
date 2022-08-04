struct UpdatePlayerMovement : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "Update_Player_Movement"
    };

    _inline void operator()(Position& pos, Player& plyer)const noexcept
    {

        if (GetKeyState('A') & 0x8000)
        {
            plyer.playerPos += xcore::vector2{ -2.f, 0.f };
            pos.m_value = plyer.playerPos;
        }
        if (GetKeyState('D') & 0x8000)
        {
            plyer.playerPos += xcore::vector2{ 2.f, 0.f };
            pos.m_value = plyer.playerPos;
        }
        if (GetKeyState('F') & 0x8000)
        {
            getOrCreateArchetype< Position, Velocity, Timer, PlayerBullet>()
                .CreateEntities(1, [&](Position& position, Velocity& bulvel, Timer& timer, PlayerBullet& bullet)
                    {
                        position.m_value = pos.m_value;
                        bulvel.m_value = bullet.bulletSpeed;
                        bulvel.m_value.Normalize();
                        position.m_value = position.m_value + bulvel.m_value;
                        timer.m_value = std::rand() / static_cast<float>(RAND_MAX) * 8;
                    });
        }

    }
};
