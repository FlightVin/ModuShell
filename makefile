objects = main.o headers.o cmd.o prompt.o error_mes.o path.o echo.o cd.o pwd.o back_process.o ls.o fore_process.o pinfo.o dll.o history.o

main: $(objects)
	gcc -o main $(objects)

main.o: headers.h main.c 

prompt.o: prompt.c prompt.h headers.h

error_mes.o : error_mes.c error_mes.h headers.h

path.o : path.c path.h headers.h

echo.o : echo.c echo.h headers.h

cd.o : cd.c cd.h headers.h

cmd.o : cmd.c cmd.h headers.h

pwd.o : pwd.c pwd.h headers.h

back_process.o : back_process.c back_process.h headers.h

headers.o : headers.c headers.h

ls.o : ls.c ls.h headers.h

fore_process.o : fore_process.c fore_process.h headers.h

pinfo.o : pinfo.c pinfo.h headers.h

dll.o : dll.c dll.h headers.h

history.o : history.c history.h headers.h

clean:
	rm main $(objects) .history_storage_file
