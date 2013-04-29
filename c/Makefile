NAME=test.cpp
OUTPUT=out
BUILD=build
comp:
	-rm -r $(BUILD)
	-mkdir $(BUILD)
	g++ $(NAME) -o $(BUILD)/$(OUTPUT) `pkg-config --cflags opencv` `pkg-config --libs opencv`
run: $(BUILD)/$(OUTPUT)
	$(BUILD)/$(OUTPUT)
