#ifndef SYNTHMANAGER_H
#define SYNTHMANAGER_H
#include "PlateReverb.h"
namespace SynthManager
{
    class Manager
    {
        public:
            float OutLeft();
            float OutRight();
            void Input(float* in);
            void Tick();
            void SetTime(float g);
            void SetDamp(float d);
            void SetDiffusion(float d);



        private:
            PlateR::Reverb reverb;

    };
}

#endif