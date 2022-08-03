struct Player
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "Player"
    };

    xcore::err Serialize(xecs::serializer::stream& TextFile, bool) noexcept
    {
        return TextFile.Field("Player stats", playerPos.m_X,playerPos.m_Y, health, bullets);
    }

    xcore::vector2 playerPos;

    int health;
};

property_begin(Player)
{
    property_var(playerPos, health)
}
property_end()
