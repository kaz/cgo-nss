install: libnss_hoge.so.2
	install -m 0644 $< /lib

libnss_hoge.so.2: nss.c hoge.a
	gcc -shared -o $@ -Wl,-Bsymbolic,-soname,$@ nss.c hoge.a
	strip $@

hoge.a: hoge.go
	go build -buildmode=c-archive hoge.go

test:
	go run hoge.go

clean:
	rm -f hoge.a hoge.h libnss_hoge.so.2
