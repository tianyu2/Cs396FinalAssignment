#pragma once
struct Timer
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "Timer"
    };

    xcore::err Serialize(xecs::serializer::stream& TextFile, bool) noexcept
    {
        TextFile.Field("Value", m_value).clear();
        return{};
    }

    float m_value;
};

property_begin(Timer)
{
    property_var(m_value)
}
property_end()