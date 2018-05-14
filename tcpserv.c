//Program for tcp server...
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<fcntl.h>
#define PORT_NUM 2500 //port number on which message will recieve and send
int main() {

int server_sockfd, client_sockfd; //variable for socket descriptor(server and client)
int server_len, client_len;       //variable for initialize structure length
char out_buf[100];
char in_buf[100];                 //variable for input and output message initialize

struct in_addr client_ip_addr;    //structure variable for 'in_addr'to store IP address of client

struct sockaddr_in server_address;//structure variable to store server data
struct sockaddr_in client_address;//structure variable to store client data

unlink("server_socket");          //deleate the name from the file system
					  //means the name or process which  last
					  //link to the file"server_socket" and ensure 
					  //that no other process also opened that file
					  //then the space used by that name or process
					  //is deleated 
server_sockfd=socket(AF_INET, SOCK_STREAM, 0);//socket descripter for server(using ipv4)

server_address.sin_family=AF_INET;//define the family EX-AF_UNIX(for local communication),AF_INET(ipv4)
server_address.sin_port=htons(PORT_NUM);//host to network short byte word
server_address.sin_addr.s_addr=htonl(INADDR_ANY);//host to network long byte order

server_len=sizeof(server_address);//storing length of structure (define below)
bind(server_sockfd, (struct sockaddr *)&server_address, server_len);//binding the socket with port num and ip
listen(server_sockfd, 5);//server goes to listen mode and wait for client (max 5 client can connect)

client_len=sizeof(client_address);//storing length of structure (define below)

client_sockfd=accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);//connection established
											     //store the client descriptor at 
											     //'client_sockid'

memcpy(&client_ip_addr, &client_address.sin_addr.s_addr,4);//memspy()function 
						//copies 4 byte(32 bit) from 
						//source (&client_address.sin_addr.s_addr)client Ip address 
						//to destination(client_ip_addr)

printf("Accept completed (IP address of client=%s port=%d) \n",inet_ntoa(client_ip_addr), ntohs(client_address.sin_port));
						//printing IP address present in(client_ip_addr) and port number

while(1) {
printf("\nEnter ur Mesg...:=");
scanf("%s",out_buf);//taking string from user for sending to client
send(client_sockfd, out_buf, (strlen(out_buf)+1), 0);//message is sent to client descriptor through 'out_buf'
								//and length is increase by 1 because to explicitely assign null 
								//at the end of the stream

recv(client_sockfd, in_buf, sizeof(in_buf), 0);//recieving message from client socket descriptor through 'in_buf'
printf("\n\tReceived from client...Mesg='%s'\n", in_buf);//printing the message
}
close(server_sockfd);//closing two socket descriptor
close(client_sockfd);
}
