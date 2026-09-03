from pathlib import Path

NtupleDIR="/data/projects/StandardModel/HMDY_b/ntuples/v12"

DYeeList = [
"301000",
"301001",
"301002",
"301003",
"301004",
"301005",
"301006",
"301007",
"301008",
"301009",
"301010",
"301011",
"301012",
"301013",
"301014",
"301015",
"301016",
"301017",
"301018",
"361106",
]

DYmmList = {
"301020",
"301021",
"301022",
"301023",
"301024",
"301025",
"301026",
"301027",
"301028",
"301029",
"301030",
"301031",
"301032",
"301033",
"301034",
"301035",
"301036",
"301037",
"301038",
"361107",
}

PIeeList = [
"364834",
"364835",
"364836",
"364837",
"364838",
"364839",
"364840",
]

PImmList = [
"364841",
"364842",
"364843",
"364844",
"364845",
"364846",
"364847",
]

DibosonList = [
"363355",
"363356",
"363357",
"363358",
"363359",
"363360",
"364250",
"364253",
"364254",
"364255",
]

TopQuarkList = {
"410470",
"410644",
"410645",
"410646",
"410647",
"410658",
"410659",
}

TopQuark_HardScatterMCAdNloList = {
"410465",
"410644",
"410645",
"410646",
"410647",
"410658",
"410659",
}

ZtautauList = [
"361108",
]


SherpaDYeeList = [
"700320",
"700321",
"700322",
"700452",
"700453",
"700454",
]

SherpaDYmmList = [
"700323",
"700324",
"700325",
"700455",
"700456",
"700457",
]

Data15List = ["data15"]
Data16List = ["data16"]
Data17List = ["data17"]
Data18List = ["data18"]

MC_tags = {
    "mc16a": "r9364",
    "mc16d": "r10201",
    "mc16e": "r10724",
}

AllList = {
"Data15" : Data15List,
"Data16" : Data16List,
"Data17" : Data17List,
"Data18" : Data18List,
"DrellYan_ee": DYeeList,
"DrellYan_mm": DYmmList,
"PI_ee" : PIeeList,
"PI_mm" : PImmList,
"Diboson": DibosonList,
"TopQuark": TopQuarkList,
"TopQuark_HardScatterMCAdNlo" : TopQuark_HardScatterMCAdNloList,
"Ztautau" : ZtautauList,
"Sherpa_DrellYan_ee" : SherpaDYeeList,
"Sherpa_DrellYan_mm" : SherpaDYmmList,
}

DATA_KEYS = ["Data15", "Data16", "Data17", "Data18"]

FinalAllList = {}

for listname in AllList:

    if listname in DATA_KEYS:
        FinalAllList[listname] = []
    else:
        FinalAllList[listname] = {mc: [] for mc in MC_tags}


SherpaDYee = {mc: [] for mc in MC_tags}

files = [str(p) for p in Path(NtupleDIR).expanduser().resolve().iterdir() if p.is_dir()]

for name in files:
    p = Path(name)

    for listname, mylist in AllList.items():

        if listname in DATA_KEYS:

            for dsid in mylist:
                if dsid in name:
                    files = [str(f.resolve()) for f in p.glob("*.root")]
                    FinalAllList[listname].extend(files)
        else:

            for dsid in mylist:
                if dsid in name:
                    for mc, tag in MC_tags.items():
                        if tag in name:
                            files = [str(f.resolve()) for f in p.iterdir() if f.is_file()]
                            FinalAllList[listname][mc].extend(files)


for key, val in FinalAllList.items():
    if key in DATA_KEYS:
        FinalAllList[key] = sorted(set(val))
    else:
        for mc in val:
            val[mc] = sorted(set(val[mc]))


for key, val in FinalAllList.items():

    if key in DATA_KEYS:
        if not val:
            print(f"Skip empty data list: {key}")
            continue

        outfile = f"SumOfWeight_{key}.list"

        with open(outfile, "w") as f:
            for x in val:
                f.write(x + "\n")

        print(f"Written: {outfile}  ({len(val)} files)")

    else:
        for mc, flist in val.items():
            if not flist:
                print(f"Skip empty data list: {key}")
                continue

            outfile = f"SumOfWeight_{key}_{mc}.list"

            with open(outfile, "w") as f:
                for x in flist:
                    f.write(x + "\n")

            print(f"Written: {outfile}  ({len(flist)} files)")

