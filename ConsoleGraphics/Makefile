target ?= 'main.cpp'



res: $(target)
	g++ $< -o $@


run: clean res
	./res


clean:
	del res*


.PHONY: clean res run
