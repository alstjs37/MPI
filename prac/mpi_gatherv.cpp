// practice mpi_gatherv
#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    
    int comm_size, myrank;
    int send_msg[3], irecv[6];
    int send_length, recv_cnt[3] = {1, 2, 3}, idisp[3] = {0, 1, 3};

    // MPI 초기화
    MPI_Init(&argc, &argv);

    // MPI rank 및 Communicator size 입력
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    // 보낼 메시지 값, rank = 1이면 1, rank = 2이면 2를 보낸다.
    for(int i = 0; i < myrank + 1; i++) send_msg[i] = myrank + 1;

    // 보낼 메세지의 길이
    send_length = myrank + 1;

    // 각 프로세스에서 서로 다른 길이의 메세지를 보내면 한 프로세스에서 모은다
    // MPI_Gatherv(송신버퍼의 시작 주소, 송신버퍼의 원소 갯수, 송신 버퍼 원소의 데이터 타입, 수신 버퍼의 주소, 수신된 원소의 개수를 저장하는 정수 배열,
    //             i번째 자리에는 프로세스 i에서 들어오는 데이터가 저장될 수신 버퍼상의 위치를 나타내는 배열, 수신 버퍼 원소의 데이터 타입, 수신(루트)프로세스의 랭크, 커뮤니케이터)
    MPI_Gatherv(&send_msg, send_length, MPI_INT, irecv, recv_cnt, idisp, MPI_INT, 0, MPI_COMM_WORLD);

    // 0을 루트로 사용, 0에서 각 프로세스가 보낸 정보 취합
    if (myrank == 0) {
        cout << "MY RANK: " << myrank << " AND I GATHERV RECV: ";
        for(int i = 0; i < 6; i++) cout << irecv[i] << " ";
        cout << endl;
    }
    
    // MPI 종료
    MPI_Finalize();

    return 0;
}