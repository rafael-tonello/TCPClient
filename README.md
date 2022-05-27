# Event TCPClient Library
Thi is an event based TCP Client. This client do not use async I/O yet or LibEvent. I wrote this code to be compiled in a system that does't support LibEvent.

# Using
To Use this library, you can copy the .cpp and .h files to your project or add this repository as a submodule of your project.

Along with this code, there is a ".vscode" folder that contains some configurations for the Visual Studio Code. If you use VSCode, you can compile the tests program direclty from the 'Debug' section of this IDE.

# How to use

To use this TCPClient, take a look in the examples bellow



## Connecting to a server and send data to it
```c++
//include the library header
#include <TCPClient.h>

int main()
{
    //declaring a client object
    TCPClientLib::TCPClient cli;
    
    //connecting to the server. The connectToServer method returns an future<bool>. So you can wait from the connection. The future result represents a sucess of failure connetion
    if (cli.connectToServer("127.0.0.1", 8085).get())
    {
        //sending data to the server
        char *data = "this is a test data";
        cli.sendData(data, 19);

        //closing the connection
        cli.disconnect();
    }
    else
    {
        cerr << "Could't connect to the server" << endl;
        return 1;
    }
    return 0;
}
```

## using a help function to send string
In the TCPCLient class there is a helper funcion that failitates the string sending to the server.
```c++
#include <TCPClient.h>

int main()
{
    TCPClientLib::TCPClient cli;
    
    //connecting to the server. 
    if (cli.connectToServer("127.0.0.1", 8085).get())
    {
        //sending data to the server
        cli.sendString("Hey server! Take this string");

        cli.disconnect();
    }
    else
    {
        cerr << "Could't connect to the server" << endl;
        return 1;
    }

    return 0;
}
```

## looping until is connect to the server
You can use the method 'isConnected' to know if the connection to the server is ok

```c++

#include <TCPClient.h>
int main()
{
    TCPClientLib::TCPClient cli;
    
    //connecting to the server. 
    if (cli.connectToServer("127.0.0.1", 8085).get())
    {
        //isConnected returns a boolean value indicating if the client is connect to the client
        while (cli.isConnected())
        {
            //do somethings while is connected to the !server
            cli.sendString("Hey server! I'm still here!");
            usleep(1000000);
        }
    }
    else
    {
        cerr << "Could't connect to the server" << endl;
        return 1;
    }
    return 0;
}
```

## You can also use the method "waitUntilDisconnect" to wait

```c++
#include <TCPClient.h>
int main()
{
    TCPClientLib::TCPClient cli;
    
    //connecting to the server. 
    if (cli.connectToServer("127.0.0.1", 8085).get())
    {
        //waitUntilDisconnect returns a future that is set when the conneciton to the server is lost or finished
        cli.waitUntilDisconnect().get();
        cout << "exiting" << endl;
    }
    else
    {
        cerr << "Could't connect to the server" << endl;
        return 1;
    }

    return 0;
}
```

## receiving data from the server
To receive data from the server, the TCPLib class you just need to informa a function to receive the data

```c++
#include <TCPClient.h>
int main()
{
    TCPClientLib::TCPClient cli;

    //seting a function to receive incoming data
    cli.addReceiveListener([&](TCPClientLib::TCPClient *cli, char* data, size_t size){
        cout << "Received from server: ";
        for (size_t c = 0; c < size; c++)
            cout << data[c];

        cout << endl;
    });
    
    //connecting to the server and wait until disconnected
    if (cli.connectToServer("127.0.0.1", 8085).get())
        cli.waitUntilDisconnect().get();
    else
    {
        cerr << "Could't connect to the server" << endl;
        return 1;
    }
    return 0
}
```

## and yes, the lib have a helper function to receive strings from the server

```c++
#include <string>
#include <TCPClient.h>

int main()
{
    TCPClientLib::TCPClient cli;

    //seting a function to receive incoming data as string
    cli.addReceiveListener_s([&](TCPClientLib::TCPClient *cli, std::string data){
        cout << "Received from server: " << data << endl;
    });
    
    
    //connecting to the server and wait until disconnected
    if (cli.connectToServer("127.0.0.1", 8085).get())
        cli.waitUntilDisconnect().get();
    else
    {
        cerr << "Could't connect to the server" << endl;
        return 1;
    }

    return 0;
}

```



# Main task List
charaters to be used ✔ ✘
 
