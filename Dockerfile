## Dockerfile for MPI communication in single & multi pod(node)

# 기본 이미지 설정
FROM ubuntu:22.04

# sudo 설치
RUN apt-get update && apt-get install sudo

# 환경변수에 추가
# apt 설치시 입력요청 무시
ARG DEBIAN_FRONTEND=noninteractive

# 패키지 설치
RUN apt-get update && apt-get install -y \
    cmake curl g++ gcc git wget vim htop dnsutils\
    build-essential expect \
    openmpi-bin libopenmpi-dev

# ssh 설치
RUN apt-get update && apt-get install -y \
    openssh-server openssh-client net-tools

# 이미지 크기를 줄이기 위해 캐시된 패키지 리스트 제거
RUN rm -rf /var/lib/apt/lists/*

#### 여기부터 SSH 
RUN mkdir /var/run/sshd

# root password 변경, $PASSWORD를 변경
RUN echo 'root:1234' | chpasswd

# ssh 설정 변경
# root 계정으로의 로그인을 허용한다. 아래 명령을 추가하지 않으면 root 계정으로 로그인이 불가능
RUN sed -ri 's/^#?PermitRootLogin\s+.*/PermitRootLogin yes/' /etc/ssh/sshd_config

# port 주석 해제 및 포트 10022로 변경
RUN sed -i 's/#Port 22/Port 10022/' /etc/ssh/sshd_config

# 응용 프로그램이 password 파일을 읽어 오는 대신 PAM이 직접 인증을 수행 하도록 하는 PAM 인증을 활성화
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

# RUN mkdir /home/mpiuser/.ssh
RUN mkdir /root/.ssh

EXPOSE 10022

CMD ["/usr/sbin/sshd", "-D", "/etc/ssh/sshd_config"]
####여기까지 SSH

# rdma를 위한 libibverbs-dev
# RUN apt-get -y install libibverbs-dev

# # mpisuer 계정 생성 및 sudo 권한 부여
# RUN adduser --disabled-password --gecos "" mpiuser  \
#     && echo 'mpiuser:mpiuser' | chpasswd \
#     && adduser mpiuser sudo \
#     && echo 'mpiuser ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

# # 이미지 내에서 사용할 디렉토리 생성 및 권한 부여
# WORKDIR /home/mpiuser
# RUN chown -R mpiuser:mpiuser /home/mpiuser

# # mpiuser 비밀번호 생성
# RUN echo 'mpiuser:1234' | chpasswd

# 이미지 내에서 일반 사용자로 전환
# USER mpiuser

RUN mkdir /root/mpiuser
WORKDIR /root/mpiuser

# MPI를 root 계정으로 실행할 때 --allow-run-as-root 옵션 없이도 실행 가능할 수 있도록
RUN echo 'export OMPI_ALLOW_RUN_AS_ROOT=1' >> ~/.bashrc
RUN echo 'export OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1' >> ~/.bashrc
# RUN source ~/.bashrc

# COPY
COPY . .

# 현재 directory를 working directory로 지정
WORKDIR .

# key.sh 실행파일로 변경
RUN chmod 755 /root/mpiuser/key.sh

# CMD
# 명령어 실행 후 죽는 걸 방지하기 위해
RUN sudo chmod 755 entrypoint.sh
ENTRYPOINT ["./entrypoint.sh"]