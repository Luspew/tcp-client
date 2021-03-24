#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

struct sockaddr_in cli_address;
int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cout << "Please, set host and port..." << endl;
        return 0;
    }

    string server_host = argv[1];
    uint port = atoi(argv[2]);

    int cli_sock = socket(AF_INET, SOCK_STREAM, 0);

    cli_address.sin_family = AF_INET;
    cli_address.sin_port = htons(port);
    inet_pton(AF_INET, server_host.c_str(), &cli_address.sin_addr);

    int connectServer = connect(cli_sock, (struct sockaddr *)&cli_address, sizeof(cli_address));
    if (connectServer == -1)
    {
        perror("Error trying to connect server");
        return 1;
    }

    int bufflen = 1024;
    char buffer[bufflen];

    string cli_inp;

    do
    {
        cout << "-> ";
        getline(cin, cli_inp);

        if (send(cli_sock, cli_inp.c_str(), cli_inp.length() + 1, 0) == -1)
        {
            perror("Erro trying to send message to server");
            continue;
        }

        memset(buffer, 0, bufflen);
        int recv_buffer = recv(cli_sock, buffer, bufflen - 1, 0);
        if (recv_buffer == -1)
        {
            perror("Erro trying to recv message to server");
            break;
        }

        cout << "ServerSays> "<< string(buffer)<<endl; 

    } while (true);
}