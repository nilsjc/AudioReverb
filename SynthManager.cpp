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
