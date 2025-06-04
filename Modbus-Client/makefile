all : client-modbus-example client-modbus-example-simple

client-modbus-example : client-modbus-example.c api-modbus-dobot.h
	gcc -I . -I /usr/local/include/modbus -o client-modbus-example client-modbus-example.c -lmodbus

client-modbus-example-simple : client-modbus-example-simple.c  api-modbus-dobot.h
	gcc -I . -I /usr/local/include/modbus -o client-modbus-example-simple client-modbus-example-simple.c -lmodbus
