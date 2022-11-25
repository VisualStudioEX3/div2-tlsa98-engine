//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Math service.
*/

#include "..\..\H\MATH.H"

math_service_t* mathService;

static int min(int a, int b)
{
    return a < b ? a : b;
}

static void div_min()
{
    int b = getparm();
    int a = getparm();

    retval(min(a, b));
}

static int max(int a, int b)
{
    return a > b ? a : b;
}

static void div_max()
{
    int b = getparm();
    int a = getparm();

    retval(max(a, b));
}

static int clamp(int v, int a, int b)
{
    return v < a ? a : (v > b ? b : v);
}

static void div_clamp()
{
    int b = getparm();
    int a = getparm();
    int v = getparm();

    retval(clamp(v, a, b));
}

static bool isClamped(int v, int a, int b)
{
    return v >= a && v <= b;
}

static void div_isClamped()
{
    int b = getparm();
    int a = getparm();
    int v = getparm();

    retval(isClamped(v, a, b));
}

static int lerp(int a, int b, int t)
{
    return a + (((b - a) * t) >> 8);
}

static void div_lerp()
{
    int t = getparm();
    int b = getparm();
    int a = getparm();

    retval(lerp(a, b, t));
}

void registerMathService()
{
    mathService = (math_service_t*)malloc(sizeof(math_service_t));

    mathService->min        = min;
    mathService->max        = max;
    mathService->clamp      = clamp;
    mathService->isClamped  = isClamped;
    mathService->lerp       = lerp;

    registerService(MATH_SERVICE, mathService);
}

void exportMathService(div_function_exporter_service_t* service)
{
    service->registerFunction("min",        2, div_min);
    service->registerFunction("max",        2, div_max);
    service->registerFunction("clamp",      3, div_clamp);
    service->registerFunction("is_clamped", 3, div_isClamped);
    service->registerFunction("lerp",       3, div_lerp);
}