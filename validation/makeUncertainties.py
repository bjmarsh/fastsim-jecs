import math

header = "{1     JetEta   1     JetPt   \"\"       Correction   Uncertainty}"

ptBins = [8, 10, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153,
          174, 196, 220, 245, 272, 300, 362, 430, 507, 592, 686, 790, 905, 1032, 1172, 1327, 
          1497, 1684, 1890, 2000, 2238, 2500, 2787, 3103, 3450]

etaBins = [-5.4,-5.0,-4.4,-4,-3.5,-3,-2.8,-2.6,-2.4,-2.2,-2.0,-1.8,-1.6,-1.4,-1.2,
           -1.0,-0.8,-0.6,-0.4,-0.2,0.,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,
           2.0,2.2,2.4,2.6,2.8,3,3.5,4,4.4,5.0,5.4]



def writeUncertainties(alg):
    upperAlg = alg.upper().replace("CHS","chs")

    fh = open("%s_unc.txt" % alg,"r")
    lines = fh.readlines()
    fh.close()

    lines = [line.strip() for line in lines if len(line.strip()) > 1]
    dVals = {}
    for line in lines:
        parts = line.split()
        eta, pt, total, count = float(parts[0]), int(parts[1]), float(parts[2]), int(parts[3])

        uncertainty = 0.2
        if count > 0:
            response = 1.0*total/count
            uncertainty = abs(1.0-response)

        dVals[(eta,pt)] = uncertainty

    # print dVals[(-5.4,8)]
    # print dVals[(2.0,12)]
    dVals = addInQuadrature(dVals, upperAlg)
    # print dVals[(-5.4,8)]
    # print dVals[(2.0,12)]

    ndiv_pt = len(ptBins)-1

    fout = open("FS_Uncertainty_%s.txt" % upperAlg, "w")
    # print header
    fout.write( header + "\n" )
    for ieta,etaLower in enumerate(etaBins[:-1]):
        etaUpper = etaBins[ieta+1]
        # print "%1.1f %1.1f %d" % (etaLower, etaUpper, 3*ndiv_pt),
        fout.write( "%1.1f %1.1f %d " % (etaLower, etaUpper, 3*ndiv_pt) )
        for ipt,ptLower in enumerate(ptBins[:-1]):
            ptUpper = ptBins[ipt+1]
            pt = 0.5*(ptUpper + ptLower)
            unc = dVals[(etaLower,ptLower)]
            # print "%1.1f %1.4f %1.4f" % (pt, unc, unc),
            fout.write( "%1.1f %1.4f %1.4f " % (pt, unc, unc) )
        # print
        fout.write("\n")

def addInQuadrature(dValsBefore, upperAlg):
    fh = open("Spring16_25nsV2_MC_Uncertainty_%s.txt" % upperAlg,"r")
    lines = fh.readlines()[1:]

    dValsExtra = {}
    for line in lines:
    # for line in lines[:1]:
        tokens = line.split()
        etaLower, etaUpper = map(float,tokens[:2])
        tokens = tokens[3:]
        ptUnc = [tokens[i:i+3] for i in range(0,len(tokens)-2,3)]
        ptUnc = map(lambda x: [float(x[0]), float(x[1])], ptUnc)
        # print ptUnc, len(ptUnc)
        # print ptBins, len(ptBins)
        ptUnc = zip(ptBins[:-1],[e[1] for e in ptUnc])
        for pt, unc in ptUnc:
            dValsExtra[(etaLower, pt)] = unc
        # print etaLower, etaUpper

    # print dValsExtra

    ## add values in quadrature
    dValsAfter = {}
    for key in dValsBefore:
        bef = dValsBefore[key]
        ext = dValsExtra[key]
        dValsAfter[key] = math.sqrt( bef*bef + ext*ext )

    return dValsAfter
    # print lines[0]


# addInQuadrature()

writeUncertainties("ak4pfchs")
writeUncertainties("ak8pfchs")
writeUncertainties("ak4pf")
writeUncertainties("ak8pf")
