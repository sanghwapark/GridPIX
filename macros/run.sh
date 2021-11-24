#!/bin/bash

nevt=10000

for ENERGY in 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0
do

#npsim --compactFile=gridpix_simple.xml --numberOfEvents ${nevt} --enableGun --gun.energy ${ENERGY}*GeV --gun.thetaMin 0*deg --gun.thetaMax 40*deg --gun.distribution uniform --gun.particle "pi-" --outputFile output_${ENERGY}_1mmlayer.root

npsim --compactFile=gridpix_simple.xml --numberOfEvents ${nevt} --enableGun --gun.energy ${ENERGY}*GeV --gun.thetaMin 0*deg --gun.thetaMax 40*deg --gun.distribution uniform --gun.particle "pi-" --outputFile output_${ENERGY}_1mmlayer.root

done
