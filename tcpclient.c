//Program for tcp client...
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<fcntl.h>
#include<unistd.h>

#define PORT_NUM 2500  //port number on which message will recieve and send
#define IP_ADDR "127.127.127.127"//Loop back ADDRESS as I am using same machine 				
                                 //for both server and reciever

int main() {

int client_sockfd;//variable for socket descriptor(client)
int server_len;//variable for initialize structure length
char out_buf[100];//variable for input and output message initialize
char in_buf[100];

struct sockaddr_in server_address;//structure variable to store server data

client_sockfd=socket(AF_INET, SOCK_STREAM, 0);//socket descripter for server(using ipv4)
server_address.sin_family=AF_INET;//define the family EX-AF_UNIX(for local communication),AF_INET(ipv4)
server_address.sin_port=htons(PORT_NUM);//host to network short byte word
server_address.sin_addr.s_addr=inet_addr(IP_ADDR);//assigning IP address defined above

server_len=sizeof(server_address);//storing length of structure (define below)
connect(client_sockfd, (struct sockaddr *)&server_address, server_len);//connect to the server which is 
									     //in listen mode

while(1) {//this infinite loop for continuous chat
recv(client_sockfd, in_buf, sizeof(in_buf), 0);//recieving message from server through client socket descriptor in 'in_buf'
printf("Received from server...Mesg='%s'\n", in_buf);//printing the message

printf("ENter ur Mesg...");
scanf("%s",out_buf);//taking string from user for sending to server
send(client_sockfd, out_buf, (strlen(out_buf)+1), 0);//message is sent to client descriptor through 'out_buf'
								//and length is increase by 1 because to explicitely assign null 
								//at the end of the stream

}
close(client_sockfd);//closing connection bye bye
}












