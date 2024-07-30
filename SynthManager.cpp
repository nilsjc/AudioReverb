#include "SynthManager.h"

float SynthManager::Manager::OutLeft()
{
    return reverb.ResultL;
}

float SynthManager::Manager::OutRight()
{
    return reverb.ResultR;
}

void SynthManager::Manager::Input(float *in)
{
    reverb.Input(in[0]);
}

void SynthManager::Manager::Tick()
{
    reverb.Tick();
    reverb.ModTick();
}

void SynthManager::Manager::LoTick()
{
    reverb.LoTick();
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
    reverb.CalculateVars();
}
