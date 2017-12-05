require 'lua-sentencepiece'
if not sentencepiece.load("test/sample.model") then
  print("ERROR: cannot load model")
else
  local src = "All of these musical influences and others (including doo-wop and soul) converged in Rawls' work, which transcended any specific genre."
  print('src:', src)
  local e = sentencepiece.encode(src)
  print('encoding:', e)
  local t = sentencepiece.decode(e)
  print('decoding', t)
end
