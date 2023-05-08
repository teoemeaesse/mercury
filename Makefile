CC = g++
LINK = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -DGL_GLEXT_PROTOTYPES
CFLAGS = -g -c $(LINK)

SOURCEDIR = src
BUILDDIR = build
PROTOSOURCEDIR = proto

EXECUTABLE = mercury
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: dir protoc $(EXECUTABLE)

dir:
	mkdir -p $(BUILDDIR)

protoc:
	protoc -I=$(PROTOSOURCEDIR) --cpp_out=$(SOURCEDIR) $(PROTOSOURCEDIR)/simulation.proto

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@ $(LINK)

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BUILDDIR)/*o $(EXECUTABLE) log.txt $(SOURCEDIR)/simulation.pb.cc $(SOURCEDIR)/simulation.pb.h
