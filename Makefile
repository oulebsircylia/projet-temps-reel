# définition des variables utilise pour la compilation
CXX= g++
SOURCE2= fractal.thread.cpp
SOURCE=fractal_julia.cpp
EXEC= julia
EXEC2=thread 
SUP=rm -rf
CXXFLAGS=-lopencv_core -lopencv_highgui -lopencv_imgproc -std=c++11 -lpthread
all:	

	$(CXX) -Wall $(SOURCE) -o $(EXEC) $(CXXFLAGS)
	./julia
compile:
	$(CXX) -Wall $(SOURCE2) -o $(EXEC2) $(CXXFLAGS)

	./thread

mrproper:clean
	$(SUP) *.o
clean:
	 $(SUP) *.o


#mrproper: clean        
	#$(SUP) julia
