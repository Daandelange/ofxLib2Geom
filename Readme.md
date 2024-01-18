
# ofxLib2Geom

An OpenFrameworks wrapper for [lib2geom](https://gitlab.com/inkscape/lib2geom/), the vector engine used in Inkscape.  
It provides a set of algoritms for computing 2D vector data.

Warning! Requires C++17 (lower lib2geom versions provide down to C++11 compatibility, but there have been API changes)

Note about lib2geom : While many features are implemented, `lib2geom` is moving away from their previous geometry lib `Livarot`, some features of Inkscape remain in that library until they are moved. Also, Inkscape still has some code parts left in its own code base, only partly using `lib2geom`. Path offsetting and boolean operations are sadly in that case.

## Early State
I was looking for boolean operations and path offsetting, which are not well integrated into this lib yet. I'm leaving this addon as is, as it provides a lot of other useful algebra.

Only tested on `Linux` + `C++17` + `OF0.11.2`, using makefiles or qt-creator, should not be hard to compile on Mac + Win as long as you're using C++17.

## Setup
Check the lib2geom dependencies, you can find them in their [readme](https://gitlab.com/inkscape/lib2geom/-/blob/master/README.md).

### Install dependencies on linux
`apt install libdouble-conversion-dev`  
`apt-get install libgtest-dev`

Alternative: Install with package manager `apt install lib2geom-dev` (installs old v1.1, on 01-2024)  
Note : currently needed on Linux to link, but could be build within the OF project too. 


### Compile library
`cd /path/to/lib2geom`
`mkdir build && cd build`
`cmake .. -D2GEOM_TESTING=OFF`
`make` or `make dist`

### Configure your project
If you're using OF 0.11.2 or below; configure your project to use C++17 or 20.  
In your project's `config.make`: `PROJECT_CFLAGS = -std=c++17`

## Coding with lib2geom

### Docs
Their doxygen docs are a bit old and need to be compile manually, but there's a [nice manual](https://gitlab.com/inkscape/lib2geom/-/tree/master/doc/manual2) that explains some base principles and a [wiki FAQ](https://wiki.inkscape.org/wiki/Working_with_2Geom_FAQ) with some tips.

### Logics
There's no glue yet so you'll have to find out how to use lib2geom. Good luck ! The example shows how to setup a `Path`, apply an offset and display the result.

Here are some tips :
- `Geom::Coord` : a double, a 1D coordinate.
- `Geom::Point` : a 2D coordinate. X and Y are mostly accessible trough `pnt[0]`.
- `Geom::Path` : A polyline structure, like OF's `ofPolyLine`.
- `Geom::Linear` : An abstraction to wrap a segment into a "time" accessible manner.
- `Geom::D2<SBasis>` : An abstraction of a shape, used to perform advanced algorithmic operations. _Warning: lib2geom is moving away from this type, to be obsoleted._
- `Geom::Piecewise<D2<SBasis>>` : A cleaned and rewinded shape abstraction.

- - - -

## License
ofxLib2Geom is MIT.  
lib2geom is [LGPL 2.1](https://gitlab.com/inkscape/lib2geom/-/blob/master/COPYING-LGPL-2.1) + [MPL 1.1](https://gitlab.com/inkscape/lib2geom/-/blob/master/COPYING-MPL-1.1).

## Credits
Made by Daan de Lange.  
Powered by lib2Geom from the Inkscape team.
.
