#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <fstream>

#define num_of_node 2

using namespace std;

string domain_to_ip(const char* server_name) {
    struct hostent *host;

    string ip_addr, server_info;

    while(1) {
        host = gethostbyname(server_name);
        if (host) {
            ip_addr = inet_ntoa(*(struct in_addr*)host->h_addr_list[0]);
            server_info = ip_addr + " " + server_name;

            return server_info;
        }
        else cout << "[WARN] WAITING FOR CHECKING ... " << endl;
    }
}

void write_file(string filename, string server_info) {
    ofstream outfile(filename, ios::app);

    if(outfile.is_open()) {
        outfile << server_info << endl;
        outfile.close();
        cout << "[SUCCESS] FILE WRITE SUCCESS" << endl;
    } else {
        cout << "[ERROR] FAIL TO OPEN FILE" << endl;
    }
}

int main (int argc, char *argv[]) {

    struct hostent *host;
    
    // file path
    string filename = "/etc/hosts";
    string ip_addr, server_info;

    // pod_hostname.service_name.namespace (using k8s headless service)
    const char* server_name[2] = {"mpi-sn03.mpi-service.mpi-mslee", "mpi-sn04.mpi-service.mpi-mslee"};
    
    for(int i = 0; i < num_of_node; i++) {
        server_info = domain_to_ip(server_name[i]);
        write_file(filename, server_info);
    }

    cout << "[SUCCESS] TOTAL PROCESS IS SUCCESSED !!" << endl;

    return 0;
}