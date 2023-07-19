@ECHO OFF
REM Safe way to use DOS MD command.

REM FYI: For any reason, this code doesn't works as expected inside of a MAKEFILE under WMAKE interpreter.
REM The IF stament always returns false even when the folder exists.

IF NOT EXIST %1\ (
    ECHO creating %1 folder on root
    MD %1
)
@ECHO ON