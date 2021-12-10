#!/bin/bash

for p in 0.2 0.4 0.6 0.8
do

fout=single_km_p${p}.root

npsim --compactFile=gridpix_canyonlands.xml --runType=run -G -N=1000 --outputFile=$fout --gun.particle "kaon-" --gun.position "0.0 0.0 1.0*cm" --gun.direction "1.0 0.0 1.0" --gun.energy ${p}*GeV --part.userParticleHandler=''

done
