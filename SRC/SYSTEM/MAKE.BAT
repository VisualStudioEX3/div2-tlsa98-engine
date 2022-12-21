wcl386 ^
SYSTEM.CPP ^
SERVICES.CPP ^
SERVICES\MATH.CPP ^
SERVICES\MEM.CPP ^
SERVICES\STRING.CPP ^
SERVICES\DIVFNEXP\DIVFNEXP.CPP ^
/l=div_dll -s

if exist *.obj del /f /q *.obj
if exist *.err del /f /q *.err