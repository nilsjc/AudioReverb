#ifndef SYNTHMANAGER_H
#define SYNTHMANAGER_H
#include "PlateReverb.h"
#include "synth.h"
#include <iostream>
namespace SynthManager
{
    class Manager
    {
        public:
            float OutLeft();
            float OutRight();
            void Input(float* in);
            void Tick();
            void LoTick();
            void SetSynthVol(float v);
            void SetTime(float g);
            void SetDamp(float d);
            void SetDiffusion(float d);
            void SetLFO1(float l);
            void setLFO2(float l);
            void setMod(float m);
            void Init();
            void SetNote1(int f);
            void SetFrequency(int f);
            void SetHarmonics(int h);
            void SetOutputVol(float v);
            void TrigEnvelope();
            void SetAttackTime(float a);
            void SetDecayTime(float d);
            void SetMixLevel(float m);

        private:
            PlateR::Reverb reverb;
            Synth::Synth synth;
            float synthLevel;
            float reverbLevel;

    };
}

#endif