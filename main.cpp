#include <iostream>

#include "AudioFile.h"
#include "plot.h"

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

    cout << "--- audio file info ---" << "\n";
    cout << "Audio file loaded: " << pathToAudioFile << "\n";
    cout << "Sample rate: " << audioFile.getSampleRate() << "\n";
    cout << "Bit depth: " << audioFile.getBitDepth() << "\n";
    cout << "Number of channels: " << audioFile.getNumChannels() << "\n";
    cout << "Length in seconds: " << audioFile.getLengthInSeconds() << "\n";
    cout << "Number of samples: " << audioFile.getNumSamplesPerChannel() << "\n";
    cout << "-----------------------" << "\n";

    // plot audio file
    signalsmith::plot::Plot2D plot;

    // Customise the axes
    float numberOfSamples = audioFile.getNumSamplesPerChannel();
    plot.x.major(0).minors(0, numberOfSamples).label("time");
    plot.y.major(0).minors(-1, 1).label("amplitude");

    auto &signal = plot.line();
    for (int x = 0; x < numberOfSamples; x++) {
        signal.add(x, audioFile.samples[0][x]);
    }

    plot.write("wnoise_plot.svg");


    return 0;
}
