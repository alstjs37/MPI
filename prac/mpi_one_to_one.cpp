#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    // MPI 초기화
    MPI_Init(&argc, &argv);

    // 현재 프로세스의 랭크와 전체 프로세스 수 얻기
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // 메시지 송신자와 수신자 지정
    int sender = 0;
    int receiver = 1;

    // 메시지 송신자가 일부 데이터 전송
    if (rank == sender) {
        int data_to_send = 42;

        // MPI_Send(전송할 데이터의 시작 주소, 전송할 데이터의 갯수, 전송할 데이터 타입, 목적지 프로세서 랭크, 메세지를 식별하는 태그, 커뮤니케이터)
        MPI_Send(&data_to_send, 1, MPI_INT, receiver, 0, MPI_COMM_WORLD);
        cout << "Process " << rank << " sent data: " << data_to_send << endl;
    }

    // 메시지 수신자가 데이터 수신
    if (rank == receiver) {
        int received_data;

        // MPI_Recv(수신할 데이터를 저장할 버퍼의 시작 주소, 수신할 데이터의 개수, 수신할 데이터의 타입, 
        //          메세지를 기다리는 송신자 프로세스의 랭크 -> MPI_ANY_SOURCE를 사용하여 어떤 프로세스에서든 메세지를 기다릴 수 있음,
        //          송신자가 메시지에 부여한 태그 -> MPI_ANY_TAG를 사용하여 어떤 태그든 수락 가능, 커뮤니케이터,
        //          메세지의 상태를 나타내는 MPI_Status 구조체에 대한 포인터, 필요하지 않을 시 MPI_STATUS_IGNORE를 사용할 수 있음)
        MPI_Recv(&received_data, 1, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Process " << rank << " received data: " << received_data << endl;
    }

    // MPI 종료
    MPI_Finalize();

    return 0;
}
