#include <iostream>


int main(){
	int cubeTris [12][3]{
		{0,3,2}, {0,2,1},
			{1,2,6}, {1,6,5},
			{5,6,7}, {5,7,4},
			{4,7,3}, {4,3,0},
			{3,7,6}, {3,6,2},
			{5,4,0}, {5,0,1}

	};

	for (auto &t : cubeTris){
		std::cout << t[0] << '\n';
	}
	return 0;
}
