# CyclicAMIChannel

This repository contains the implementation of an OpenFOAM model for the case of flow old underground river with a roof supported by columns (inspired by a few running under Buenos Aires).

The case implements offset `cyclicAMI` patches to simulate only a portion of the tunnel, allowing to quickly reach steady-state conditions.

Using AMI means that the mesh doesn't need to match perfectly between patches, which makes things much simpler to set up. Creating perfectly matching patches is very difficult/impossible with some meshers.

Most flow variables, such as velocity and phase fraction, can be mapped directly between patches. However, as flow steadily goes downward, the p_rgh needs to have a discrete jump between both ends. To this end, the case includes a custom boundary condition called `p_rghJumpAMI` which introduces the correct offset based on the density of the fluid on each face.

It uses `interFoam` to solve the free surface, and URANS treatment to solve the turbulence, using the `kOmegaSST` model.


## Getting Started

* Compile the boundary condition running `wmake libso` on the appropiate folder.
* Run the `prepare.sh` to generate the mesh and set up the simulation.
* Then run the case with `interFoam`

## License

This project is licensed under the MIT License - see the LICENSE.md file for details

## Author

Nicolás Diego Badano (https://www.linkedin.com/in/nicolas-diego-badano/)
