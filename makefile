all: vmsim vmgen vmstats

vmsim: vmsim.c
	gcc -o vmsim vmsim.c

vmgen: vmgen.c
	gcc -o vmgen vmgen.c

vmstats: vmstats.c
	gcc -o vmstats vmstats.c

clean:
	rm -f vmsim vmgen vmstats vmrates.dat vmrefs.dat

