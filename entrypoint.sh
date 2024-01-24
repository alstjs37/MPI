#!/bin/bash

# 무한 루프를 실행하여 컨테이너가 종료되지 않도록 유지
while true; do
  sleep 1
done

# ssh service start
service ssh start
echo "Starting SSH server ... "

# 원하는 작업 또는 명령을 추가
echo "Container is running ..."