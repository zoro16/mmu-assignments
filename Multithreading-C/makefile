EXECS= prime-openmp2 prime-pthread4
GCC?=gcc 

all: ${EXECS}

prime-pthread4: prime-pthread4.c
	${GCC} -o prime-pthread4 prime-pthread4.c -pthread

prime-openmp2: prime-openmp2.c
	${GCC} -o prime-openmp2 prime-openmp2.c -fopenmp

clean:
	rm ${EXECS}
