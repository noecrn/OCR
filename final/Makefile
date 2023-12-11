# Makefile principal
all:
	gcc -o main main.c
	$(MAKE) -C sources/image_transform 
	$(MAKE) -C sources/interface
	$(MAKE) -C sources/pre_process
	$(MAKE) -C sources/solver
	$(MAKE) -C sources/temp
	$(MAKE) -C sources/temp2
	$(MAKE) -C sources/temp3

.PHONY: clean

clean:
	rm -rf main.o
	rm -rf main
	$(MAKE) -C sources/image_transform clean
	$(MAKE) -C sources/interface clean
	$(MAKE) -C sources/pre_process clean
	$(MAKE) -C sources/solver clean
	$(MAKE) -C sources/temp clean
	$(MAKE) -C sources/temp2 clean
	$(MAKE) -C sources/temp3 clean
