MPICC?=mpicc
MPIRUN?=mpirun
EXECS=integrate

begin?=0
end?=2
points?=10000
proc?=4

Defaults=integrate.o

RunParams=$(begin) $(end) $(points)

all: main clean run

main group imain: $(Defaults)
	$(MPICC) -o $(EXECS) $@.c $(Defaults)

run:
	$(MPIRUN) -n $(proc) ./$(EXECS) $(RunParams)

clean:
	rm -f *.o

%.o: %.c %.h
	$(MPICC) -c $< -o $@
