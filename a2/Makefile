SRC = extractTemps.c
EXEC = extractTemps
CFLAGS = -Wall

main: $(SRC)
	gcc $(SRC) -o $(EXEC) $(CFLAGS) -O3

debug:
	gcc $(SRC) -o $(EXEC) $(CFLAGS) -DDEBUG 

plot: main
	./extractTemps sensordata.txt temps.dat
	gnuplot tempPlot

plotwin: main
	./extractTemps.exe sensordata.txt temps.dat
	gnuplot tempPlotWin

plotmac: plot
	qlmanage -p graph.png

clean:
	rm $(EXEC)
	rm *.png
	rm temps.dat