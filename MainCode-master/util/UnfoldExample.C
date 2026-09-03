#include <iostream>
#include <TRandom3.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <RooUnfoldResponse.h>
#include <RooUnfoldBayes.h>

int main() {
    // Random number generator for simulation
    TRandom3 random;

    // Create histograms for true and measured distributions
    TH1D* hTrue = new TH1D("hTrue", "True Distribution", 40, 0.0, 10.0);
    TH1D* hMeasured = new TH1D("hMeasured", "Measured Distribution", 40, 0.0, 10.0);

    // Response matrix
    RooUnfoldResponse response(hMeasured, hTrue);

    // Simulate events (filling the response matrix)
    for (int i = 0; i < 10000; ++i) {
        double trueValue = random.Gaus(5.0, 1.0);  // True value with Gaussian distribution
        double measuredValue = random.Gaus(trueValue, 0.5);  // Measured with detector resolution

        // Fill the response matrix with true and measured values
        response.Fill(measuredValue, trueValue);

        // Fill true and measured histograms
        hTrue->Fill(trueValue);
        hMeasured->Fill(measuredValue);
    }

    // Perform Bayesian unfolding with 4 iterations
    RooUnfoldBayes unfold(&response, hMeasured, 4);
    TH1D* hUnfolded = (TH1D*)unfold.Hreco();

    // Draw the histograms
    TCanvas* canvas = new TCanvas("canvas", "Unfolding Example", 800, 600);
    hMeasured->SetLineColor(kRed);
    hUnfolded->SetLineColor(kBlue);
    hTrue->SetLineColor(kGreen);

    hMeasured->Draw("HIST");
    hUnfolded->Draw("HISTSAME");
    hTrue->Draw("HISTSAME");

    // Add a legend
    auto legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(hMeasured, "Measured", "l");
    legend->AddEntry(hUnfolded, "Unfolded", "l");
    legend->AddEntry(hTrue, "True", "l");
    legend->Draw();

    // Save the canvas
    canvas->SaveAs("unfolding_example.png");

    // Clean up
    delete hTrue;
    delete hMeasured;
    delete hUnfolded;
    delete canvas;

    return 0;
}

