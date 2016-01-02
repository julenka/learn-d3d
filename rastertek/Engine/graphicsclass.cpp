////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
    m_Direct3D = 0;
    m_outputFile = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
    bool result;

    // Create the Direct3D object
    m_Direct3D = new D3DClass;
    if (!m_Direct3D) 
    {
        return false;
    }

    // Initialize the Direct3D object
    result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
        return false;
    }

    m_outputFile = new std::ofstream("output.txt");
    WriteVideoCardInfoToFile();

    return true;
}


void GraphicsClass::WriteVideoCardInfoToFile() {
    if (m_outputFile && m_outputFile->is_open())
    {
        char cardName[128];
        int memory;
        m_Direct3D->GetVideoCardInfo(cardName, memory);
        *m_outputFile << "video card name: " << cardName << std::endl;
        *m_outputFile << "memory size: " << memory << std::endl;
    }
}

void GraphicsClass::Shutdown()
{
    if (m_Direct3D)
    {
        m_Direct3D->Shutdown();
        delete m_Direct3D;
        m_Direct3D = 0;
    }

    if (m_outputFile)
    {
        m_outputFile->close();
        delete m_outputFile;
        m_outputFile = 0;
    }
    return;
}


bool GraphicsClass::Frame()
{
    bool result;

    // Render the graphics scene
    result = Render();
    if (!result)
    {
        return false;
    }
    return true;
}


bool GraphicsClass::Render()
{
    // Clear the buffers to begin the scene
    m_Direct3D->BeginScene(1.0f, 1.0f, 0.5f, 1.0f);

    // Present the rendered scene to the screen
    m_Direct3D->EndScene();
    return true;
}