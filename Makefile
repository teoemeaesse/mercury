CC = g++
LINK = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -DGL_GLEXT_PROTOTYPES
SUBDIRS = $(shell find $(SOURCEDIR) -type d)
INCLUDES = $(addprefix -I, $(SUBDIRS))
CFLAGS = -g -c $(LINK) $(INCLUDES)

SOURCEDIR = src
BUILDDIR = build
PROTOSOURCEDIR = proto

EXECUTABLE = mercury
SOURCES = $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: dir protoc $(EXECUTABLE)

dir:
	mkdir -p $(BUILDDIR)
	for dir in $(shell find $(SOURCEDIR) -type d); do mkdir -p $(BUILDDIR)/$\${dir#$(SOURCEDIR)/}; done


protoc:
	protoc -I=$(PROTOSOURCEDIR) --cpp_out=$(SOURCEDIR)/persistency $(PROTOSOURCEDIR)/simulation.proto

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@ $(LINK)

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BUILDDIR)/*o $(EXECUTABLE) log.txt $(SOURCEDIR)/persistency/simulation.pb.cc $(SOURCEDIR)/persistency/simulation.pb.h
