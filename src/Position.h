#pragma once
struct Position
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "Position"
    };

    xcore::err Serialize(xecs::serializer::stream& TextFile, bool) noexcept
    {
        TextFile.Field("Value", m_value.m_X, m_value.m_Y).clear();
        return{};
    }

    xcore::vector2 m_value;
};

property_begin(Position)
{
    property_var(m_value)
}
property_end()
