
#include <xecs.h>
#define GLUT_STATIC_LIB
#include <GL/glut.h>
#include <GlutPrint.h>

#include <KeyInputs.h>
#include <RenderingInfo.h>
#include <Components.h>
#include <Grid.h>
#include <Systems.h>
#include <random>
#include <Game.h>
#include <Helper.h>
//---------------------------------------------------------------------------------------
// GAME
//---------------------------------------------------------------------------------------




void UpdateTimer(int value) noexcept
{
    // Post re-paint request to activate display()
    glutPostRedisplay();

    // next timer call milliseconds later
    glutTimerFunc(15, UpdateTimer, 0);
}
int main(int argc, char** argv)
{
	xcore::Init("1945");
    s_Game.m_GameMgr = std::make_unique<xecs::game_mgr::instance>();
    s_Game.Initialize();
    s_Game.InitializeGame();
    glutInitWindowSize(s_Game.m_renderingInfo.m_width, s_Game.m_renderingInfo.m_height);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow(xcore::get().m_pAppName);

    glutDisplayFunc([](void) noexcept
        {
            s_Game.m_GameMgr->Run();
            //++iFrame;
            
            if (s_Game.m_Keys.getKey('g')) std::cout << "yay "<< std::endl;
            s_Game.m_Keys.FrameUpdate();
        });  

    glutTimerFunc(0, UpdateTimer, 0);
    
    glutReshapeFunc(
        [](int w, int h) noexcept
        {
            s_Game.m_renderingInfo.m_width = w;
            s_Game.m_renderingInfo.m_height = h;
        }
    );

    glutKeyboardFunc(
        [](unsigned char Key, int MouseX, int MouseY) noexcept
        {
            s_Game.m_Keys.setKeyState(Key, true);
            s_Game.m_MouseX = MouseX;
            s_Game.m_MouseY = MouseY;
        }
    );
    glutKeyboardUpFunc(
        [](unsigned char Key, int MouseX, int MouseY) noexcept
        {
            s_Game.m_Keys.setKeyState(Key, false);
            s_Game.m_MouseX = MouseX;
            s_Game.m_MouseY = MouseY;
        }
    );
    glutMouseFunc(
        [](int Button, int State, int MouseX, int MouseY) noexcept
        {
            s_Game.m_MouseX = MouseX;
            s_Game.m_MouseY = MouseY;
            if (Button == GLUT_LEFT_BUTTON) s_Game.m_MouseLeft = (State == GLUT_DOWN);
            else if (Button == GLUT_RIGHT_BUTTON) s_Game.m_MouseRight = (State == GLUT_DOWN);
        }
    );
    glutMainLoop();

    s_Game.m_GameMgr.reset();
    xcore::Kill();
	return 0;
}

