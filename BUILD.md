# BUILD.md
---------------------------------------------------
## macOS 
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
###### Dependencies
Before continuing, assure that these packages are installed:
- libjpeg-dev
- libsqlite3-dev
- libmagic-dev
- libexif-dev

###### Building
You need to install meson as described [here](https://mesonbuild.com/Quick-guide.html)
you will need the following packages:
- python3-pip3
- python3
- pkg-config
- cmake

the following command will build ospl:
`meson . build && cd build && ninja`

## Windows
Comming later
