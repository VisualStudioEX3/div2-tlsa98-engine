//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Math service functions exported to DIV language.
*/

#include "DIVFNEXP.H"

math_service_t* service;

void exportMathService(LIBRARY_PARAMS)
{
    service = (math_service_t*)getService(MATH_SERVICE);

    COM_export(DIV_MATH_FUNC_MIN_NAME,          min,        DIV_MATH_FUNC_MIN_PARAMS);
    COM_export(DIV_MATH_FUNC_MAX_NAME,          max,        DIV_MATH_FUNC_MAX_PARAMS);
    COM_export(DIV_MATH_FUNC_CLAMP_NAME,        clamp,      DIV_MATH_FUNC_CLAMP_PARAMS);
    COM_export(DIV_MATH_FUNC_IS_CLAMPED_NAME,   isClamped,  DIV_MATH_FUNC_IS_CLAMPED_PARAMS);
    COM_export(DIV_MATH_FUNC_LERP_NAME,         lerp,       DIV_MATH_FUNC_LERP_PARAMS);
}

void min()
{
    int b = getparm();
    int a = getparm();
    int result = service->min(a, b);

    retval(result);
}

void max()
{
    int b = getparm();
    int a = getparm();
    int result = service->max(a, b);

    retval(result);
}

void clamp()
{
    int b = getparm();
    int a = getparm();
    int v = getparm();
    int result = service->clamp(v, a, b);

    retval(result);
}

void isClamped()
{
    int b = getparm();
    int a = getparm();
    int v = getparm();
    bool result = service->isClamped(v, a, b);

    retval(result);
}

void lerp()
{
    int t = getparm();
    int b = getparm();
    int a = getparm();
    int result = service->lerp(a, b, t);

    retval(result);
}