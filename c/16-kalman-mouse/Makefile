NAME=DisplayImage.cpp
OUTPUT=out
comp:
	g++ $(NAME) -o $(OUTPUT) `pkg-config --cflags opencv` `pkg-config --libs opencv`
run: $(OUTPUT)
	./$(OUTPUT)
