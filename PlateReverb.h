#ifndef PLATEREVERB_H
#define PLATEREVERB_H
namespace PlateR
{
    class Reverb
    {
        public:
            void ModTick();
            void Input(float input);
            void Tick();
            void LoTick();
            void CalculateVars();
            float Gain = 0.8f;
            float Diffusion = 0.5f;
            float Damping = 0.1f;
            float ResultL;
            float ResultR;
            float LFO1freq = 0.1;
            float LFO2freq = 0.08;
            float LFO1ampl = 0.2;
            float LFO2ampl = 0.2;

        private:
            const int Sample_Rate = 44100;
            float allPass(float input, float gain, float(&delayLine)[], int& play, int& rec);
            float longDelay(float input, float(&delayLine)[], int& play, int& rec);
            float pipe1 = 0.0f;
            float pipe2 = 0.0f;
            float loPass1(float input, float gain);
            float loPass2(float input, float gain);
            float modWave1 = 0.0f;
            float modWave2 = 0.0f;
            float angle1 = 0; 
            float angle2 = 0;
            float modWaveRad = 0;
            const float doublePI = 6.2831853;

        // vars


    };
}
#endif