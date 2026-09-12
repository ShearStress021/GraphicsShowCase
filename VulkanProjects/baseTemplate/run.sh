glslc --version


FILE="shaders/shader.frag.spv"


if [ -f "$FILE" ] ; then
	echo "Shaders created already"
	
else
	glslc shaders/shader.vert -o shaders/shader.vert.spv
	glslc shaders/shader.frag -o shaders/shader.frag.spv

fi



	

BUILD="build"


if [ -d "$BUILD" ] ; then
	cd build && make && cd ..
else
	mkdir build && cd build && cmake .. && make && cd ..
fi



./build/res


rm -rf shaders/shader.frag.spv
rm -rf shaders/shader.vert.spv
