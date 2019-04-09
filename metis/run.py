from metis.CMSSWTask import CMSSWTask
from metis.Sample import DirectorySample, DummySample
from metis.StatsParser import StatsParser
import time

import numpy as np

indir_nopu = "/hadoop/cms/store/user/bemarsh/ProjectMetis/QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8_privateMC_fastsim_NoPU_94x_AODSIM_v2/"
indir_flatpu = "/hadoop/cms/store/user/bemarsh/ProjectMetis/QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8_privateMC_fastsim_FlatPU_94x_AODSIM_v2/"

tag = "JRAv1"
total_summary = {}
for _ in range(10000):

    jra_nopu = CMSSWTask(
        sample = DirectorySample(
            location = indir_nopu,
            dataset = "/QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8/privateMC_fastsim_NoPU_94x/JRA"
            ),
        open_dataset = True,
        files_per_output = 10,
        pset = "../run_JRA_cfg_update.py",
        cmssw_version = "CMSSW_9_4_12",
        scram_arch = "slc6_amd64_gcc630",
        tag = tag,
        tarfile = "lib_JRA.tar.xz",
        dont_check_tree = True,
        calc_neg_events = False,
        )

    jra_flatpu = CMSSWTask(
        sample = DirectorySample(
            location = indir_flatpu,
            dataset = "/QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8/privateMC_fastsim_FlatPU_94x/JRA"
            ),
        open_dataset = True,
        files_per_output = 10,
        pset = "../run_JRA_cfg_update.py",
        cmssw_version = "CMSSW_9_4_12",
        scram_arch = "slc6_amd64_gcc630",
        tag = tag,
        tarfile = "lib_JRA.tar.xz",
        dont_check_tree = True,
        calc_neg_events = False,
        )

    tasks = [jra_nopu, jra_flatpu]

    for task in tasks:
        task.process()
        summary = task.get_task_summary()
        total_summary[task.get_sample().get_datasetname()] = summary

    StatsParser(data=total_summary, webdir="~/public_html/dump/metis_jra/").do()
    time.sleep(30*60)
