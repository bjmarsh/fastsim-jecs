import ROOT as r
import numpy as np

r.gStyle.SetNumberContours(255)
r.gStyle.SetOptStat(0)
r.gROOT.SetBatch(1)

algo = "ak8puppi"

fin = r.TFile("{0}.root".format(algo))
t = fin.Get("t")

ptbins = 10*1.5**np.arange(0,16)
ptbinsfine = np.array([10,11,12,13,14,15,17,20,23,27,30,35,40,45,57,72,90,120,150,200,300,400,550,750,1000,1500,2000,2500,3000,3500,4000,4500,5000,10000], dtype=float)
netabinsfine = 50

etabins = np.array([0, 1.3, 2.5, 3.0, 5.0], dtype=float)
pubins = np.array([0,10,20,30,40,50,60,70], dtype=float)

h2_count = r.TH2D("h2_count", ";p_{T} [GeV];#eta", ptbinsfine.size-1, ptbinsfine, netabinsfine, -4.7, 4.7)
h2_l1corr = r.TH2D("h2_l1corr", ";p_{T} [GeV];#eta", ptbinsfine.size-1, ptbinsfine, netabinsfine, -4.7, 4.7)
h2_l2corr = r.TH2D("h2_l2corr", ";p_{T} [GeV];#eta", ptbinsfine.size-1, ptbinsfine, netabinsfine, -4.7, 4.7)

h3_pucount = r.TH3D("h3_pucount", ";p_{T} [GeV];tnpu", ptbins.size-1, ptbins, pubins.size-1, pubins, etabins.size-1, etabins)
h3_offsetcorr = r.TH3D("h3_offsetcorr", ";p_{T} [GeV];tnpu", ptbins.size-1, ptbins, pubins.size-1, pubins, etabins.size-1, etabins)
h3_offsetuncorr = r.TH3D("h3_offsetuncorr", ";p_{T} [GeV];tnpu", ptbins.size-1, ptbins, pubins.size-1, pubins, etabins.size-1, etabins)

h2_respcount = r.TH2D("h2_respcount", ";p_{T} [GeV];#eta", ptbins.size-1, ptbins, etabins.size-1, etabins)
h2_respcorr = r.TH2D("h2_respcorr", ";p_{T} [GeV];#eta", ptbins.size-1, ptbins, etabins.size-1, etabins)
h2_respuncorr = r.TH2D("h2_respuncorr", ";p_{T} [GeV];#eta", ptbins.size-1, ptbins, etabins.size-1, etabins)

# nevt = 1000000
nevt = 1000000000
t.Draw("eta_ref:pt_ref>>h2_count", "", "goff", nevt)
t.Draw("eta_ref:pt_ref>>h2_l1corr", "l1corr", "goff", nevt)
t.Draw("eta_ref:pt_ref>>h2_l2corr", "l2corr", "goff", nevt)
t.Draw("eta_ref:tnpu:pt_ref>>h3_pucount", "", "goff", nevt)
t.Draw("eta_ref:tnpu:pt_ref>>h3_offsetcorr", "pt_pu*l1corr-pt_nopu", "goff", nevt)
t.Draw("eta_ref:tnpu:pt_ref>>h3_offsetuncorr", "pt_pu-pt_nopu", "goff", nevt)
t.Draw("eta_ref:pt_ref>>h2_respcount", "", "goff", nevt)
t.Draw("eta_ref:pt_ref>>h2_respcorr", "pt_pu*l1corr*l2corr/pt_ref", "goff", nevt)
t.Draw("eta_ref:pt_ref>>h2_respuncorr", "pt_pu/pt_ref", "goff", nevt)

h_l1ptcount = h2_count.ProjectionX()
h_l1pt = h2_l1corr.ProjectionX()
h_l1etacount = h2_count.ProjectionY()
h_l1eta = h2_l1corr.ProjectionY()

h_l2ptcount = h2_count.ProjectionX()
h_l2pt = h2_l2corr.ProjectionX()
h_l2etacount = h2_count.ProjectionY()
h_l2eta = h2_l2corr.ProjectionY()

h2_l1corr.Divide(h2_count)
h2_l2corr.Divide(h2_count)
h_l1pt.Divide(h_l1ptcount)
h_l1eta.Divide(h_l1etacount)
h_l2pt.Divide(h_l2ptcount)
h_l2eta.Divide(h_l2etacount)

c = r.TCanvas()
c.SetLogx()
r.gStyle.SetPalette(r.kLightTemperature)
h2_l1corr.GetZaxis().SetRangeUser(0.5,1.5)
h2_l1corr.Draw("colz")
c.SaveAs("bennettplots/{0}_L1corrPtEtaFine.pdf".format(algo))
c.SaveAs("bennettplots/{0}_L1corrPtEtaFine.png".format(algo))

