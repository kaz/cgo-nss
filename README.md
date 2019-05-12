# cgo_nss

cgoでnssをextendしたい
https://www.gnu.org/software/libc/manual/html_node/Name-Service-Switch.html

## /c

Cで実装した。
`**.hoge`をすべて拾って適当なアドレスに解決する。

拡張するとして、外部にHTTPリクエストを飛ばしたりJSONパースしたりするのがつらい。シュッとかけないので。

## /go

Goで実装した。
`**.hoge`をすべて拾って適当なアドレスに解決する。

cgoでCのポインタを扱うのが若干辛い。

## /cgo

CとGoで実装した。
`**.hoge`をすべて拾って適当なアドレスに解決する。

実際にLookupするのがGoで、Cがそのインタフェースを担うイメージ。
`/c`と`/go`のいいところ取りをしたかった。

### Lookup時に死ぬ

ビルド時に`-Bsymbolic`をつけないと死ぬ。
原因は調べてない。

```
function symbol table not sorted by program counter: 0x7f611ac5ebb0 runtime.return0 > 0x457c40 _cgo_topofstack
```

### そもそも動かない

`/c`の`make test`で引けてない。`libnss_hoge`が呼ばれてない雰囲気。
そのほかの場合（たとえば`ping`コマンドとか）は引けてる。
原因は調べてない。解決法も見つかってない。
