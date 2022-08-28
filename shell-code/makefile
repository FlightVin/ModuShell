main: main.o prompt.o error_mes.o echo.o
	gcc -o main main.o prompt.o error_mes.o echo.o

main.o: headers.h main.c

prompt.o: prompt.c headers.h prompt.h

error_mes.o : error_mes.c error_mes.h headers.h

echo.o : echo.c echo.h headers.h

clean:
	rm main main.o error_mes.o prompt.o