#include "AudioManager.h"
#include "ResourcePath.hpp"

AudioManager::AudioManager()
: m_music()
, m_soundMap()
, m_soundList(100)
, m_soundListIndex(0)
{
}

void AudioManager::init()
{
   loadSoundEffect(resourcePath() + "audio/gun_shoot.wav", GUN_SHOOT);
   loadSoundEffect(resourcePath() + "audio/ship_explosion.wav", SHIP_EXPLOSION);
   loadSoundEffect(resourcePath() + "audio/asteroid_hit.wav", ASTEROID_HIT);
   loadSoundEffect(resourcePath() + "audio/asteroid_explosion.wav", ASTEROID_EXPLOSION);
   loadSoundEffect(resourcePath() + "audio/scout_hit.wav", SCOUT_HIT);
   loadSoundEffect(resourcePath() + "audio/scout_explosion.wav", SCOUT_EXPLOSION);
   loadSoundEffect(resourcePath() + "audio/blip.wav", SELECT_BLIP);

   if (!m_music.openFromFile(resourcePath() + "audio/Space_Fighter_Loop.ogg"))
   {
      printf("Error loading music.");
   }
}


void AudioManager::playSound(SoundId id)
{
   auto it = m_soundMap.find(id);

   if (it != end(m_soundMap))
   {
      play(it->second);
   }
}

void AudioManager::playMusic()
{
    m_music.play();
    m_music.setLoop(true);
}

void AudioManager::pauseMusic()
{
    if (m_music.getStatus() == sf::SoundSource::Playing)
    {
        m_music.pause();
    }
    else
    {
        m_music.play();
    }
}

void AudioManager::loadSoundEffect(const std::string& fileName, SoundId id)
{
   auto it = m_soundMap.find(id);

   if (it != end(m_soundMap))
   {
      // Sound already loaded
      return;
   }

   if(!m_soundMap[id].loadFromFile(fileName.c_str()))
   {
      printf("Colud not load sound");
   }
}

void AudioManager::play(const sf::SoundBuffer& soundBuffer)
{
   for (size_t i = 0; i < m_soundList.size(); ++i)
   {
      auto& sound(m_soundList[m_soundListIndex]);

      if (sound.getStatus() != sf::SoundSource::Playing)
      {
         sound.setBuffer(soundBuffer);
         sound.play();
         m_soundListIndex = ++m_soundListIndex % m_soundList.size();
         break;
      }

      m_soundListIndex = ++m_soundListIndex % m_soundList.size();
   }
}
