// practice mpi_gather
#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    
    int comm_size, myrank;
    int send_msg, irecv[3];

    // MPI 초기화
    MPI_Init(&argc, &argv);

    // MPI rank 및 Communicator size 입력
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    send_msg = myrank + 1;

    // 각 프로세스에서 myrank+1 값을 보내면 한 프로세스에서 모은다
    // MPI_Gather(송신버퍼의 시작 주소, 송신버퍼의 원소 갯수, 송신 버퍼 원소의 데이터 타입, 수신 버퍼의 주소, 수신할 원소의 갯수, 수신 버퍼 원소의 데이터 타입, 수신(루트)프로세스의 랭크, 커뮤니케이터)
    MPI_Gather(&send_msg, 1, MPI_INT, irecv, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // 0을 루트로 사용, 0에서 각 프로세스가 보낸 정보 취합
    if (myrank == 0) {
        cout << "MY RANK: " << myrank << " AND I RECV: ";
        for(int i = 0; i < 3; i++) cout << irecv[i] << " ";
        cout << endl;
    }
    
    // MPI 종료
    MPI_Finalize();

    return 0;
}