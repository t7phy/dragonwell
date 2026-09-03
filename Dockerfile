# syntax=docker/dockerfile:1.7

ARG ROOT_IMAGE=rootproject/root:6.30.06-ubuntu22.04@sha256:9d2a9dd6991dc3571eeb8a33b0eb313cfd785eb3303b14ce0170b09a44c2ecb7
ARG RUST_IMAGE=rust:1.80.1-bullseye@sha256:f6f599d3f027a97fb60cb87854199fcde390e25cee216712c3f9eede545b052e

FROM ${RUST_IMAGE} AS pineappl-build

SHELL ["/bin/bash", "-o", "pipefail", "-c"]
ARG PINEAPPL_VERSION=1.0.0
ARG CARGO_C_VERSION=0.9.32

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        ca-certificates \
        curl \
        libssl-dev \
        pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /tmp/build
RUN cargo install cargo-c --version "${CARGO_C_VERSION}" --locked \
    && curl -fsSL "https://codeload.github.com/NNPDF/pineappl/tar.gz/refs/tags/v${PINEAPPL_VERSION}" -o pineappl.tar.gz \
    && echo "fc06d88318a0029071e15370a5a62f8e7749f801c97d7fbec63cb1b99f4d4f0f  pineappl.tar.gz" | sha256sum -c - \
    && tar -xzf pineappl.tar.gz \
    && cd "pineappl-${PINEAPPL_VERSION}" \
    && cargo cinstall --release --locked --package pineappl_capi --prefix=/opt/pineappl \
    && pkg-config --define-prefix --validate /opt/pineappl/lib/pkgconfig/pineappl_capi.pc

FROM ${ROOT_IMAGE} AS dependencies

USER root
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

ARG BUILD_JOBS=4
ARG LHAPDF_VERSION=6.5.6
ARG HOPPET_VERSION=1.2.0
ARG APPLGRID_VERSION=1.5.46
ARG FASTNLO_VERSION=2.3.1pre-2411
ARG YAML_CPP_VERSION=0.8.0
ARG APFEL_VERSION=3.1.1
ARG APFELGRID_VERSION=1.0.1
ARG APFELXX_VERSION=4.8.1
ARG BAT_VERSION=1.0.0

ENV DRAGONWELL_DEPS=/opt/dragonwell-deps \
    PATH=/opt/dragonwell-deps/bin:/opt/root/bin:${PATH} \
    LD_LIBRARY_PATH=/opt/dragonwell-deps/lib:/opt/dragonwell-deps/lib64:/opt/root/lib \
    CMAKE_PREFIX_PATH=/opt/dragonwell-deps:/opt/root \
    PKG_CONFIG_PATH=/opt/dragonwell-deps/lib/pkgconfig:/opt/dragonwell-deps/lib64/pkgconfig \
    LHAPDF_ROOT_DIR=/opt/dragonwell-deps \
    Hoppet_ROOT_DIR=/opt/dragonwell-deps \
    APPLGRID_ROOT_DIR=/opt/dragonwell-deps \
    FASTNLO_ROOT_DIR=/opt/dragonwell-deps \
    YAML_ROOT_DIR=/opt/dragonwell-deps \
    APFEL_ROOT_DIR=/opt/dragonwell-deps \
    apfelxx_ROOT_DIR=/opt/dragonwell-deps \
    BAT_ROOT_DIR=/opt/dragonwell-deps

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        autoconf \
        automake \
        build-essential \
        ca-certificates \
        curl \
        gfortran \
        git \
        libboost-all-dev \
        libeigen3-dev \
        libgsl-dev \
        libtool \
        pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /tmp/build

RUN curl -fsSL "https://github.com/jbeder/yaml-cpp/archive/refs/tags/${YAML_CPP_VERSION}.tar.gz" -o yaml-cpp.tar.gz \
    && echo "fbe74bbdcee21d656715688706da3c8becfd946d92cd44705cc6098bb23b3a16  yaml-cpp.tar.gz" | sha256sum -c - \
    && tar -xzf yaml-cpp.tar.gz \
    && cmake -S "yaml-cpp-${YAML_CPP_VERSION}" -B yaml-cpp-build \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX="${DRAGONWELL_DEPS}" \
        -DBUILD_SHARED_LIBS=ON \
        -DYAML_CPP_BUILD_CONTRIB=OFF \
        -DYAML_CPP_BUILD_TESTS=OFF \
        -DYAML_CPP_BUILD_TOOLS=OFF \
    && cmake --build yaml-cpp-build --parallel "${BUILD_JOBS}" \
    && cmake --install yaml-cpp-build \
    && rm -rf yaml-cpp.tar.gz "yaml-cpp-${YAML_CPP_VERSION}" yaml-cpp-build

