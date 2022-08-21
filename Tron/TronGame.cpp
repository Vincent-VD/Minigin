#include "TronGame.h"

#include "BulletMoveComponent.h"
#include "FPSComponent.h"
#include "InputComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "GameObject.h"
#include "fstream"
#include "HudComponent.h"
#include "Minigin.h"
#include "MovementComponent.h"
#include "PlayerCollisionComponent.h"
#include "ScoreComponent.h"
#include "TextureComponent2D.h"

std::shared_ptr<cycle::GameObject> CreateTile(float x, float y);
std::shared_ptr<cycle::GameObject> CreatePlayer(float x, float y);
std::vector<std::shared_ptr<cycle::GameObject>> CreateHUD();


void TronGame::LoadGame() const
{
	auto& scene = cycle::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<cycle::GameObject>();
	auto fps = new cycle::FPSComponent(go.get());
	go->GetTransform()->SetPosition(0, 0, 0.f);
	auto font = cycle::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto text = new cycle::TextComponent(go.get(), "0 FPS", font);
	go->AddComponent(text);
	go->AddComponent(fps);

	std::vector<std::shared_ptr<cycle::GameObject>> grid{ ReadLevelFile("Data/Level_1.txt") };

	for (std::shared_ptr<cycle::GameObject>& gameObject : grid)
	{
		scene.Add(gameObject);
	}

	scene.Add(CreatePlayer(33, 150));

	std::vector<std::shared_ptr<cycle::GameObject>> hud{ CreateHUD() };

	for (std::shared_ptr<cycle::GameObject>& gameObject : hud)
	{
		scene.Add(gameObject);
	}

	scene.Add(go);
}

std::vector<std::shared_ptr<cycle::GameObject>> TronGame::ReadLevelFile(const std::string& filename) const
{
	std::vector<std::shared_ptr<cycle::GameObject>> res{};

	std::ifstream obj(filename.c_str());
	if (!obj) {
		std::cerr << "Cannot open " << filename << std::endl;
	}

	float y{ cycle::g_WindowsInfo.m_Height - 19 * 32.f}; //window height - # rows * texture size
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
	PlayerCollisionComponent* collisionComp{ new PlayerCollisionComponent{go.get(), "tile", x, y, 32, 32, false}};

	go->GetTransform()->SetPosition(x, y, 0.f);
	go->AddComponent(textureComp);
	go->AddComponent(collisionComp);

	return go;
}

std::shared_ptr<cycle::GameObject> CreatePlayer(float x, float y)
{
	std::shared_ptr<cycle::GameObject> go = std::make_shared<cycle::GameObject>();
	cycle::TextureComponent2D* textureComp{ new cycle::TextureComponent2D{go.get(), "Tank_1.png", x, y, 32, 32, true} };
	PlayerCollisionComponent* collisionComp{ new PlayerCollisionComponent{go.get(), "player", x, y, 28, 28, true}};

	MovementComponent* movementComp{ new MovementComponent(go.get())};
	TurretComponent* turretComponent{ new TurretComponent{go.get()} };

	auto inputComponent = new cycle::InputComponent (go.get());

	inputComponent->AddCommand('W', cycle::XBoxController::ControllerButton::DPadUp, std::make_unique<MoveUp>(cycle::Command::InputType::held, inputComponent, movementComp));
	inputComponent->AddCommand('A', cycle::XBoxController::ControllerButton::DPadLeft, std::make_unique<MoveLeft>(cycle::Command::InputType::held, inputComponent, movementComp));
	inputComponent->AddCommand('S', cycle::XBoxController::ControllerButton::DPadDown, std::make_unique<MoveDown>(cycle::Command::InputType::held, inputComponent, movementComp));
	inputComponent->AddCommand('D', cycle::XBoxController::ControllerButton::DPadRight, std::make_unique<MoveRight>(cycle::Command::InputType::held, inputComponent, movementComp));
	inputComponent->AddCommand('\0', cycle::XBoxController::ControllerButton::LeftStick, std::make_unique<MoveStick>(cycle::Command::InputType::held, inputComponent, movementComp));
	inputComponent->AddCommand('R', cycle::XBoxController::ControllerButton::RightShoulder, std::make_unique<FireBullet>(cycle::Command::InputType::pressed, inputComponent));

	go->GetTransform()->SetPosition(x, y, 0.f);
	go->AddComponent(textureComp);
	go->AddComponent(collisionComp);
	go->AddComponent(turretComponent);
	go->AddComponent(inputComponent);
	go->AddComponent(movementComp);

	return go;
}

std::vector<std::shared_ptr<cycle::GameObject>> CreateHUD()
{
	std::vector<std::shared_ptr<cycle::GameObject>> res{};

	std::shared_ptr<cycle::GameObject> go = std::make_shared<cycle::GameObject>();
	std::shared_ptr<cycle::GameObject> go1 = std::make_shared<cycle::GameObject>();
	std::shared_ptr<cycle::GameObject> go2 = std::make_shared<cycle::GameObject>();
	std::shared_ptr<cycle::GameObject> go3 = std::make_shared<cycle::GameObject>();
	std::shared_ptr<cycle::GameObject> go4 = std::make_shared<cycle::GameObject>();
	auto font = cycle::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);
	auto fontSmall = cycle::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	cycle::TextComponent* textComp1{ new cycle::TextComponent{go1.get(), "10000", fontSmall}};
	cycle::TextComponent* textComp2{ new cycle::TextComponent{go2.get(), "0", font}};
	cycle::TextComponent* textComp3{ new cycle::TextComponent{go3.get(), "10000", fontSmall}};
	cycle::TextComponent* textComp4{ new cycle::TextComponent{go4.get(), "0", font}};

	ScoreComponent* scoreComp1{ new ScoreComponent{go1.get(), true, 10000, 100, textComp1} };
	ScoreComponent* scoreComp2{ new ScoreComponent{go2.get(), false, 0, 0, textComp2} };
	ScoreComponent* scoreComp3{ new ScoreComponent{go3.get(), true, 10000, 100, textComp3} };
	ScoreComponent* scoreComp4{ new ScoreComponent{go4.get(), false, 0, 0, textComp4} };

	HudComponent* hudComp{ new HudComponent{go.get(), scoreComp1, scoreComp2, scoreComp3, scoreComp4} };

	go1->GetTransform()->SetPosition(100, 20, 0.f);
	go2->GetTransform()->SetPosition(100, 50, 0.f);
	go3->GetTransform()->SetPosition(300, 20, 0.f);
	go4->GetTransform()->SetPosition(300, 50, 0.f);

	go1->SetParent(go.get());
	go2->SetParent(go.get());
	go3->SetParent(go.get());
	go4->SetParent(go.get());

	go1->AddComponent(scoreComp1);
	go1->AddComponent(textComp1);

	go2->AddComponent(scoreComp2);
	go2->AddComponent(textComp2);

	go3->AddComponent(scoreComp3);
	go3->AddComponent(textComp3);

	go4->AddComponent(scoreComp4);
	go4->AddComponent(textComp4);

	go->AddComponent(hudComp);

	

	res.push_back(go);
	res.push_back(go1);
	res.push_back(go2);
	res.push_back(go3);
	res.push_back(go4);

	return res;

}
