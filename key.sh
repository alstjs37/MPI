# !/bin/bash
ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa

ssh-copy-id -i ~/.ssh/id_rsa.pub mpi-sn04.mpi-service.mpi-mslee