/*
 Lukas Cardot-goyette - Simple sound class using FMOD library
 */

#include "sound.h"

#include <stdio.h>


bool Sound::isOn = true;
bool Sound::isPossible = true;
char * Sound::currentSound;

FMOD_RESULT Sound::result;
FMOD_SYSTEM * Sound::fmodsystem;
FMOD_SOUND * Sound::sound;
FMOD_CHANNEL * Sound::channel;

void Sound::initialize (void)
{
    //create the sound system. If fails, sound is set to not possible
    result = FMOD_System_Create(&fmodsystem);
    if (result != FMOD_OK)
    {
        isPossible = false;
    }
    
    //if initialise the sound system. If fails, sound is set to not possible
    if (isPossible)
    {
        result = FMOD_System_Init(fmodsystem,2, FMOD_INIT_NORMAL, 0);
    }
    if (result != FMOD_OK)
    {
        isPossible = false;
    }
    
    //set to mute
    if (isPossible)
    {
        FMOD_Channel_SetVolume(channel,0.0f);
    }
}

void Sound::load (const char * filename)
{
    currentSound = (char *)filename;
    if (isPossible && isOn)
    {
        result = FMOD_Sound_Release(sound);
        result = FMOD_System_CreateSound(fmodsystem, currentSound, FMOD_CREATESAMPLE, 0, &sound);
        if (result != FMOD_OK)
        {
            isPossible = false;
        }
    }
}

void Sound::unload (void)
{
    if (isPossible)
    {
        result = FMOD_Sound_Release(sound);
    }
}

void Sound::play (bool pause)
{
    if (isPossible && isOn)
    {
        result = FMOD_System_PlaySound(fmodsystem,FMOD_CHANNEL_FREE, sound, 0, NULL);
        FMOD_Channel_SetMode(channel,FMOD_LOOP_NORMAL);
    }
}

void Sound::toggleSound (void)
{
    isOn = !isOn;
    if (isOn == true)
    {
        load(currentSound);
        play();
    }
    if (isOn == false)
    {
        unload();
    }
}

void Sound::togglePause (void)
{
    FMOD_BOOL p;
    FMOD_Channel_GetPaused(channel,&p);
    FMOD_Channel_SetPaused (channel,!p);
}

bool Sound::getSound (void)
{
    return isOn;
}
