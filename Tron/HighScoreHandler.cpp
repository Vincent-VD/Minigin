#include "HighScoreHandler.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "ScoreComponent.h"
#include <algorithm>

#include "GameObject.h"
#include "TextComponent.h"


void HighScoreHandler::ReadScoreFromFile()
{
	std::ifstream obj(m_Filename.c_str());
	if (!obj) {
		std::cerr << "Cannot open " << m_Filename << std::endl;
	}

	std::string line;
	while (std::getline(obj, line))
	{
		std::stringstream str{ line };

		std::string a{}, b{};
		int score{};
		str >> a >> b >> score;
		//std::cout << score << std::endl;
		m_PlayerScores.push_back(score);
	}
	obj.close();
}

void HighScoreHandler::WriteScoreToFile() const
{
	std::ofstream obj(m_Filename.c_str());
	if (!obj) {
		std::cerr << "Cannot open " << m_Filename << std::endl;
	}

	int iter{ 1 };
	for (auto score : m_PlayerScores)
	{
		std::string line{ std::to_string(iter) + ":\t" + "Tom" + "\t" + std::to_string(score) + "\n" };
		obj << line;
		++iter;
	}
	obj.close();
}

void HighScoreHandler::InsertNewScore()
{
	auto winner{ ScoreTally::GetInstance().DecideWinner() };

	m_PlayerScores.push_back(winner.first);

	std::sort(m_PlayerScores.begin(), m_PlayerScores.end());

	m_PlayerScores.resize(10);
}

void HighScoreHandler::SetTextToComponent() const
{
	//auto textComp{ m_pGameObject->GetComponent<cycle::TextComponent>() };

	std::string res{};

	for(size_t iter = 0; iter < m_pTextComps.size(); ++iter)
	{
		const auto currScore{ m_PlayerScores[iter] };
		const auto currComp{ m_pTextComps[iter] };

		std::string line{ std::to_string(iter) + ":   " + "Tom" + "  " + std::to_string(currScore) };
		currComp->SetText(line);
	}

	//textComp->SetText(res);
}
