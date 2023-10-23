#pragma once
#include "framework.h"
class Color {

public:

    static const XMFLOAT4 inline red() { return { 1,0,0,1 }; };
    static const XMFLOAT4 inline green() { return { 0,1,0,1 }; };
    static const XMFLOAT4 inline blue() { return { 0,0,1,1 }; };

    static const XMFLOAT4 inline yellow() { return { 1,1,0,1 }; };
    static const XMFLOAT4 inline purple() { return { 1,0,1,1 }; };
    static const XMFLOAT4 inline cyan() { return { 0,1,1,1 }; };

    static const XMFLOAT4 inline white() { return { 1,1,1,1 }; };
    static const XMFLOAT4 inline black() { return { 0,0,0,0 }; };

};