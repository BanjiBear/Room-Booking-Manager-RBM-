//COMP2432 Group Project
//Group G08
/*	CHEN Yi pu
	CHEUNG Man Fung
	LIANG, Rui
	LIU, Sicheng
	XIE Yangxiaolong
*/

// For testing purpose, please DO NOT COPY AND PASTE FROM PDF FILE
// There will be unrecognizable symbols

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void cutTenant(char input[1024], char tenant[15]){
	int i, j, p, q = 0;
	// Copy the tenant who makes the request using nested for-loop
	for(i = 0; i < 1024; i++){
		if(input[i] == ' '){
		//printf("%d\n", i);	// For debugging
			for(j = i+1; j < 1024; j++){
				if(input[j] == ' '){
					for(p = i+2; p < j; p++){
						tenant[q] = input[p];
						q++;
					}
					break;
				}
			}
			break;
		}
	}
}

void cutTime(char input[1024], char time[20]){
	int i, j, q = 0;
	// Copy the booked time of the request
	for(i = 0; i < strlen(input); i++){
		if(input[i] == ' '){
			q++;
		}
		if(q == 2){
			for(j = 0; j < 16; j++){
				time[j] = input[i+1];
				i++;
			}
			break;
		}
	}
}

void cutDuration(char input[1024], char duration[5]){
	int i, j, q = 0, p = 0;
	//Copy the duration
	for(i = 0; i < strlen(input); i++){
		if(input[i] == ' '){
			q++;
		}
		if(q == 4){
			for(j = i+1; j < i+4; j++){
				duration[p] = input[j];
				p++;
			}
			break;
		}
	}
}

void cutCallee(char input[1024], char callee[5]){
	int i, j, p = 0, q = 0;
	// Copy the number of callees using nested for-loop
	for(i = 0; i < strlen(input); i++){
		if(input[i] == ' '){
			q++;
		}
		if(q == 5){
			for(j = i+1; j < strlen(input); j++){
				if(input[j] == ' ' | input[j] == ';'){
					break;
				}
				callee[p] = input[j];
				p++;
			}
			break;
		}
	}
}

void cutDevice(char input[1024], char commandType[15], char device[30]){
	int i, q = 0;
	if(strncmp(commandType, "bookDevice", 10) == 0){
		for(i = 0; i < strlen(input); i++){
			if(input[i] == ' '){
				q++;
			}
			if(q == 5){
				q = 0;
				while(i < strlen(input) - 3){
					device[q] = input[i+1];
					q++; i++;
				}
			}
		}
	}
	else{
		for(i = 0; i < strlen(input); i++){
			if(input[i] == ' '){q++;}
			if(q == 6){
				for(q = i + 1; q < strlen(input); q++){
					if(input[q] == ';'){
						break;
					}
					device[q - (i + 1)] = input[q];
				}
			}
		}
	}
}

void cutFirstDevice(char device[30], char firstDevice[15]){
	int i, j;
	for (i = 0; i < 30; i++){
		if (device[i] == ' '){
			for (j = 0; j < i; j++) firstDevice[j] = device[j];
		}
	}
}

void cutSecondDevice(char device[30], char secondDevice[15]){
	int i, j, k;
	for (i = 0; i < 30; i++){
		if (device[i] == ' '){
			for (j = i+1; j < i+16; j++) secondDevice[j-i-1] = device[j];
		}
	}
}

void cutCommandType(char input[1024], char commandType[15]){
		int i, j, q = 0;
		for(i = 0; i < 1024; i++){
			if(input[i] == ' '){
				q++;
				//printf("%d\n", i);	// For debugging
				for(j = 0; j < i; j++){
					commandType[j] = input[j];
				}
				break;
			}
		}
		if(q == 0){
			for(i = 0; i < 1024; i++){
				if(input[i] == ';'){break;}
				commandType[i] = input[i];
			}
		}
}

void cutBatch(char input[1024], char batch[20]){
		int i, j;
		for (i = 10; i < strlen(input); i++){
				if (input[i] == '.'){
						for (j = 10; j < i+4; j++) batch[j-10] = input[j];
						break;
				}
		}
}

void cutMessage(char input[1024], char message[30]){
		int i, j, n;
		int counter1 = 0;
		int counter2 = 0;
		for (i = 0; i < 1024; i++){
			if (input[i] == ' ') counter1++;
			if (counter1 == 2){
				for (j = i+1; j < 1024; j++){
					if (input[j] == ' ') counter2++;
					if (counter2 == 3){
						for (n = i+1; n < j; n++){
							message[n-i-1] = input[n];
						}
						return;
					}
				}
			}
		}
}

