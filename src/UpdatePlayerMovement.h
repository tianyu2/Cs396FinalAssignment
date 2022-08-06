#include "SaiKang.h"
struct UpdatePlayerMovement : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "Update_Player_Movement"
    };

    using query = std::tuple
        <
        xecs::query::must<Player>
        >;

    _inline void operator()(Position& pos, Player& plyer, Timer& _timer)const noexcept
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

        if (pos.m_value.m_X < 0)
        {
            pos.m_value.m_X = 0;
        }
        else if (pos.m_value.m_X >= grid::max_resolution_width_v)
        {
            pos.m_value.m_X = grid::max_resolution_width_v - 1;
        }
        static float temp = 0.0f;

        temp += _timer.m_value;
        if (temp >= bulletSpawnRate)
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

            temp = 0.0f;
        }
    }
};
