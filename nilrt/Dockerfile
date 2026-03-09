FROM ubuntu:24.04 AS build

ENV EPICS_ROOT=/epics
ENV EPICS_BASE=${EPICS_ROOT}/epics-base
ENV PVXS=${EPICS_ROOT}/pvxs

RUN apt-get update && \
	apt-get install -y --no-install-recommends \
	build-essential \
	ca-certificates \
	python3 \
	cmake \
	file \
	libevent-dev

# Install NILRT toolchain
ADD --chmod=a+x https://download.ni.com/support/softlib/labview/labview_rt/2023Q1/LinuxToolchains/linux/oecore-x86_64-core2-64-toolchain-9.2.sh .
RUN ./oecore-x86_64-core2-64-toolchain-9.2.sh -y

# Build EPICS Base
ARG EPICS_BASE_VERSION=7.0
ADD https://github.com/epics-base/epics-base.git#${EPICS_BASE_VERSION} ${EPICS_BASE}
COPY <<EOF ${EPICS_BASE}/configure/CONFIG_SITE.local
SHARED_LIBRARIES=NO
STATIC_BUILD=YES
EOF
RUN make -C ${EPICS_BASE} -j $(nproc) && make -C ${EPICS_BASE} clean

# Build PVXS
ARG PVXS_VERSION=1.5.1
ADD https://github.com/epics-base/pvxs.git#${PVXS_VERSION} ${PVXS}
COPY <<EOF ${PVXS}/configure/CONFIG_SITE.local
SHARED_LIBRARIES=NO
STATIC_BUILD=YES
EOF
COPY <<EOF ${PVXS}/configure/RELEASE.local
EPICS_BASE=${EPICS_BASE}
EOF
RUN make -C ${PVXS} -j $(nproc) && make -C ${PVXS} clean

WORKDIR ${EPICS_ROOT}

RUN --mount=source=CMakeLists.txt,target=CMakeLists.txt \
	--mount=source=CMakePresets.json,target=CMakePresets.json \
	--mount=source=cmake,target=cmake \
	--mount=source=src,target=src \
	cmake --preset=nilrt && cmake --build --preset=nilrt && cpack --preset=nilrt

FROM scratch
COPY --from=build /epics/build/nilrt/*.ipk /
