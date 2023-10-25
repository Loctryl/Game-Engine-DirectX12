#include "Application.h"

Application::Application()
{
    mMainWindow = Window();
    mDirectX = D3DApp(&mMainWindow.GetHWND());
    mTimer = GameTimer();
    mAppPaused = false;
}

void Application::Init()
{
    mMainWindow.InitWindow();
    mDirectX.Init();
}

int Application::Run()
{
    MSG msg = { 0 };

    mTimer.Reset();

    // Boucle de messages principale :
    while (msg.message != WM_QUIT)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        mTimer.Tick();

        if (!mAppPaused)
        {
            Update(mTimer);
            Render(mTimer);
        }
       
    }

    return (int)msg.wParam;
}

void Application::CalculateFrameStats()
{

    static int frameCnt = 0;
    static float timeElapsed = 0.0f;
    frameCnt++;
    // Compute averages over one second period.
    if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
    {
        float fps = (float)frameCnt; // fps = frameCnt / 1
        float mspf = 1000.0f / fps;
        wstring fpsStr = to_wstring(fps);
        wstring mspfStr = to_wstring(mspf);
        wstring windowText =
            L" fps: " + fpsStr +
            L" mspf: " + mspfStr;
        SetWindowText(mMainWindow.GetHWND(), windowText.c_str());

        // Reset for next average.
        frameCnt = 0;
        timeElapsed += 1.0f;
    }

}

void Application::Update(GameTimer timer)
{
    CalculateFrameStats();
    mDirectX.Update(timer);
}

void Application::Render(GameTimer timer)
{
    mDirectX.Draw(timer);
}
