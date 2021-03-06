/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "ClientToPlaces.h"

void client_to_places_1(char *host, char* returnCity, char* state)
{
	CLIENT *clnt;
	returnTypeC  *result_1;
	city  ctop_1_arg;
    places** airportList;

#ifndef	DEBUG
	clnt = clnt_create (host, CLIENT_TO_PLACES, CLIENT_TO_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
    strcpy(ctop_1_arg.city, returnCity);
    strcpy(ctop_1_arg.state, state);
	result_1 = ctop_1(&ctop_1_arg, clnt);
	if (result_1 == (returnTypeC *) NULL) {
		clnt_perror (clnt, "call failed");
	}

    airportList = &result_1->returnTypeC_u.resultC;
    
	//if recieve failed call, tell the user
    if(strcmp((*airportList)->name,"FAILED") == 0){
	printf("%s  \n", "Please be more specific or use a different city!");
    printf("%s  \n", "Some cities have: City, Township etc. in their name!");
	printf("%s  \n", "Proper format:");
	printf("%s  \n", "./ClientToPlaces_client localhost 'city' ST");
	}
    else{
		//print out the city name, state, etc. for the head
	printf("%s, %s: %g, %.2f\n", (*airportList)->name, (*airportList)->state , (*airportList)->lat, (*airportList)->lon);
	(*airportList) = (*airportList)->next;
    
		//print out the city name, state etc. for the bodies
        for(int i = 0; i < 5; i++){
		printf("code=%s, name=%s, state=%s, distance: %.2f miles\n", (*airportList)->code, (*airportList)->name, (*airportList)->state, (*airportList)->dist);
		(*airportList) = (*airportList)->next;
		}
    }

    clnt_freeres(clnt, (xdrproc_t)xdr_returnTypeC, (char *)result_1);

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
  char *host;
  char* returnCity;
  char* state;
  if (argc < 2) {
	  printf ("usage: %s server_host\n", argv[0]);
	  exit (1);
  }
  host = argv[1];
  returnCity = argv[2];
  state = argv[3];
  client_to_places_1(host, returnCity, state);
exit (0);
}
