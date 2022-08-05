struct EnemyRusherSpaceShips
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "EnemyRusherSpaceShips"
    };

    xcore::vector2 bulletSpeed = { 0,-5 };
};

property_begin(EnemyRusherSpaceShips)
{
    property_var(bulletSpeed)
}
property_end()
