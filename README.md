This repository defines a lua wrapper rock for [sentencepiece](https://github.com/google/sentencepiece).

## Installation

You need first to install sentencepiece then:

```
luarocks make lua-sentencepiece-scm-1.rockspec
```

## Test and use

```
lua test.lua
```

The module creates a `sentencepiece` namespace with 3 functions:

* `sentencepiece.load(model)`: loads the model, returns false if not successful
* `sentencepiece.encode(string)`: encode the string (convert into pieces table)
* `sentencepiece.decode(table)`: build a string from the table of piece
