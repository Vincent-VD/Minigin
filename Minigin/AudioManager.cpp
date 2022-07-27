#include "AudioManager.h"
#include <algorithm>
#include <iostream>
#include <thread>

using namespace cycle;

void AudioManager::Init()
{
	m_Head = 0;
	m_Tail = 0;
	m_PendingSounds = std::vector<SoundDesc>(MAX_PENDING);
	//todo: init fmod
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_pFmodSystem);
	if(result != FMOD_OK)
	{
		
		printf("FMOD error! (%d) \n", result);
		//exit(-1);
	}

	result = m_pFmodSystem->init(100, FMOD_INIT_NORMAL, nullptr);	// Initialize FMOD.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) \n", result);
		//exit(-1);
	}

	FMOD::ChannelGroup* channelGroup = nullptr;
	result = m_pFmodSystem->createChannelGroup("inGameSoundEffects", &channelGroup);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD: Failed to create in-game sound effects channel group\n";
		//exit(-1);
	}

	FMOD::Sound* sound{};
	if(m_pFmodSystem->createSound("Source/S_Car_Pain_Edition_Overflow.mp3", FMOD_DEFAULT, nullptr, &sound) != FMOD_OK)
	{
		std::cout << "SDEFGHSDFJKFGSFD\n";
	}

	FMOD::Channel* channel = nullptr;
	result = m_pFmodSystem->playSound(sound, nullptr, false, &channel);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD: Failed to play sound\n";
		//exit(-1);
	}

}

void AudioManager::PlayAudio(SoundDesc soundDesc)
{
	for(int iter = m_Head; iter != m_Tail; iter = (iter + 1) % MAX_PENDING)
	{
		SoundDesc curr{ m_PendingSounds[iter] };
		if(curr.id == soundDesc.id)
		{
			curr.volume = std::max(curr.volume, soundDesc.volume);
			return;
		}
	}
	m_PendingSounds[m_Tail] = soundDesc;
	m_Tail = (m_Tail + 1) % MAX_PENDING;
}

void AudioManager::Update()
{
	//todo: play & thread audio
	
}
