# sandbox
Falling sand simulation game for Linux written in C.
Game uses SDL 2.0 development library for graphics.
Try out [https://sandboxels.r74n.com/](https://sandboxels.r74n.com/) and [https://artsology.com/sandspiel.php](https://artsology.com/sandspiel.php) browser games to familiarize with the concept of "Falling-sand Game".

### How to run the game
Firstly install necessary development packages using command:
```Bash
sudo apt-get install build-essential git make \
pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
libaudio-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev \
libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev fcitx-libs-dev \
libpipewire-0.3-dev libwayland-dev libdecor-0-dev
```

Then install SDL library and its dependencies by command:
```Bash
sudo apt-get install libsdl2-dev
```

Clone or download this repository. Build and run the game with GNU Make. Run these commands in command line:
```Bash
cd sandbox
make
./main
```

### For non-Linux users
If you have system other than Linux (Ubuntu 22.04 LTS) here are some useful links to help you launch the game:
- [https://github.com/libsdl-org/SDL/blob/main/docs/README.md](https://github.com/libsdl-org/SDL/blob/main/docs/README.md)
- [https://wiki.libsdl.org/SDL2/Installation](https://wiki.libsdl.org/SDL2/Installation)