## stl30_simple
This project contains the **minimizing** set of SGI STL 3.0 version.  
  
The original source code can be downloaded from [https://www.sgi.com/tech/stl/download.html](https://www.sgi.com/tech/stl/download.html)
  
I prefer the 3.0 version since this version is simple but enough to show the  
spirit of C++ STL. Also I did some extra simplification as below to make it more readable.

* remove the nonstandard STL header files, e.g. `vector.h` will be excluded.
* remove the nonreached code according to compile switch definition in `stl_config.h`.
* use the morden directory structure to organize code.
* use the cmake to build the code.

