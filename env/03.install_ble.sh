RED="\e[31m"
RESET="\e[0m"
echo
echo -e $RED apt-get update$RESET
echo
sudo apt update
echo
echo
echo -e $RED apt-get update$RESET
echo
sudo apt update
echo
echo -e $RED"0) Install libbluetooth-dev"$RESET
echo
sudo apt-get -y install libbluetooth-dev
# download and install pexpect and python library for bluetooth && LE
echo
echo -e $RED"1) Install pexpect"$RESET
echo
sudo pip install pexpect
# install pybluz for python 
echo
echo -e $RED"2) Install pybluez"$RESET
echo
sudo pip install pybluez
# install gattlib including dependent package
echo
echo -e $RED"3) Install libboost-all-dev and gattlib"$RESET
echo
sudo apt-get -y install libboost-all-dev
sudo pip install gattlib
# install bluepy for bluepy.btle module
echo
echo -e $RED"4) Install bluepy"$RESET
echo
sudo pip install bluepy
