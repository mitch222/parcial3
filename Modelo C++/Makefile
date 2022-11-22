#/*************
#* Fecha: 22 noviembre 2022
#* Autor: Mitchell Bermin
#*********************/

GCC = g++

all: final

final: main.o extractiondata.o linearregression.o
	@echo "linking and producing the final application"
	$(GCC) main.o extractiondata.o linearregression.o -o final
	
main.o: main.cpp
	@echo "Compiling the main file"
	$(GCC) -c main.cpp

extractiondata.o: extractiondata.cpp
	@echo "Compiling the extractiondata file"
	$(GCC) -c extractiondata.cpp
	
linearregression.o: linearregression.cpp
	@echo "Compiling the linearregression file"
	$(GCC) -c linearregression.cpp

	
clean:
	@echo "Cleaning objects"
	rm *.o final 
