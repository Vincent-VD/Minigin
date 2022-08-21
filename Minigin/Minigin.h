#pragma once
struct SDL_Window;
namespace cycle
{
	class Game;

	struct WindowInfo
	{
		WindowInfo() = default;
		WindowInfo(float width, float height)
			: m_Width(width)
			, m_Height(height)
		{
		}

		const float m_Width{};
		const float m_Height{};
	};

	const WindowInfo g_WindowsInfo{ 640.f, 680.f };

	class Minigin
	{
	public:
		void Initialize();
		void SetGame(const Game* game) { m_pGame = game; };
		void LoadGame() const;
		void Cleanup();
		void Run();
		//bool CheckExit();
		//std::pair<int, int> GetWindowSize();

	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		const Game* m_pGame{};
		SDL_Window* m_Window{};
	};
}