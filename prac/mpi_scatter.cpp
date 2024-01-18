#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    int myrank, num_of_proccess;
    int send_msg[3], recv_buf;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_of_proccess);

    for(int i = 0; i < num_of_proccess; i++) send_msg[i] = i+1;

    // MPI_Scatter(송신 버퍼의 주소, 각 프로세스로 보내지는 원소 개수, 송신버퍼 데이터 타입, 수신 버퍼 주소, 수신 버퍼 원소 갯수, 수신 버퍼의 데이터 타입, 송신 프로세스 랭크, 커뮤니케이터)
    MPI_Scatter(send_msg, 1, MPI_INT, &recv_buf, 1, MPI_INT, 0, MPI_COMM_WORLD);

    cout << "MY RANK IS " << myrank << " AND I RECV: " << recv_buf << endl;

    MPI_Finalize();

    return 0;
}