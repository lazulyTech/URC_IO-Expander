Port = /dev/cu.usbserial-6DD2D0256D
Band = 1500000

all:
	pio -f -c vim run -t compiledb

upload:
	pio -f -c vim run --target upload

clean:
	pio -f -c vim run --target clean

program:
	pio -f -c vim run --target program

uploadfs:
	pio -f -c vim run --target uploadfs

update:
	pio -f -c vim update

compiledb:
	pio -t compiledb

monitor:
	pio device monitor -p ${Port} -b ${Band}

