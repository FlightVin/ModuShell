main: main.o prompt.o error_mes.o path.o echo.o cd.o
	gcc -o main main.o prompt.o error_mes.o path.o echo.o cd.o

main.o: headers.h main.c

prompt.o: prompt.c headers.h prompt.h

error_mes.o : error_mes.c error_mes.h headers.h

path.o : path.c path.h headers.h

echo.o : echo.c echo.h headers.h

cd.o : cd.c cd.h cd.h

clean:
	rm main main.o error_mes.o prompt.o path.o echo.o cd.o