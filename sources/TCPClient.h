//TODO: Create a new socket system using libuv: docs.libuv.org/en/v1.x/guide.html


#ifndef _TCPSERVER_H
#define _TCPSERVER_H

#include <functional>
#include <map>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <vector>
#include <ThreadPool.h>
#include <string>

#pragma region include for networking
    #include <sys/types.h>
    #include <arpa/inet.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <errno.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/ioctl.h>
    #include <signal.h>
#pragma endregion
#include <ThreadPool.h>

namespace TCPClientLib
{
    using namespace std;

    enum CONN_EVENT{CONNECTED, DISCONNECTED};

    class TCPClient{
        private:
            #ifdef __TESTING__
                public: 
            #endif
            const int _CONF_DEFAULT_LOOP_WAIT = 500;
            const int _CONF_READ_BUFFER_SIZE = 10240;

            int listenersIdCounter = 0;

            atomic<bool> running;
            map<int, function<void(TCPClient *client, char* data,  size_t size)>> receiveListeners;
            map<int, function<void(TCPClient *client, string data)>> receiveListeners_s;

            map<int, function<void(TCPClient *client, CONN_EVENT event)>> connEventsListeners;

            void notifyListeners_dataReceived(char* data, size_t size);
            void notifyListeners_connEvent(CONN_EVENT action);
            bool SocketIsConnected(int socket);
            void debug(string msg){cout << "Debug: " << msg << endl;}
            bool SetSocketBlockingEnabled(int fd, bool blocking);
        public:
            map<string, string> tags;

            int socketHandle;
            mutex writeMutex;
            void sendData(char* data, size_t size);
            void sendString(string data);

            future<bool> connectToServer(string server_, int port_ );
            bool isConnected();
            void disconnect();

            int addReceiveListener(function<void(TCPClient *client, char* data,  size_t size)> onReceive);
            void removeListener(int id);
            int addReceiveListener_s(function<void(TCPClient *client, string data)> onReceive);
            void removeListener_s(int id);
            int addConEventListener(function<void(TCPClient *client, CONN_EVENT event)> onConEvent);
            void removeConEventListener(int id);

            

            TCPClient(string server, int port)
            {
                this->connectToServer(server, port);
                running = false;
            }

            TCPClient(){
                running = false;
            }

            ~TCPClient(){
                running = false;
            }
    };
    
}
#endif