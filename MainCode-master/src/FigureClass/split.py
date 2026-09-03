from ROOT import TFile, TTree, TH1F
import sys
import os
import argparse
import shutil


# 每个文件最小的事件数为m
parser = argparse.ArgumentParser(description='split root file, for multi-threading')
# parser.add_argument('--m', type=int, default=500, help="maximum number of events")
parser.add_argument('--m', type=int, default=1000000, help="maximum number of events")
parser.add_argument('--random', type=bool, default=False, help="randomly split")
parser.add_argument('--infile', type=str, help="infile dir")
parser.add_argument('--outfile', type=str, help="outfile dir")

args = parser.parse_args()


# workdir = os.path.dirname(os.path.abspath(__file__))
workdir = os.getcwd()

outputpath = os.path.join(workdir, args.outfile)

m: int = args.m



def split_single_thread(filepath, order, n, i):
    # [[打开文件]] 
    try:
        f = TFile(filepath)
    except:
        print("input file {} not found".format(filepath))
        sys.exit()
    filename = os.path.basename(filepath)
    t = f.Get("SelectedEvents")
    NTotal = t.GetEntries()
    print("file {}-{} begin".format(filename, i))
    # [[创建新的文件]] 
    # filepath的倒数第二层目录的名字
    # newdir = os.path.basename(os.path.dirname(filepath))
    output = filename.replace(".root", "_%d.root" % i)
    output = os.path.join(outputpath, output)
    # output = os.path.join(outputpath, newdir + "_" + output)
    fnew = TFile(output, "recreate")
    tnew = t.CloneTree(0)
    # [[写入新的文件]] 
    for j in range(NTotal):
        if j % n != i:
            continue
        t.GetEntry(order[j])
        tnew.Fill()
    fnew.Write()
    fnew.Close()
    f.Close()
    # del tnew, t, fnew, f
    print("file {}-{} done".format(filename, i))

def split(filepath):
    try:
        f = TFile(filepath)
    except:
        print("input file {} not found".format(filepath))
        sys.exit()

    t = f.Get("SelectedEvents")
    try:
        NTotal = t.GetEntries()
    except:
        print("\n\tfile {} is crushed\n".format(filepath))
        return
    f.Close()
    filename = os.path.basename(filepath)
    if NTotal < m:
        # 直接复制到新的对应的目录
        outputfile = os.path.join(outputpath, filename)
        shutil.copy(filepath, outputfile)
        print("file {} copied".format(filename))
        return
    
    order = range(NTotal)
    if(args.random):
        print("randomly split")
        import random
        order = list(order)
        random.shuffle(order)
        print("randomly split done")

    

    # N个file
    n = NTotal // m + 1
    # pool.map(split_single_thread, order, n, range(n))
    for i in range(n):
        pool.apply_async(split_single_thread, (filepath, order, n, i))


def loop(path):
    """
    递归地遍历目录及其子目录，找到root文件并分割。
    参数：
        path：目录的路径
    """
    if not os.path.exists(path):
        raise FileNotFoundError("path not found: " + path)
    for root, dirs, files in os.walk(path):
        for file in files:
            if file.endswith(".root"):
                split(os.path.join(root, file))
        for dir in dirs:
            loop(os.path.join(root, dir))



# 多线程
import multiprocessing as mp
pool = mp.Pool(processes=mp.cpu_count())
        
# 删除旧的splitedSamples目录
if os.path.exists(outputpath):
    decision = input("delete old splitedSamples? (y/n)")
    if decision == "y":
        shutil.rmtree(outputpath)
    else:
        sys.exit()
os.mkdir(outputpath)

loop(os.path.join(workdir, args.infile))


pool.close()
pool.join()


outputlistfilepath = os.path.join(outputpath, "filelist")
# 如果存在，删除
if os.path.exists(outputlistfilepath):
    os.remove(outputlistfilepath)
outputlistfile = open(outputlistfilepath, "w")


# 在outputpath下找到所有的root文件
allfiles = os.listdir(outputpath)
allfiles_fullpath = []
for file in allfiles:
    if file.endswith(".root"):
        allfiles_fullpath.append(os.path.join(outputpath, file))

# 排序
allfiles_fullpath.sort()

for file in allfiles_fullpath:
    outputlistfile.write(file + "\n")

outputlistfile.close()
