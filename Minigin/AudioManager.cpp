#include "AudioManager.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <SDL.h>
#include <thread>
#include <SDL_mixer.h>
#include "fmod.hpp"

using namespace cycle;

class AudioManager::AudioManagerImpl
{
public:
	AudioManagerImpl() = default;
	virtual ~AudioManagerImpl() = default;
	AudioManagerImpl(const AudioManagerImpl& other) = delete;
	AudioManagerImpl(AudioManagerImpl&& other) noexcept = delete;
	AudioManagerImpl& operator=(const AudioManagerImpl& other) = delete;
	AudioManagerImpl& operator=(AudioManagerImpl&& other) noexcept = delete;

	virtual void PlayAudio(const std::string filename, const float volume) = 0;
};

class AudioManager::FMODAudioManagerImpl : public AudioManagerImpl
{
public:
	FMODAudioManagerImpl()
	{
		FMOD_RESULT result = FMOD::System_Create(&m_pFmodSystem);
		if (result != FMOD_OK)
		{

			printf("FMOD error! (%d) \n", result);
			//exit(-1);
		}

		result = m_pFmodSystem->init(10, FMOD_INIT_NORMAL, nullptr);	// Initialize FMOD.
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) \n", result);
			//exit(-1);
		}
	}
	~FMODAudioManagerImpl() override
	{
		m_pFmodSystem->release();
	}

	FMODAudioManagerImpl(const FMODAudioManagerImpl& other) = delete;
	FMODAudioManagerImpl(FMODAudioManagerImpl&& other) noexcept = delete;
	FMODAudioManagerImpl& operator=(const FMODAudioManagerImpl& other) = delete;
	FMODAudioManagerImpl& operator=(FMODAudioManagerImpl&& other) noexcept = delete;

	void PlayAudio(const std::string filename, const float volume) override
	{
		
		FMOD::Sound* sound{};
		if (m_pFmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, nullptr, &sound) != FMOD_OK)
		{
			std::cout << "FMOD: Failed to create sound\n";
		}

		FMOD::Channel* fmodChannel{};
		fmodChannel->setVolume(volume);
		if (m_pFmodSystem->playSound(sound, nullptr, false, &fmodChannel) != FMOD_OK)
		{
			std::cout << "FMOD: Failed to play sound\n";
		}
	}

private:

	FMOD::System* m_pFmodSystem{ nullptr };

};


class AudioManager::SDLAudioManagerImpl : public AudioManagerImpl
{
public:
	SDLAudioManagerImpl()
	{
		// init sound
		SDL_Init(SDL_INIT_AUDIO);

		const int audioRate = 22050;
		const Uint16 audioFormat = AUDIO_S16SYS;
		const int audioChannels = 2;
		const int audioBuffers = 2048;

		if (Mix_OpenAudioDevice(audioRate, audioFormat, audioChannels, audioBuffers, nullptr, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE |
			SDL_AUDIO_ALLOW_CHANNELS_CHANGE) != 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
		}
	}
	~SDLAudioManagerImpl() override = default;
	SDLAudioManagerImpl(const SDLAudioManagerImpl& other) = delete;
	SDLAudioManagerImpl(SDLAudioManagerImpl&& other) noexcept = delete;
	SDLAudioManagerImpl& operator=(const SDLAudioManagerImpl& other) = delete;
	SDLAudioManagerImpl& operator=(SDLAudioManagerImpl&& other) noexcept = delete;

	void PlayAudio(const std::string filename, const float volume) override
	{
		auto fct = [this](const std::string filename, float volume)
		{
			Mix_Chunk* mixChunk = Mix_LoadWAV(filename.c_str());

			if (mixChunk != nullptr)
			{
				Mix_Volume(m_Channel, static_cast<int>(volume) * MIX_MAX_VOLUME);
				Mix_PlayChannel(m_Channel, mixChunk, 0);
				++m_Channel;
				if(m_Channel > 2)
				{
					m_Channel = 2;
				}
			}
			else
			{
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't play audio file: %s", Mix_GetError());
			}

		};

		std::thread thread{ fct, filename, volume };
		thread.detach();
	}

private:
	int m_Channel = 1;
};


void AudioManager::Init()
{
	//std::cout << "Other (?) thread ID: " << std::this_thread::get_id() << std::endl;

	m_Head = 0;
	m_Tail = 0;
	m_PendingSounds = std::vector<SoundDesc>(MAX_PENDING);
	m_pImpl = new SDLAudioManagerImpl();
}

AudioManager::~AudioManager()
{
	delete m_pImpl;
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

	if (m_Head == m_Tail) return;

	std::string path{ "Source/" };
	const SoundDesc soundDesc{ m_PendingSounds[m_Head] };
	switch (soundDesc.id)
	{
	case SoundId::def:
		break;
	case SoundId::theme:
		path += "S_Car_Pain_Edition_Overflow.wav";
		break;
	case SoundId::ram:
		path += "S_BatteringRamHit_04.wav";
		break;
	}

	m_pImpl->PlayAudio(path.c_str(), soundDesc.volume);

	m_Head = (m_Head + 1) % MAX_PENDING;
	
}