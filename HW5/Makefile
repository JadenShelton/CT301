NETID=jshel02
#Used for naming your tar file
ASN=HW5
#Used for naming the executable
SOURCES=HW5.cpp Image.cpp Pixel.cpp PPMGenerator.cpp
#List any files you need to make for source files
HEADERS=Image.h Pixel.h PPMGenerator.h
#List any Header files
OBJECTS=HW5.o Image.o Pixel.o PPMGenerator.o
#List any Object files you need to create for your assignment
TARNAME=$(NETID)_$(ASN).tar

RM=rm
#Change to del if on a windows machine
#Used to create a standard tar file naming convention

#Required Content Do not Modify below this line
CXXFLAGS=-Wall -Werror -Wfatal-errors -O2

%.o: %.cpp
		g++ -c -g $(CXXFLAGS) $<

$(ASN): $(OBJECTS)
		g++ $(CXXFLAGS) -o $(ASN) $(OBJECTS)

tar:
		tar -cf $(TARNAME) $(SOURCES) $(HEADERS) Makefile

clean:
		$(RM) -f $(TARNAME) $(ASN) $(OBJECTS) *.gch *.gcov a.out
