#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nss.h>
#include <netdb.h>
#include <netinet/in.h>

enum nss_status _nss_hoge_gethostbyname2_r (const char *name, int af, struct hostent *ret, char *buf, size_t buflen, int *errnop, int *h_errnop) {
	*errnop = *h_errnop = 0;

	printf("C_LOOKUP_2 >>> %d %s \n", af, name);

	if (af != AF_INET) {
		return NSS_STATUS_NOTFOUND;
	}
	if (strstr(name, ".hoge") == NULL) {
		return NSS_STATUS_NOTFOUND;
	}

	ret->h_name = (char*)name;
	ret->h_aliases = calloc(sizeof(char*), 1);
	ret->h_addrtype = af;
	ret->h_length = 4;
	ret->h_addr_list = calloc(sizeof(char*), 2);
	unsigned char *addr = ret->h_addr_list[0] = calloc(sizeof(char), 4);
	addr[0] = 1; addr[1] = 14; addr[2] = 5; addr[3] = 14;

	return NSS_STATUS_SUCCESS;
}
enum nss_status _nss_hoge_gethostbyname_r (const char *name, struct hostent *ret, char *buf, size_t buflen, int *errnop, int *h_errnop) {
	printf("C_LOOKUP_1 >>> %s \n", name);
	return _nss_hoge_gethostbyname2_r(name, AF_INET, ret, buf, buflen, errnop, h_errnop);
}

int main () {
	struct hostent *result = gethostbyname2("narusejun.com.hoge", AF_INET);
	if (result == NULL) {
		puts("Not Found");
		return 0;
	}

	printf("h_name: %s\n", result->h_name);
	for (int i = 0; result->h_aliases[i] != NULL; i++) {
		printf("h_aliases[%d]: %s\n", i, result->h_aliases[i]);
	}
	printf("h_addrtype: %d\n", result->h_addrtype);
	printf("h_length: %d\n", result->h_length);
	for (int i = 0; result->h_addr_list[i] != NULL; i++) {
		unsigned char *addr = result->h_addr_list[i];
		printf("h_addr_list[%d]: %d.%d.%d.%d\n", i, addr[0], addr[1], addr[2], addr[3]);
	}

	return 0;
}