// this function is used to check if the booking information is valid
// if valid, the function will return 1, or 0.
int ifValid(char input[1024]){
	// input is the initial string enter by user
	// declare information
	int i;
	char commandType[15] = {0};
	char tenant[15] = {0};
	char device[30] = {0};
	char arrangeOrder[5] = {0};
	char batch[20] = {0};
		// first get the command type
		cutCommandType(input, commandType);
		//printf("'%s'\n", commandType);
		// see if the command type is correct
		if(strncmp(commandType, "endProgram", 10) == 0){return 1;}
		else if(strncmp(commandType, "addMeeting", 10) == 0 || strncmp(commandType, "addPresentation", 15) == 0 || strncmp(commandType, "addConference", 13) == 0 || strncmp(commandType, "bookDevice", 10) == 0){
			// check the tenant
			cutTenant(input, tenant);
			//printf("'%s'\n", tenant);
			if(!(strncmp(tenant,"tenant_A",8) == 0 || strncmp(tenant,"tenant_B",8) == 0 || strncmp(tenant,"tenant_C",8) == 0 || strncmp(tenant,"tenant_D",8) == 0 || strncmp(tenant,"tenant_E",8) == 0)){
				printf("The input tenant is incorrect!\n");
				return 0;
			}
			// check the device
			cutDevice(input, commandType, device);
			//printf("%d\n", strlen(device));
			// for addMeeting
			if(strncmp(commandType, "addMeeting", 10) == 0){
				if(!(strlen(device) == 0 || strncmp(device,"projector_2K screen_100",23) == 0 || strncmp(device,"projector_2K screen_150",23) == 0 || strncmp(device,"projector_4K screen_100",23) == 0 || strncmp(device,"projector_4K screen_150",23) == 0 || strncmp(device,"webcam_FHD monitor_50",21) == 0 || strncmp(device,"webcam_FHD monitor_75",21) == 0 || strncmp(device,"webcam_UHD monitor_50",21) == 0 || strncmp(device,"webcam_UHD monitor_75",21) == 0)){
					printf("The required device is incorrect!\n");
					return 0;
				}
			}
			else if(strncmp(commandType, "addPresentation", 15) == 0 || strncmp(commandType, "addConference", 13) == 0){
				if(!(strncmp(device,"projector_2K screen_100",23) == 0 || strncmp(device,"projector_2K screen_150",23) == 0 || strncmp(device,"projector_4K screen_100",23) == 0 || strncmp(device,"projector_4K screen_150",23) == 0 || strncmp(device,"webcam_FHD monitor_50",21) == 0 || strncmp(device,"webcam_FHD monitor_75",21) == 0 || strncmp(device,"webcam_UHD monitor_50",21) == 0 || strncmp(device,"webcam_UHD monitor_75",21) == 0)){
					printf("The required device is incorrect!\n");
					return 0;
				}
			}
			else if(strncmp(commandType, "bookDevice", 10) == 0){
				if(!(strncmp(device,"webcam_FHD",10) == 0 || strncmp(device,"webcam_UHD",10) == 0 || strncmp(device,"monitor_50",10) == 0 || strncmp(device,"monitor_75",10) == 0 || strncmp(device,"projector_2K",12) == 0 || strncmp(device,"projector_4K",10) == 0 || strncmp(device,"screen_100",10) == 0 || strncmp(device,"screen_150",10) == 0)){
					printf("The required device is incorrect!\n");
					return 0;
				}
			}
		}
		else if(strncmp(commandType, "printBookings", 13) == 0 || strncmp(commandType,"addBatch",8) == 0){
			if(strncmp(commandType, "printBookings", 13) == 0){
				// cut the arrange order out
				int q = 0;
				for(i = 0; i < strlen(input); i++){
					if(input[i] == '-'){
						for(q = i + 1; q < strlen(input); q++){
							if(input[q] == ';'){
								break;
							}    
							arrangeOrder[q - (i + 1)] = input[q];
						}   
						break;
					}
				}
				// check the arrange order
				if(!(strncmp(arrangeOrder,"fcfs",4) == 0 || strncmp(arrangeOrder,"prio",4) == 0 || strncmp(arrangeOrder,"ALL",3) == 0)){
					printf("The input algorithm is incorrect!\n");
					return 0;
				}
		}
		return 1;
		}
		else{  // the commandType is incorrect
			printf("The command type is incorrect!\n");
			return 0;
		}
		return 1;
}

