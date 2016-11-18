CXX=g++-5

all:
	@mkdir -p build/
	@cmake -DCMAKE_CXX_COMPILER=${CXX} -B./build/ -H.
	@make -C build/
	@cp build/quadris .

clean:
	@rm -rf build/
	@rm -f quadris

.PHONY: all clean debug