#pragma once
#include "Singleton.h"
#include <vector>
#include "fmod_studio.hpp"
#include "fmod_common.h"
#include "fmod.hpp"


namespace cycle
{
	enum class SoundId
	{
		def = -1,
		main = 0
	};

	struct SoundDesc
	{
		SoundId id{ SoundId::def };
		int volume{ 0 };
	};

	class AudioManager : public Singleton<AudioManager>
	{
	public:

		void Init();

		~AudioManager() override = default;
		AudioManager(const AudioManager& other) = delete; 
		AudioManager(AudioManager&& other) noexcept = delete;
		AudioManager& operator=(const AudioManager& other) = delete;
		AudioManager& operator=(AudioManager&& other) noexcept = delete;

		void PlayAudio(SoundDesc soundDesc);
		void Update();

	private:
		friend class Singleton<AudioManager>;
		AudioManager() = default;
		static const int MAX_PENDING{ 16 };
		int m_Head{};
		int m_Tail{};
		std::vector<SoundDesc> m_PendingSounds;

		FMOD::System* m_pFmodSystem{ nullptr };

	};
}