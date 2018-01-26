This repository defines a lua wrapper rock for [sentencepiece](https://github.com/google/sentencepiece).

## Installation

1\. Install [sentencepiece](https://github.com/google/sentencepiece)
2\. Install Lua development libraries:

On Ubuntu, they can be installed with apt-get:

```bash
sudo apt-get install lua5.1 liblua5.1-dev
```

3\. Install the wrapper:


```bash
luarocks make lua-sentencepiece-scm-1.rockspec
```

## Test and use

```
lua test.lua
```

The module creates a `sentencepiece` namespace with 2 functions:

* `sentencepiece.encode(model, string)`: encodes the string (convert into pieces table)
* `sentencepiece.decode(model, table)`: builds a string from the table of piece
