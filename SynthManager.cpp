#include "SynthManager.h"

float SynthManager::Manager::OutLeft()
{
    //return synth.OscResult;
    return reverb.ResultL;
}

float SynthManager::Manager::OutRight()
{
    //return synth.OscResult;

    return reverb.ResultR;
}

void SynthManager::Manager::Input(float *in)
{
    //reverb.Input(in[0]);
    reverb.Input(synth.OscResult);
}

void SynthManager::Manager::Tick()
{
    synth.ClickHi();
    reverb.Tick();
    reverb.ModTick();
}

void SynthManager::Manager::LoTick()
{
    reverb.LoTick();
}

void SynthManager::Manager::SetSynthVol(float v)
{
}

void SynthManager::Manager::SetTime(float g)
{
    reverb.Gain = g;
}

void SynthManager::Manager::SetDamp(float d)
{
    reverb.Damping = d;
}

void SynthManager::Manager::SetDiffusion(float d)
{
    reverb.Diffusion = d;
}

void SynthManager::Manager::SetLFO1(float l)
{
    reverb.LFO1freq = l;
}

void SynthManager::Manager::setLFO2(float l)
{
    reverb.LFO2freq = l;
}

void SynthManager::Manager::setMod(float m)
{
    reverb.LFO1ampl = m;
    reverb.LFO2ampl = m;
}

void SynthManager::Manager::Init()
{
    synth.InitVars();
    reverb.CalculateVars();
}

void SynthManager::Manager::SetFrequency(int f)
{
    synth.SetOscFrequency(f);
}

void SynthManager::Manager::SetHarmonics(int h)
{
    synth.SetHarmonics(h);
}

void SynthManager::Manager::SetOutputVol(float v)
{
    synth.SetOutputVol(v);
}
