#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <fstream>

using namespace std;

int main (int argc, char *argv[]) {

    struct hostent *host;
    
    // file path
    string filename = "/etc/hosts";
    string ip_addr, server_info;

    // pod_hostname.service_name.namespace (using k8s headless service)
    const char* server_name = "mpi-sn03.mpi-service.mpi-mslee";
    
    if ((host = gethostbyname(server_name)) == NULL) {
        cout << "ERROR: NOT DEFINE HOSTNAME ( " << server_name << " )" << endl;
    }

    ip_addr = inet_ntoa(*(struct in_addr*)host->h_addr_list[0]);
    server_info = ip_addr + " " + server_name;

    // open file with write mode & write with append mode
    ofstream outfile(filename, ios::app);

    // if file open success
    if (outfile.is_open()) {
        // write at file
        outfile << server_info << endl;

        // close file
        outfile.close();
        cout << "FILE WRITE SUCCESS" << endl;
    } else {
        // fail to open file
        cerr << "ERROR: FAIL TO OPEN FILE" << endl;
    }

    return 0;
}