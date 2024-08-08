#ifndef SYNTH_H
#define SYNTH_H
namespace Synth
{
    class Synth
    {
        public:
            void SetOscFrequency(int f);
            float OscResult;
            void SetHarmonics(int h);
            void SetOutputVol(float vol);
            void TrigEnvelope();
            float AttackTime = 0.01;
            float DecayTime = 0.01;
            void ClickHi();
            void ClickLo();

            void InitVars();


        private:
            bool envIsOn = false;
            bool envUp = false;
            float envelope = 0.0;
            float outPutVol = 0.5;
            float oscillatorFreq = 100.0;
            float UpdateWithLinearInterpolation(float frequency);
            void createHarmonics(int start, int length, int harmonic);
            void UpdateEnvelope();
    };
}
#endif