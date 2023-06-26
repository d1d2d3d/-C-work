#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>
#include <unordered_map>
#include <thread>
#include <chrono>
#include<fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace rapidjson;

#define PORT 8080
#define MAX_PENDING_CONNECTIONS 10
#define BUFFER_SIZE 1024*1024


//设置非阻塞
void setnonblocking(int fd){
    int old_flag =fcntl(fd,F_GETFL);
    int new_flag = old_flag | O_NONBLOCK;
    fcntl(fd,F_SETFL,new_flag);
}

void process_response(int client_socket){
    Document response;
    response.SetObject();
    Value status;
    status.SetString("success", response.GetAllocator());
    response.AddMember("data", status, response.GetAllocator());
    StringBuffer buf;
    Writer<StringBuffer> writer(buf);
    response.Accept(writer);
    std::string response_data = buf.GetString();

    std::stringstream response_stream;
    response_stream << "HTTP/1.1 200 OK\r\n"
                    << "Content-Length: " << response_data.length() << "\r\n"
                    << "Content-Type: application/json\r\n"
                    << "Connection: keep-alive\r\n"
                    << "\r\n"
                    << response_data;
    std::string response_str = response_stream.str();

    int byte_have_send=send(client_socket, response_str.c_str(), response_str.length(), 0);
    
}
void handle_request(int client_socket) {
    // 读取HTTP请求
    auto start=std::chrono::high_resolution_clock::now();
    char buffer[BUFFER_SIZE];
    std::stringstream request_stream;
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    while (bytes_received > 0) {
        request_stream.write(buffer, bytes_received);
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    }
    std::string request = request_stream.str();

    
    // 解析HTTP请求头
    std::unordered_map<std::string, std::string> headers;
    std::istringstream header_stream(request);
    std::string line;
    std::getline(header_stream, line);
    while (line != "\r") {
        size_t pos = line.find(":");
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            headers[key] = value;
        }
        std::getline(header_stream, line);
    }

    //process_response(client_socket);

    // 解析HTTP请求负载
    std::string name;
    std::string userName;
    std::string password;
    std::string filename;
    std::ofstream file;
    std::istringstream payload_stream(request.substr(request.find("\r\n\r\n") + 4));
    std::getline(payload_stream, line);
    std::getline(payload_stream, line);
    while (line.substr(0, 12) != "Content-Type") {
        if (line.find("Content-Disposition: form-data;") != std::string::npos) {
            size_t pos = line.find("name=\"") + 6;
            name = line.substr(pos, line.find("\"", pos) - pos);
            if (name == "file") {
                pos = line.find("filename=\"") + 10;
                filename = password+".jpg";
                file.open(filename, std::ios::out | std::ios::binary);
            }else if(name == "name"){
                std::getline(payload_stream, line);
                std::getline(payload_stream, line);
                userName=line.substr(0);
                userName.erase(userName.length()-1);

            }
            else if(name == "password"){
                std::getline(payload_stream, line);
                std::getline(payload_stream, line);
                password=line.substr(0);
                password.erase(password.length()-1);
            }
        } 
        std::getline(payload_stream, line);
    }
    std::getline(payload_stream, line);
    std::getline(payload_stream, line);
    while (line.substr(0,2) != "--"){
        file << line << std::endl;
        std::getline(payload_stream, line);
    }
    file.close();
    auto end=std::chrono::high_resolution_clock::now();
    auto duration=std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout<<"处理报文花费时间: "<<duration.count()<<" 微秒"<<std::endl;

    //回应
    process_response(client_socket);
    close(client_socket);
}

int main() {
    // 创建监听socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Error: failed to create server socket.\n";
        return 1;
    }

    int reuse=1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR,&reuse, sizeof(reuse));

    // 绑定socket到本地端口
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Error: failed to bind server socket.\n";
        return 1;
    }

    // 开始监听端口
    if (listen(server_socket, MAX_PENDING_CONNECTIONS) == -1) {
        std::cerr << "Error: failed to listen on server socket.\n";
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << ".\n";

    // 循环处理客户端连接
    while (true) {
        struct sockaddr_in client_address;
        socklen_t client_address_size = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_size);
        if (client_socket == -1) {
            std::cerr << "Error: failed to accept client connection.\n";
            continue;
        }
        setnonblocking(client_socket);
        std::cout << "Received a connection from " << inet_ntoa(client_address.sin_addr) << ":" << ntohs(client_address.sin_port) << ".\n";

        // 使用线程处理客户端请求
        std::thread t(handle_request, client_socket);
        t.detach();
    }
    // 关闭监听socket
    close(server_socket);
    return 0;
}