RUN curl -fsSL "https://lhapdf.hepforge.org/downloads/?f=LHAPDF-${LHAPDF_VERSION}.tar.gz" -o lhapdf.tar.gz \
    && echo "6b8b7e38dc26a977a24f5a321215b7054c14a4469d04134d70cb93a860eeeea7  lhapdf.tar.gz" | sha256sum -c - \
    && tar -xzf lhapdf.tar.gz \
    && cd "LHAPDF-${LHAPDF_VERSION}" \
    && ./configure --prefix="${DRAGONWELL_DEPS}" --disable-python \
    && make -j"${BUILD_JOBS}" \
    && make install \
    && sed -i 's/    --includedir)/    --incdir|--includedir)/' "${DRAGONWELL_DEPS}/bin/lhapdf-config" \
    && test "$("${DRAGONWELL_DEPS}/bin/lhapdf-config" --incdir)" = "${DRAGONWELL_DEPS}/include" \
    && cd /tmp/build \
    && rm -rf lhapdf.tar.gz "LHAPDF-${LHAPDF_VERSION}"

RUN curl -fsSL "https://hoppet.hepforge.org/downloads/hoppet-${HOPPET_VERSION}.tgz" -o hoppet.tar.gz \
    && echo "bffd1bbfd3cc8d1470ded5c82fe33346d44e86cf426439eb77ab7702f319e448  hoppet.tar.gz" | sha256sum -c - \
    && tar -xzf hoppet.tar.gz \
    && cd "hoppet-${HOPPET_VERSION}" \
    && ./configure --prefix="${DRAGONWELL_DEPS}" \
    && make -j"${BUILD_JOBS}" \
    && make install \
    && cd /tmp/build \
    && rm -rf hoppet.tar.gz "hoppet-${HOPPET_VERSION}"

