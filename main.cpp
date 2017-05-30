#include <cstdlib>

#include "render.h"
#include <cstdio>

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("command usage: ./exe filename\n");
		exit(0);
	}
 
	render renderer;
	camera cam;
	
	renderer.readInput(argv[1], cam);
	
	renderer.initImg();
	
	renderer.renderImage(cam);
	
	return 0;	
}
