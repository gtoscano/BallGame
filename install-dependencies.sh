#!/usr/bin/env bash
# install-dependencies.sh — installs everything needed to build all the games
# on Debian or Ubuntu, then builds raylib (which is not packaged).
#
#   bash install-dependencies.sh            # install everything
#   bash install-dependencies.sh --dry-run  # only show what would be done
#
# Run it as your normal user (not with sudo); it asks for sudo when needed.
set -euo pipefail
cd "$(dirname "$0")"

DRY_RUN=false
[[ "${1:-}" == "--dry-run" ]] && DRY_RUN=true

# ---------- the packages, grouped by framework ----------
BASIC=(build-essential pkg-config git)                 # g++, make, pkg-config, git
NCURSES=(libncurses-dev)                               # ncurses/
QT=(qt6-base-dev qt6-base-dev-tools qmake6)            # qt/      (qmake6 + moc)
IMGUI=(libimgui-dev libglfw3-dev)                      # imgui/   (ImGui + GLFW)
RAYLIB=(libgl-dev libx11-dev libxrandr-dev libxinerama-dev   # raylib/ (needed to
        libxcursor-dev libxi-dev libwayland-dev libxkbcommon-dev)  # build raylib)

run() {   # print a command, and run it unless --dry-run
    echo "+ $*"
    $DRY_RUN || "$@"
}

available() {   # is this package in the apt repositories?
    local info
    info=$(apt-cache policy "$1" 2>/dev/null)
    [[ "$info" =~ Candidate:\ [^\(] ]]     # "(none)" means not available
}

# ---------- checks ----------
if [[ $EUID -eq 0 ]]; then
    echo "Please run as your normal user (the script uses sudo when needed)."
    exit 1
fi
if ! command -v apt-get >/dev/null; then
    echo "This script is for Debian/Ubuntu (apt-get not found)."
    exit 1
fi

# ---------- 1. install packages ----------
echo "== Updating the package list"
run sudo apt-get update

TO_INSTALL=()
MISSING=()
for pkg in "${BASIC[@]}" "${NCURSES[@]}" "${QT[@]}" "${IMGUI[@]}" "${RAYLIB[@]}"; do
    if available "$pkg"; then TO_INSTALL+=("$pkg"); else MISSING+=("$pkg"); fi
done

echo "== Installing ${#TO_INSTALL[@]} packages"
run sudo apt-get install -y "${TO_INSTALL[@]}"

# ---------- 2. build raylib (not packaged in Debian/Ubuntu) ----------
echo "== Building raylib (raylib/setup_raylib.sh)"
run bash raylib/setup_raylib.sh

# ---------- 3. summary ----------
echo
echo "================ Summary ================"
if $DRY_RUN; then
    echo "(dry run: nothing was installed)"
else
    check() {   # name, command that must succeed
        if eval "$2" >/dev/null 2>&1; then printf '  %-10s OK\n' "$1"
        else                               printf '  %-10s NOT AVAILABLE\n' "$1"; fi
    }
    check "g++ C++20" "echo 'int main(){}' | g++ -std=c++20 -x c++ - -o /dev/null"
    check "ncurses"   "echo '#include <ncurses.h>
int main(){}' | g++ -x c++ - -lncurses -o /dev/null"
    check "raylib"    "test -f raylib/external/raylib/src/libraylib.a"
    check "Qt 6"      "command -v qmake6"
    check "ImGui"     "pkg-config --exists imgui glfw3"
fi
if (( ${#MISSING[@]} )); then
    echo
    echo "Not available on this Debian/Ubuntu version (skipped): ${MISSING[*]}"
    echo "The games that need them will not build; all the others will."
fi
echo
echo "Done. Try:  cd iostream/ball && make run"
