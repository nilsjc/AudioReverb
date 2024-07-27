#include "wx/wx.h"
#include "wx/slider.h"
#include <wx/event.h>
#include <iostream>
#include "SynthManager.h"
#include "AudioStream.h"
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    void StartAudio();


private:
    SynthManager::Manager manager;
    AudioStream::Runner runner;
    void OnSlChanged(wxCommandEvent &event);
    bool running = true;
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
};

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
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

    grid->Add(new wxStaticText(this, 20008, ""));
    grid->Add(new wxStaticText(this, 20002, "time"));
    grid->Add(new wxStaticText(this, 20003, "damp"));
    grid->Add(new wxStaticText(this, 20004, "diffusion"));
    grid->Add(new wxStaticText(this, 20005, ""));
    grid->Add(new wxStaticText(this, 20006, ""));
    grid->Add(new wxStaticText(this, 20007, ""));
    grid->Add(new wxStaticText(this, 20008, ""));

    grid->Add(new wxStaticText(this, 20008, "Value:"));
    grid->Add(label10, 1, wxEXPAND | wxALL);

    this->SetSizer(grid);
    grid->Layout();
}

void MyFrame::StartAudio()
{
    // start reverb engine
    runner.SetManager(&manager);
    runner.Open();
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
        }
            break;
        case 2:
        {
            float dampv = value/100.0;
            manager.SetDamp(dampv);
        }
            break;
        case 3:
        {
            float diffusionv = value/100.0;
            manager.SetDiffusion(diffusionv);
        }
            break;
        
        default:
            break;
    }
    label10->SetLabel(std::to_string(value));
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
