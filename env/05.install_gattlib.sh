# cmake 설치
echo
echo -e $RED apt-get update$RESET
echo
sudo apt update
echo
echo
echo "sudo apt install cmake"
echo
sudo apt -y install cmake
# gattlib 빌드
echo "gattlib build"
echo "download lib from git - git clone https://github.com/labapart/gattlib.git"
echo
git clone https://github.com/labapart/gattlib.git
echo
echo "Change directory to gattlib - gattlib top - cd gattlib"
cd gattlib
echo
echo "build using cmake----"
echo "mkdir buile and cd build"
echo
mkdir build && cd build
echo "execute cmake - cmake -DGATTLIB_BUILD_DOCS=OFF .."
cmake -DGATTLIB_BUILD_DOCS=OFF ..
echo
echo "build using make and install : make && sudo make install"
echo
make && sudo make install
echo " configure dynamic linker run-time bindings : ldconfig"
sudo ldconfig
echo
