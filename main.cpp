#include <iostream>
// #include <cstdint>

#include "AudioFile.h"

using namespace std;

#define PROJECT_ROOT_DIR "C:/dev/audio_playground"

int main(int argc, char *argv[])
{
    cout << "--- hack audio --" << "\n";
    
    // read in audio file
    const string pathToAudioFile = string(PROJECT_ROOT_DIR) + "/wav_files/wnoise.wav";

    AudioFile<float> audioFile;
    bool loaded = audioFile.load(pathToAudioFile);
    if (!loaded) {
        cout << "Error, unabled to load audiofile: " << pathToAudioFile << "\n";
        return 1;
    }

    cout << "Audio file loaded: " << pathToAudioFile << "\n";
    cout << "Sample rate: " << audioFile.getSampleRate() << "\n";
    cout << "Bit depth: " << audioFile.getBitDepth() << "\n";
    cout << "Number of channels: " << audioFile.getNumChannels() << "\n";
    cout << "Length in seconds: " << audioFile.getLengthInSeconds() << "\n";

    // plot audio file

    return 0;
}
