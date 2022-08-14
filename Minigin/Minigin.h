#pragma once
struct SDL_Window;
namespace cycle
{
	class Game;

	class Minigin
	{
	public:
		void Initialize();
		void SetGame(const Game* game) { m_pGame = game; };
		void LoadGame() const;
		void Cleanup();
		void Run();
		bool CheckExit();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		const Game* m_pGame{};
		SDL_Window* m_Window{};
	};
}