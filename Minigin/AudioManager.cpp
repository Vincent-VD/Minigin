#include "AudioManager.h"
#include <algorithm>
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
