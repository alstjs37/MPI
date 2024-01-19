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

    // 서버 소켓 생성
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cerr << "Error creating server socket." << endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // 서버 주소 설정
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);  // 사용할 포트 번호
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // 서버 소켓에 주소 바인딩
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "Error binding server socket." << endl;
        close(serverSocket);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // 클라이언트의 연결을 기다림
    if (listen(serverSocket, 1) == -1) {
        cerr << "Error listening for clients." << endl;
        close(serverSocket);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    cout << "Server on Node " << world_rank << " is waiting for incoming connections..." << endl;

    // 클라이언트 연결을 수락
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    cout << "TCP CONECTION SUCCESS !!" << endl << endl;
    if (clientSocket == -1) {
        cerr << "Error accepting client connection." << endl;
        close(serverSocket);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    cout << "Server on Node " << world_rank << " connected to client. IP: " << inet_ntoa(clientAddr.sin_addr) << ", Port: " << ntohs(clientAddr.sin_port) << endl;

    // 클라이언트로부터 메시지 수신
    char buffer[1024];
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        cerr << "Error receiving data from client." << endl;
    } else {
        buffer[bytesRead] = '\0';  // Null terminate the received data
        cout << "Received from client: " << buffer << endl;
    }

    // 클라이언트에게 응답 전송
    const char* response = "Hello from server!";
    ssize_t bytesSent = send(clientSocket, response, strlen(response), 0);
    if (bytesSent == -1) {
        cerr << "Error sending data to client." << endl;
    }

    // 소켓 종료
    close(clientSocket);
    close(serverSocket);

    MPI_Finalize();
    return 0;
}