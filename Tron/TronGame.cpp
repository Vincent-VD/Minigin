#include "TronGame.h"
#include "FPSComponent.h"
#include "InputComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "GameObject.h"
#include "fstream"
#include "MovementComponent.h"
#include "TextureComponent2D.h"

std::shared_ptr<cycle::GameObject> CreateTile(float x, float y);
std::shared_ptr<cycle::GameObject> CreatePlayer(float x, float y);


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

	std::vector<std::shared_ptr<cycle::GameObject>> grid{ ReadLevelFile("Data/Level_1.txt") };

	for (std::shared_ptr<cycle::GameObject>& gameObject : grid)
	{
		scene.Add(gameObject);
	}

	scene.Add(CreatePlayer(50, 50));

	scene.Add(go);
}

std::vector<std::shared_ptr<cycle::GameObject>> TronGame::ReadLevelFile(const std::string& filename) const
{
	std::vector<std::shared_ptr<cycle::GameObject>> res{};

	std::ifstream obj(filename.c_str());
	if (!obj) {
		std::cerr << "Cannot open " << filename << std::endl;
	}

	float y{ 680.f - 19 * 32.f}; //window height - # rows * texture size
	std::string line;
	while (std::getline(obj, line))
	{
		float x{};
		for (const char& ch : line)
		{
			//std::cout << ch << std::endl;
			if(ch == '#')
			{
				res.push_back(CreateTile(x, y));
			}
			x += 32.f;
		}
		y += 32.f;
		
	}

	return res;
}

std::shared_ptr<cycle::GameObject> CreateTile(float x, float y)
{
	std::shared_ptr<cycle::GameObject> go = std::make_shared<cycle::GameObject>();
	cycle::TextureComponent2D* textureComp{ new cycle::TextureComponent2D{go.get(), "Tile.png", x, y, 32, 32, false}};
	cycle::CollisionComponent* collisionComp{ new cycle::CollisionComponent{go.get(), x, y, 32, 32, false}};

	go->GetTransform()->SetPosition(x, y, 0.f);
	go->AddComponent(textureComp);
	go->AddComponent(collisionComp);

	return go;
}

std::shared_ptr<cycle::GameObject> CreatePlayer(float x, float y)
{
	std::shared_ptr<cycle::GameObject> go = std::make_shared<cycle::GameObject>();
	cycle::TextureComponent2D* textureComp{ new cycle::TextureComponent2D{go.get(), "Tank_1.png", x, y, 32, 32, true} };
	cycle::CollisionComponent* collisionComp{ new cycle::CollisionComponent{go.get(), x, y, 32, 32, true} };

	MovementComponent* movementComp{ new MovementComponent(go.get())};
	auto inputComponent = new cycle::InputComponent (go.get());

	inputComponent->AddCommand('W', cycle::XBoxController::ControllerButton::DPadUp, std::make_unique<MoveUp>(cycle::Command::InputType::held, inputComponent, movementComp));
	inputComponent->AddCommand('A', cycle::XBoxController::ControllerButton::DPadLeft, std::make_unique<MoveLeft>(cycle::Command::InputType::held, inputComponent, movementComp));
	inputComponent->AddCommand('S', cycle::XBoxController::ControllerButton::DPadDown, std::make_unique<MoveDown>(cycle::Command::InputType::held, inputComponent, movementComp));
	inputComponent->AddCommand('D', cycle::XBoxController::ControllerButton::DPadRight, std::make_unique<MoveRight>(cycle::Command::InputType::held, inputComponent, movementComp));
	inputComponent->AddCommand('\0', cycle::XBoxController::ControllerButton::LeftStick, std::make_unique<MoveStick>(cycle::Command::InputType::held, inputComponent, movementComp));
	inputComponent->AddCommand('\0', cycle::XBoxController::ControllerButton::ButtonA, std::make_unique<cycle::Test>(cycle::Command::InputType::pressed));

	go->GetTransform()->SetPosition(x, y, 0.f);
	go->AddComponent(textureComp);
	go->AddComponent(collisionComp);
	go->AddComponent(inputComponent);
	go->AddComponent(movementComp);

	return go;
}
