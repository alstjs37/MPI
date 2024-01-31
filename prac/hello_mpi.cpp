#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    // MPI 초기화
    MPI_Init(&argc, &argv);

    // 현재 프로세스의 랭크와 전체 프로세스 수 얻기
    int rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // 현재 프로세서의 이름을 저장할 배열
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    
    // 현재 프로세서의 이름과 길이 얻기
    int node_name;
    MPI_Get_processor_name(processor_name, &node_name);

    // 각 프로세스에서 출력
    cout << "Hello from process " << rank << " of " << world_size << " on node ( " << processor_name << " )" << endl;

    // MPI 종료
    MPI_Finalize();

    return 0;
}

