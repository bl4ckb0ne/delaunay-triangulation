# delaunay-triangulation

## Pseudo-code algorithm

```
subroutine triangulate
input : vertex list
output : triangle list
   initialize the triangle list
   determine the supertriangle
   add supertriangle vertices to the end of the vertex list
   add the supertriangle to the triangle list
   for each sample point in the vertex list
      initialize the edge buffer
      for each triangle currently in the triangle list
         calculate the triangle circumcircle center and radius
         if the point lies in the triangle circumcircle then
            add the three triangle edges to the edge buffer
            remove the triangle from the triangle list
         endif
      endfor
      delete all doubly specified edges from the edge buffer
         this leaves the edges of the enclosing polygon only
      add to the triangle list all triangles formed between the point 
         and the edges of the enclosing polygon
   endfor
   remove any triangles from the triangle list that use the supertriangle vertices
   remove the supertriangle vertices from the vertex list
end
```
  
## Sample  
  
![alt text](https://github.com/Bl4ckb0ne/delaunay-triangulation/blob/pointers/sample.png "Is you can't see this, there's normaly an image here")  
  

From the [Wikipedia page of the algorithm](https://en.wikipedia.org/wiki/Bowyer%E2%80%93Watson_algorithm)  
  
## Requirement  
  
You'll need [SFML 2](http://www.sfml-dev.org/download/sfml/2.3.2/) at least to run the example, and C++11 to compiles it.

## Usage

To build it, just do a simple
```sh
make
```
You can change the compiler on the makefile (the CXX var)
```sh
make CXX=g++ 		# to use the GCC compiler
make CXX=clang++ 	# default compiler
```

The executable's name is ``` delaunay ```, with no arguments
```sh
./delaunay
```

And finally
```sh
make clean
```
To clear the executable and the build dear.
