#pragma once
#include "Singleton.h"
#include <vector>

namespace FMOD
{
	class System;
}

namespace cycle
{
	enum class SoundId
	{
		def = -1,
		theme = 0,
		death = 1,
		shoot = 2
	};

	struct SoundDesc
	{
		SoundId id{ SoundId::def };
		float volume{ 0 };
	};

	class AudioManager : public Singleton<AudioManager>
	{
	public:

		class AudioManagerImpl;
		AudioManagerImpl* m_pImpl;

		class FMODAudioManagerImpl;

		class SDLAudioManagerImpl;

		void Init();

		~AudioManager() override;
		AudioManager(const AudioManager& other) = delete; 
		AudioManager(AudioManager&& other) noexcept = delete;
		AudioManager& operator=(const AudioManager& other) = delete;
		AudioManager& operator=(AudioManager&& other) noexcept = delete;

		void PlayAudio(SoundDesc soundDesc);
		void Update();

	protected:
		friend class Singleton<AudioManager>;
		AudioManager() = default;
		static const int MAX_PENDING{ 16 };
		int m_Head{};
		int m_Tail{};
		std::vector<SoundDesc> m_PendingSounds;

		FMOD::System* m_pFmodSystem{ nullptr };
	};
}
