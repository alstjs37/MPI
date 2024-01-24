#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <fstream>
#include <sstream>

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
        else cout << "WAITING FOR CHECKING ... " << endl;
    }
}

void write_file(string filename, string server_info) {
    ofstream outfile(filename, ios::app);

    if(outfile.is_open()) {
        outfile << server_info << endl;
        outfile.close();
        cout << "FILE WRITE SUCCESS" << endl;
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
    
    // file path
    string filename = "./example.txt";
    string server_info;

    // pod_hostname.service_name.namespace (using k8s headless service)
    const char* server_name[2] = {"www.google.com", "www.naver.com"};

    // for(int i = 0; i < num_of_node; i++) {
    //     server_info = domain_to_ip(server_name[i]);
    //     write_file(filename, server_info);
    // }

    cout << "result ---> " << split_domain(server_name[0]) << endl;

    cout << "TOTAL PROCESS IS SUCCESSED !!" << endl;
    return 0;
}

// #include <iostream>
// #include <netdb.h>
// #include <arpa/inet.h>
// #include <fstream>

// using namespace std;

// int main (int argc, char *argv[]) {

//     struct hostent *host;
    
//     // file path
//     string filename = "/etc/hosts";
//     string ip_addr, server_info;

//     // pod_hostname.service_name.namespace (using k8s headless service)
//     const char* server_name = "mpi-sn03.mpi-service.mpi-mslee";
    
//     if ((host = gethostbyname(server_name)) == NULL) {
//         cout << "ERROR: NOT DEFINE HOSTNAME ( " << server_name << " )" << endl;
//     }

//     ip_addr = inet_ntoa(*(struct in_addr*)host->h_addr_list[0]);
//     server_info = ip_addr + " " + server_name;

//     // open file with write mode & write with append mode
//     ofstream outfile(filename, ios::app);

//     // if file open success
//     if (outfile.is_open()) {
//         // write at file
//         outfile << server_info << endl;

//         // close file
//         outfile.close();
//         cout << "FILE WRITE SUCCESS" << endl;
//     } else {
//         // fail to open file
//         cerr << "ERROR: FAIL TO OPEN FILE" << endl;
//     }

//     return 0;
// }