# Learning OpenGL with C

### Requirements

- GLFW (built in libraries folder)
- glad (in location of source folder with main.c)
- CMake

#### Current Stage

- Create window
- Colour window
- Triangle

#### Next Steps

- Index buffers

#### To work on

- UI

###### Explanations

- Graphics pipeline
	- Takes data to convert into frame
	- Data is the vertex data array
		- Contains position, vertex, colour, coordinates
	- 1st stage: Vertex shader
		- Takes all verticies positions & transforms them (or keep them the exact same)
	- 2nd stage: Shape assembly
		- takes all positions and shapes them based on a primitive
			- a Primitive is: a shape e.g. triangle, point or line
	- 3rd stage: Geometry shader
		- can add verticies and create new primitives out of already existing primitives
	- 4th stage: Rasterisation
		- all mathematical shapes become pixels
	- 5th stage: Fragment shader
		- adds colours to pixels, lighting shadows
	- 6th stage: Tests and blending
		- belnding of transparent objects and colours

- Index buffer tells OpenGL the order in which it goes over the verticies e.g.
	- Zelda tri-force triangle
	-			2
	-		3		5
	-	 0		4		1
	- indices = [0,4,3
	-			 4,1,5
	-			 3,5,2]