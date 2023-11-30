/*
  ==============================================================================

    QrCodeConvert.cpp
    Created: 27 Nov 2023 9:38:32pm
    Author:  vitor

  ==============================================================================
*/
#include "QrCodeConvert.h"
#include <sstream>
#include <JuceHeader.h>

std::string QrCodeConvert::toSvgString(qrcodegen::QrCode& qr, int border)
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
    return sb.str();
}

std::string QrCodeConvert::printQr(const qrcodegen::QrCode& qr)
{
    std::string textData;
    int border = 4;
    for (int y = -border; y < qr.getSize() + border; y++) {
        for (int x = -border; x < qr.getSize() + border; x++) {
            textData += (qr.getModule(x, y) ? "##" : "  ");
        }
        textData += "\n";
    }
    textData += "\n";

    return textData;
}

void QrCodeConvert::exportFile(const std::string svg)
{
    auto initialPath = File::getSpecialLocation(File::hostApplicationPath).getParentDirectory().getFullPathName();

    File resourceFile(initialPath + "\\file.svg");
   
    if (resourceFile.exists()) {
        resourceFile.deleteFile();
    }

    FileOutputStream output(resourceFile);

    if (!output.openedOk()) {
        DBG("FileOutputstream didn't open correctly...");
    }

    output.write(svg.c_str(), svg.size());
    
    output.flush();

    if (output.getStatus().failed()) {
        DBG("Failed in outputstream");
    }

}
