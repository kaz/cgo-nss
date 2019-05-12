package main

import (
	"C"
	"fmt"
	"net"
	"strings"
)

//export lookup_instance
func lookup_instance(name *C.char) *C.char {
	host := C.GoString(name)
	if !strings.HasSuffix(host, ".hoge") {
		return nil
	}
	return C.CString(string([]byte{1, 14, 5, 14}))
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
