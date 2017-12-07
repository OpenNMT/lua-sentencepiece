local sentencepiece = require 'lua-sentencepiece'

local src_en = "All of these musical influences and others (including doo-wop and soul) converged in Rawls' work, "..
               "which transcended any specific genre."
print('src_en:', src_en)
local enc_en = sentencepiece.encode("test/en.model", src_en)
print('encoding:', enc_en)
local t_en = sentencepiece.decode("test/en.model", enc_en)
print('decoding', t_en)

local src_fr = "Le programme d'investissement dans la fabrication de neige de culture est en augmentation de 50% "..
               "cette saison en Haute-Savoie."
print('src_fr:', src_fr)
local enc_fr = sentencepiece.encode("test/fr.model", src_fr)
print('encoding:', enc_fr)
local t_fr = sentencepiece.decode("test/fr.model", enc_fr)
print('decoding', t_fr)
