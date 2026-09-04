# DragonWell

## Download with Singularity / Apptainer

Download the latest published container and replace any existing local copy:

```sh
singularity pull --force dragonwell.sif \
  docker://ghcr.io/t7phy/dragonwell:latest
```

For a reproducible run, download a specific release instead:

```sh
singularity pull dragonwell-v0.0.4alpha.sif \
  docker://ghcr.io/t7phy/dragonwell:v0.0.4alpha
```

Replace `singularity` with `apptainer` if that is the command installed on
your system.

## Run with Singularity / Apptainer

Open the container shell:

```sh
singularity run dragonwell.sif
```

To run `PDFFit_Minuit2`, change to the directory containing `Config.yml`,
`DataList.yml`, and `Parameters.yml`, then run:

```sh
singularity exec dragonwell.sif PDFFit_Minuit2
```

The current directory is normally bound automatically. If the run uses an
external LHAPDF installation, bind its data directory to `/lhapdf`:

```sh
singularity exec \
  --bind "$(lhapdf-config --datadir):/lhapdf" \
  dragonwell.sif \
  PDFFit_Minuit2
```

## Download and run with Docker

Download the latest published image:

```sh
docker pull ghcr.io/t7phy/dragonwell:latest
```

Open the container shell:

```sh
docker run --rm -it ghcr.io/t7phy/dragonwell:latest
```

Docker does not bind the current directory automatically. To run
`PDFFit_Minuit2`, change to the directory containing `Config.yml`,
`DataList.yml`, and `Parameters.yml`, then mount that directory as `/work`:

```sh
docker run --rm -it \
  --volume "$PWD:/work" \
  --workdir /work \
  ghcr.io/t7phy/dragonwell:latest \
  PDFFit_Minuit2
```

If the run uses an external LHAPDF installation, mount its data directory as
`/lhapdf` as well:

```sh
docker run --rm -it \
  --volume "$PWD:/work" \
  --volume "$(lhapdf-config --datadir):/lhapdf" \
  --workdir /work \
  ghcr.io/t7phy/dragonwell:latest \
  PDFFit_Minuit2
```