void schedule(int p2cfd[15][2], int c2pfd[15][2], char request[1024]){
	int i, j;
	char commandType[15] = {0}; char device[30] = {0}; char callee[5] = {0}; char tenant[15] = {0}; char message[30] = {0}; char response[2] = {0};
	cutTenant(request, tenant);
		cutCommandType(request, commandType);
		cutDevice(request, commandType, device);
		cutCallee(request, callee);
		cutMessage(request, message);

		// test
		//printf("test:\n");
		//printf("commandType: %s\n", commandType);
		//printf("tenant: %s\n", tenant);
		//printf("device: %s\n", device);
		//printf("callee: %s\n", callee);
		//printf("message: %s\n", message);

		// open required files
		FILE *tenantA_A = fopen("TenantA_A.txt", "a"); FILE *tenantA_R = fopen("TenantA_R.txt", "a");
		FILE *tenantB_A = fopen("TenantB_A.txt", "a"); FILE *tenantB_R = fopen("TenantB_R.txt", "a");
		FILE *tenantC_A = fopen("TenantC_A.txt", "a"); FILE *tenantC_R = fopen("TenantC_R.txt", "a");
		FILE *tenantD_A = fopen("TenantD_A.txt", "a"); FILE *tenantD_R = fopen("TenantD_R.txt", "a");
		FILE *tenantE_A = fopen("TenantE_A.txt", "a"); FILE *tenantE_R = fopen("TenantE_R.txt", "a");

	int flag = 1; // indicate accept or reject request
	int room;
		//printf("test: '%s'\n", device);
		// ask devices(if any)
		if (strlen(device) != 0){
				char firstDevice[15] = {0}; char secondDevice[15] = {0};
				cutFirstDevice(device, firstDevice);
				cutSecondDevice(device, secondDevice);

				// for bookDevice
				if (strlen(firstDevice) == 0){
					for (i = 0; i < 15; i++) firstDevice[i] = device[i];
				}

				// test
				//printf("test: \n");
				//printf("first device: %s\n", firstDevice);
				//printf("second device: %s\n", secondDevice);

				for (i = 0; i < 2; i++){
						char child[15] = {0};
						if (i == 0){
							for (j = 0; j < 15; j++) child[j] = firstDevice[j];
						}
						else{
							for (j = 0; j < 15; j++) child[j] = secondDevice[j];
						}

						if (strncmp(child, "webcam_FHD", 10) == 0){
							// ask the first webcam_FHD child
							write(p2cfd[3][1], message, 30);
							read(c2pfd[3][0], response, 2);
							if (response[0] == '0'){ // first child rejects
								// ask the second webcam_FHD child
								write(p2cfd[4][1], message, 30);
								read(c2pfd[4][0], response, 2);
								if (response[0] == '0'){ // second child rejects
									flag = 0;
								}
							}
						}
						else if (strncmp(child, "webcam_UHD", 10) == 0){
							// ask the webcam_UHD child
							write(p2cfd[5][1], message, 30);
							read(c2pfd[5][0], response, 2);
							if (response[0] == '0'){ // child rejects
								flag = 0;
							}
						}
						else if (strncmp(child, "monitor_50", 10) == 0){
							// ask the first monitor_50 child
							write(p2cfd[6][1], message, 30);
							read(c2pfd[6][0], response, 2);
							if (response[0] == '0'){ // first child rejects
							// ask the second monitor_50 child
								write(p2cfd[7][1], message, 30);
								read(c2pfd[7][0], response, 2);
								if (response[0] == '0'){ // second child rejects
									flag = 0;
								}
							}
						}
						else if (strncmp(child, "monitor_75", 10) == 0){
							// ask the monitor_75 child
							write(p2cfd[8][1], message, 30);
							read(c2pfd[8][0], response, 2);
							if (response[0] == '0'){ // child rejects
								flag = 0;
							}
						}
						else if (strncmp(child, "projector_2K", 12) == 0){
							// ask the first projector_2k child
							write(p2cfd[9][1], message, 30);
							read(c2pfd[9][0], response, 2);
							if (response[0] == '0'){ // first child rejects
								// ask the second projector_2k child
								write(p2cfd[10][1], message, 30);
								read(c2pfd[10][0], response, 2);
								if (response[0] == '0'){ // second child rejects
									flag = 0;
								}
							}
				}
						else if (strncmp(child, "projector_4K", 12) == 0){
							// ask the projector_4k child
							write(p2cfd[11][1], message, 30);
							read(c2pfd[11][0], response, 2);
							if (response[0] == '0'){ // child rejects
								flag = 0;
							}
						}
						else if (strncmp(child, "screen_100", 10) == 0){
							// ask the first screen_100 child
							write(p2cfd[12][1], message, 30);
							read(c2pfd[12][0], response, 2);
							if (response[0] == '0'){ // first child rejects
								// ask the second screen_100 child
								write(p2cfd[13][1], message, 30);
								read(c2pfd[13][0], response, 2);
								if (response[0] == '0'){ // second child rejects
									flag = 0;
								}
							}
						}
						else if (strncmp(child, "screen_150", 10) == 0){ // screen_150
							// ask the screen_150 child 
							write(p2cfd[14][1], message, 30);
							read(c2pfd[14][0], response, 2);
							if (response[0] == '0'){ // child rejects
								flag = 0;
							}
						}
				}
		}
		// ask rooms
		if (flag == 1 && strncmp(commandType, "bookDevice", 10) != 0){
				if (atoi(callee) > 20){ // too many people, reject
						flag = 0;
				}
				else if (atoi(callee) > 10){
						// ask child processes for room
						write(p2cfd[2][1], message, 30); // sned to roomC
						read(c2pfd[2][0], response, 2);
						if (response[0] == '0') { // child rejects
							flag = 0;
						}
						else{
							room = 2; // roomC
						}
				}
				else{
						// ask roomA first
						write(p2cfd[0][1], message, 30);
						read(c2pfd[0][0], response, 2);
						if (response[0] == '0'){ // roomA rejects
							// ask roomB then
							write(p2cfd[1][1], message, 30);
							read(c2pfd[1][0], response, 2);
							if (response[0] == '0'){ // roomB rejects
								// ask roomC finally
								write(p2cfd[2][1], message, 30);
								read(c2pfd[2][0], response, 2);
								if (response[0] == '0'){ // roomC rejects
									flag = 0;
								}
								else{
									room = 2; // roomC
								}
							}
							else{
								room = 1; // roomB
							}
						}
						else{
							room = 0; // roomA
						}
				}
		}

		if (flag == 1){ // accept the request
				// write to corresponding output files
				switch(tenant[7]){
						case 'A': if (room == 0) fprintf(tenantA_A, "A %s", request);
									else if (room == 1) fprintf(tenantA_A, "B %s", request);
									else fprintf(tenantA_A, "C %s", request); break;
						case 'B': if (room == 0) fprintf(tenantB_A, "A %s", request);
									else if (room == 1) fprintf(tenantB_A, "B %s", request);
									else fprintf(tenantB_A, "C %s", request); break;
						case 'C': if (room == 0) fprintf(tenantC_A, "A %s", request);
									else if (room == 1) fprintf(tenantC_A, "B %s", request);
									else fprintf(tenantC_A, "C %s", request); break;
						case 'D': if (room == 0) fprintf(tenantD_A, "A %s", request);
									else if (room == 1) fprintf(tenantD_A, "B %s", request);
									else fprintf(tenantD_A, "C %s", request); break;
						case 'E': if (room == 0) fprintf(tenantE_A, "A %s", request);
									else if (room == 1) fprintf(tenantE_A, "B %s", request);
									else fprintf(tenantE_A, "C %s", request); break;
						default: exit(1); 
				}
				// send accept messages to all childs
				for (i = 0; i < 15; i++){
						write(p2cfd[i][1], "a", 2);
				}
		}
		else{ // reject the request
				// write to corresponding output files
				switch(tenant[7]){
						case 'A': fprintf(tenantA_R, "%s", request); break;
						case 'B': fprintf(tenantB_R, "%s", request); break;
						case 'C': fprintf(tenantC_R, "%s", request); break;
						case 'D': fprintf(tenantD_R, "%s", request); break;
						case 'E': fprintf(tenantE_R, "%s", request); break;
						default: exit(1); 
				}
				// send reject messages to all childs
				for (i = 0; i < 15; i++){
						write(p2cfd[i][1], "r", 2);
				}
		}

		// close these files
		fclose(tenantA_A); fclose(tenantA_R);
		fclose(tenantB_A); fclose(tenantB_R);
		fclose(tenantC_A); fclose(tenantC_R);
		fclose(tenantD_A); fclose(tenantD_R);
		fclose(tenantE_A); fclose(tenantE_R);
}

