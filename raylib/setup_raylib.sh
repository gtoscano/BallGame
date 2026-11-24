#!/usr/bin/env bash
# Downloads and builds raylib 5.5 ONCE into games/raylib/external/raylib.
# Every game in this folder links against it. Run from anywhere:
#   bash setup_raylib.sh
set -e
cd "$(dirname "$0")"
mkdir -p external
if [ ! -d external/raylib ]; then
    git clone --depth 1 --branch 5.5 https://github.com/raysan5/raylib.git external/raylib
fi
make -C external/raylib/src PLATFORM=PLATFORM_DESKTOP -j4
echo "raylib ready: external/raylib/src/libraylib.a"
