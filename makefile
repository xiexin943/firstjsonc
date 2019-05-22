check:check.o jsonc.o formatjson.o dictlist.o symboljson.o
	gcc -o check -g check.o jsonc.o formatjson.o dictlist.o symboljson.o 
check.o:formatjson.h dictlist.h symboljson.h
clean:
	-rm -rf *.o
	cp -afb ./* /beifen