void printBookings(int code, int p2cfd[15][2], int c2pfd[15][2]){
		// code: 0 -> fcfs
		// code: 1 -> prio
		int i;
		
		// clear required files
		FILE *tenantA_A = fopen("TenantA_A.txt", "wb"); FILE *tenantA_R = fopen("TenantA_R.txt", "wb");
		FILE *tenantB_A = fopen("TenantB_A.txt", "wb"); FILE *tenantB_R = fopen("TenantB_R.txt", "wb");
		FILE *tenantC_A = fopen("TenantC_A.txt", "wb"); FILE *tenantC_R = fopen("TenantC_R.txt", "wb");
		FILE *tenantD_A = fopen("TenantD_A.txt", "wb"); FILE *tenantD_R = fopen("TenantD_R.txt", "wb");
		FILE *tenantE_A = fopen("TenantE_A.txt", "wb"); FILE *tenantE_R = fopen("TenantE_R.txt", "wb");
		fclose(tenantA_A); fclose(tenantA_R);
		fclose(tenantB_A); fclose(tenantB_R);
		fclose(tenantC_A); fclose(tenantC_R);
		fclose(tenantD_A); fclose(tenantD_R);
		fclose(tenantE_A); fclose(tenantE_R);
		
		// initialize child processes
		for (i = 0; i < 15; i++){
				write(p2cfd[i][1], "i", 2);
		}
		if (code == 0){ // fcfs
			// open fcfs records file
				FILE *booking = fopen("Booking.txt", "r");
				// schedule requests
				char request[1024] = {0};
				while (fgets(request, 1024, booking) != NULL){
					// test
					//printf("test: %s\n", request);

					schedule(p2cfd, c2pfd, request);
				}
		}
		else { // prio
			// open priority records files
				FILE *conference = fopen("Conference.txt", "r");
				FILE *presentation = fopen("Presentation.txt", "r");
				FILE *meeting = fopen("Meeting.txt", "r");
				FILE *device = fopen("Device.txt", "r");
				// schedule requests
				char request[1024] = {0};
				while(fgets(request, 1024, conference) != NULL){
					schedule(p2cfd, c2pfd, request);
				}
				while(fgets(request, 1024, presentation) != NULL){
					schedule(p2cfd, c2pfd, request);
				}
				while(fgets(request, 1024, meeting) != NULL){
					schedule(p2cfd, c2pfd, request);
				}
				while(fgets(request, 1024, device) != NULL){
					schedule(p2cfd, c2pfd, request);
				}
		}
}

