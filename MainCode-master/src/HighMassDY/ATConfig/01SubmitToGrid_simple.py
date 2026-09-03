#!/usr/bin/env python
import TopExamples.grid as grid
import MC16_TOPQ1
import os

config = grid.Config()
config.CMake         = True
config.code          = 'top-xaod'
config.gridUsername  = 'yafu' #USERNAME
config.excludedSites = ''
config.noSubmit      = False # set to True if you just want to test the submission 
# config.excludedSites = 'ANALY_CONNECT,ANALY_CONNECT_SHORT'#'ANALY_GOEGRID'
# config.noSubmit      = True
# config.memory	     = '4000'
config.maxNFilesPerJob = '20'

config.mergeType     = 'Default' #'None', 'Default' or 'xAOD'
# config.destSE        = 'BNL-OSG2_LOCALGROUPDISK' 
config.destSE        = ''
#config.newOpts       = '--allowTaskDuplication' ###Be careful only for broken jobs
#config.otherOptions  = '--allowTaskDuplication' 
#config.otherOptions  = '--useNewCode'
####################################################################################

#config.suffix       = 'HMDY_Loose_Test6_ELFakes'
#config.settingsFile = 'configs_ElFakes/dil-cuts_mc16d.txt'
#config.extFile      = './PRW/*.root'
#config.extFile      = '.root,.so'
#config.otherOptions  = '--extFile=./PRW/*.root'
#names = ['Data17Period' ]
#config.maxFileSize='20000000000000'
#samples = grid.Samples(names)
#grid.submit(config, samples)

##Electron Fakes
## MC16a 
#config.suffix       = 'HMDY_Loose_110225_ElFakes_data15'
#config.settingsFile = 'configs_ElFakes/dil-cuts_mc16a.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'Data15Period']
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
#config.suffix       = 'HMDY_Loose_110225_ElFakes_data16'
#config.settingsFile = 'configs_ElFakes/dil-cuts_mc16a.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'Data16Period']
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
#config.suffix       = 'HMDY_Loose_110225_ElFakes'
#config.settingsFile = 'configs_ElFakes/dil-cuts_mc16a.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'PI_mc16a','Diboson_mc16a_Unbinned','DYee_mc16a','Ztoee_mc16a','TopQuark_mc16a','Ztotautau_mc16a','Wjets_mc16a']
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
## print grid.checkDatasetExists(names)
#

#config.suffix       = 'HMDY_Loose_110225_ElFakes_data17'
#config.settingsFile = 'configs_ElFakes/dil-cuts_mc16d.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#names = ['Data17Period']
#config.maxFileSize='20000000000000'
#samples = grid.Samples(names)
#grid.submit(config, samples)

## MC16d                                                                                                                                                              
#config.suffix       = 'HMDY_Loose_110225_ElFakes'
#config.settingsFile = 'configs_ElFakes/dil-cuts_mc16d.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#names = [ 'PI_mc16d','Diboson_mc16d_Unbinned','DYee_mc16d','Ztoee_mc16d','TopQuark_mc16d','Ztotautau_mc16d','Wjets_mc16d' ]
#config.maxFileSize='20000000000000'
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
#

#config.suffix       = 'HMDY_Loose_170225_ElFakes_data18'
#config.settingsFile = 'configs_ElFakes/dil-cuts_mc16e.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#names = [ 'Data18Period']
#config.maxFileSize='20000000000000'
#samples = grid.Samples(names)
#grid.submit(config, samples)

## MC16e                                                                                                                                                                 
#                                  
#config.suffix       = 'HMDY_Loose_170225_ElFakes'
#config.settingsFile = 'configs_ElFakes/dil-cuts_mc16e.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#names = [ 'PI_mc16e','Diboson_mc16e_Unbinned','DYee_mc16e','Ztoee_mc16e','TopQuark_mc16e','Ztotautau_mc16e','Wjets_mc16e']
#config.maxFileSize='20000000000000'
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
#
#

#config.suffix       = 'HMDY_Loose_140325_Signal'
#config.settingsFile = 'configs_signal/dil-cuts_Signal_mc16a.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'DYee_mc16a','Ztoee_mc16a']
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
#config.suffix       = 'HMDY_Loose_140325_Signal'
#config.settingsFile = 'configs_signal/dil-cuts_Signal_mc16d.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'DYee_mc16d','Ztoee_mc16d']
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
#config.suffix       = 'HMDY_Loose_140325_Signal'
#config.settingsFile = 'configs_signal/dil-cuts_Signal_mc16e.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'DYee_mc16e','Ztoee_mc16e']
#samples = grid.Samples(names)
#grid.submit(config, samples)

