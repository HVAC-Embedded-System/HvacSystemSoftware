from bluetooth import *



portnum = 3
server_socket=BluetoothSocket( RFCOMM )
server_socket.bind(("", portnum))
server_socket.settimeout(20)

while portnum > 2:					#upper number not inclusive
	
	server_socket.listen(1)

	print "Listening..."

	client_socket, address = server_socket.accept()

	print address
	print bluetooth.lookup_name(address)
	
	data = client_socket.recv(2048)

	print "received [%s]" % data
	

client_socket.close()
server_socket.close()
