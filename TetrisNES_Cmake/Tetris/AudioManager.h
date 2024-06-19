#pragma once
#include <map>
#include <SDL_mixer.h>

class AudioManager
{
public:
  AudioManager();
  ~AudioManager();

  void AddSound(const std::string& path, const std::string& name);

  void PlaySound(const std::string& name) const;

private:
  
  std::map<std::string, Mix_Chunk*> m_SoundEffects;
};
