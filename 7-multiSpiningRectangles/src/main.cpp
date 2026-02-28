#include "rectangle.hpp"
#include <iostream>


#define WIDTH 800
#define HEIGHT 600

int main()
{
	
	rectangle::Rectangle app{WIDTH,HEIGHT, "My Rectangle"};

	try {
        app.run();
    }
    catch (const std::exception& e ){
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}
