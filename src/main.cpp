#include <iostream>
#include <sstream>
#include "inc/repository.h"
#include <al.h>
#include <thread>

#define AL_UNIX_FILE        "/tmp/alunix.sock"
using namespace std;

int32_t exec_cmd(repository & repo, std::string prompt)
{
    int fret = 0;
    string cmd, key, value;
    std::map<std::string, std::string>::iterator it;

    stringstream stream_buf(prompt);
    stream_buf >> cmd>>key>>value;


    if("SET" == cmd)
    {
        fret = repo.set_data(key, value);
        if(0 == fret)
            cout<<"OK"<<endl;
    }
    else if (cmd == "GET")
    {
        fret = repo.get_data(key,value, &it);
        if(0 == fret)
            cout<< it->second<<endl;

    }
    else if(cmd == "DELETE")
    {
        fret = repo.del_data(key);
        if(0 == fret)
            cout<<"OK"<<endl;
    }
    else
    {
        cerr<<"Illegal Command"<<endl;
    }

}


void server_cb(cpayload *payload)
{

    fprintf(stderr,"Callback: %s\n", payload->payload);
    al_write_sock(payload->cli_sock, payload->payload, payload->payload_len);
}
void thr_cb(repository * repo)
{
    int32_t server_sock;
    int32_t fret;
    server_sock = al_srv_open_sock(SOCK_UNIX);
    fret = al_unix_srv_bind(server_sock, AL_UNIX_FILE);
    if(-1 == fret)
    {
        return ;
    }
    fret =  al_srv_listen_sock(server_sock,4);
    if(-1 == fret)
    {
        perror("Listen");
        return ;
    }

    fret = al_srv_serve_reqs(server_sock, server_cb);
}
int main()
{

    repository repo("test_repo.txt");
    string line;

    std::thread ipc_thr( thr_cb, &repo);

    repo.open_file();
    while (1) {
        cout<<"> ";
        getline(cin, line);
        exec_cmd(repo,line);
    }


}
