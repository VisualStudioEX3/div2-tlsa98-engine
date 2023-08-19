<h1 align="center">
<img src="https://github.com/VisualStudioEX3/VisualStudioEX3/blob/master/Shared/Images/div_games_studio/div2_logo/div2_logo.png" alt="DIV Games Studio 2 logo" width="512" />
<br>
TLSA98 Engine</h1>
<h6 align="center">© Visual Studio EX3, José Miguel Sánchez Fernández - 2022 - 2023</h6>
<h2 align="center">A native game engine for DIV Games Studio 2 (vanilla)</h2>

> **Note**
> Check the [**develop**](https://github.com/VisualStudioEX3/div2-tlsa98-engine/tree/develop) and [**feature**](https://github.com/VisualStudioEX3/div2-tlsa98-engine/branches/all?query=feature) branches to follow progress of this project.

# Introduction

This is a side project where I spent my spare time working in some fun ideas to improve **DIV Games Studio 2** through his DLL system, and a way to practice with C language and challenge me with old technologies, trying some architecture ideas and new features for the DIV Games Studio engine like the follow ones:

- Service architecture.
- In-game interactive debug console (Quake console style).
- Callbacks and event support.
- Component system for DIV Games Studio processes.
- Basic box collision system.
- Advanced input manager based on maps with action and axes.
- Basic GUI system for ease compose in-game menus and HUD systems.
- And many other awesome features.

The main purpose is liberate DIV code to the necessity of write complex features with the limitation of the language and engine, and to be able to separate the code in many files as you want instead of a huge single code file, and then simply add and setup the required behaviours in each DIV process in a similar way to do in modern game engines. In few words: use DIV language as a top-level script system and move all complex features to native code.

All effort is focused on build an engine for develop a possible 2D cinematic platformer, but how is it based on services and components in separated libraries for each system specialization, the engine will be suitable for any type of game.

The engine is full developing in **ANSI C-89** and using **Watcom C++ 10.6** as compiler. This election of C language version and compiler is because that is the officially compiler supported to develop compatbile DLLs for **DIV Games Studio 2 'vanilla'**, the original published version on 1998 (other DIV Games Studio forks, no taking count of Fenix or Bennu forks, maybe support newer versions or other compilers).

> **Note**
> A previous attempt as a framework, a collection of individual DLLs, is available on the following repository: [DIV2 Framework](https://github.com/VisualStudioEX3/div2-framework).

# What is DIV Games Studio?

###### Wikipedia page: https://es.wikipedia.org/wiki/DIV_Games_Studio

Maybe was one of the first game engines for the public. **DIV Games Studio** is a complete solution to develop games for **MS-DOS** and published in 1997 (DIV1) and 1998 (DIV2). 

Is a full windows graphic environment with tools for creation and editing 2D graphics (with a complete drawing suit), particle FX, character animations, font character sets, sounds effects and a complete language programming with a syntax between **Pascal** and **C**, including an integrated debugger and a full complete documentation with a lot of tutorials and samples. 

This engine allow to develop common 2D games with a full of advanced graphic features, and pseudo 3D games using the [Mode7](https://en.wikipedia.org/wiki/Mode_7) and later, with DIV2, the Mode8 (3D feature like the original Doom).

**DIV Games Studio** was very popular at the end of ninetys and early 2000. Was the start point of an entire generation of game developers of nowdays. During the years, the community was develop a multiple forks like [Fenix Project](https://web.archive.org/web/20071012230137/http://fenix.divsite.net/) (with multiple flavours), [eDivc](https://github.com/vroman/edivc), CDiv, [Div GO](https://www.divgo.net/), [Gemix Studio](http://www.gemixstudio.com/), [Bennu GD](https://www.bennugd.org/), or [PixTudio](https://pixtudio.org/).

Currently exists 2 projects to bring it to live again:
* [Div DX / DIV Games Studio 3](https://github.com/DIVGAMES/DIV-Games-Studio) - A port of DIV Games Studio 2 to modern systems (running on Windows, Linux and Mac natively) but keeping the all original features of DIV Games Studio 2. One of the interested features, including the fix of most of the existing bugs on original DIV2, is the posibility of export the games natively to multiple systems, including Android, HTML5 and some consoles. This project has still in beta and seems to be abandoned since 2016.
* [DIV Games Studio 2.02](https://github.com/vii1/DIV) - A reconstruction and fixing of the original DIV Games Studio 2 (v 2.01) for MS-DOS. This is an active project today where the developers want to fix the multiple bugs in the language programming and engine, improve the tools, and, maybe in a future, create a version for Amiga OS.

**DIV Games Studio** if fully functional on [DOSBox](https://www.dosbox.com/). You can download **DIV Games Studio 2** ISO from [Archive.org](https://archive.org/details/div-games-studio-2) as abandoneware.

![DIV Games Studio 2 screenshots](https://github.com/VisualStudioEX3/VisualStudioEX3/blob/develop/Shared/Images/div_games_studio/div2_screen_mosaic.png)
