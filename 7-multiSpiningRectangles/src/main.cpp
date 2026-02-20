#include "triangle.hpp"
#include <iostream>


#define WIDTH 800
#define HEIGHT 600

int main()
{
	
	triangle::Triangle app{WIDTH,HEIGHT, "My Triangle"};

	try {
        app.run();
    }
    catch (const std::exception& e ){
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}
