#ifndef HOST_AUDIO_H
#define HOST_AUDIO_H

#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

class Audio  {
private:
    AudioGeneratorMP3 *mp3;
    AudioFileSourceSD *file;
    AudioOutputI2S *out;
    AudioFileSourceID3 *id3; 
    bool playing = true;
public:
    // Audio();
    void playMP3(char *filename);
};

#endif