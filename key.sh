# !/bin/bash
HOST4="mpi-sn04"
HOST5="mpi-sn05"

PORT="10022"
PASSWORD="1234"

ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa

# ssh-copy-id -i ~/.ssh/id_rsa.pub mpi-sn04 (same as below command)
expect << EOF
    spawn ssh-copy-id -p $PORT $HOST4
    expect {
        "yes/no" {
            send "yes\r"
            exp_continue
        }
        -nocase "password" {
            send "$PASSWORD\r"
            exp_continue
        }
        eof
    }
EOF

# ssh-copy-id -i ~/.ssh/id_rsa.pub mpi-sn05 (same as below command)
expect << EOF
    spawn ssh-copy-id -p $PORT $HOST5
    expect {
        "yes/no" {
            send "yes\r"
            exp_continue
        }
        -nocase "password" {
            send "$PASSWORD\r"
            exp_continue
        }
        eof
    }
EOF