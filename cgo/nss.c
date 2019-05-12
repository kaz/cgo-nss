#include <nss.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include "hoge.h"

enum nss_status _nss_hoge_gethostbyname2_r (const char *name, int af, struct hostent *ret, char *buf, size_t buflen, int *errnop, int *h_errnop) {
	*errnop = *h_errnop = 0;

	printf("CGO_LOOKUP_2 >>> %d %s \n", af, name);

	if (af != AF_INET) {
		return NSS_STATUS_NOTFOUND;
	}

	char* result = lookup_instance((char*)name);
	if (result == NULL) {
		return NSS_STATUS_NOTFOUND;
	}

	ret->h_name = (char*)name;
	ret->h_aliases = calloc(sizeof(char*), 1);
	ret->h_addrtype = af;
	ret->h_length = 4;
	ret->h_addr_list = calloc(sizeof(char*), 2);
	ret->h_addr_list[0] = result;

	return NSS_STATUS_SUCCESS;
}
enum nss_status _nss_hoge_gethostbyname_r (const char *name, struct hostent *ret, char *buf, size_t buflen, int *errnop, int *h_errnop) {
	printf("CGO_LOOKUP_1 >>> %s \n", name);
	return _nss_hoge_gethostbyname2_r(name, AF_INET, ret, buf, buflen, errnop, h_errnop);
}
