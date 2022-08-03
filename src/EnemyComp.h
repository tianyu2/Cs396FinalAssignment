struct Enemy
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "Enemy"
    };

    xcore::err Serialize(xecs::serializer::stream& TextFile, bool) noexcept
    {
        return TextFile.Field("Enemy stats", enemyPos.m_X, enemyPos.m_Y);
    }

    xcore::vector2 offsetPos = {50 , 0};

    xcore::vector2 enemyPos = {0,10};

};

property_begin(Enemy)
{
    property_var(enemyPos, offsetPos)
}
property_end()
