# !/bin/bash
sudo g++ -o /root/mpiuser/k8s/check_info.out /root/mpiuser/k8s/check_info.cpp

sudo /root/mpiuser/k8s/check_info.out

source /root/mpiuser/key.sh

echo "[SUCCESS] SSH KEY GENERATED && COPY TO OTHER PODS"