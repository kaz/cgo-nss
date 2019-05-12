package main

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <nss.h>
// #include <netdb.h>
// #include <netinet/in.h>
// #define PTR_SIZE sizeof(char*)
import "C"

import (
	"fmt"
	"net"
	"strings"
)

//export _nss_hoge_gethostbyname2_r
func _nss_hoge_gethostbyname2_r(name *C.char, af C.int, ret *C.struct_hostent, buf *C.char, buflen C.size_t, errnop *C.int, h_errnop *C.int) C.enum_nss_status {
	*errnop = 0
	*h_errnop = 0

	fmt.Printf("GO_LOOKUP_2 >>> %d %s\n", af, C.GoString(name))

	if af != C.AF_INET {
		return C.NSS_STATUS_NOTFOUND
	}

	host := C.GoString(name)
	if !strings.HasSuffix(host, ".hoge") {
		return C.NSS_STATUS_NOTFOUND
	}

	ret.h_name = name
	ret.h_aliases = (**C.char)(C.calloc(C.PTR_SIZE, 1))
	ret.h_addrtype = af
	ret.h_length = 4
	ret.h_addr_list = (**C.char)(C.calloc(C.PTR_SIZE, 2))
	*ret.h_addr_list = C.CString(string([]byte{1, 14, 5, 14}))

	return C.NSS_STATUS_SUCCESS
}

//export _nss_hoge_gethostbyname_r
func _nss_hoge_gethostbyname_r(name *C.char, ret *C.struct_hostent, buf *C.char, buflen C.size_t, errnop *C.int, h_errnop *C.int) C.enum_nss_status {
	fmt.Printf("GO_LOOKUP_1 >>> %s\n", C.GoString(name))
	return _nss_hoge_gethostbyname2_r(name, C.AF_INET, ret, buf, buflen, errnop, h_errnop)
}

func main() {
	addrs, err := net.LookupIP("narusejun.com.hoge")
	if err != nil {
		panic(err)
	}
	for _, addr := range addrs {
		fmt.Println(addr.String())
	}
}
