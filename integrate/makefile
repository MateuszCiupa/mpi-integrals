MPICC?=mpicc
MPIRUN?=mpirun
EXECS=integrate

Begin?=0
End?=2
NumPoints?=10000

Defaults=integrate.o
RunFlags=-n 4
RunParams=$(Begin) $(End) $(NumPoints)

all: main clean run

main group imain: $(Defaults)
	$(MPICC) -o $(EXECS) $@.c $(Defaults)

run:
	$(MPIRUN) ${RunFlags} ./$(EXECS) $(RunParams)

clean:
	rm -f $(EXECS)
	rm -f *.o

%.o: %.c %.h
	$(MPICC) -c $< -o $@
