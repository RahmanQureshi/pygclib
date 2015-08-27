#include "gclibo.h" //by including the open-source header, all other headers are pulled in.
#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[])
{

	setbuf(stdout, NULL);

	GReturn rc;
	//GSize* bytesReturned = malloc(sizeof(GSize));
	char buf[1024]; //traffic buffer
	char cmd[1024];
	
	rc = GVersion(buf, sizeof(buf));
	printf("rc: %d\n", (int) rc);
	printf("version: %s\n", buf); //Print the library version

	GCon g; //var used to refer to a unique connection
	
	const char* address = "10.10.1.21 -d";
	rc = GOpen(address, &g); //Open a connection to Galil, store the identifier in g.
	printf("Connection\n");
	printf("rc: %d\n", (int) rc);

	rc = GInfo(g, buf, sizeof(buf));
	printf("rc: %d\n", (int) rc);
	printf("info: %s\n", buf); //Print the connection info
	
	while(1)
	{
		printf("DMC Command: ");
		scanf("%s", cmd);
		if( strcmp(cmd, "quit") ) {
			rc = GCommand(g, cmd, buf, sizeof(buf), 0);
			printf("Buffer: %s\n", buf);
			printf("Returned: %d\n", (int) rc);
		} else {
			break;
		}
	}
	
	
	rc = GClose(g); //Don't forget to close!
	printf("Closing\n");
	printf("rc: %d\n", (int) rc);
	
	return rc;
}
