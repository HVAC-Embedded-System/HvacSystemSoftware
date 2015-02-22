import bluetooth
import sys
import select

#Device class contains all the information needed to talk to a device
class Device:
    def __init__(self, target_name, target_address, target_port, target_capabilities):
        self.name = target_name
        self.address = target_address
        self.port = target_port
        self.capabilities = target_capabilities
        self.socket = None

    def set_socket(self, sockfd):
        self.socket = sockfd

    def close_socket(self):
        self.socket.close()
        self.socket = None

devices = list()
#lists used for select call
rlist = list()
wlist = list()
xlist = list()

config = open('.config', 'r+')

for line in config:
    port = 3
    target_name, target_address, operations = line.split('|')
    print "Connecting to", target_name, " ", target_address
    operations = operations.split('&')
    
    new_device = Device(target_name, target_address, port, operations)
    devices.append(new_device)
    port = port + 1

config.close()

for device in devices:

    nearby_devices = bluetooth.discover_devices()

    for bdaddr in nearby_devices:

        try:
            print bluetooth.lookup_name( bdaddr )
        except:
            print "couldn't print the name"

        if device.name == bluetooth.lookup_name( bdaddr ):
            if device.address == bdaddr:
            
                print "Connecting"
                sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
                sock.connect((device.address, device.port))
                #wlist for now. will change in the future once we know what will be happening first
                wlist.append(sock)
                device.set_socket(sock)

                break

    if device.address is not None:
        print "found target bluetooth device with address ", device.address
    else:
        print "could not find target bluetooth device nearby"

#rlist.append(sys.stdin)    
#instead of adding stdin, we are having the user input come from another device so that select can be used properly

lists = select.select(rlist, wlist, xlist)

list1 = lists[0]
list2 = lists[1]
list3 = lists[2]

fd = list2.pop(0)

if fd is None:
    print "None ready to read"
else:
    fd.send("Hello")
    fd.close()



