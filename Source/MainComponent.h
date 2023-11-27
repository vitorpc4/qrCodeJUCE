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
    TextButton btnGenerate{ "Gera QRCode"};

private:
    //==============================================================================
    // Your private member variables go here...
    std::unique_ptr<Drawable> background;
    void generateQrCode();
    void printQr(const qrcodegen::QrCode &qr);
    std::string qrCodeGenerated;
    std::string toSvgString(qrcodegen::QrCode& qr, int border);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
