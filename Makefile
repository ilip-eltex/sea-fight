TARGET=typetest
CC=gcc
DBG=-g
LD=-l

HEADERS += test \
		network


all: $(TARGET)
	

$(TARGET): main.o types.o 
	$(CC) $(DBG) build/$< -o $@

test_network: test_network.o netmanager.o types.o 
	$(CC) $(DBG) types.h network/netmanager.h build/$< -o $@

main.o: main.c types.h
	$(CC) -c $(DBG) $< -o build/$@

types.o: types.h
	$(CC) -c $(DBG) $< -o build/$@

test_network.o: test_net.c types.h
	$(CC) -c $(DBG)  $< -o build/$@
	
netmanager.o: network/netmanager.c network/netmanager.h  
	$(CC) -c $(DBG)  $< -o build/$@

build:
	mkdir build

clean:
	rm -rf build/
	rm $(TARGET)*

ignore:
	cat "$(TARGET)*" >>.gitignore
