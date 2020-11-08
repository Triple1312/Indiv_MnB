# dit bestand zal gerund worden en moet voor de nodige input en output zorgen
# je mag hier aanpassingen doen, maar dezelfde functionaliteit moet ondersteund worden
# als er een bestand niet aangemaakt wordt, krijg je daar ook geen punten voor
#
# in dit bestand wordt er van uit gegaan dat er een executable met de naam indiv staat
# dat volgende parameters ondersteunt:
# <algoritme> <inputfile> <outputfile(s)>:
# - algoritme is een uit cnf, cyk, ll1, lr, multitm, tm, tmsub (voor subroutines), pda2cfg
# - inputfile is het inputbestand (let op bij tm zijn dat er 3)
# - outputfile is het outputbestand (indien de output geen pda is, geef je telkens de dot output van de input)
# het is de bedoeling dat hieronder enkel de lijnen komen van de algoritmes die je ondersteunt

# CYK: de output bestaat uit de resulterende tabel, niet in dot formaat, bv in html en de conclusie van CYK
# de input bestaat uit de cfg en de gegeven inputstring
./indiv cyk input-cyk1.json baaba output-cyk1.txt
./indiv cyk input-cyk1.json abba output-cyk1.txt
./indiv cyk input-cyk2.json aaabb output-cyk2.txt
./indiv cyk input-cyk2.json aaabbb output-cyk2.txt

# PDA2CFG: je geeft de resulterende cfg in een leesbare vorm
./indiv pda2cfg input-pda2cfg1.json output-pda2cfg1.txt
./indiv pda2cfg input-pda2cfg2.json output-pda2cfg2.txt
