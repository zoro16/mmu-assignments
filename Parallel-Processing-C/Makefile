EXECS=serial dual clust
MPICC?=mpicc 

all: ${EXECS}

serial: serial.c
	${MPICC} -o serial parameters.h serial.c -lm

dual: dual.c
	${MPICC} -o dual parameters.h dual.c -lm

clust: clust.c
	${MPICC} -o clust parameters.h clust.c -lm

clean:
	rm ${EXECS}
