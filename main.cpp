#include "wx/wx.h"
#include "wx/slider.h"
#include <wx/event.h>
#include "wx/button.h"
#include <iostream>
#include "SynthManager.h"
#include "AudioStream.h"
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    void StartAudio();
    void StopAudio();


private:
    SynthManager::Manager manager;
    AudioStream::Runner runner;
    void OnSlChanged(wxCommandEvent &event);
    void StartStopAudio(wxCommandEvent &event);
    bool running = false;
    wxStaticText *label10 = new wxStaticText(this, 20010, "50");
    wxSlider* sliders[8]={
        new wxSlider(this,10001,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator),
        new wxSlider(this,10002,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator),
        new wxSlider(this,10003,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator),
        new wxSlider(this,10004,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator),
        new wxSlider(this,10005,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator),
        new wxSlider(this,10006,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator),
        new wxSlider(this,10007,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator),
        new wxSlider(this,10008,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator)
    };
    wxButton* startStopButton = new wxButton(this, 30001, "start audio");
    wxButton* modulationButton = new wxButton(this, 30002, "mod wave");
};

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // Related to precalculations in audio engine
    manager.Init();

    // Wxwidgets related stuff
    wxGridSizer *grid = new wxGridSizer(3, 8, 0, 0);
    // bind sliders to function
    for(int x=0; x <8; x++)
    {
        sliders[x]->Bind(wxEVT_SLIDER, &MyFrame::OnSlChanged, this);
    }
    
    // add sliders to grid
    for(int x=0; x <8; x++)
    {
        grid->Add(sliders[x],1, wxEXPAND | wxALL);
    }

    //bind buttons
    startStopButton->Bind(wxEVT_BUTTON, &MyFrame::StartStopAudio, this);

    grid->Add(new wxStaticText(this, 20001, ""));
    grid->Add(new wxStaticText(this, 20002, "time"));
    grid->Add(new wxStaticText(this, 20003, "damp"));
    grid->Add(new wxStaticText(this, 20004, "diffsn"));
    grid->Add(new wxStaticText(this, 20005, "LFO1 f"));
    grid->Add(new wxStaticText(this, 20006, "LFO2 f"));
    grid->Add(new wxStaticText(this, 20007, "depth"));
    grid->Add(new wxStaticText(this, 20008, ""));

    grid->Add(new wxStaticText(this, 20008, "Value:"));
    grid->Add(label10, 1, wxEXPAND | wxALL);
    grid->Add(startStopButton);
    // grid->Add();
    // grid->Add(modulationButton);

    this->SetSizer(grid);
    grid->Layout();
}

void MyFrame::StartAudio()
{
    // start reverb engine
    runner.SetManager(&manager);
    //runner.Open();
}
void MyFrame::StartStopAudio(wxCommandEvent &event)
{
    if(running)
    {
        runner.Terminate();
        running = false;
        startStopButton->SetLabel("start audio");
    }else{
        runner.Open();
        running = true;
        startStopButton->SetLabel("stop audio");
    }
}
void MyFrame::OnSlChanged(wxCommandEvent &event)
{
    int slider = event.GetId() - 10001;
    int value = sliders[slider]->GetValue();
    switch (slider)
    {
        case 1:
        {
            if(value==100)value=99;
            float timev = value/100.0;
            manager.SetTime(timev);
            label10->SetLabel(std::to_string(timev));
        }
            break;
        case 2:
        {
            float dampv = value/100.0;
            manager.SetDamp(dampv);
            label10->SetLabel(std::to_string(dampv));
        }
            break;
        case 3:
        {
            float diffusionv = value/100.0;
            manager.SetDiffusion(diffusionv);
            label10->SetLabel(std::to_string(diffusionv));
        }
            break;
        case 4:
        {
            float lfo1freq = value;
            manager.SetLFO1(lfo1freq);
            label10->SetLabel(std::to_string(lfo1freq));
        }
            break;
        case 5:
        {
            float lfo2freq = value;
            manager.setLFO2(lfo2freq);
            label10->SetLabel(std::to_string(lfo2freq));
        }
            break;
        case 6:
        {
            float modAmp = value/4.0;
            manager.setMod(modAmp);
            label10->SetLabel(std::to_string(modAmp));
        }
        
        default:
            break;
    }
    event.Skip();
}


class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Experimental audio...", wxDefaultPosition, wxDefaultSize);
    frame->StartAudio();
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);
