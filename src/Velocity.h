#pragma once

struct Velocity
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "Velocity"
    };

    xcore::err Serialize(xecs::serializer::stream& TextFile, bool) noexcept
    {
        TextFile.Field("Value", m_value.m_X, m_value.m_Y).clear();
        return { };
    }

    xcore::vector2 m_value;
};

property_begin(Velocity)
{
    property_var(m_value)
}
property_end()