h_l1pt.SetMarkerStyle(20)
h_l1pt.SetMarkerColor(r.kRed)
h_l1pt.SetLineColor(r.kRed)
h_l1pt.Draw("PE")
c.SaveAs("bennettplots/{0}_L1corrPt.pdf".format(algo))
c.SaveAs("bennettplots/{0}_L1corrPt.png".format(algo))

c.SetLogx(0)
h_l1eta.SetMarkerStyle(20)
h_l1eta.SetMarkerColor(r.kRed)
h_l1eta.SetLineColor(r.kRed)
h_l1eta.Draw("PE")
c.SaveAs("bennettplots/{0}_L1corrEta.pdf".format(algo))
c.SaveAs("bennettplots/{0}_L1corrEta.png".format(algo))

c.SetLogx()
r.gStyle.SetPalette(r.kLightTemperature)
h2_l2corr.GetZaxis().SetRangeUser(0.5,1.5)
h2_l2corr.Draw("colz")
c.SaveAs("bennettplots/{0}_L2corrPtEtaFine.pdf".format(algo))
c.SaveAs("bennettplots/{0}_L2corrPtEtaFine.png".format(algo))

h_l2pt.SetMarkerStyle(20)
h_l2pt.SetMarkerColor(r.kRed)
h_l2pt.SetLineColor(r.kRed)
h_l2pt.Draw("PE")
c.SaveAs("bennettplots/{0}_L2corrPt.pdf".format(algo))
c.SaveAs("bennettplots/{0}_L2corrPt.png".format(algo))

c.SetLogx(0)
h_l2eta.SetMarkerStyle(20)
h_l2eta.SetMarkerColor(r.kRed)
h_l2eta.SetLineColor(r.kRed)
h_l2eta.Draw("PE")
c.SaveAs("bennettplots/{0}_L2corrEta.pdf".format(algo))
c.SaveAs("bennettplots/{0}_L2corrEta.png".format(algo))

c2 = r.TCanvas("c2","c2",600,600)
c2.SetLogx()
colors = [r.kRed+1,r.kOrange+8,r.kYellow+1,r.kSpring+2,r.kGreen+2,r.kAzure-2, r.kViolet]

for ieta in range(etabins.size-1):
    for ipu in range(pubins.size-1):
        hcount = h3_pucount.ProjectionX(str(ieta)+str(ipu)+"count",ipu+1,ipu+1,ieta+1,ieta+1)
        hcorr = h3_offsetcorr.ProjectionX(str(ieta)+str(ipu)+"corr",ipu+1,ipu+1,ieta+1,ieta+1)
        
        hcorr.Divide(hcount)
        hcorr.SetMarkerStyle(20)
        hcorr.SetMarkerColor(colors[ipu])
        hcorr.SetLineColor(colors[ipu])
        
        if ipu==0:
            hcorr.GetYaxis().SetRangeUser(-10,20)
            hcorr.GetYaxis().SetTitle("#LT offset #GT [GeV]")
            hcorr.GetYaxis().SetTitleOffset(1.1)
            hcorr.SetTitle("")
            hcorr.Draw("PE")
            leg = r.TLegend(0.5, 0.6, 0.8, 0.88)
            leg.AddEntry(hcorr, "{0} #leq PU < {1}".format(int(pubins[ipu]), int(pubins[ipu+1])))
        else:
            hcorr.Draw("PE SAME")
            leg.AddEntry(hcorr, "{0} #leq PU < {1}".format(int(pubins[ipu]), int(pubins[ipu+1])))

    leg.Draw()
    text = r.TLatex()
    text.SetNDC(1)
    text.SetTextFont(62)
    text.SetTextSize(0.04)
    text.DrawLatex(0.17, 0.85, "{0} jets".format(algo))
    text.DrawLatex(0.17, 0.80, "{0} #leq |#eta| < {1}".format(etabins[ieta], etabins[ieta+1]))

    c2.SaveAs("bennettplots/{0}_L1closure_corr_eta{1}.pdf".format(algo, ieta))
    c2.SaveAs("bennettplots/{0}_L1closure_corr_eta{1}.png".format(algo, ieta))

