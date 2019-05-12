install: libnss_hoge.so.2
	install -m 0644 $< /lib

libnss_hoge.so.2: hoge.go
	go build -buildmode=c-shared -o $@ $<
	strip $@

test:
	go run hoge.go

clean:
	rm -f libnss_hoge.so.2 libnss_hoge.so.h
