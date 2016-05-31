//包含zmq的头文件 
#include "runSocket.h"

using namespace std;


int main(int argc, char * argv[])
{
	CrunSocket socket;
	const char * port = "tcp://*:7766";
	if(socket.init(port) != 1)
		exit(0);
	socket.run();
	socket.destroy();
	exit(0);
}
