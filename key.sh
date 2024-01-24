# !/bin/bash
HOST="mpi-sn04"
PASSWORD="1234"

ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa

expect << EOF
    spawn ssh-copy-id $HOST
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

# ssh-copy-id -i ~/.ssh/id_rsa.pub mpi-sn04