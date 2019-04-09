import FWCore.ParameterSet.Config as cms

#!
#! PROCESS
#!
# Conditions source options: GT, SQLite, DB
conditionsSource = "GT"
era = "Fall17_17Nov2017_V32_94X_MC"
doProducer = False
process = cms.Process("JRA")
multithread = False
if doProducer:
	process = cms.Process("JRAP")
	multithread = True


#!
#! CHOOSE ALGORITHMS
#!
# Note: Not all combinations of options will work
# Algorithm options: ak, kt, ic, sc, ca
# Size options: integers 1-10
# Jet type options: calo, pf, pfchs, puppi
# Correction levels: '' (blank), l1, l2, l3, l2l3, l1l2l3

# algsizetype = {'ak':[4,8]}
# jettype = ['pf','pfchs','puppi']
# corrs = ['']

algorithms = []
jcr = cms.VPSet()

for alg in ['ak4pf', 'ak4pfchs', 'ak8pfchs', 'ak4puppi', 'ak8puppi' ]:
# for alg in ['ak4pfchs', 'ak4puppi', 'ak8puppi']:
# for alg in ['ak4pfchs']:
    print "Adding jet algorithm:", alg
    algorithms.append(alg)

# for k, v in algsizetype.iteritems():
#     for s in v:
# 	for j in jettype:
#             for c in corrs:
# 	        algorithms.append(str(k+str(s)+j+c))
#                 print "Adding jet algorithm:", algorithms[-1]
# 	        if conditionsSource != "GT":
#                     upperAlg = str(k.upper()+str(s)+j.upper().replace("CHS","chs")).replace("PUPPI","PFPuppi")
# 		    jcr.append(cms.PSet(record = cms.string("JetCorrectionsRecord"),
# 					tag = cms.string("JetCorrectorParametersCollection_"+era+"_"+upperAlg),
# 					label= cms.untracked.string(upperAlg)))

# If need be you can append additional jet collections using the style below
#algorithms.append('ak5calo')


#!
#! CONDITIONS (DELIVERING JEC BY DEFAULT!)
#!
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = cms.string('94X_mc2017_realistic_v17')

if conditionsSource != "GT":
    # from CondCore.DBCommon.CondDBSetup_cfi import *
    from CondCore.CondDB.CondDB_cfi import CondDB

    if conditionsSource == "DB":
        CondDB.connect = cms.string("frontier://FrontierPrep/CMS_CONDITIONS")
    elif conditionsSource == "SQLite":
	CondDB.connect = cms.string('sqlite_file:'+era+'.db')    

    process.jec = cms.ESSource("PoolDBESSource",CondDB,
			       toGet =  cms.VPSet(jcr))
    process.es_prefer_jec = cms.ESPrefer("PoolDBESSource","jec")


#!
#! INPUT
#!
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100))

##############################################
# External Input File (most likely from DAS) #
##############################################
try:
    process.load("JetMETAnalysis.JetAnalyzers.<filename without extension>")
except ImportError:
    print "Couldn't open the external list of files from DAS. If you just checkout out the JetResponseAnalyzer package you will need to make this file yourself. Currently Falling back to opening the list hard-coded in run_JRA_cfg.py. This is not a bad action as long as it is what you intended to have happen."
    inputFiles = cms.untracked.vstring(
	    # 'root://cmsxrootd.fnal.gov//store/mc/RunIIFall17FSDR/QCD_Pt-15to7000_TuneCP2_Flat_13TeV_pythia8_FlatPU/AODSIM/ForJEC_SUSY_94X_mc2017_realistic_v15-v1/60001/F43C4F10-2933-E911-BA80-FA163E42D7F5.root'
	    'file:/hadoop/cms/store/user/bemarsh/ProjectMetis/QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8_privateMC_fastsim_FlatPU_94x_AODSIM_v2/output_42.root',
	    )
    process.source = cms.Source("PoolSource", fileNames = inputFiles )


#!
#! SERVICES
#!
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 10
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))
if doProducer:
    process.add_(cms.Service("Tracer"))
    process.options.numberOfThreads = cms.untracked.uint32(8)
    process.options.numberOfStreams = cms.untracked.uint32(0)
else:
    process.load('CommonTools.UtilAlgos.TFileService_cfi')
    process.TFileService.fileName=cms.string('JRA.root')


#!
#! NEEDED FOR PFCHS
#!
process.load('CommonTools.ParticleFlow.pfNoPileUpJME_cff')
process.pfPileUpJME.checkClosestZVertex = False


#!
#! JET & REFERENCE KINEMATIC CUTS
#!
import JetMETAnalysis.JetAnalyzers.Defaults_cff as Defaults


#!
#! RUN JET RESPONSE ANALYZER
#!

# set to False to use jets from the input file (NOT RECOMMENDED)
doJetReco = True
outCom = cms.untracked.vstring('drop *')
from JetMETAnalysis.JetAnalyzers.addAlgorithm import addAlgorithm
for algorithm in algorithms:
    if (algorithm.find('HLT') > 0) :
        process.load("Configuration.Geometry.GeometryIdeal_cff")
        process.load("Configuration.StandardSequences.MagneticField_cff")
        addAlgorithm(process,algorithm,Defaults,False,doProducer)
    else:
        addAlgorithm(process,algorithm,Defaults,doJetReco,doProducer)
    outCom.extend(['keep *_'+algorithm+'_*_*'])


#!
#! Check the keep and drop commands being added to the outputCommamnds
#!
printOC = False
if printOC:
    for oc in outCom:
        print oc


#!
#! Output
#!
if doProducer:
    process.out = cms.OutputModule("PoolOutputModule",
				   fileName = cms.untracked.string('JRAP.root'),
				   outputCommands = outCom
				   )
    process.e = cms.EndPath(process.out)


#!
#! THAT'S ALL! CAN YOU BELIEVE IT? :-D
#!

#Not sure what this does
#processDumpFile = open('runJRA.dump' , 'w')
#print >> processDumpFile, process.dumpPython()
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.options.allowUnscheduled = cms.untracked.bool(True)
