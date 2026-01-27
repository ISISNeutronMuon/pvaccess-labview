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

ADD --chmod=a+x https://download.ni.com/support/softlib/labview/labview_rt/2023Q1/LinuxToolchains/linux/oecore-x86_64-core2-64-toolchain-9.2.sh .
RUN ./oecore-x86_64-core2-64-toolchain-9.2.sh -y

ADD https://github.com/epics-base/epics-base.git#7.0 ${EPICS_BASE}
RUN make -C ${EPICS_BASE} -j $(nproc) && make -C ${EPICS_BASE} clean

ADD https://github.com/epics-base/pvxs.git#1.4.1 ${PVXS}
RUN echo 'EPICS_BASE=/epics/epics-base' > ${PVXS}/configure/RELEASE.local
RUN make -C ${PVXS} -j $(nproc) && make -C ${PVXS} clean

ADD https://git.yoctoproject.org/opkg-utils.git#0.7.0 /opkg-utils
RUN make -C /opkg-utils install-utils

WORKDIR ${EPICS_ROOT}

RUN --mount=source=CMakeLists.txt,target=CMakeLists.txt \
	--mount=source=src,target=src \
	--mount=source=nilrt,target=nilrt \
	nilrt/build-package

FROM scratch
COPY --from=build /epics/pvalabview_*.ipk /
