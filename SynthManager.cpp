#include "SynthManager.h"

float SynthManager::Manager::OutLeft()
{
    float synthAu = synth.OscResult * synthLevel;
    float reverbAu = reverb.ResultL * reverbLevel;
    return synthAu + reverbAu;
}

float SynthManager::Manager::OutRight()
{
    float synthAu = synth.OscResult * synthLevel;
    float reverbAu = reverb.ResultR * reverbLevel;
    return synthAu + reverbAu;
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

void SynthManager::Manager::TrigEnvelope()
{
    synth.TrigEnvelope();
}

void SynthManager::Manager::SetAttackTime(float a)
{
    synth.AttackTime = a;
}

void SynthManager::Manager::SetDecayTime(float d)
{
    synth.DecayTime = d;
}

void SynthManager::Manager::SetMixLevel(float m)
{
    synthLevel = m;
    reverbLevel = 1.0 - m;
}
