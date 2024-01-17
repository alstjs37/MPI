// practice MPI_Allgather
#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    int myrank;
    int send_msg, recv_buf[3];

    // MPI 초기화
    MPI_Init(&argc, &argv);

    // MPI rank값 반환
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    // 보낼 메세지
    send_msg = myrank + 1;
    
    // MPI_Allgather 이전 recv_buf
    cout << "MY RANK: " << myrank << " BEFORE I ALLGATHER: ";
    for(int i = 0; i < 3; i++) cout << recv_buf[i] << " ";
    cout << endl;

    // MPI_Allgather(송신 버퍼의 시작 주소, 송신 버퍼의 원소 개수, 송신 버퍼의 데이터 타입, 수신 버퍼의 주소, 각 프로세스로부터 수신된 데이터 갯수, 수신버퍼 데이터 타입, 커뮤니케이터)
    // 배열은 어차피 시작주소가 변수를 가지고 있으니까 추가적으로 & 연산자를 써줄 필요가 없다.
    MPI_Allgather(&send_msg, 1, MPI_INT, recv_buf, 1, MPI_INT, MPI_COMM_WORLD);

    cout << "MY RANK: " << myrank << " AFTHER I ALLGATHER: ";
    for(int i = 0; i < 3; i++) cout << recv_buf[i] << " ";
    cout << endl;

    // MPI 종료
    MPI_Finalize();

    return 0;
}