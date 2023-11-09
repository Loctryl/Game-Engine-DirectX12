#pragma once
#include "framework.h"

// Static class providing default float4 for colors
class Color {
public:
    static inline XMFLOAT4 red() { return { 1,0,0,1 }; };
    static inline XMFLOAT4 green() { return { 0,1,0,1 }; };
    static inline XMFLOAT4 blue() { return { 0,0,1,1 }; };

    static inline XMFLOAT4 yellow() { return { 1,1,0,1 }; };
    static inline XMFLOAT4 purple() { return { 1,0,1,1 }; };
    static inline XMFLOAT4 cyan() { return { 0,1,1,1 }; };

    static inline XMFLOAT4 white() { return { 1,1,1,1 }; };
    static inline XMFLOAT4 black() { return { 0,0,0,0 }; };
};