//this function is used to print out all the records
void printOutput(int code){
    // code: 0 -> fcfs
    // code: 1 -> prio
    FILE *openFile[5];
    char tenant[5][10] = {"Tenant_A","Tenant_B","Tenant_C","Tenant_D","Tenant_E"};
    char request[1024] = {0};   // use to store a term of request
    char temp[1024] = {0};
    openFile[0] = fopen("TenantA_A.txt","r");
    openFile[1] = fopen("TenantB_A.txt","r");
    openFile[2] = fopen("TenantC_A.txt","r");
    openFile[3] = fopen("TenantD_A.txt","r");
    openFile[4] = fopen("TenantE_A.txt","r");
    printf("\n");
    if(code == 0){
        printf("*** Room Booking - ACCEPTED / FCFS ***\n");
    }else if (code == 1){
        printf("*** Room Booking - ACCEPTED / PRIO ***\n");
    }
    printf("\n");
    int i = 0;
    for(;i<5;i++){
        printf("%s has the following bookings:\n",tenant[i]);
        printf("\n");
        printf("Date         Start   End     Type          Room       Device\n");
        printf("===========================================================================\n");     
        while(fgets(request, 1024, openFile[i]) != NULL){
        	char printRequest[1024] = {0}; // use to store the print request
            char roomNum;
            char type[15] = {0};
    		char time[20] = {0};
   		    char date[11] = {0};
    		char start[6] = {0};
    		char duration[5] = {0};
    		char end[6] = {0};
    		char room[7] = {0};
    		char device[30] = {0};
    		char device1[15] = {0};
    		char device2[15] = {0};
            // get the room information
            roomNum = request[0];  
            if(roomNum == 'A'){
            	strcpy(room,"room_A");
            }else if(roomNum == 'B'){
            	strcpy(room,"room_B");
            }else if(roomNum == 'C'){
            	strcpy(room,"room_C");
            }else{
            	strcpy(room,"*     ");
            }
            strncpy(printRequest,request+2,sizeof(request)-2);  // the left request except room information is stored in printRequest
            cutTime(printRequest,time);
            // get date
            strncpy(date,time,10);
            // get start time
            strncpy(start,time+11,5);
            // get end time
            char hour[3] = "";
            int endTime = 0;
            char offset[5] = ":00";
            strncpy(hour,start,2);  // get the start time
            cutDuration(printRequest,duration);  // get the duration
            // calculate the end time
            endTime = atoi(hour) + atoi(duration);
			
			if (endTime > 24){
				endTime = endTime-24;
			}
			
            if(endTime < 10){
            	end[0] = '0';
            	end[1] = (char)(endTime+48);
            	strcat(end,offset);
            }else if(endTime>=10 && endTime < 20){
            	end[0] = '1';
            	end[1] = (char)(endTime-10+48);
            	strcat(end,offset);
            }else{
            	end[0] = '2';
            	end[1] = (char)(endTime-20+48);
            	strcat(end,offset);
            }
            cutCommandType(printRequest,type);
            // bookDevice dont need room
            if (strncmp(type, "bookDevice", 10) == 0) strcpy(room,"*     ");
            // get device information
            cutDevice(printRequest,type,device);
            if(strcmp(device,"") == 0){
            	strcpy(device,"*    ");
            }else if(strncmp(type,"addMeeting",10) == 0 || strncmp(type,"addPresentation",15) == 0 || strncmp(type,"addConference",13) == 0){
                cutFirstDevice(device,device1);
                cutSecondDevice(device,device2);
            }
            // get the type
            if(strncmp(type,"addMeeting",10) == 0){
            	strcpy(type,"Meeting       ");
            }else if(strncmp(type,"addPresentation",15) == 0){
            	strcpy(type,"Presentation  ");
            }else if(strncmp(type,"addConference",13) == 0){
            	strcpy(type,"Conference    ");
            }else{
            	strcpy(type,"*             ");
            }
            if(strcmp(device1,"") == 0){  // no device need or just one device need
                printf("%s   %s   %s   %s%s     %s\n",date,start,end,type,room,device);
            }else{  // there are 2 devices are needed
                printf("%s   %s   %s   %s%s     %s\n",date,start,end,type,room,device1);
                printf("                                                      %s\n",device2);
            } 
        }
        printf("\n");
    }
    printf("   - End -\n");
    printf("\n");
    printf("===========================================================================\n");
    printf("\n");
    i = 0;
    for(;i<5;i++){
        fclose(openFile[i]);
    }
    openFile[0] = fopen("TenantA_R.txt","r");
    openFile[1] = fopen("TenantB_R.txt","r");
    openFile[2] = fopen("TenantC_R.txt","r");
    openFile[3] = fopen("TenantD_R.txt","r");
    openFile[4] = fopen("TenantE_R.txt","r");
    if(code == 0){
        printf("*** Room Booking - REJECTED / FCFS ***\n");
    }else if(code == 1){
        printf("*** Room Booking - REJECTED / PRIO ***\n");
    }
    printf("\n");
    i = 0;
    for(;i<5;i++){
        int counter = 0;
        while(fgets(temp, 1024, openFile[i]) != NULL){
            counter++;
        }
        rewind(openFile[i]);

        printf("%s (there are %d bookings rejected):\n",tenant[i],counter);
        printf("\n");
        printf("Date         Start   End     Type          Device\n");
        printf("===========================================================================\n");     
        while(fgets(request, 1024, openFile[i]) != NULL){
            char type[15] = {0};
    		char time[20] = {0};
   		    char date[11] = {0};
    		char start[6] = {0};
    		char duration[5] = {0};
    		char end[6] = {0};
    		char device[30] = {0};
    		char device1[15] = {0};
    		char device2[15] = {0};
            cutTime(request,time);
            // get date
            strncpy(date,time,10);
            // get start time
            strncpy(start,time+11,5);
            // get end time
            char hour[3] = "";
            int endTime = 0;
            char offset[5] = ":00";
            strncpy(hour,start,2);  // get the start time
            cutDuration(request,duration);  // get the duration
            // calculate the end time
            endTime = atoi(hour) + atoi(duration);
			
			if (endTime > 24){
				endTime = endTime-24;
			}
			
            if(endTime < 10){
            	end[0] = '0';
            	end[1] = (char)(endTime+48);
            	strcat(end,offset);
            }else if(endTime>=10 && endTime < 20){
            	end[0] = '1';
            	end[1] = (char)(endTime-10+48);
            	strcat(end,offset);
            }else{
            	end[0] = '2';
            	end[1] = (char)(endTime-20+48);
            	strcat(end,offset);
            }
            cutCommandType(request,type);
            // get device information
            cutDevice(request,type,device);
            if(strcmp(device,"") == 0){
            	strcpy(device,"*      ");
            }else if(strncmp(type,"addMeeting",10) == 0 || strncmp(type,"addPresentation",15) == 0 || strncmp(type,"addConference",13) == 0){
                cutFirstDevice(device,device1);
                cutSecondDevice(device,device2);
            }
            // get the type
            if(strncmp(type,"addMeeting",10) == 0){
            	strcpy(type,"Meeting       ");
            }else if(strncmp(type,"addPresentation",15) == 0){
            	strcpy(type,"Presentation  ");
            }else if(strncmp(type,"addConference",13) == 0){
            	strcpy(type,"Conference    ");
            }else{
            	strcpy(type,"*             ");
            }
            if(strcmp(device1,"") == 0){  // no device need or just one device need
                printf("%s   %s   %s   %s%s\n",date,start,end,type,device);
            }else{  // there are 2 devices are needed
                printf("%s   %s   %s   %s%s\n",date,start,end,type,device1);
                printf("                                           %s\n",device2);
            } 
        }
        printf("\n");
    }
    printf("   - End -\n");
    printf("\n");
    printf("===========================================================================\n");
    i = 0;
    for(;i<5;i++){
        fclose(openFile[i]);
    }   
}