for ieta in range(etabins.size-1):
    for ipu in range(pubins.size-1):
        hcount = h3_pucount.ProjectionX(str(ieta)+str(ipu)+"count",ipu+1,ipu+1,ieta+1,ieta+1)
        huncorr = h3_offsetuncorr.ProjectionX(str(ieta)+str(ipu)+"uncorr",ipu+1,ipu+1,ieta+1,ieta+1)
        
        huncorr.Divide(hcount)
        huncorr.SetMarkerStyle(20)
        huncorr.SetMarkerColor(colors[ipu])
        huncorr.SetLineColor(colors[ipu])
        
        if ipu==0:
            huncorr.GetYaxis().SetRangeUser(-10,20)
            huncorr.GetYaxis().SetTitle("#LT offset #GT [GeV]")
            huncorr.GetYaxis().SetTitleOffset(1.1)
            huncorr.SetTitle("")
            huncorr.Draw("PE")
            leg = r.TLegend(0.5, 0.6, 0.8, 0.88)
            leg.AddEntry(huncorr, "{0} #leq PU < {1}".format(int(pubins[ipu]), int(pubins[ipu+1])))
        else:
            huncorr.Draw("PE SAME")
            leg.AddEntry(huncorr, "{0} #leq PU < {1}".format(int(pubins[ipu]), int(pubins[ipu+1])))

    leg.Draw()
    text = r.TLatex()
    text.SetNDC(1)
    text.SetTextFont(62)
    text.SetTextSize(0.04)
    text.DrawLatex(0.17, 0.85, "{0} jets".format(algo))
    text.DrawLatex(0.17, 0.80, "{0} #leq |#eta| < {1}".format(etabins[ieta], etabins[ieta+1]))

    c2.SaveAs("bennettplots/{0}_L1closure_uncorr_eta{1}.pdf".format(algo, ieta))
    c2.SaveAs("bennettplots/{0}_L1closure_uncorr_eta{1}.png".format(algo, ieta))
            

c = r.TCanvas()
c.SetLogx()
c.SetTickx()
c.SetTicky()
colors = [r.kBlack, r.kBlue, r.kRed, r.kMagenta]
styles = [20, 24, 22, 26]
for ieta in range(etabins.size-1):
    hcount = h2_respcount.ProjectionX(str(ieta)+"respcount", ieta+1, ieta+1)
    hcorr = h2_respcorr.ProjectionX(str(ieta)+"respcorr", ieta+1, ieta+1)

    hcorr.Divide(hcount)
    hcorr.SetMarkerColor(colors[ieta])
    hcorr.SetLineColor(colors[ieta])
    hcorr.SetMarkerStyle(styles[ieta])

    if ieta==0:
        hcorr.GetYaxis().SetRangeUser(0.8,1.2)
        hcorr.GetYaxis().SetTitle("#LT Corrected Response #GT")
        hcorr.GetXaxis().SetTitle("p_{T}(gen) [GeV]")
        hcorr.Draw("PE")
        leg = r.TLegend(0.65, 0.67, 0.87, 0.87)
        leg.SetLineColor(r.kWhite)
    else:
        hcorr.Draw("PE SAME")
    
    leg.AddEntry(hcorr, "{0} #leq |#eta| < {1}".format(etabins[ieta], etabins[ieta+1]))

leg.Draw()
line = r.TLine()
line.SetLineWidth(1)
line.SetLineColor(r.kBlack)
line.SetLineStyle(1)
# line.DrawLine(ptbins[0], 1, ptbins[-1], 1)
line.SetLineStyle(2)
line.DrawLine(ptbins[0], 1.02, ptbins[-1], 1.02)
line.DrawLine(ptbins[0], 0.98, ptbins[-1], 0.98)

c.SaveAs("bennettplots/{0}_L1L2closure_corr.pdf".format(algo))
c.SaveAs("bennettplots/{0}_L1L2closure_corr.png".format(algo))

for ieta in range(etabins.size-1):
    hcount = h2_respcount.ProjectionX(str(ieta)+"respcount", ieta+1, ieta+1)
    huncorr = h2_respuncorr.ProjectionX(str(ieta)+"respuncorr", ieta+1, ieta+1)

    huncorr.Divide(hcount)
    huncorr.SetMarkerColor(colors[ieta])
    huncorr.SetLineColor(colors[ieta])
    huncorr.SetMarkerStyle(styles[ieta])

    if ieta==0:
        if "puppi" in algo:
            huncorr.GetYaxis().SetRangeUser(0.5,1.3)
        else:
            huncorr.GetYaxis().SetRangeUser(0.8,1.6)            
        huncorr.GetYaxis().SetTitle("#LT Uncorrected Response #GT")
        huncorr.GetXaxis().SetTitle("p_{T}(gen) [GeV]")
        huncorr.Draw("PE")
        leg = r.TLegend(0.65, 0.67, 0.87, 0.87)
        leg.SetLineColor(r.kWhite)
    else:
        huncorr.Draw("PE SAME")
    
    leg.AddEntry(huncorr, "{0} #leq |#eta| < {1}".format(etabins[ieta], etabins[ieta+1]))

leg.Draw()
line = r.TLine()
line.SetLineWidth(1)
line.SetLineColor(r.kBlack)
line.SetLineStyle(1)
# line.DrawLine(ptbins[0], 1, ptbins[-1], 1)
line.SetLineStyle(2)
line.DrawLine(ptbins[0], 1.02, ptbins[-1], 1.02)
line.DrawLine(ptbins[0], 0.98, ptbins[-1], 0.98)

c.SaveAs("bennettplots/{0}_L1L2closure_uncorr.pdf".format(algo))
c.SaveAs("bennettplots/{0}_L1L2closure_uncorr.png".format(algo))

