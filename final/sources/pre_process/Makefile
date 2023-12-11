# Makefile

CC = gcc -D__NO_INLINE__
CPPFLAGS =
CFLAGS = -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS = 
LDLIBS = `pkg-config --libs sdl2 SDL2_image` -lm

SRC = main.c grayscale.c threshold.c cannyFilter.c operation.c adjust_gamma.c gaussian_blur.c contrast.c save.c median_blur.c read_image.c ../neural_network/init_NN.c ../neural_network/NN_fun.c ../neural_network/data_set_reader.c ../neural_network/digit_reco.c
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

all: main save read_image

save: grayscale.o threshold.o cannyFilter.o operation.o adjust_gamma.o gaussian_blur.o contrast.o median_blur.o
main: grayscale.o threshold.o cannyFilter.o operation.o adjust_gamma.o gaussian_blur.o contrast.o median_blur.o
read_image: read_image.o 


grayscale: grayscale.o
threshold: threshold.o operation.o
cannyFilter: cannyFilter.o
operation: operation.o
adjust_gamma: adjust_gamma.o
gaussian_blur: gaussian_blur.o
contrast: contrast.o
median_blur: median_blur.o
#neural_network: ../neural_network/init_NN.o ../neural_network/NN_fun.o ../neural_network/data_set_reader.o ../neural_network/digit_reco.o
read_image: read_image.o operation.o grayscale.o ../neural_network/init_NN.o ../neural_network/NN_fun.o ../neural_network/data_set_reader.o ../neural_network/digit_reco.o

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}
	${RM} result.png


# END

