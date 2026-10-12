# SpellChessArena

SpellChessArena is a Qt-based desktop application and the dedicated GUI for [icecream](https://github.com/Pawwz85/icecream), the SpellChess engine. It provides a graphical workspace for viewing, editing, analysing, and playing SpellChess games.

## Features
- **Engine games:** play SpellChess against a human, a configured engine or setup a game between 2 engines
- **Live analysis:** continuously analize the current board or document position with a selected engine while you browse or edit it.
- **Game and document annotation:** analyze an existing game or document once, using fixed-depth or fixed-time analysis, and copy the resulting PGN or PGN4 to the clipboard.
- **Principal variations and evaluation tools:** add panels for principal variations, engine logs, engine controls, and the evaluation thermometer from the Views menu.
- Import games from chess.com by pasting PGN4.

## Application usage

### Configure engines

1. Open **Settings → Manage engines**.
2. Add an engine executable. The application probes it through UCI before accepting it.
3. In the engine list, use the available actions to edit or remove an engine, or move it up and down to reorder the configured list.

Engine entries are persisted through Qt application settings, so they remain available the next time the application starts. The picker targets executable files; on Windows, this generally means selecting an `.exe` file. Engines must support the expected UCI protocol, including responding to the initial `uci` probe with `uciok`. SpellChess-compatible engines, particularly [icecream](https://github.com/Pawwz85/icecream), are recommended.

### Start an engine game

1. Open **Game → New game**.
2. For White and Black, choose **Human** or **Engine**. When using an engine player, select one of the engines configured above.
3. Configure each side's time control. You can use infinite time or a simple clock with an initial time, increment, and margin.
4. Set optional engine limits: move time, nodes searched, and maximum depth. You can also enable pondering so the engine thinks during the opponent's turn.
5. Set the starting FEN if the game should begin from a position other than the default, and optionally select a `.spell` opening book.
6. Accept the dialog to start the game.

### Enable live analysis

First configure at least one engine. Then open **Settings → Select live analysis engine** and choose the engine to use. Live analysis is continuous: it follows the current board or document position as you navigate through moves or change the position, rather than annotating the whole document once. The engine's output can be viewed by adding analysis-related panels from **Views**, such as **Principal Variations**, **Engine Logs**, **Engine Control Panel**, or **Eval Thermomether**.

### Annotate a game or document

1. Open a document or import one with **Game → Load PGN4**. A position can also be loaded with **Game → Load FEN**.
2. Choose **Game → Analise game** (the menu keeps this existing spelling).
3. Select the configured engine and choose either fixed-depth analysis or fixed-time analysis per position.
4. Optionally enable recursive analysis to include variations as well as the main line.
5. Accept the configuration and wait for the progress indicator to finish.
6. Use **Game → Copy PGN** or **Game → Copy PGN4** to copy the annotated document to the clipboard. The appropriate action is selected for the current document type.

This one-time document annotation workflow is separate from live analysis. PGN and PGN4 clipboard export is the verified way to retain or share the annotated result; no separate document-save workflow is assumed.

PGN4 is the chess.com's game/document format used for importing SpellChess games, while application specific FEN string extension is used to load a starting position into a new document. Optional analysis panels can be added or rearranged from the **Views** menu when more detailed engine output is needed.

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

### Packaging a Windows release

The project uses CPack to produce a ZIP archive and a Windows Installer (`.msi`).
On Windows, configure with a Visual Studio generator and build the `PACKAGE`
target, or run CPack directly after building:

```text
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
cpack --config build/CPackConfig.cmake -C Release -G WIX
```

The Windows application uses the statically linked MSVC runtime (`/MT`) and
the generated installer includes Qt's deployed runtime files and the bundled
assets. The GitHub Actions release workflow runs this packaging step for tags
matching `vMAJOR.MINOR.PATCH` and publishes the Windows `.msi` installer and ZIP archive,
as well as a Linux `.tar.gz` binary package.

The Linux package can be generated locally with:

```text
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
cpack --config build/CPackConfig.cmake -C Release -G TGZ
```

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
