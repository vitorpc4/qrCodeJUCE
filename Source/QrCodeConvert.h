/*
  ==============================================================================

    QrCodeConvert.h
    Created: 27 Nov 2023 9:38:32pm
    Author:  vitor

  ==============================================================================
*/

#pragma once
#include <iostream>
#include "qrcodegen.h"

struct QrCodeConvert {
    static std::string toSvgString(qrcodegen::QrCode& qr, int border);
    static std::string printQr(const qrcodegen::QrCode& qr);
};