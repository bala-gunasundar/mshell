BINS = cp rm mkdir

all : ${BINS}

% : %.o
	${CC} $< -o $@

%.o : %.c
	${CC} -c $<

dist-clean:
	rm -rf *~

clean:
	rm -rf ${BINS}
