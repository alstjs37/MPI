## Dockerfile for MPI communication in single pod(node)

# 기본 이미지 설정
FROM ubuntu:22.04

# 일반 사용자를 추가하고 권한 부여
# RUN useradd -m -s /bin/bash mpiuser

# sudo 설치
RUN apt-get update && apt-get install sudo

# mpisuer 계정 생성 및 sudo 권한 부여
RUN adduser --disabled-password --gecos "" mpiuser  \
    && echo 'mpiuser:mpiuser' | chpasswd \
    && adduser mpiuser sudo \
    && echo 'mpiuser ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

# 사용자에게 sudo 권한 부여
# RUN usermod -aG sudo mpiuser

# 이미지 내에서 사용할 디렉토리 생성 및 권한 부여
WORKDIR /home/mpiuser
RUN chown -R mpiuser:mpiuser /home/mpiuser

# 환경변수에 추가
# apt 설치시 입력요청 무시
ARG DEBIAN_FRONTEND=noninteractive

# 패키지 설치
RUN apt-get update && apt-get install -y \
    cmake curl g++ gcc git wget vim htop dnsutils\
    build-essential \
    openmpi-bin libopenmpi-dev

# 이미지 크기를 줄이기 위해 캐시된 패키지 리스트 제거
RUN rm -rf /var/lib/apt/lists/*

# rdma를 위한 libibverbs-dev
RUN apt-get -y install libibverbs-dev

# 이미지 내에서 일반 사용자로 전환
USER mpiuser

# COPY
COPY . .

# 현재 directory를 working directory로 지정
WORKDIR .

# RUN
# RUN cd build
# RUN cmake .
# RUN make

# CMD
# 명령어 실행 후 죽는 걸 방지하기 위해
CMD ["sleep", "infinity"]