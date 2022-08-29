objects = main.o headers.o cmd.o prompt.o error_mes.o path.o echo.o cd.o pwd.o back_process.o

main: $(objects)
	gcc -o main $(objects)

main.o: headers.h main.c

prompt.o: prompt.c prompt.h

error_mes.o : error_mes.c error_mes.h

path.o : path.c path.h

echo.o : echo.c echo.h

cd.o : cd.c cd.h

cmd.o : cmd.c cmd.h

pwd.o : pwd.c pwd.h

back_process.o : back_process.c back_process.h

headers.o : headers.c headers.h

clean:
	rm main $(objects)
