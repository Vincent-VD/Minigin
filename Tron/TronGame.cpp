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
#include "HighScoreHandler.h"
#include "HudComponent.h"
#include "HudObserver.h"
#include "LifeComponent.h"
#include "Minigin.h"
#include "MovementComponent.h"
#include "PlayerCollisionComponent.h"
#include "PlayerManager.h"
#include "ScoreComponent.h"
#include "SpawnPointManager.h"
#include "Subject.h"
#include "TextureComponent2D.h"
#include "TileCollisionComponent.h"

std::shared_ptr<cycle::GameObject> CreateTile(float x, float y);
std::shared_ptr<cycle::GameObject> CreatePlayer(float x, float y, const int playerId);
std::vector<std::shared_ptr<cycle::GameObject>> CreateHUD();


void TronGame::LoadGame() const
{
	auto& scene = cycle::SceneManager::GetInstance().CreateScene("Level_1");

	auto go = std::make_shared<cycle::GameObject>("fps");
	auto fps = new cycle::FPSComponent(go.get());
	go->GetTransform()->SetPosition(0, 0, 0.f);
	auto font = cycle::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto text = new cycle::TextComponent(go.get(), "0 FPS", font);
	go->AddComponent(text);
	go->AddComponent(fps);

	std::vector<std::shared_ptr<cycle::GameObject>> grid{ ReadLevelFile("../Data/Level_1.txt") };

	for (std::shared_ptr<cycle::GameObject>& gameObject : grid)
	{
		scene.Add(gameObject);
	}

	const Fvec2 pos1{ 33, 150 };
	const Fvec2 pos2{ cycle::g_WindowsInfo.m_Width - 64.f, 170 };

	const std::vector<Fvec2> spawnPoints{ pos1, pos2 };

	SpawnPointManager::GetInstance().Init(spawnPoints);
	PlayerManager::GetInstance().Init();

	std::vector<std::shared_ptr<cycle::GameObject>> hud{ CreateHUD() };

	std::shared_ptr<cycle::GameObject> player1{ CreatePlayer(pos1.x, pos1.y, 1)};
	cycle::Subject* subjectComp{ new cycle::Subject{go.get()} };
	HudObserver* observer{ new HudObserver{hud[0].get()} };
	subjectComp->AddObserver(observer);
	player1->AddComponent(subjectComp);

	std::shared_ptr<cycle::GameObject> player2{ CreatePlayer(pos2.x, pos2.y, 2)};
	subjectComp = new cycle::Subject{go.get()};
	observer = new HudObserver{hud[0].get()};
	subjectComp->AddObserver(observer);
	player2->AddComponent(subjectComp);

	for (std::shared_ptr<cycle::GameObject>& gameObject : hud)
	{
		scene.Add(gameObject);
	}

	scene.Add(player1);
	PlayerManager::GetInstance().AddPlayer(player1.get());
	scene.Add(player2);
	PlayerManager::GetInstance().AddPlayer(player2.get());

	ScoreTally::GetInstance().Init(hud[0].get());

	scene.Add(go);
}

void TronGame::LoadEnd()
{
	auto& scene = cycle::SceneManager::GetInstance().CreateScene("End");

	auto go = std::make_shared<cycle::GameObject>("title");
	auto font = cycle::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto winner{ ScoreTally::GetInstance().DecideWinner() };
	auto text = new cycle::TextComponent(go.get(), "Player " + std::to_string(winner.second) + " has won!", font);
	go->GetTransform()->SetPosition(cycle::g_WindowsInfo.m_Width / 2.f - 100.f, 100.f, 0.f);
	go->AddComponent(text);
	scene.Add(go);

	font = cycle::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	std::vector<cycle::TextComponent*> textComps{};
	for(int iter = 1; iter < 11; ++iter)
	{
		auto obj = std::make_shared<cycle::GameObject>("top10");
		cycle::TextComponent* textComp = new cycle::TextComponent(obj.get(), "test", font);
		textComps.push_back(textComp);
		obj->GetTransform()->SetPosition(cycle::g_WindowsInfo.m_Width / 2.f - 150.f, (iter * 60.f), 0.f);
		obj->AddComponent(textComp);
		scene.Add(obj);
	}

	HighScoreHandler highScore{ textComps };
	highScore.ReadScoreFromFile();
	highScore.InsertNewScore();
	highScore.SetTextToComponent();
	highScore.WriteScoreToFile();
	

	//scene.Add(go);

	cycle::SceneManager::GetInstance().NextScene();
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

	obj.close();
	return res;
}

std::shared_ptr<cycle::GameObject> CreateTile(float x, float y)
{
	std::shared_ptr<cycle::GameObject> go = std::make_shared<cycle::GameObject>("tile");
	cycle::TextureComponent2D* textureComp{ new cycle::TextureComponent2D{go.get(), "Tile.png", x, y, 32, 32, false}};
	TileCollisionComponent* collisionComp{ new TileCollisionComponent{go.get(), x, y, 32, 32, false}};

	go->GetTransform()->SetPosition(x, y, 0.f);
	go->AddComponent(textureComp);
	go->AddComponent(collisionComp);

	return go;
}

std::shared_ptr<cycle::GameObject> CreatePlayer(float x, float y, const int playerId)
{
	std::shared_ptr<cycle::GameObject> go = std::make_shared<cycle::GameObject>("player_" + std::to_string(playerId));
	cycle::TextureComponent2D* textureComp{ new cycle::TextureComponent2D{go.get(), "Tank_" + std::to_string(playerId) + ".png", x, y, 32, 32, true} };
	PlayerCollisionComponent* collisionComp{ new PlayerCollisionComponent{go.get(), x, y, 28, 28, true}};

	MovementComponent* movementComp{ new MovementComponent(go.get()) };
	TurretComponent* turretComponent{ new TurretComponent{go.get()} };

	LifeComponent* lifeComp{ new LifeComponent{go.get()} };

	auto inputComponent = new cycle::InputComponent (go.get(), playerId - 1);

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
	go->AddComponent(lifeComp);

	return go;
}

std::vector<std::shared_ptr<cycle::GameObject>> CreateHUD()
{
	std::vector<std::shared_ptr<cycle::GameObject>> res{};

	std::shared_ptr<cycle::GameObject> go = std::make_shared<cycle::GameObject>("hud");
	std::shared_ptr<cycle::GameObject> go2 = std::make_shared<cycle::GameObject>("hud");
	std::shared_ptr<cycle::GameObject> go3 = std::make_shared<cycle::GameObject>("hud");
	std::shared_ptr<cycle::GameObject> go4 = std::make_shared<cycle::GameObject>("hud");
	std::shared_ptr<cycle::GameObject> go1 = std::make_shared<cycle::GameObject>("hud");
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
