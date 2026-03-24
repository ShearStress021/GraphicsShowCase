#include "renderer.hpp"
#include "window.hpp"
#include <iostream>


#define WIDTH 800
#define HEIGHT 600

int main()
{
    
    cube::Window window{WIDTH, HEIGHT, "My Cube"};

	cube::Cube app{window};

	try {
        app.run();
    }
    catch (const std::exception& e ){
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}
