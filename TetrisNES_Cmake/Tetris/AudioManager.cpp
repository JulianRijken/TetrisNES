#include "pch.h"
#include "AudioManager.h"
#include <SDL.h>
#include <iostream>

AudioManager::AudioManager()
{
  // init sound
  SDL_Init(SDL_INIT_AUDIO);

  int frequency = 48000;
  Uint16 format = AUDIO_S16SYS;
  int channels = 2;
  int chunkSize = 4096;

  if (Mix_OpenAudio(frequency, format, channels, chunkSize) != 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
    exit(-1);
  }
}

AudioManager::~AudioManager()
{
  SDL_Quit();
}

void AudioManager::AddSound(const std::string& path, const std::string& name)
{
	Mix_Chunk* tmpChunk = Mix_LoadWAV(path.c_str());
	if (tmpChunk != nullptr)
	{
		if (m_SoundEffects.count(name))
		{
			std::cout << "Sound with the name " << name << " already exists" << std::endl;
			return;
		}

		m_SoundEffects.insert({ name, tmpChunk });
		std::cout << (m_SoundEffects.size() - 1) << " Sound is Ready, path: " << path << std::endl;
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
	}
}

void AudioManager::PlaySound(const std::string& name) const
{
  if (!m_SoundEffects.count(name))
  {
    std::cout << "Sound does not exist." << std::endl;
    return;
  }

  Mix_PlayChannel(-1, m_SoundEffects.at(name), 0);
  //std::cout << "Played Sound: " << name << std::endl;
}
