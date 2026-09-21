target ?= 'main.cpp'



res: $(target)
	g++ $< -o $@


run: clean res
	./res.exe


clean:
	del res*


.PHONY: clean res run
