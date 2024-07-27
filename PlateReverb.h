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
            float Gain = 0.8f;
            float Diffusion = 0.5f;
            float Damping = 0.1f;
            float ResultL;
            float ResultR;

        private:
        // functions
            float allPass(float input, float gain, float(&delayLine)[], int& play, int& rec);
            float longDelay(float input, float(&delayLine)[], int& play, int& rec);
            float pipe1 = 0.0f;
            float pipe2 = 0.0f;
            float loPass1(float input, float gain);
            float loPass2(float input, float gain);

        // vars


    };
}
#endif