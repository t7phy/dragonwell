#!/usr/bin/env python

# Read the submission directory as a command line argument. You can
# extend the list of arguments with your private ones later on.
import optparse
parser = optparse.OptionParser()
parser.add_option( '-d', '--submission-dir', dest = 'submission_dir',
                   action = 'store', type = 'string', default = 'submitDir',
                   help = 'Submission directory for EventLoop' )
parser.add_option( '-f', '--file-list', dest = 'file_list',
                   action = 'store', type = 'string', default = 'file.list',
                   help = 'name of file list' )
parser.add_option( '-n', '--max-events', dest = 'max_events',
                   action = 'store', type = int, default = None,
                   help = 'max events need to be processed' )
parser.add_option( '-s', '--is-simulation', dest = 'is_simulation',
                   action = 'store', type = int, default = 0,
                   help = 'is data or MC' )
parser.add_option( '-g', '--run-grid', dest = 'run_grid',
                   action = 'store', type = int, default = None,
                   help = 'run on the grid' )
parser.add_option( '-u', '--user-name', dest = 'user_name',
                   action = 'store', type = 'string', default = 'yafu',
                   help = 'user nickname' )
parser.add_option( '-o', '--output-tag', dest = 'output_tag',
                   action = 'store', type = 'string', default = 'testSubmit',
                   help = 'tag for grid jobs' )
parser.add_option( '-y', '--data-year', dest = 'data_year',
                   action = 'store', type = 'string', default = '1516',
                   help = 'year of data taking' )
parser.add_option( '-v', '--mv-version', dest = 'mc_version',
                   action = 'store', type = 'string', default = 'mc16a',
                   help = 'mc version' )
parser.add_option( '-x', '--sys-filter', dest = 'sys_filter',
                   action = 'store', type = 'string', default = 'nominal',
                   help = 'systematic name filter' )
parser.add_option( '-m', '--max-systematic', dest = 'max_systematic',
                   action = 'store', type = int, default = -1,
                   help = 'maximum systematics to process' )
( options, args ) = parser.parse_args()

# Set up (Py)ROOT.
import ROOT
ROOT.xAOD.Init().ignore()

# Set up the sample handler object. See comments from the C++ macro
# for the details about these lines.
import os
sh = ROOT.SH.SampleHandler()
sh.setMetaString( 'nc_tree', 'CollectionTree' )

import fileinput
if options.run_grid:
        for line in fileinput.input(options.file_list):
                ROOT.SH.scanRucio(sh, line.rstrip('\n'))
#                sh.setMetaString( "nc_grid_filter", "*" )  ###for AOD files, where default filter *.root* may not be found
else:
        ROOT.SH.readFileList(sh, 'testSample', options.file_list);

#inputFilePath = os.getenv( 'ALRB_TutorialData' )
#ROOT.SH.ScanDir().filePattern( 'DAOD_EGAM8.15623819._000206.pool.root.1' ).scan( sh, inputFilePath )
sh.printContent()

# Create an EventLoop job.
job = ROOT.EL.Job()
job.sampleHandler( sh )
if options.max_events:
        job.options().setDouble( ROOT.EL.Job.optMaxEvents, options.max_events )

output = ROOT.EL.OutputStream('myOutput')
job.outputAdd(output)
#ntuple = ROOT.EL.NTupleSvc('myOutput')
#job.algsAdd(ntuple)

# Create the algorithm's configuration.
from AnaAlgorithm.AnaAlgorithmConfig import AnaAlgorithmConfig
config = AnaAlgorithmConfig( 'SkimToNtupleTriLep/AnalysisAlg',
                              isMC = options.is_simulation,
                              Year = options.data_year,
                              mcVersion = options.mc_version,
                              SysFilter = options.sys_filter,
                              maxSys = options.max_systematic,
                              outputName = "myOutput")
#sh_hist = ROOT.SH.SampleHandler()
#sh_hist.load (submitDir + '/output-ANALYSIS')

# later on we'll add some configuration options for our algorithm that go here

# Add our algorithm to the job
job.algsAdd( config )

# Run the job using the direct driver.
if options.run_grid:
        driver = ROOT.EL.PrunDriver()
        driver.options().setString("nc_outputSampleName", "user."+options.user_name+"."+options.output_tag+".%in:name[2]%_%in:name[3]%")
        driver.options().setDouble(ROOT.EL.Job.optGridMergeOutput, 0)
        driver.submitOnly(job, options.submission_dir)
else:
        driver = ROOT.EL.DirectDriver()
        driver.submit( job, options.submission_dir )
