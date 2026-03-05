#include "gravity.hpp"
#include <iostream>


#define WIDTH 800
#define HEIGHT 600

int main()
{
	
	gravity::Gravity app{WIDTH,HEIGHT, "Gravitation System Simulation"};

	try {
        app.run();
    }
    catch (const std::exception& e ){
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}
