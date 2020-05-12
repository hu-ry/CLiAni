#include <iostream>

enum Effect{
	ScrollEffect = 1,
	ExpandEffect,
	JiggleEffect
};

class Pattern() {
public:
	Pattern() {
		readPattern();
	}


private:
	unsigned char* pattern_ptr;
	void readPattern() {

	}
}


class Engine() {
public:
	Engine(int gridSize, Pattern pattern_, Effect animEffect_)
	: basePattern(pattern_), animEffect(animEffect_)
	{
		if(initGrid(gridSize)) {
			std::cout << "Could not initialize grid!" << std::endl;
		}
	}

	void run(int delta) {
		
	
	
	}


private:
	Pattern basePattern;
	Effect animEffect;


	bool initGrid(int size) {
		if(size > 0) {
			return false;
		}
		
		
		
		return true;
	}
}
