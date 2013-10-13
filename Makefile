CXX = g++
CFLAGS = `root-config --cflags`
LFLAGS = `root-config --glibs`

TARGET = Buffon.exe

all: $(TARGET)

Buffon.exe : BN.o Dict.o Application.o
	$(CXX) -o $@ $^ $(LFLAGS) 

%.o: %.cxx
	$(CXX) $(CFLAGS) -c $<

Dict.cxx : BN.h
	@rootcint -f $@ -c $^

clean:
	@rm *.o *.d Buffon.exe Dict.h Dict.cxx
