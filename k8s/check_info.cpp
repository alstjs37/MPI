#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <fstream>

using namespace std;

int main (int argc, char *argv[]) {

    struct hostent *host;
    
    // 파일 경로
    string filename = "/etc/hosts";
    string ip_addr, server_info;

    // pod_hostname.service_name.namespace
    const char* server_name = "mpi-sn03.mpi-service.mpi-mslee";
    
    if ((host = gethostbyname(server_name)) == NULL) {
        cout << "ERROR: NOT DEFINE HOSTNAME ( " << server_name << " )" << endl;
    }

    ip_addr = inet_ntoa(*(struct in_addr*)host->h_addr_list[0]);
    server_info = ip_addr + " " + server_name;

    // 파일 쓰기 모드로 열기
    ofstream outfile(filename);

    // 파일 열기에 성공한 경우
    if (outfile.is_open()) {
        // 파일에 쓰기
        outfile << server_info << endl;

        // 파일 닫기
        outfile.close();
        cout << "FILE WRITE SUCCESS" << endl;
    } else {
        // 파일 열기에 실패한 경우
        cerr << "ERROR: FAIL TO OPEN FILE" << endl;
    }

    return 0;
}