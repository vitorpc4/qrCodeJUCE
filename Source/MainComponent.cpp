
#include <iostream>
#include <sstream>
#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent()
{
    //background = (Drawable::createFromImageData(BinaryData::calculaTest, BinaryData::calculaTestSize));



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

    btnGenerate.onClick = [this] { generateQrCode(); };
    
    if (qrCodeGenerated != "") {
        //background->draw(g, 1.f, AffineTransform());
        //background->drawAt(g, getWidth()/ 2, getHeight() / 2, 1.f);
        addAndMakeVisible(background.get());
        repaint();
        //g.drawText(qrCodeGenerated, 20, 40, 200, 40, juce::Justification::centred, true);
    }
}

void MainComponent::resized()
{
    auto local = getBounds();
    btnGenerate.setBounds(getWidth() - 350, getHeight() - 80, 85, 50);

    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::generateQrCode()
{
    const char* text = "155475987";
    qrcodegen::QrCode qr0 = qrcodegen::QrCode::encodeText(text, qrcodegen::QrCode::Ecc::LOW);
    auto svg = toSvgString(qr0, 4);
    auto voidData = svg.c_str();
    auto sizeOfData = sizeof(voidData);
    auto sizeString = svg.size();

    auto xml = *parseXML(svg).get();
    
    background = Drawable::createFromSVG(xml);
    Rectangle<int> bounds = getLocalBounds().reduced(100);
    background->setTransformToFit(bounds.toFloat(), RectanglePlacement::onlyIncreaseInSize);
}

void MainComponent::printQr(const qrcodegen::QrCode& qr)
{
    int border = 4;
    for (int y = -border; y < qr.getSize() + border; y++) {
        for (int x = -border; x < qr.getSize() + border; x++) {
            qrCodeGenerated += (qr.getModule(x, y) ? "##" : "  ");
        }
        qrCodeGenerated+="\n";
    }
    qrCodeGenerated += "\n";
}

std::string MainComponent::toSvgString(qrcodegen::QrCode& qr, int border)
{
    if (border < 0)
        throw std::domain_error("Border must be non-negative");
    if (border > INT_MAX / 2 || border * 2 > INT_MAX - qr.getSize())
        throw std::overflow_error("Border too large");

    std::ostringstream sb;
    sb << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    sb << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
    sb << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
    sb << (qr.getSize() + border * 2) << " " << (qr.getSize() + border * 2) << "\" stroke=\"none\">\n";
    sb << "\t<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/>\n";
    sb << "\t<path d=\"";
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            if (qr.getModule(x, y)) {
                if (x != 0 || y != 0)
                    sb << " ";
                sb << "M" << (x + border) << "," << (y + border) << "h1v1h-1z";
            }
        }
    }
    sb << "\" fill=\"#000000\"/>\n";
    sb << "</svg>\n";
    qrCodeGenerated = "Criado";
    return sb.str();
}
