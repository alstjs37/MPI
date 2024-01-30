#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <fstream>
#include <sstream>

#define num_of_node 3

using namespace std;

// change domain to ip addr and return "ip addr + domain name"
string domain_to_ip(const char* server_name) {
    string ip_addr, server_info;
    
    struct hostent *host;

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

// write server_info( "ip addr + domain name ") to /etc/hosts
void write_file(string filename, string server_info, string short_domain) {
    server_info = server_info + " " + short_domain;
    ofstream outfile(filename, ios::app);

    if(outfile.is_open()) {
        outfile << server_info << endl;
        outfile.close();
        cout << "[SUCCESS] FILE WRITE SUCCESS" << endl;
    } else {
        cout << "[ERROR] FAIL TO OPEN FILE" << endl;
    }
}

string split_domain(string domain_name) {
    string str = domain_name, token;
    istringstream ss(str);

    getline(ss, token, '.');
    
    return token;
}

int main (int argc, char *argv[]) {

    struct hostent *host;
    
    // file path
    string filename = "/etc/hosts";
    string ip_addr, server_info, mini_domain;

    // pod_hostname.service_name.namespace (using k8s headless service)
    const char* server_name[num_of_node] = {"mpi-sn03.mpi-service.mpi-mslee", "mpi-sn04.mpi-service.mpi-mslee", "mpi-sn05.mpi-service.mpi-mslee"};
    
    // change domain to ip and write file
    for(int i = 0; i < num_of_node; i++) {
        server_info = domain_to_ip(server_name[i]);
        mini_domain = split_domain(server_name[i]);
        write_file(filename, server_info, mini_domain);
    }

    cout << "[SUCCESS] TOTAL PROCESS IS SUCCESSED !!" << endl;

    return 0;
}