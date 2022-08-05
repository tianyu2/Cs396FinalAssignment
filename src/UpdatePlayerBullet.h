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
                    enemyent.enemyHp -= 1.0f;

                    if (enemyent.enemyHp <= 0.0f)
                    {
                        DeleteEntity(enemy);
                    }

                    DeleteEntity(Entity);
                }
            });
    }
};
