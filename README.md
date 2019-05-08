[![Build Status](https://travis-ci.org/BoeingX/distributed-ray-tracing.svg?branch=master)](https://travis-ci.org/BoeingX/distributed-ray-tracing)

This project implements the [Phong reflection model](https://en.wikipedia.org/wiki/Phong_reflection_model) for
[ray tracing](https://en.wikipedia.org/wiki/Ray_tracing_%28graphics%29)

# Get started

Compile the project with `GNU Make`

```bash
make
```

and launch the executable with

```bash
./main
```

# Limitation

- Only spheres are supported
- [Open MPI](https://www.open-mpi.org/) suport is (temporarily) removed
- Microsoft Windows not tested
