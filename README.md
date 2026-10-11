# SpellChessArena

SpellChessArena is a Qt-based desktop application and the dedicated GUI for [icecream](https://github.com/Pawwz85/icecream), the SpellChess engine. It provides a graphical workspace for viewing, editing, analysing, and playing SpellChess games.

## Features
- Play spell chess against engine
- Import games from chess.com by pasting PGN4
- Game review
- Live engine analisis
- Analysis tools including principal variations and eval bar

## Requirements

- Windows, Linux, or another platform supported by Qt 6 and the configured C++ toolchain.
- A C++17-compatible compiler.
- CMake 3.28 or newer.
- Qt 6 with the following components:
  - Core
  - Widgets
  - Gui
  - Concurrent
- Git and network access during configuration, because CMake downloads [SpellChessLib](https://github.com/Pawwz85/SpellChessLib) version `v1.0.0` through `FetchContent`.

The application is configured as a Windows GUI executable on Windows, so no console window is created for the installed application.

## Building

From the repository root, configure and build with CMake:

```text
cmake -S . -B build
cmake --build build --config Release
```

The executable is generated in the configuration-specific build directory. On a multi-configuration generator such as Visual Studio, it is typically located at:

```text
build/Release/SpellChessArena.exe
```

To install the application and its assets into a chosen directory:

```text
cmake --install build --config Release --prefix install
```

The install tree contains the `SpellChessArena` executable and the bundled `assets/` directory.

### Qt discovery

If CMake cannot find Qt 6 automatically, provide the Qt installation path when configuring. For example, with a Qt installation that contains `lib/cmake/Qt6`:

```text
cmake -S . -B build -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/msvc2022_64"
```

Replace the path with the Qt kit and compiler used on the local machine.

## Running

After building, launch the generated `SpellChessArena` executable. The application starts with an empty SpellChess document and opens the main window.

Engine analysis requires a compatible UCI engine configuration. The GUI is intended to be used with the SpellChess engine ecosystem, especially [icecream](https://github.com/Pawwz85/icecream).

## Tests

The repository contains GoogleTest-based tests for core MVC and observer functionality under `tests/`. The test subdirectory is currently not enabled by the top-level CMake configuration. To enable and run them, uncomment the `add_subdirectory(tests)` line in the root `CMakeLists.txt`, ensure GoogleTest is available to CMake, then configure and build the `UnitTests` target.

## Repository layout

- `src/` — application startup and top-level dialogs/windows.
- `BoardGrid/` — board model, rendering, interaction, and piece sprites.
- `BoardViewer/` — document viewing, game sessions, move lists, spells, and board validation.
- `EngineTools/` — engine controls, logging, evaluation, and principal variations.
- `SpellButton/` — spell counters and spell-bar widgets.
- `SpriteSet/` — sprite-set loading and scheme management.
- `Misc/` — shared application utilities and configuration.
- `assets/` — bundled chess-piece and spell artwork.
- `tests/` — unit tests for core components.

## Asset attribution and licensing

Third-party artwork attribution is documented in [assets/spells/ATTRIBUTION.md](assets/spells/ATTRIBUTION.md). In particular, the spell icons are adapted from [Game-icons.net](https://game-icons.net/) under [CC BY 3.0](https://creativecommons.org/licenses/by/3.0/), and the fantasy chess pieces are sourced from [Lichess](https://github.com/lichess-org/lila/tree/master/public/piece/fantasy) and associated with the [MIT license](https://github.com/maurimo/chess-art/blob/main/LICENSE).

Check the licenses of all dependencies before redistributing a build.

## Related projects

- [icecream](https://github.com/Pawwz85/icecream) — the SpellChess engine this GUI is dedicated to.
- [SpellChessLib](https://github.com/Pawwz85/SpellChessLib) — the library fetched and linked by this project.
