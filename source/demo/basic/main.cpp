// #include <windows.h>
#include "../../../include/gbEngine.h"

using namespace gbEngine;

// int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
int main(int argc, char ** argv)
{
	EnvBasic env;
	env.Init();
	auto window = env.CreateRenderWindow(Point(100, 100), Size(600, 400), nullptr);
	env.ExecEventLoop();
	env.DestroyRenderWindow(window);
	env.Release();

	return 0;
}