# APFELgrid consumes APPLgrid's internal igrid API, which APPLgrid does not install.
COPY MainCode-master/src/MCFMPatch/ApplGrid/ /tmp/applgrid-patch/
RUN curl -fsSL "https://applgrid.hepforge.org/downloads/applgrid-${APPLGRID_VERSION}.tgz" -o applgrid.tar.gz \
    && echo "166171623d859c42a75aa9659d780a7a22091b9fd936fb3035b1230b73dedaac  applgrid.tar.gz" | sha256sum -c - \
    && tar -xzf applgrid.tar.gz \
    && cp -a /tmp/applgrid-patch/. "applgrid-${APPLGRID_VERSION}/" \
    && cd "applgrid-${APPLGRID_VERSION}" \
    && autoreconf --force --install \
    && ./configure --prefix="${DRAGONWELL_DEPS}" \
    && make -j"${BUILD_JOBS}" \
    && make install \
    && cp -a src/*.h "${DRAGONWELL_DEPS}/include/appl_grid/" \
    && mkdir -p "${DRAGONWELL_DEPS}/share/applgrid" \
    && cp -a share/. "${DRAGONWELL_DEPS}/share/applgrid/" \
    && cd /tmp/build \
    && rm -rf applgrid.tar.gz "applgrid-${APPLGRID_VERSION}" /tmp/applgrid-patch

FROM dependencies AS fastnlo-dependency

COPY MainCode-master/src/MCFMPatch/FastNLO/ /tmp/fastnlo-patch/
RUN curl -fsSL "https://fastnlo.hepforge.org/code/v23/fastnlo_toolkit-${FASTNLO_VERSION}.tar.gz" -o fastnlo.tar.gz \
    && echo "cbe2cbf5785690e23e964fb9922895acda1210565e481657be23d62bc699a93a  fastnlo.tar.gz" | sha256sum -c - \
    && tar -xzf fastnlo.tar.gz \
    && cp -a /tmp/fastnlo-patch/. "fastnlo_toolkit-${FASTNLO_VERSION}/" \
    && cd "fastnlo_toolkit-${FASTNLO_VERSION}" \
    && LIBS="$(lhapdf-config --libs)" ./configure --prefix="${DRAGONWELL_DEPS}" \
    && make -j"${BUILD_JOBS}" \
    && make install \
    && cd /tmp/build \
    && rm -rf fastnlo.tar.gz "fastnlo_toolkit-${FASTNLO_VERSION}" /tmp/fastnlo-patch

FROM fastnlo-dependency AS full-dependencies

COPY --from=pineappl-build /opt/pineappl/ /opt/dragonwell-deps/

COPY MainCode-master/src/MCFMPatch/apfel/ /tmp/apfel-patch/
RUN curl -fsSL "https://codeload.github.com/scarrazza/apfel/tar.gz/refs/tags/${APFEL_VERSION}" -o apfel.tar.gz \
    && echo "9006b2a9544e504e8f6b5047f665054151870c3c3a4a05db3d4fb46f21908d4b  apfel.tar.gz" | sha256sum -c - \
    && tar -xzf apfel.tar.gz \
    && cp -a /tmp/apfel-patch/. "apfel-${APFEL_VERSION}/" \
    && cmake -S "apfel-${APFEL_VERSION}" -B apfel-build \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX="${DRAGONWELL_DEPS}" \
        -DAPFEL_ENABLE_PYTHON=OFF \
        -DAPFEL_ENABLE_TESTS=OFF \
        -DAPFEL_DOWNLOAD_PDFS=OFF \
    && cmake --build apfel-build --parallel "${BUILD_JOBS}" \
    && cmake --install apfel-build \
    && rm -rf apfel.tar.gz "apfel-${APFEL_VERSION}" apfel-build /tmp/apfel-patch

RUN curl -fsSL "https://codeload.github.com/nhartland/APFELgrid/tar.gz/refs/tags/v${APFELGRID_VERSION}" -o apfelgrid.tar.gz \
    && echo "67c580af6d0fa45a9a1bc6674725a3c534474f5eae650903931bca688bf0edc4  apfelgrid.tar.gz" | sha256sum -c - \
    && tar -xzf apfelgrid.tar.gz \
    && cd "APFELgrid-${APFELGRID_VERSION}" \
    && autoreconf --force --install \
    && ./configure --prefix="${DRAGONWELL_DEPS}" --with-apfel="${DRAGONWELL_DEPS}" \
    && make -j"${BUILD_JOBS}" \
    && make install \
    && cd /tmp/build \
    && rm -rf apfelgrid.tar.gz "APFELgrid-${APFELGRID_VERSION}"

RUN curl -fsSL "https://codeload.github.com/vbertone/apfelxx/tar.gz/refs/tags/${APFELXX_VERSION}" -o apfelxx.tar.gz \
    && echo "68ee531fc61f488bbdf65ea974093da4c5f821f02a88fa1a453aa34220418616  apfelxx.tar.gz" | sha256sum -c - \
    && tar -xzf apfelxx.tar.gz \
    && cmake -S "apfelxx-${APFELXX_VERSION}" -B apfelxx-build \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX="${DRAGONWELL_DEPS}" \
    && cmake --build apfelxx-build --target apfelxx --parallel "${BUILD_JOBS}" \
    && cmake --install apfelxx-build \
    && rm -rf apfelxx.tar.gz "apfelxx-${APFELXX_VERSION}" apfelxx-build

# BAT 1.0.0 uses a string helper removed after older ROOT releases.
RUN curl -fsSL "https://codeload.github.com/bat/bat/tar.gz/refs/tags/v${BAT_VERSION}" -o bat.tar.gz \
    && echo "184ff58f16fa35e73a4c48c9b218c2d8daac0a387e3400e8b2f995beb18f3b66  bat.tar.gz" | sha256sum -c - \
    && tar -xzf bat.tar.gz \
    && cd "bat-${BAT_VERSION}" \
    && sed -i \
        -e '/using ROOT::Math::Util::ToString;/d' \
        -e 's/ToString(i)/std::to_string(i)/g' \
        -e 's/ROOT::Math::Util::ToString/std::to_string/g' \
        src/BCIntegrate.cxx src/BCParameterSet.cxx \
    && autoreconf --force --install \
    && ./configure --prefix="${DRAGONWELL_DEPS}" \
    && make -j"${BUILD_JOBS}" \
    && make install \
    && cd /tmp/build \
    && rm -rf bat.tar.gz "bat-${BAT_VERSION}"

RUN sed -i 's|/opt/pineappl|/opt/dragonwell-deps|g' \
        "${DRAGONWELL_DEPS}/lib/pkgconfig/pineappl_capi.pc" \
    && pkg-config --validate pineappl_capi \
    && test -d "$(pkg-config --variable=includedir pineappl_capi)"

FROM full-dependencies AS dragonwell-build

ARG BUILD_JOBS=4
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        nlohmann-json3-dev \
    && rm -rf /var/lib/apt/lists/*

COPY MainCode-master/ /tmp/dragonwell-source/

RUN cmake -S /tmp/dragonwell-source -B /tmp/dragonwell-build \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/opt/dragonwell \
    && for feature in USE_LHAPDF USE_TMVA USE_ROOFIT USE_APPLGRID USE_BAT USE_HOPPET USE_FNLO USE_MINUIT2 USE_YAML USE_APFEL USE_PINEAPPL; do \
        grep -q "^${feature}:BOOL=ON$" /tmp/dragonwell-build/CMakeCache.txt; \
       done \
    && cmake --build /tmp/dragonwell-build --parallel "${BUILD_JOBS}" \
    && cmake --install /tmp/dragonwell-build

FROM dragonwell-build AS runtime

LABEL org.opencontainers.image.source="https://github.com/t7phy/dragonwell" \
      org.opencontainers.image.title="DragonWell" \
      org.opencontainers.image.description="DragonWell PDF fitting tools and their scientific dependencies"

ENV PATH=/opt/dragonwell/bin:${PATH} \
    LD_LIBRARY_PATH=/opt/dragonwell/lib:${LD_LIBRARY_PATH} \
    LHAPDF_PDF_DIR=/lhapdf

RUN ldconfig \
    && for executable in \
        PDFFit_Minuit2 \
        PDFFit_BAT \
        PineAPPLConvolute \
        ApplConvolute \
        FastNLOConvolute; do \
        executable_path="$(command -v "${executable}")"; \
        test -x "${executable_path}"; \
        ! ldd "${executable_path}" | grep -q 'not found'; \
       done

WORKDIR /work
CMD ["/bin/bash"]
