# C++20 Games for Students — Starting Point

**First time on a new computer (Debian/Ubuntu):**
```bash
bash install-dependencies.sh            # installs everything and builds raylib
bash install-dependencies.sh --dry-run  # only shows what it would do
```

Every folder is named after the **library** it uses, and each one contains the
same starter program: `ball/`. Pick a framework, copy its `ball/` folder, and
grow it into your own game.

```
.
├── iostream/ball/   only the C++ standard library (cin / cout), turn-based
├── ncurses/ball/    real-time game in the terminal (works over SSH)
├── raylib/ball/     graphics window, we write the game loop
├── qt/ball/         graphics window, Qt runs the loop (event-driven)
└── imgui/ball/      graphics window + live GUI controls (Dear ImGui)
```

## `ball/`: the base for your new game
One short `main.cpp`: a ball in the middle and a bar. Arrow keys move the ball;
past the edge it disappears. Each file ends with **TRY THIS** exercises using `for` loops.

| Folder            | Build & run                         | First time only                                   |
|-------------------|-------------------------------------|---------------------------------------------------|
| `iostream/ball/`  | `make run` (w/a/s/d + Enter)        | nothing                                           |
| `ncurses/ball/`   | `make run`                          | `sudo apt install libncurses-dev`                 |
| `raylib/ball/`    | `make run`                          | `bash raylib/setup_raylib.sh` (builds raylib into `raylib/external/`) |
| `qt/ball/`        | `qmake6 && make && ./ball`          | `sudo apt install qt6-base-dev qt6-base-dev-tools qmake6` |
| `imgui/ball/`     | `make run`                          | `sudo apt install libimgui-dev libglfw3-dev`      |

`install-dependencies.sh` already does all of the "first time only" steps.

## Starting your own game
```bash
cp -r raylib/ball raylib/my-game   # use the framework you chose
cd raylib/my-game
make run
```
Then change `main.cpp` step by step, following the game loop:
**input -> update -> draw** (in `qt/` Qt calls you instead: `keyPressEvent`,
`timerEvent`, `paintEvent`).

Which framework?
- `iostream/` — simplest; turn-based games (guessing, cards, board games).
- `ncurses/` — real-time in the terminal; works over SSH.
- `raylib/` — graphics window, you write the loop (needs a desktop, not plain SSH).
- `qt/` — event-driven Qt 6 Widgets window (needs a desktop or `ssh -X`).
- `imgui/` — like raylib plus sliders/buttons to tweak your game live (needs a desktop).

Slides: `slides/games-frameworks-slides.html` (or `.pdf`).
