#include "synth.h"
#include <math.h>
const int sampleRate = 44100;
float phase;
int TableSize = 512;
float fTableSize = 512.0;
float dtable0[512];
float table[512];

void Synth::Synth::SetOscFrequency(int f)
{
    oscillatorFreq = (float)f;
}

void Synth::Synth::ClickHi()
{
    OscResult = UpdateWithLinearInterpolation(oscillatorFreq);
}

void Synth::Synth::InitVars()
{
    float angle=0.0;
    for(int x = 0; x < 512; x++)
    {
        table[x]= 1.0 * sin(angle);
        angle += (6.2831853 / 512)*2;
    }
    for(int x = 1; x < 512; x++)
    {
        dtable0[x-1]=table[x]-table[x-1];
    }
    dtable0[0]=table[254]-table[0];
}


float Synth::Synth::UpdateWithLinearInterpolation(float frequency)
{
        int i = (int) phase;
        float alpha = phase - (float) i;
        phase += (fTableSize/sampleRate)*frequency;

        if(phase >= fTableSize)
                phase -= fTableSize;

        return table[i] + dtable0[i]*alpha;
}
