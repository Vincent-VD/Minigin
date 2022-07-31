#pragma once
#include <thread>
struct SDL_Window;
namespace cycle
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
		bool CheckExit();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};
}