#config.suffix       = 'HMDY_Loose_130325_Signal_data15'
#config.settingsFile = 'configs_signal/dil-cuts_Data.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'Data15Period']
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
#config.suffix       = 'HMDY_Loose_130325_Signal_data16'
#config.settingsFile = 'configs_signal/dil-cuts_Data.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'Data16Period']
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
#config.suffix       = 'HMDY_Loose_130325_Signal_data17'
#config.settingsFile = 'configs_signal/dil-cuts_Data.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'Data17Period']
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
#config.suffix       = 'HMDY_Loose_130325_Signal_data18'
#config.settingsFile = 'configs_signal/dil-cuts_Data.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'Data18Period']
#samples = grid.Samples(names)
#grid.submit(config, samples)


###Muon Fakes
## MC16a
#
#config.suffix       = 'HMDY_Loose_070325_MuFakes_data15'
#config.settingsFile = 'configs_MuonFakes/dil-cuts_mc16a.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'Data15Period']
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
#config.suffix       = 'HMDY_Loose_070325_MuFakes_data16'
#config.settingsFile = 'configs_MuonFakes/dil-cuts_mc16a.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'Data16Period']
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
config.suffix       = 'HMDY_Loose_140325a_MuFakes'
config.settingsFile = 'configs_MuonFakes/dil-cuts_mc16a.txt'
config.otherOptions  = '--extFile=./PRW/*.root'
config.maxFileSize='20000000000000'
names = [ 'Diboson_mc16a_Unbinned', 'Triboson_mc16a','ttV_mc16a']
samples = grid.Samples(names)
grid.submit(config, samples)
#
#
#
#config.suffix       = 'HMDY_Loose_070325_MuFakes_data17'
#config.settingsFile = 'configs_MuonFakes/dil-cuts_mc16d.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#names = ['Data17Period']
#config.maxFileSize='20000000000000'
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
## MC16d
config.suffix       = 'HMDY_Loose_140325a_MuFakes'
config.settingsFile = 'configs_MuonFakes/dil-cuts_mc16d.txt'
config.otherOptions  = '--extFile=./PRW/*.root'
names = [ 'Diboson_mc16d_Unbinned', 'Triboson_mc16d','ttV_mc16d']
config.maxFileSize='20000000000000'
samples = grid.Samples(names)
grid.submit(config, samples)
#
#
#
#config.suffix       = 'HMDY_Loose_070325_MuFakes_data18'
#config.settingsFile = 'configs_MuonFakes/dil-cuts_mc16e.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#names = [ 'Data18Period']
#config.maxFileSize='20000000000000'
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
## MC16e                                                                                                                                                                 
#                                  
config.suffix       = 'HMDY_Loose_140325a_MuFakes'
config.settingsFile = 'configs_MuonFakes/dil-cuts_mc16e.txt'
config.otherOptions  = '--extFile=./PRW/*.root'
names = [ 'Diboson_mc16e_Unbinned', 'Triboson_mc16e','ttV_mc16e']
config.maxFileSize='20000000000000'
samples = grid.Samples(names)
grid.submit(config, samples)

#config.suffix       = 'HMDY_Loose_130325_Signal'
#config.settingsFile = 'configs_signal/dil-cuts_Signal_mc16a.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'DYmumu_mc16a','Ztomumu_mc16a']
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
#config.suffix       = 'HMDY_Loose_130325_Signal'
#config.settingsFile = 'configs_signal/dil-cuts_Signal_mc16d.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'DYmumu_mc16d','Ztomumu_mc16d']
#samples = grid.Samples(names)
#grid.submit(config, samples)
#
#config.suffix       = 'HMDY_Loose_130325_Signal'
#config.settingsFile = 'configs_signal/dil-cuts_Signal_mc16e.txt'
#config.otherOptions  = '--extFile=./PRW/*.root'
#config.maxFileSize='20000000000000'
#names = [ 'DYmumu_mc16e','Ztomumu_mc16e']
#samples = grid.Samples(names)
#grid.submit(config, samples)