void printSummary(int code, int p2cfd[15][2], int c2pfd[15][2]){
		// code: 0 -> fcfs
		// code: 1 -> prio
		int i, n;
	FILE *booking = fopen("Booking.txt", "r"); FILE *invalid = fopen("Invalid.txt", "r");
	FILE *tenantA_A = fopen("TenantA_A.txt", "r"); FILE *tenantA_R = fopen("TenantA_R.txt", "r");
	FILE *tenantB_A = fopen("TenantB_A.txt", "r"); FILE *tenantB_R = fopen("TenantB_R.txt", "r");
	FILE *tenantC_A = fopen("TenantC_A.txt", "r"); FILE *tenantC_R = fopen("TenantC_R.txt", "r");
	FILE *tenantD_A = fopen("TenantD_A.txt", "r"); FILE *tenantD_R = fopen("TenantD_R.txt", "r");
	FILE *tenantE_A = fopen("TenantE_A.txt", "r"); FILE *tenantE_R = fopen("TenantE_R.txt", "r");

	int numOfValidRequest = 0, numOfInvalidRequest = 0, numOfAcceptedRequest = 0, numOfRejectedRequest = 0, totalNumOfRequest = 0;
	char request[1024] = {0}; char utilization[6] = {0};
	// calculate statistics
	while (fgets(request, 1024, booking) != NULL) numOfValidRequest++;
	while (fgets(request, 1024, invalid) != NULL) numOfInvalidRequest++;
	while (fgets(request, 1024, tenantA_A) != NULL) numOfAcceptedRequest++;
	while (fgets(request, 1024, tenantB_A) != NULL) numOfAcceptedRequest++;
	while (fgets(request, 1024, tenantC_A) != NULL) numOfAcceptedRequest++;
	while (fgets(request, 1024, tenantD_A) != NULL) numOfAcceptedRequest++;
	while (fgets(request, 1024, tenantE_A) != NULL) numOfAcceptedRequest++;
	while (fgets(request, 1024, tenantA_R) != NULL) numOfRejectedRequest++;
	while (fgets(request, 1024, tenantB_R) != NULL) numOfRejectedRequest++;
	while (fgets(request, 1024, tenantC_R) != NULL) numOfRejectedRequest++;
	while (fgets(request, 1024, tenantD_R) != NULL) numOfRejectedRequest++;
	while (fgets(request, 1024, tenantE_R) != NULL) numOfRejectedRequest++;

	totalNumOfRequest = numOfValidRequest + numOfInvalidRequest;
	float validPercentage = 100.0 * numOfValidRequest / totalNumOfRequest;
	float acceptPercentage = 100.0 * numOfAcceptedRequest / totalNumOfRequest;
	float rejectPercentage = 100.0 * numOfRejectedRequest / totalNumOfRequest;

	printf("\n");
	if (code == 0){
		printf("*** Room Booking Manager - Summary Report ***\n");
		printf("\n");
		printf("Performance:\n");
		printf("\n");
		printf("  For FCFS:\n");
	}
	else{
		printf("  For PRIO:\n");
	}

	printf("            Total Number of Bookings Received: %d (%.1f%)\n", numOfValidRequest, validPercentage);
	printf("                  Number of Bookings Assigned: %d (%.1f%)\n", numOfAcceptedRequest, acceptPercentage);
	printf("                  Number of Bookings Rejected: %d (%.1f%)\n", numOfRejectedRequest, rejectPercentage);
	printf("\n");
	printf("            Utilization of Time Slot:\n");
	// get utilization from child processes
	write(p2cfd[0][1], "s", 2);
	read(c2pfd[0][0], utilization, 6);
	n = atoi(utilization);
	printf("                 room_A          - %.1f%\n", n*100.0/168.0);
	write(p2cfd[1][1], "s", 2);
	read(c2pfd[1][0], utilization, 6);
	n = atoi(utilization);
	printf("                 room_B          - %.1f%\n", n*100.0/168.0);
	write(p2cfd[2][1], "s", 2);
	read(c2pfd[2][0], utilization, 6);
	n = atoi(utilization);
	printf("                 room_C          - %.1f%\n", n*100.0/168.0);
	write(p2cfd[3][1], "s", 2);
	read(c2pfd[3][0], utilization, 6);
	n = atoi(utilization);
	printf("                 webcam_FHD(1)   - %.1f%\n", n*100.0/168.0);
	write(p2cfd[4][1], "s", 2);
	read(c2pfd[4][0], utilization, 6);
	n = atoi(utilization);
	printf("                 webcam_FHD(2)   - %.1f%\n", n*100.0/168.0);
	write(p2cfd[5][1], "s", 2);
	read(c2pfd[5][0], utilization, 6);
	n = atoi(utilization);
	printf("                 webcam_UHD      - %.1f%\n", n*100.0/168.0);
	write(p2cfd[6][1], "s", 2);
	read(c2pfd[6][0], utilization, 6);
	n = atoi(utilization);
	printf("                 monitor_50(1)   - %.1f%\n", n*100.0/168.0);
	write(p2cfd[7][1], "s", 2);
	read(c2pfd[7][0], utilization, 6);
	n = atoi(utilization);
	printf("                 monitor_50(2)   - %.1f%\n", n*100.0/168.0);
	write(p2cfd[8][1], "s", 2);
	read(c2pfd[8][0], utilization, 6);
	n = atoi(utilization);
	printf("                 monitor_75      - %.1f%\n", n*100.0/168.0);
	write(p2cfd[9][1], "s", 2);
	read(c2pfd[9][0], utilization, 6);
	n = atoi(utilization);
	printf("                 projector_2K(1) - %.1f%\n", n*100.0/168.0);
	write(p2cfd[10][1], "s", 2);
	read(c2pfd[10][0], utilization, 6);
	n = atoi(utilization);
	printf("                 projector_2K(2) - %.1f%\n", n*100.0/168.0);
	write(p2cfd[11][1], "s", 2);
	read(c2pfd[11][0], utilization, 6);
	n = atoi(utilization);
	printf("                 projector_4K    - %.1f%\n", n*100.0/168.0);
	write(p2cfd[12][1], "s", 2);
	read(c2pfd[12][0], utilization, 6);
	n = atoi(utilization);
	printf("                 screen_100(1)   - %.1f%\n", n*100.0/168.0);
	write(p2cfd[13][1], "s", 2);
	read(c2pfd[13][0], utilization, 6);
	n = atoi(utilization);
	printf("                 screen_100(2)   - %.1f%\n", n*100.0/168.0);
	write(p2cfd[14][1], "s", 2);
	read(c2pfd[14][0], utilization, 6);
	n = atoi(utilization);
	printf("                 screen_150      - %.1f%\n", n*100.0/168.0);
	printf("\n");
	printf("            Invalid request(s) made: %d\n", numOfInvalidRequest);
	printf("\n");
}


