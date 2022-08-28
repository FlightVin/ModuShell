objects = main.o cmd.o prompt.o error_mes.o path.o echo.o cd.o pwd.o

main: $(objects)
	gcc -o main $(objects)

main.o: headers.h main.c

prompt.o: prompt.c headers.h prompt.h

error_mes.o : error_mes.c error_mes.h headers.h

path.o : path.c path.h headers.h

echo.o : echo.c echo.h headers.h

cd.o : cd.c cd.h cd.h

cmd.o : cmd.c cmd.h headers.h

pwd.o : pwd.c pwd.h headers.h

clean:
	rm main $(objects)