// practice MPI_boradcast
#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

    int myrank;
    int imsg[4];

    // MPI 초기화
    MPI_Init(&argc, &argv);
    
    // 각 프로세스 마다 RANK 부여
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    // rank == 0인 프로세스 (Master)에게만 [1,2,3,4] 나머지는 [0,0,0,0]
    if (myrank == 0) {
        for(int i = 0; i < 4; i++) imsg[i] = i+1;
    } else {
        for(int i = 0; i < 4; i++) imsg[i] = 0;
    }

    // broadcast 전 msg 출력
    cout << "MY RANK: " << myrank << " BEFORE: ";
    for(int i = 0; i < 4; i++) cout << imsg[i] << " ";
    cout << endl;

    // Broadcast
    // MPI_Bcast(버퍼 시작 주소, 버퍼 원소 갯수, 버퍼 원소의 MPI 데이터 타입, 루트 프로세스의 랭크, 커뮤니케이터)
    MPI_Bcast(imsg, 4, MPI_INT, 0, MPI_COMM_WORLD);

    // broadcast 후 msg 출력
    cout << "MY RANK: " << myrank << " AFTER: ";
    for(int i = 0; i < 4; i++) cout << imsg[i] << " ";
    cout << endl;

    // MPI 종료
    MPI_Finalize();

    return 0;
}