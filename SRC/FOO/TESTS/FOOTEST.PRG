//! FOO.DLL - Test library.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, Jos‚ Miguel S nchez Fern ndez - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    DIV Games Studio 2 test program for FOO.DLL.
*/

compiler_options _case_sensitive;

program tlsa98_engine_foo_test;

import "system.dll";
import "foo.dll";

begin
    helloWorldTest();
    waitInputToExit();
end

function waitInputToExit()
begin
    write(0, 0, 190, 0, "Press any key to exit...");

    while (scan_code == 0)
        frame;
    end

    exit("Ok", 0);
end

function helloWorldTest()
private
    string message;

begin
    getHelloWorldMessage(message);
    write(0, 0, 0, 0, message);
end