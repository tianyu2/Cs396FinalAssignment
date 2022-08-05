struct Enemy
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "Enemy"
    };

    xcore::err Serialize(xecs::serializer::stream& TextFile, bool) noexcept
    {
        return TextFile.Field("Enemy stats", enemyPos.m_X, enemyPos.m_Y, canShoot);
    }

    float enemyHp = 50.0f;

    xcore::vector2 offsetPos = {50 , 0};

    xcore::vector2 enemyPos = {0,10};

    bool shooter = false;

    bool canShoot = false;

    bool bulletisShot = false;
};

property_begin(Enemy)
{
    property_var(enemyPos, offsetPos, enemyHp)
}
property_end()
