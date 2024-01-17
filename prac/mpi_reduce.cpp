// practice MPI_Reduce
#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    int myrank, istart, iend;
    double arr[9], sum = 0.0, result;

    // MPI 초기화
    MPI_Init(&argc, &argv);

    // MPI rank값 반환
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    istart = myrank * 3;
    iend = istart + 2;

    // arr 배열 생성
    for(int i = istart; i < iend + 1; i++) arr[i] = i+1;

    // 각 프로세스에서 따로 sum 계산
    for(int i = istart; i < iend + 1; i++) sum += arr[i];

    // 각 프로세스에서 계산한 sum 값 한 프로세스로 합치기
    // MPI_Reduce(송신 버퍼의 시작 주소, 수신버퍼의 시작 주소, 송신 버퍼의 원소 갯수, 송신버퍼의 데이터 타입, 환산 연산자, 루트 프로세스 랭크, 커뮤니케이터)
    MPI_Reduce(&sum, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(myrank == 0) cout << "I gather with sum operation! result = " << result << endl;

    // MPI 종료
    MPI_Finalize();

    return 0;
}