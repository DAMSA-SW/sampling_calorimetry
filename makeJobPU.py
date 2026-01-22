#!/cvmfs/sft.cern.ch/lcg/views/LCG_106/x86_64-el9-gcc13-dbg/bin/python3
import ROOT, math, random, os, sys



tmpMac = """/random/setSeeds {r1} {r2} {r3} {r4} {r5} {r6} {r7}  {r8}  {r9}  {r10} {r11}
/run/numberOfThreads 1
/detector/absorberLength {AT} mm
/detector/gapLength 10 mm
/detector/numLayers {nL}
/detector/absorberMaterial {AM}
/detector/targetLength 15 cm
/analysis/setFileName {fName}
/run/initialize
/gun/particle e-
/gun/position 0 0 -55 cm
/gun/momentum 0 0 1
/gun/energy 8 GeV
/run/beamOn 10000
"""

tmpSh = """#!/bin/sh
source /cvmfs/sft.cern.ch/lcg/views/LCG_106/x86_64-el9-gcc13-dbg/setup.sh
cd {batchPath}
{g4Path}/ALPGun {gMac}
"""

condorSub = """executable              = $(filename)
universe                = vanilla
getenv                  = True
RequestCpus		= 1
RequestMemory		= 15360
#output 		= log/$(filename)_$(Process).out
#error 			= log/$(filename)_$(Process).err
accounting_group        = group_cms
+JobBatchName = "{batchName}"
queue filename matching {shFiles}*.sh
"""
ATL = ['440']
nLL = ['1']
AML = ['G4_CESIUM_IODIDE']
g4Path = os.getcwd()

for AT in ATL:
    for AM in AML:
        batchPath = g4Path+ '/batch/eBeam_8_GeV_PU_1E4_EOT_10000_pulse_15_cm_target_{AM}_AT_{AT}_GT_10'.format(AM=AM,AT=AT)
        nL = nLL[ATL.index(AT)]
        os.makedirs(batchPath, exist_ok=True)
        os.chdir(batchPath)
        for r in range(10000):
            tmpName = "DAMSA_8_GeV_eBeam_1E4_EOT_{r:03d}".format(r=r)
            tmpC = open(tmpName+'.mac','w')
            r1 = "%d"%(random.random()*1000000)
            r2 = "%d"%(random.random()*1000000)
            r3 = "%d"%(random.random()*1000000)
            r4 = "%d"%(random.random()*1000000)
            r5 = "%d"%(random.random()*1000000)
            r6 = "%d"%(random.random()*1000000)
            r7 = "%d"%(random.random()*1000000)
            r8 = "%d"%(random.random()*1000000)
            r9 = "%d"%(random.random()*1000000)
            r10 = "%d"%(random.random()*1000000)
            r11 = "%d"%(random.random()*1000000)
            tmpC.write(tmpMac.format(
                r1=r1, r2=r2, r3=r3, r4=r4, r5=r5, r6=r6, r7=r7, r8=r8, r9=r9, r10=r10, r11=r11,
                AT=AT, nL=nL, AM=AM, fName=tmpName
            ))
            tmpC.close()
            tmpS = open(tmpName+'.sh','w')
            tmpS.write(tmpSh.format(g4Path=g4Path,batchPath=batchPath,gMac=tmpName+'.mac'))
            tmpS.close()
          
        os.system("chmod 755 *.sh")
        condorSubmit = open("condor.sub","w")
        condorSubmit.write(condorSub.format(shFiles='DAMSA_',batchName=batchPath.split("/")[-1]))
        condorSubmit.close()
        os.system("condor_submit condor.sub")
        os.chdir(g4Path)
