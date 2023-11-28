
#include <iostream>
#include <sstream>
#include "MainComponent.h"
#include "QrCodeConvert.h"

//==============================================================================
MainComponent::MainComponent()
{
    inputData.setText("Insert data");
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    addAndMakeVisible(btnGenerate);
    addAndMakeVisible(inputData);
    btnGenerate.onClick = [this] { generateQrCode(); };

}

void MainComponent::resized()
{
    auto local = getBounds();
    btnGenerate.setBounds(getWidth() - 350, getHeight() - 80, 85, 50);
    inputData.setBounds(10, 25, 200, 24);

    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::generateQrCode()
{
    textData = inputData.getTextValue().getValue().toString();
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(textData.toRawUTF8(), qrcodegen::QrCode::Ecc::LOW);
    auto stringSvg = QrCodeConvert::toSvgString(qr, 4);
    auto xml = *parseXML(stringSvg).get();
    printQr(xml);
}

void MainComponent::printQr(juce::XmlElement& xml)
{
    background = Drawable::createFromSVG(xml);
    Rectangle<int> bounds = getLocalBounds().reduced(100);
    background->setTransformToFit(bounds.toFloat(), RectanglePlacement::onlyIncreaseInSize);
    addAndMakeVisible(background.get());
    repaint();
}

