# Building
In order to build the source, you will have to download it. You can do so using git 
```shell
git clone https://github.com/AngeloFrangione/libospl.git
```
## macOS 
You will need to install [meson](https://mesonbuild.com/Quick-guide.html)
```shell
brew install python3
pip3 install meson==0.56.2 ninja
```
You will need to install the following dependencies (via brew or macports):
```shell
brew install libjpeg sqlite3 libmagic libexif
```
The following command will build ospl:
```shell
meson . build
cd build
ninja
```
## GNU/Linux
You will need to install [meson version 0.56.3](https://mesonbuild.com/Quick-guide.html)
```shell
sudo apt install python3 python3-pip python3-setuptools python3-wheel cmake pkg-config lcov
pip3 install meson==0.56.2 ninja
#Add the bin folder showed after installation to your PATH
```
You will need to install the following dependencies
```shell
sudo apt install libjpeg-dev libsqlite3-dev libmagic-dev libexif-dev
```
The following command will build ospl:
```shell
meson . build
cd build
ninja
```
## Windows crosscompilation with Mingw-w64
follow the install instructions from GNU/Linux.
additionally you will need to install `mingw-w64`
```shell
sudo apt install mingw-w64 mingw-w64-tools 
```
The following commands will cross build ospl:
```
meson . winbuild --cross-file cross_file.txt
cd winbuild
ninja
```
after the build process completed you need to copy the dlls from the individual subprojects and put them in the build folder in order to run ospl.exe

note: you need to run ospl.exe in an admin shell in order to create the thumbnails. This bug will be adressed in future versions of ospl.

## Running tests
After building ospl you can run the tests to ensure everything is working correctly. To do so, make sure you are in the build folder and then run this command:
```shell
meson compile empty_files
ninja test
```