int processRequest(char input[1024], int p2cfd[15][2], int c2pfd[15][2]){
	char commandType[15] = {0};
	int i, j, n, code;
	cutCommandType(input, commandType);
	
	// open files
		FILE *booking = fopen("Booking.txt", "a");
		FILE *conference = fopen("Conference.txt", "a");
		FILE *presentation = fopen("Presentation.txt", "a");
		FILE *meeting = fopen("Meeting.txt", "a");
		FILE *device = fopen("Device.txt", "a");
	
	// handle request 
		if (ifValid(input) == 0){ // invalid input
			FILE *invalid = fopen("Invalid.txt", "a");
			fprintf(invalid, "%s", input);
			fclose(invalid);
			return 0;
		}

		if (strncmp(commandType, "addConference", 13) == 0){
				fprintf(conference, "%s", input);
				fprintf(booking, "%s", input);
				printf("-> [Pending]\n");
				code = 0;
		}
		else if (strncmp(commandType, "addPresentation", 15) == 0){
				fprintf(presentation, "%s", input);
				fprintf(booking, "%s", input);
				printf("-> [Pending]\n");
				code = 0;
		}
		else if (strncmp(commandType, "addMeeting", 10) == 0){
				fprintf(meeting, "%s", input);
				fprintf(booking, "%s", input);
				printf("-> [Pending]\n");
				code = 0;
		}
		else if (strncmp(commandType, "bookDevice", 10) == 0){
				fprintf(device, "%s", input);
				fprintf(booking, "%s", input);
				printf("-> [Pending]\n");
				code = 0;
		}
		else if (strncmp(commandType, "addBatch", 8) == 0){
			char filename[20] = {0};
			cutBatch(input, filename);
				FILE *batch = fopen(filename, "r");
				char request[1024] = {0};
				while (fgets(request, 1024, batch) != NULL){
						processRequest(request, p2cfd, c2pfd);
				}
				printf("-> [Pending]\n");
				code = 0;
				fclose(batch);
		}
		else if (strncmp(commandType, "printBookings", 13) == 0){
				if (input[15] == 'f'){
						printBookings(0, p2cfd, c2pfd);
						printOutput(0);
				}
				else if (input[15] == 'p'){
						printBookings(1, p2cfd, c2pfd);
						printOutput(1);
				}
				else{ // ALL
						printBookings(0, p2cfd, c2pfd);
						printOutput(0);
						printBookings(1, p2cfd, c2pfd);
						printOutput(1);
						printBookings(0, p2cfd, c2pfd);
						printSummary(0, p2cfd, c2pfd);
						printBookings(1, p2cfd, c2pfd);
						printSummary(1, p2cfd, c2pfd);
				}
				printf("-> [Done!]\n");
				code = 0;
		}
		else{ // end the program
				code = 1;
		}
		
		// close files
	fclose(booking);
	fclose(conference);
	fclose(presentation);
	fclose(meeting);
	fclose(device);
	
	return code;
}

