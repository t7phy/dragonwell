# DragonWell

DragonWell is a PDF-fitting code built around ROOT and a collection of HEP
libraries. This repository includes a reproducible Linux x86-64 container that
builds the complete set of features enabled by DragonWell's default CMake
configuration, including APFEL, APFELgrid, APFEL++, BAT, and PineAPPL.

The run cards (`Config.yml`, `DataList.yml`, and `Parameters.yml`) and external
datasets are runtime inputs; they are not baked into the image.

## Published container

Pushing a Git tag whose name begins with `v` publishes the corresponding OCI
image to GitHub Container Registry. For example, tag `v0.0.1alpha` publishes:

```text
ghcr.io/t7phy/dragonwell:v0.0.1alpha
```

The workflow accepts tags only when the tagged commit is part of `main`. It
publishes Linux x86-64 images and deliberately does not give prereleases the
ambiguous `latest` tag.

After the first workflow run, verify that the package visibility is **Public**
under the package settings on GitHub. Public GHCR images can be pulled without
registry credentials.

## Singularity / Apptainer on HPC

Pull the OCI image and convert it to SIF:

```sh
singularity pull dragonwell-v0.0.1alpha.sif \
  docker://ghcr.io/t7phy/dragonwell:v0.0.1alpha
```

Run it from a directory containing the three run cards:

```sh
singularity exec \
  dragonwell-v0.0.1alpha.sif \
  PDFFit_Minuit2
```

Replace `singularity` with `apptainer` when that is the command installed on
the cluster. Singularity/Apptainer bind the current directory by default, so no
explicit working-directory bind is needed. Bind only external paths that the
cluster does not already expose inside containers. For example, to supply an
LHAPDF data directory:

```sh
singularity exec \
  --bind /path/on/host/lhapdf:/lhapdf \
  --env LHAPDF_DATA_PATH=/lhapdf \
  dragonwell-v0.0.1alpha.sif \
  PDFFit_Minuit2
```

## Local Docker build

Build from the repository root:

```sh
docker build --progress=plain --tag dragonwell:dev .
```

Run from a directory containing the three run cards:

```sh
docker run --rm -it \
  --volume "$PWD:/work" \
  --workdir /work \
  dragonwell:dev \
  PDFFit_Minuit2
```

See [`containers/README.md`](containers/README.md) for dependency and runtime
details.
