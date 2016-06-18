from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'forJECsPU-v1'
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../run_JRA_cfg.py'

config.section_("Data")
config.Data.inputDataset = '/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/RunIISpring16FSPremix-ForSUSJECs_80X_mcRun2_asymptotic_v12-v1/AODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1

config.section_("Site")
config.Site.storageSite = 'T2_US_UCSD'
