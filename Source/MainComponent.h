#pragma once

#include <JuceHeader.h>
#include "qrcodegen.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void generateQrCode();

private:
    //==============================================================================
    // Your private member variables go here...
    std::unique_ptr<Drawable> background;
    TextEditor inputData;
    TextButton btnGenerate{ "Gera QRCode" };
    void printQr(juce::XmlElement& xml);

    String textData;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
