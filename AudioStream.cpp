#include "AudioStream.h"
#include "portaudio.h"
#include <iostream>
typedef float SAMPLE;
void AudioStream::Runner::SetManager(SynthManager::Manager* managerA)
{
    manager = managerA;
}

int AudioStream::Runner::paUserCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags)
{

    float *out = (float*)outputBuffer;
    int j;
    (void) timeInfo; /* Prevent unused variable warnings. */
    (void) statusFlags;

    const SAMPLE *in = (const SAMPLE*)inputBuffer;

    if(inputBuffer==NULL)
    {
        *out++ = 0;  /* left */
        *out++ = 0;  /* right */
    }
    else
    {
        //create signal
        for( j=0; j<framesPerBuffer; j++ )
        {
            SAMPLE sample[1];
            sample[0] = *in++; /* MONO input */
            // // reverb input
            manager->Input(sample);
            // // clock reverb memory 
            manager->Tick();

            float lvalue = manager->OutLeft();
            float rvalue = manager->OutRight();

            *out++ = lvalue;  /* left */
            *out++ = rvalue;  /* right */
        }
    }
    return paContinue;
}

void AudioStream::Runner::Open()
{
    PaError err;
    err = Pa_Initialize();
    if(err != paNoError)
    {
        std::cout << "problem initializing\n";
        return;
    }

    std::cout <<"AudioHal:: Opening stream...\n";
    err = Pa_OpenDefaultStream(
        &stream,
        1,          /* no input channels */
        2,          /* stereo output */
        paFloat32,  /* 32 bit floating point output */
        Sample_Rate,
        256,        /* frames per buffer */
        &Runner::paCallback,
        this
    );

    if (err != paNoError)
    {
        Terminate();
        return;
    }

    err = Pa_StartStream( stream );
    
    if (err != paNoError)
    {
        return;
    }
}

void AudioStream::Runner::Terminate()
{
    Pa_Terminate();
}
