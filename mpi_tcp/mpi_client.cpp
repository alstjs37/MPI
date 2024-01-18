#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <mpi.h>

using namespace std;

int main() {
    MPI_Init(NULL, NULL);

    // MPI 정보 가져오기
    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // 클라이언트 소켓 생성
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        cerr << "Error creating client socket." << endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // 서버 주소 설정
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);  // 서버 포트 번호
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // 서버 IP 주소

    // 서버에 연결
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "Error connecting to server." << endl;
        close(clientSocket);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    cout << "Connected to server." << endl;

    // 서버로 메시지 전송
    const char* message = "Hello from client!";
    ssize_t bytesSent = send(clientSocket, message, strlen(message), 0);
    if (bytesSent == -1) {
        cerr << "Error sending data to server." << endl;
    }

    // 서버로부터 응답 수신
    char buffer[1024];
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        cerr << "Error receiving data from server." << endl;
    } else {
        buffer[bytesRead] = '\0';  // Null terminate the received data
        cout << "Received from server: " << buffer << endl;
    }

    // 소켓 종료
    close(clientSocket);

    MPI_Finalize();
    return 0;
}