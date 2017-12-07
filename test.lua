require 'lua-sentencepiece'

local src = "All of these musical influences and others (including doo-wop and soul) converged in Rawls' work, which transcended any specific genre."
print('src:', src)
local e = sentencepiece.encode("test/sample.model", src)
print('encoding:', e)
local t = sentencepiece.decode("test/sample.model", e)
print('decoding', t)
