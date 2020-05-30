# BUILD.md
---------------------------------------------------
## macOS 
###### Install meson
For using meson you need to do the following steps:
- brew install python3

###### Dependencies
Before continuing, assure that these packages are installed (via brew or macports):

- libjpeg
- sqlite3
- libmagic
- libexif

###### Building
the following command will build ospl:   
`meson . build && cd build && ninja`

## GNU/Linux

###### Install meson
For using meson you need to do the following steps:
- `sudo apt install python3 python3-pip python3-setuptools python3-wheel ninja-build`
- `pip3 install meson`
- add the bin folder showed after installation to your PATH

###### Dependencies
Before continuing, assure that these packages are installed:
- libjpeg-dev
- libsqlite3-dev
- libmagic-dev
- libexif-dev

###### Building
the following command will build ospl:   
`meson . build && cd build && ninja`

## Windows
Comming later