int main(int argc, char *argv[]){

	printf("\n");
	printf("~~ WELCOME TO PolySME ~~\n");	// Print the welcome message

	// pipe creation
	int i, j, n;
	int p2cfd[15][2]; // parent to child pipes
	int c2pfd[15][2]; // child to parent pipes
	
	for (i = 0; i < 15; i++){
		if (pipe(p2cfd[i]) < 0){
			printf("Errors when creating pipes!\n");
			exit(1);
		}
		if (pipe(c2pfd[i]) < 0){
			printf("Errors when creating pipes!\n");
			exit(1);
		}
	}
	
	// child processes creation and initialization
	int parentid, myid, pid, index = -1;
	int timeslots[7][24]; // the test schedule is seven days (5.10-5.16)
	char message[30] = {0};
	parentid = getpid();
	for (i = 0; i < 15; i++){ // create 15 child processes
		if (getpid() == parentid){
			fork();
			if (getpid() != parentid) index = i;
		}
	}

	// test
	//printf("test: %d\n", index);
	
	if (index != -1){
		// test
		//printf("Child: %d %d\n", getpid(), index);

		// child processes
		// index: 0, 1, 2 -> room
		// index: 3, 4, 5 -> webcams
		// index: 6, 7, 8 -> monitors
		// index: 9, 10, 11 -> projectors
		// index: 12, 13, 14 -> projection screens
		// message format:  YYYY-MM-DD hh:mm n.n
		// message example: 2021-05-16 10:00 3.0
		
		// close unused ends of pipes
		close(p2cfd[index][1]);
		close(c2pfd[index][0]);
		
		// read from parent process
		while ((n = read(p2cfd[index][0], message, 30)) > 0){
			// test
			//printf("test: %s %d %d\n", message, getpid(), index);
			// initialize
			int startPoint = 0;
			int valid = 1;
			char date[11] = {0}; char time[6] = {0}; char duration[5] = {0};
			// terminate
			if (message[0] == 't') break;
			// initialize the timeslots
			if (message[0] == 'i'){
				for (i = 0; i < 7; i++){
					for (j = 0; j < 24; j++) timeslots[i][j] = 0;
				}
				continue;
			}
			// accept the booking
			if (message[0] == 'a'){
				for (i = 0; i < 7; i++){
					for (j = 0; j < 24; j++){
						if (timeslots[i][j] == 2) timeslots[i][j] = 1;
					}
				}
				continue;
			} 
			// reject the booking
			if (message[0] == 'r'){
				for (i = 0; i < 7; i++){
					for (j = 0; j < 24; j++){
						if (timeslots[i][j] == 2) timeslots[i][j] = 0;
					}
				}
				continue;
			}
			// calculate utilization of timeslots
			if (message[0] == 's'){
					int utilized = 0;
					char utilization[6] = {0};
					for (i = 0; i < 7; i++){
							for (j = 0; j < 24; j++){
									if (timeslots[i][j] == 1) utilized++;
							}
					}
					sprintf(utilization, "%d", utilized);
					write(c2pfd[index][1], utilization, 6);
					continue;
			}
			
			// test
			//printf("test: %s %d %d\n", message, getpid(), index);

			// message handling
			// date: 
			for (i = startPoint; i < 30; i++){
				if (message[i] == ' '){
					for (j = startPoint; j < i; j++) date[j-startPoint] = message[j];
					startPoint = i+1;
					break;
				}
			}
			for (i = startPoint; i < 30; i++){
				if (message[i] == ' '){
					for (j = startPoint; j < i; j++) time[j-startPoint] = message[j];
					startPoint = i+1;
					break;
				}
			}
			for (i = startPoint; i < 30; i++){
				if (message[i] == '.'){
					for (j = startPoint; j <= i+1; j++) duration[j-startPoint] = message[j];
					break;
				}
			}

			// test 
			//printf("test:\n");
			//printf("date: %s\n", date);
			//printf("time: %s\n", time);
			//printf("duration: %s\n", duration);
	
			// check whether the requested time slot is idle
			char day[6] = {0}; char hour[6] = {0}; char dura[10] = {0};

			for (i = 10; i >= 0; i--){
				if (date[i] == '-'){
					for (j = i+1; j <= 10; j++) day[j-i-1] = date[j];
					break;
				}
			}
			strncpy(hour, time, 2);
			hour[2] = '\0';
			for (i = 0; i < 10; i++){
				if (duration[i] == '.'){
					for (j = 0; j < i; j++) dura[j] = duration[j];
					break;
				}
			}

			int intDay = atoi(day);
			int h = atoi(hour);
			int d = atoi(dura);

			// test
			//printf("test:\n");
			//printf("date: %d\n", intDay);
			//printf("hour: %d\n", h);
			//printf("duration: %d\n", d);

			for (i = h; i < h+d; i++){ // check timeslots
				if (i < 24){
					if (timeslots[intDay-10][i] == 1){
						valid = 0;
						break;
					}
				}
				else{
					if (timeslots[intDay-10+1][i-24] == 1){
						valid = 0;
						break;
					}
				}
			}

			// test
			//printf("test: \n");
			//for (i = 0; i < 7; i++){
			//	for (j = 0; j < 24; j++){
			//		printf("%d ", timeslots[i][j]);
			//	}
			//	printf("\n");
			//}
			//printf("valid: %d\n", valid);

			if (valid == 1){ // the request can be fulfilled
				for (i = h; i < h+d; i++){
					if (i < 24){
						timeslots[intDay-10][i] = 2;
					}
					else{
						timeslots[intDay-10+1][i-24] = 2;
					}
				}
				write(c2pfd[index][1], "1", 2); // 1 indicates valid request
			}
			else{ // the request cannot be fulfilled
				write(c2pfd[index][1], "0", 2); // 0 indicates invalid request
			}	
		}
		// close other ends of pipes
		close(c2pfd[index][1]);
		close(p2cfd[index][0]);
		
		exit(0);
	}
	else if (getpid() == parentid){ 
			// parent process
			// Handle the user input and decide the command type
			// printf("Parent\n");	//For debugging
		
		// close unused ends of pipes
		for (i = 0; i < 15; i++){
				close(p2cfd[i][0]);
				close(c2pfd[i][1]);
		}

			// clear all records in the text file
			FILE *booking = fopen("Booking.txt", "wb"); // this file is for fcfs 
			FILE *conference = fopen("Conference.txt", "wb"); // the following four files are for priority
			FILE *presentation = fopen("Presentation.txt", "wb");
			FILE *meeting = fopen("Meeting.txt", "wb");
			FILE *device = fopen("Device.txt", "wb");
			FILE *invalid = fopen("Invalid.txt", "wb"); // this file is to store invalid requests
			fclose(booking);
			fclose(conference);
			fclose(presentation);
			fclose(meeting);
			fclose(device);
			fclose(invalid);

			while(1){
				// gets input from the user
				char input[1024] ={0};
				printf("Please enter booking: \n");		// Prompt the user to enter inputs
				fgets(input, 1024, stdin);
					
				// test
				//printf("%s\n", input);

				// handle the booking request
				int code = 0;
				code = processRequest(input, p2cfd, c2pfd);
				if (code == 1){
					// print ending messages
					printf("-> Bye!\n");
					// send termination messages to all childs
					for (i = 0; i < 15; i++){
						write(p2cfd[i][1], "t", 2);
					}
					// close other ends of pipes
					for (i = 0; i < 15; i++){
						close(p2cfd[i][1]);
						close(c2pfd[i][0]);
					}
					break;
				}
			}
	}
	
	// ending
	wait(NULL);
	exit(0);
}
