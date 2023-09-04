TTTTT


```shell
lint-history --relevant 'return (filename.endswith(b".cpp") or filename.endswith(b".h") or filename.endswith(b".cc"))' \
${bin_path}/clang-format -style=file:${cf_path}/cf.ini -i
```
