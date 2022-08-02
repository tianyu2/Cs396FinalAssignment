struct UpdatePlayerMovement : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "Update_Player_Movement"
    };

    _inline void operator()(Position& pos, Player& plyer)const noexcept
    {
       // plyer.scr += (std::rand() / 1000);
       //
       // if (plyer.scr % 10)
       // {
       //     std::cout << "Current Player Score: " << plyer.scr << std::endl;
       // }

        if (GetKeyState('A') & 0x8000)
        {
            plyer.playerPos += xcore::vector2{ -2.f, 0.f };
            pos.m_value = plyer.playerPos;
        }
        if (GetKeyState('D') & 0x8000)
        {
            plyer.playerPos += xcore::vector2{ 2.f, 0.f };
            pos.m_value = plyer.playerPos;
        }
        //if (GetKeyState('W') & 0x8000)
        //{
        //    plyer.playerPos += xcore::vector2{ 0.f, -2.f };;
        //    trans.m_pos = plyer.playerPos;
        //}
        //if (GetKeyState('S') & 0x8000)
        //{
        //    plyer.playerPos += xcore::vector2{ 0.f, 2.f };;
        //    trans.m_pos = plyer.playerPos;
        //}

    }
};
