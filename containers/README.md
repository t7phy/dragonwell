# DragonWell container

The image targets DragonWell's complete default-enabled feature set on Linux
x86-64. It uses ROOT 6.30.06 on Ubuntu 22.04 and builds the remaining HEP
dependencies from pinned source archives.

Build from the repository root:

```sh
docker build --progress=plain -t dragonwell:dev .
```

Run from a directory containing `Config.yml`, `DataList.yml`, and
`Parameters.yml`:

```sh
docker run --rm -it -v "$PWD:/work" -w /work dragonwell:dev PDFFit_Minuit2
```

The equivalent Apptainer/Singularity invocation can run `PDFFit_Minuit2`
directly from the current directory, which is bound automatically. Dataset and
interpolation grid paths remain controlled by `DataList.yml`; they are not
stored in the image. External paths that are not already visible inside the
container must be bound explicitly. LHAPDF data sets are likewise expected to
be supplied at runtime by binding their host directory and setting
`LHAPDF_DATA_PATH`.

Tagged builds are published to GitHub Container Registry as
`ghcr.io/t7phy/dragonwell:<tag>`. See the repository's top-level README for the
exact Singularity/Apptainer pull and execution commands.

All features that default to enabled in DragonWell's top-level CMake project
are enabled in this image, including APFEL/APFELgrid/APFEL++, BAT, and
PineAPPL. Features that default to disabled remain disabled.
