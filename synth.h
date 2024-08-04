#ifndef SYNTH_H
#define SYNTH_H
namespace Synth
{
    class Synth
    {
        public:
            void SetOscFrequency(int f);
            float OscResult;
            void SetFilterFreq(int f);
            void SetFilterQ(int q);
            void SetAmpAttack(int a);
            void SetAmpDecay(int d);
            void SetFiltAttack(int a);
            void SetFiltDecay(int d);

            void SetStage1(int s);
            void SetStage2(int s);
            void SetStage3(int s);
            void SetStage4(int s);
            void SetStage5(int s);
            void SetStage6(int s);
            void SetTempo(int t);
            void Modulation(int m);

            void ClickHi();
            void ClickLo();

            void InitVars();


        private:
            float oscillatorFreq = 440.0;
            float UpdateWithLinearInterpolation(float frequency);
    };
}
#endif