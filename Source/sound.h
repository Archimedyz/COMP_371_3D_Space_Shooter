#include "fmod.h"

class Sound {
private:
    static bool isOn; //is sound on?
    static bool isPossible; //is it possible to play sound?
    static char * currentSound; //currently played sound
    
    static FMOD_RESULT result;
    static FMOD_SYSTEM * fmodsystem;
    static FMOD_SOUND * sound;
    static FMOD_CHANNEL * channel;
    
public:
    static void initialize (); //initializes sound
   
    static void load (const char * filename); //loads a soundfile
    static void unload (); //frees the sound object
    static void play (bool pause = false); //plays a sound
    
    static bool getSound (); //checks if sound is on
    
    static void toggleSound (); //toggles sound on and off - Game Over?
    static void togglePause (); //toggle pause on and off - Pause menu?
};