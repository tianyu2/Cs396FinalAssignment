#pragma once
struct Scale
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "Scale"
    };

    xcore::vector2 m_Value;
};

property_begin(Scale)
{
    property_var(m_Value)
}
property_end()