NAME=test.cpp
OUTPUT=out

comp:
	g++ $(NAME) -o $(OUTPUT) `pkg-config --cflags --libs opencv`
run: $(OUTPUT)
	./$(OUTPUT)
# %.run: %.cpp
# 	g++ $< -o $@ `pkg-config --cflags --libs opencv`
