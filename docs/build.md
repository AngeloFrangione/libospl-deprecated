# Building
In order to build the source, you will have to download it. You can do so using git 
```shell
git clone https://github.com/AngeloFrangione/libospl.git
```
## macOS 
You will need to install [meson](https://mesonbuild.com/Quick-guide.html)
```shell
brew install python3
pip3 install meson ninja
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
You will need to install [meson](https://mesonbuild.com/Quick-guide.html)
```shell
sudo apt install python3 python3-pip python3-setuptools python3-wheel ninja-build cmake pkg-config lcov
pip3 install meson ninja
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
## Windows
Coming later

## Running tests
After building ospl you can run the tests to ensure everything is working correctly. To do so, make sure you are in the build folder and then run this command:
```shell
meson compile empty_files
ninja test
```