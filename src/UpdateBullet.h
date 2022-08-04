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
        xecs::query::instance m_QueryAny;
        m_QueryAny.m_Must.AddFromComponents<Player>();
        Foreach(Search(m_QueryAny), [&](entity& entplyer, Position& pos, Player& plyer)noexcept
            {
                if (constexpr auto distance_v = 3; (plyer.playerPos - position.m_value).getLengthSquared() < distance_v * distance_v)
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
                }
            });

            position.m_value += Bullet.bulletSpeed;
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
