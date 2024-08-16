#include "synth.h"
#include <math.h>
const int sampleRate = 44100;
float phase;
const int TableSize = 512;
float fTableSize = 512.0;
float dtable0[1024];
float table[4096];
int peek = 0;
int waveSelect = 0;
int nextWaveSelect = TableSize;
float wave1vol = 0.0;
float wave2vol = 0.0;
const int mixReso = 32;
int readIndex = 0;
const int sinePointTable[512]
{
256, 259, 262, 265, 269, 272, 275, 278, 281, 284, 287, 290, 294, 297, 300, 303,
306, 309, 312, 315, 318, 321, 324, 327, 330, 333, 336, 339, 342, 345, 348, 351,
354, 357, 360, 363, 365, 368, 371, 374, 377, 379, 382, 385, 388, 390, 393, 396,
398, 401, 403, 406, 408, 411, 413, 416, 418, 421, 423, 426, 428, 430, 433, 435,
437, 439, 441, 444, 446, 448, 450, 452, 454, 456, 458, 460, 462, 463, 465, 467,
469, 471, 472, 474, 476, 477, 479, 480, 482, 483, 485, 486, 487, 489, 490, 491,
493, 494, 495, 496, 497, 498, 499, 500, 501, 502, 503, 504, 504, 505, 506, 506,
507, 508, 508, 509, 509, 510, 510, 510, 511, 511, 511, 512, 512, 512, 512, 512,
512, 512, 512, 512, 512, 512, 511, 511, 511, 510, 510, 510, 509, 509, 508, 508,
507, 506, 506, 505, 504, 504, 503, 502, 501, 500, 499, 498, 497, 496, 495, 494,
493, 491, 490, 489, 487, 486, 485, 483, 482, 480, 479, 477, 476, 474, 472, 471,
469, 467, 465, 463, 462, 460, 458, 456, 454, 452, 450, 448, 446, 444, 441, 439,
437, 435, 433, 430, 428, 426, 423, 421, 418, 416, 413, 411, 408, 406, 403, 401,
398, 396, 393, 390, 388, 385, 382, 379, 377, 374, 371, 368, 365, 363, 360, 357,
354, 351, 348, 345, 342, 339, 336, 333, 330, 327, 324, 321, 318, 315, 312, 309,
306, 303, 300, 297, 294, 290, 287, 284, 281, 278, 275, 272, 269, 265, 262, 259,
256, 253, 250, 247, 243, 240, 237, 234, 231, 228, 225, 222, 218, 215, 212, 209,
206, 203, 200, 197, 194, 191, 188, 185, 182, 179, 176, 173, 170, 167, 164, 161,
158, 155, 152, 149, 147, 144, 141, 138, 135, 133, 130, 127, 124, 122, 119, 116,
114, 111, 109, 106, 104, 101, 99, 96, 94, 91, 89, 86, 84, 82, 79, 77,
75, 73, 71, 68, 66, 64, 62, 60, 58, 56, 54, 52, 50, 49, 47, 45,
43, 41, 40, 38, 36, 35, 33, 32, 30, 29, 27, 26, 25, 23, 22, 21,
19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 8, 7, 6, 6,
5, 4, 4, 3, 3, 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4,
5, 6, 6, 7, 8, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
19, 21, 22, 23, 25, 26, 27, 29, 30, 32, 33, 35, 36, 38, 40, 41,
43, 45, 47, 49, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 71, 73,
75, 77, 79, 82, 84, 86, 89, 91, 94, 96, 99, 101, 104, 106, 109, 111,
114, 116, 119, 122, 124, 127, 130, 133, 135, 138, 141, 144, 147, 149, 152, 155,
158, 161, 164, 167, 170, 173, 176, 179, 182, 185, 188, 191, 194, 197, 200, 203,
206, 209, 212, 215, 218, 222, 225, 228, 231, 234, 237, 240, 243, 247, 250, 253,

};

void Synth::Synth::SetOscFrequency(int f)
{
    oscillatorFreq = (float)f;
}

void Synth::Synth::SetHarmonicsPot(int p)
{
    harmonicsPot = p;
    SetHarmonics(p);
}

void Synth::Synth::SetHarmonics(int h)
{
    int ws = 0;
    float mix = 0;
    int count = 0;
    int copyH = h;
    while(copyH > (mixReso-1))
    {
        ++count;
        copyH = copyH - mixReso;
    }
    ws = count;
    mix = (float)h-(mixReso * count);
    mix /= 64.0;
    waveSelect = ws * TableSize;
    nextWaveSelect = (ws+1) * TableSize;
    wave1vol = 1.0 - mix;
    wave2vol = mix;
}

void Synth::Synth::SetOutputVol(float vol)
{
    outPutVol = vol;
}

void Synth::Synth::TrigEnvelope()
{
    if(envIsOn==false)
    {
        envIsOn = true;
        envUp = true;
    }
    
}

void Synth::Synth::ChangeReadWave()
{
    sineRead ^= true;
}

void Synth::Synth::ClickHi()
{
    OscResult = UpdateWithLinearInterpolation(oscillatorFreq + envFMsig);
}

void Synth::Synth::ClickLo()
{
    if(envIsOn)
    {
        UpdateEnvelope();
        envWMsig = envelope * envWM;
        envWMsig *=100;
        int envWMint = (int)envWMsig;
        SetHarmonics(harmonicsPot + envWMint);
        envFMsig = envelope * envFM;
    }
}

void Synth::Synth::InitVars()
{
    float angle=0.0;
    // sine wave tables
    for(int x = 0; x < 8; x++)
    {
        createHarmonics(x*512,512,1+x);
    }    
}


float Synth::Synth::UpdateWithLinearInterpolation(float frequency)
{
        int i = (int) phase;
        float alpha = phase - (float) i;
        phase += (fTableSize/sampleRate)*frequency;

        if(phase >= fTableSize)
                phase -= fTableSize;

        if(sineRead){
            readIndex = sinePointTable[i];
        }else{
            readIndex = i;
        }
        float first = table[readIndex + waveSelect];
        float second = table[(readIndex + nextWaveSelect)];
        float result = (first * wave1vol) + (second * wave2vol);
        return result * envelope;
}

void Synth::Synth::createHarmonics(int start, int length, int harmonic)
{
    float angle=0.0;
    // sine wave tables
    for(int x = start; x < start + length; x++)
    {
        table[x]= 1.0 * sin(angle);
        angle += (6.2831853 / 512)* 2 *harmonic;
    }
}

void Synth::Synth::UpdateEnvelope()
{
    if(envUp)
    {
        envelope += AttackTime;
        if(envelope>=1.0)
        {
            envUp = false;
            envelope = 1.0;
        }
    }else{
        envelope -= DecayTime;
        if(envelope<=0)
        {
            envIsOn = false;
            envelope = 0.0;
        }
    }


}
