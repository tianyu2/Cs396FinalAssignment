struct PlayerBullet
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "PlayerBullet"
    };

    xcore::vector2 bulletSpeed = { 0,5 };

};

property_begin(PlayerBullet)
{
    property_var(bulletSpeed)
}
property_end()
