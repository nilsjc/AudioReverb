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
            void ClickHi();
            void ClickLo();

            void InitVars();


        private:
            float outPutVol = 0.5;
            float oscillatorFreq = 100.0;
            float UpdateWithLinearInterpolation(float frequency);
            void createHarmonics(int start, int length, int harmonic);
    };
}
#endif