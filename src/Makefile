CFLAGS = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -DGL_GLEXT_PROTOTYPES

make:
	g++ -g -c main.cpp $(CFLAGS)
	g++ main.o -g -o main camera.cpp window.cpp shader.cpp utils.cpp exceptions.cpp $(CFLAGS)

clean:
	rm *.o main log.txt
