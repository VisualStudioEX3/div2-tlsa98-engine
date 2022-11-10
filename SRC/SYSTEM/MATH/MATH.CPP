//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Math service.
*/

#include "MATH.H"

math_service_t* mathService;

static int min(int a, int b)
{
    return a < b ? a : b;
}

static int max(int a, int b)
{
    return a > b ? a : b;
}

static int clamp(int v, int a, int b)
{
    return v < a ? a : (v > b ? b : v);
}

static bool isClamped(int v, int a, int b)
{
    return v >= a && v <= b;
}

static int lerp(int a, int b, int t)
{
    return a + (((b - a) * t) >> 8);
}

void registerMathService()
{
    mathService = (math_service_t*)malloc(sizeof(math_service_t));

    mathService->min = min;
    mathService->max = max;
    mathService->clamp = clamp;
    mathService->isClamped = isClamped;
    mathService->lerp = lerp;

    registerService(MATH_SERVICE, mathService);
}