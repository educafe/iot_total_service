RED="\e[31m"
RESET="\e[0m"
echo "This is BlueZ package Installation"
echo "BlueZ package is required for bluetooth development on Linux"
echo
echo
echo -e $RED apt-get update$RESET
echo
sudo apt update
echo
#install required library for bluez installation
echo
echo -e $RED" 1) Install libglib2.0-dev"$RESET
echo 
sudo apt -y install libglib2.0-dev
echo
echo -e $RED" 2) Install libdbus-1-dev"$RESET
echo
sudo apt -y install libdbus-1-dev
echo
echo -e $RED" 3) Install libudev-dev"$RESET
echo
sudo apt -y install libudev-dev
echo
echo -e $RED" 4) Install libical-dev"$RESET
echo
sudo apt -y install libical-dev
echo
echo -e $RED" 5) Install libreadline-dev"$RESET
echo
sudo apt -y install libreadline-dev
echo
#bluez download
echo
echo -e $RED"3) Download and Install Bluez-5.54"$RESET
echo
cd ~/Downloads
wget http://www.kernel.org/pub/linux/bluetooth/bluez-5.54.tar.xz
# to get latest bluez, visit http://www.bluez.org/ and get link of selected version of bluez
tar -xJvf bluez-5.54.tar.xz
cd bluez-5.54
# install bluez 
./configure
make 
sudo make install
cd ~/

# ./configure 명령어를 실행할 시 에러가 발생하는 경우
# apt-cache search libglib 명령어를 수행하면 관련 패키지를 보여준다. 
# apt-cache showpkg libglib2.0 -> 버전이 2.5x를 보여주므로 조건을 만족한다.