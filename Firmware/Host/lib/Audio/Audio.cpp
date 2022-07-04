#include "Audio.h"
#include <M5Stack.h>

void Audio::playMP3(char *filename){
    file = new AudioFileSourceSD(filename);
    id3 = new AudioFileSourceID3(file);
    out = new AudioOutputI2S(0, 1); // Output to builtInDAC
    out->SetOutputModeMono(true);
    out->SetGain(1.0);
    mp3 = new AudioGeneratorMP3();
    mp3->begin(id3, out);
    while(mp3->isRunning()) {
        if (!mp3->loop()) mp3->stop();
    }
}