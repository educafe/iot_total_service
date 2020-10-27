from bluetooth.ble import DiscoveryService

service = DiscoveryService()
devices = service.discover(2)

dev= devices.items();
print dev

for address, name in devices.items():
    print("name: {}, address: {}".format(name, address))


# It requires to install gattlib. In order to install gattlib, 
# all dependent libraries must be installed first
# $ sudo apt-get install libboost-all-dev
# And then $ sudo pip install gattlib