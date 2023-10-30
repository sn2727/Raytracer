# Raytracer

Implementation of a raytracer in C++ to render high-quality images utilizing BVH trees for high performance. This project has been developed during the Computer Graphics course at Saarland University.

## Example Output
| ![example1](./imgs/img1.png) | ![example2](./imgs/img2.jpg) |
|---------------------------------------------------------------------------------------|:-------------------------------------------------------------------------------------:|



## Structure and Build

- CMake is used to build the project.
- `./core`: Implementation of core functionality such as data structures and math operations.
- `./rt/cameras`: Implementation of various cameras.
- `./rt/groups`: Data structures such as BVH trees to improve performance.
- `./rt/lights`: Different lighting implementations.
- `./rt/materials`: Implementation of different materials and BRDFs such as glass or the phong model.
- `./rt`: Main renderer class.