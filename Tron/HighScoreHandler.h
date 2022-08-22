#pragma once
#include <string>
#include <vector>

namespace cycle
{
	class TextComponent;
}

class HighScoreHandler
{
public:
	HighScoreHandler(std::vector<cycle::TextComponent*> textComps) : m_pTextComps(textComps) {}
	virtual ~HighScoreHandler() = default;
	HighScoreHandler(const HighScoreHandler& other) = delete;
	HighScoreHandler(HighScoreHandler&& other) noexcept = delete;
	HighScoreHandler& operator=(const HighScoreHandler& other) = delete;
	HighScoreHandler& operator=(HighScoreHandler&& other) noexcept = delete;

	void ReadScoreFromFile();
	void WriteScoreToFile() const;

	void InsertNewScore();

	void SetTextToComponent() const;

private:
	const std::string m_Filename{"../Data/thehighs.txt"};
	std::vector<int> m_PlayerScores{};

	std::vector<cycle::TextComponent*> m_pTextComps;
};

