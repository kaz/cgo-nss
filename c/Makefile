install: libnss_hoge.so.2
	install -m 0644 $< /lib

libnss_hoge.so.2: hoge.c
	gcc -shared -o $@ -Wl,-soname,$@ $<
	strip $@

test: a.out
	./$<

a.out: hoge.c
	gcc -o $@ $<

clean:
	rm -f a.out libnss_hoge.so.2
