server:
	g++ src/server/socket.cpp src/server/object.cpp server.cpp -o server

client:
	g++ src/client/socket.cpp client.cpp -o client