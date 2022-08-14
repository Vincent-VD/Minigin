#include "TronGame.h"

#include "FPSComponent.h"
#include "InputComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "Scene.h"

void TronGame::LoadGame() const
{
	auto& scene = cycle::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<cycle::GameObject>();
	auto fps = new cycle::FPSComponent(go.get());
	go->GetTransform()->SetPosition(80, 20, 0.f);
	auto font = cycle::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto text = new cycle::TextComponent(go.get(), "0 FPS", font);
	go->AddComponent(text);
	go->AddComponent(fps);

	auto input = new cycle::InputComponent(go.get());

	input->AddCommand('A', cycle::XBoxController::ControllerButton::ButtonA, std::make_unique<cycle::Test>(cycle::Command::InputType::pressed));

	go->AddComponent(input);

	scene.Add(go);
}
