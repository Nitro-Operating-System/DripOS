# DripOS
[![][discord_image]][discord_link]

An OS made for fun.
NOTE: This is based off of this tutorial: https://github.com/cfenollosa/os-tutorial

## Usage:

### Linux:

#### With Make

Install **build-essential** and **QEMU** for your distribution

Run
```
make
make run
```

#### Without Make
Install QEMU for your distribution and download image file from the [latest release][release_link]

Run
```
qemu-system-i386 -soundhw pcspk -device isa-debug-exit,iobase=0xf4,iosize=0x04 -fda os-image.bin
```

### Windows:

Download and install qemu from [weilnetz][qemu_link]

And execute **os-image.bin** by opening cmd.exe and running
```
cd "\Program Files\qemu"
qemu-system-i386.exe -m 256 -soundhw pcspk -device isa-debug-exit,iobase=0xf4,iosize=0x04 -fda /path/to/Downloads/DripOS-master/DripOS/os-image.bin
```

[discord_image]:https://img.shields.io/badge/discord-DripOS-738bd7.svg?style=square
[discord_link]:https://discord.gg/E9ZXZWn
[qemu_link]:https://qemu.weilnetz.de/w64/qemu-w64-setup-20180815.exe
[release_link]:https://github.com/Menotdan/DripOS/releases
