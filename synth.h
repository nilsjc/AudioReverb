#ifndef SYNTH_H
#define SYNTH_H
namespace Synth
{
    class Synth
    {
        public:
            void SetOscFrequency(int f);
            void SetHarmonicsPot(int p);
            float OscResult;
            void SetHarmonics(int h);
            void SetOutputVol(float vol);
            void TrigEnvelope();
            float AttackTime = 0.01;
            float DecayTime = 0.01;
            float envFM = 0.0;
            float envWM = 0.0;
            void ChangeReadWave();


            void ClickHi();
            void ClickLo();

            void InitVars();


        private:
            bool sineRead = false;
            bool envIsOn = false;
            bool envUp = false;
            float envelope = 0.0;
            float outPutVol = 0.5;
            float oscillatorFreq = 100.0;
            float envFMsig = 0.0;
            float envWMsig = 0.0;
            int harmonicsPot = 0;
            float UpdateWithLinearInterpolation(float frequency);
            void createHarmonics(int start, int length, int harmonic);
            void UpdateEnvelope();
    };
}
#endif