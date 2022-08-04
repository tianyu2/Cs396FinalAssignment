struct Bullet
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "Bullet"
    };

    xcore::err Serialize(xecs::serializer::stream& TextFile, bool) noexcept
    {
        return TextFile.Field("ShipOwner", m_ShipOwner);
    }

    xecs::component::entity m_ShipOwner;

    xcore::vector2 bulletSpeed = { 0,5 };
};

property_begin(Bullet)
{
    property_var(m_ShipOwner, bulletSpeed)
}
property_end()
