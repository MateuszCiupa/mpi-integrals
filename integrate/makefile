MPICC?=mpicc
MPIRUN?=mpirun
EXECS=integrate

Defaults=integrate.o
RunFlags=-n 4
RunParams=0 2 1000000

all: main clean run

main group non_block: ${Defaults}
	${MPICC} -o ${EXECS} $@.c ${Defaults}

run:
	${MPIRUN} ${RunFlags} ./${EXECS} ${RunParams}

clean:
	rm *.o

%.o: %.c %.h
	${MPICC} -c $< -o $@
