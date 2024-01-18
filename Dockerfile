# 기본 이미지 설정
FROM ubuntu:20.04

# 일반 사용자를 추가하고 권한 부여
RUN useradd -m mpiuser

# 이미지 내에서 사용할 디렉토리 생성 및 권한 부여
WORKDIR /home/mpiuser
RUN chown -R mpiuser:mpiuser /home/mpiuser

# 이미지 내에서 일반 사용자로 전환
USER mpiuser

# 환경변수에 추가
# apt 설치시 입력요청 무시
ARG DEBIAN_FRONTEND=noninteractive

# 패키지 설치
RUN apt-get update && apt-get install -y \
    build-essential \
    openmpi-bin \
    libopenmpi-dev

# cmake를 위한 g++
# rdma를 위한 libibverbs-dev
RUN apt-get -y install g++ cmake git libibverbs-dev

# COPY
COPY . .

# 현재 directory를 working directory로 지정
WORKDIR .

# RUN
RUN cd build
RUN cmake .
RUN make

# CMD
# 명령어 실행 후 죽는 걸 방지하기 위해
CMD ["sleep", "infinity"]

# RUN apt-get --yes -qq update \
#  && apt-get --yes -qq upgrade \
#  && apt-get --yes -qq install \
#                       bzip2 \
#                       cmake \
#                       cpio \
#                       curl \
#                       g++ \
#                       gcc \
#                       gfortran \
#                       git \
#                       gosu \
#                       libblas-dev \
#                       liblapack-dev \
#                       libopenmpi-dev \
#                       openmpi-bin \
#                       python3-dev \
#                       python3-pip \
#                       virtualenv \
#                       wget \
#                       zlib1g-dev \
#                       vim       \
#                       htop      \