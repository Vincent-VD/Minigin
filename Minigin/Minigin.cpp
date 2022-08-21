#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputComponent.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Timer.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl2.h"

#include <chrono>

#include "AudioManager.h"
#include "BaseCollisionComponent.h"
#include "Game.h"

using namespace std;

//cycle::GameWindow::GameWindow(float width, float height)
//	: m_WindowWidth(width)
//	, m_WindowHeight(height)
//{
//}

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void cycle::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"TRON - Vincent Van Denberghe (2GD07E - 202055275)",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		static_cast<int>(g_WindowsInfo.m_Width),
		static_cast<int>(g_WindowsInfo.m_Height),
		SDL_WINDOW_OPENGL
	);

	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

//std::pair<int, int> cycle::Minigin::GetWindowSize()
//{
//	int w{}, h{};
//	SDL_GetWindowSize(m_Window, &w, &h);
//	return { w, h };
//}


/**
 * Code constructing the scene world starts here
 */
void cycle::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>("test");
	auto fps = new FPSComponent(go.get());
	go->GetTransform()->SetPosition(80, 20, 0.f);
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto text = new TextComponent(go.get(), "0 FPS", font);
	go->AddComponent(text);
	go->AddComponent(fps);

	auto input = new InputComponent(go.get(), 0);

	//input->AddCommand('A', cycle::XBoxController::ControllerButton::ButtonA, std::make_unique<Test>(cycle::Command::InputType::pressed));

	go->AddComponent(input);

	scene.Add(go);


	/*auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);*/

	/*auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextComponent>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);*/
}

void cycle::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void cycle::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	cycle::Timer::GetInstance().Init(MsPerFrame);
	cycle::CollisionManager::GetInstance().Init();
	AudioManager& audioManager{ AudioManager::GetInstance() };
	audioManager.Init();

	m_pGame->LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& timer = Timer::GetInstance();

		//audioManager.PlayAudio(SoundDesc{ SoundId::theme, 1.f });
		

		// todo: this update loop could use some work.
		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag{};
		//float fixedTimeStep{ 0.02f };
		SDL_Event e;
		while (doContinue)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					doContinue = false;
				}
			}

			const auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			timer.SetDeltaTime(deltaTime);
			lastTime = currentTime;
			//timer.Update();
			//std::cout << deltaTime << std::endl;
			lag += deltaTime;
			
			//doContinue = input.ProcessInput();
			while (lag >= Minigin::MsPerFrame)
			{
				sceneManager.FixedUpdate();
				lag -= Minigin::MsPerFrame;
			}
			audioManager.Update();
			sceneManager.Update();
			renderer.Render();

			const auto sleepTime = currentTime + std::chrono::milliseconds(Minigin::MsPerFrame) - std::chrono::high_resolution_clock::now();
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}