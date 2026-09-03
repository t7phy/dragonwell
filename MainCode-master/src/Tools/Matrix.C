#ifndef MATRIX_SOURCE
#define MATRIX_SOURCE

#include "Tools/Tools.h"

void RowTransform0(int i, double scale, int j, TH2D *matrix)
{


    int XNBins = matrix->GetXaxis()->GetNbins();

    int YNBins = matrix->GetYaxis()->GetNbins();


    for (int k = 0; k < XNBins; k++)
    {
        double val = matrix->GetBinContent(k + 1, j + 1) + matrix->GetBinContent(k + 1, i + 1) * scale;
        double val_err = sqrt(matrix->GetBinError(k + 1, j + 1) * matrix->GetBinError(k + 1, j + 1) +
                              matrix->GetBinError(k + 1, i + 1) * matrix->GetBinError(k + 1, i + 1) * scale * scale);

        matrix->SetBinContent(k + 1, j + 1, val);
        matrix->SetBinError(k + 1, j + 1, val_err);
    }
}

void RowScale0(int i, double scale, TH2D *matrix)
{

    int XNBins = matrix->GetXaxis()->GetNbins();

    int YNBins = matrix->GetYaxis()->GetNbins();


    for (int k = 0; k < XNBins; k++)
    {
        double val = matrix->GetBinContent(k + 1, i + 1) * scale;
        double val_err = sqrt(matrix->GetBinError(k + 1, i + 1) * matrix->GetBinError(k + 1, i + 1) * scale * scale);

        matrix->SetBinContent(k + 1, i + 1, val);
        matrix->SetBinError(k + 1, i + 1, val_err);
    }
}

void ReverseMatrix(TH2D *matrix, TH2D *reverse)
{

    int binx = matrix->GetXaxis()->GetNbins();
    int biny = matrix->GetYaxis()->GetNbins();


    TH2D *temp = new TH2D("temp", "temp", binx, 0, binx, biny, 0, biny);
    temp->Sumw2();

    for (int i = 0; i < binx; i++)
    {
        for (int j = 0; j < binx; j++)
        {
            temp->SetBinContent(i + 1, j + 1, matrix->GetBinContent(i + 1, j + 1));
            temp->SetBinError(i + 1, j + 1, 0);

            if (i == j)
            {
                reverse->SetBinContent(i + 1, j + 1, 1);
                reverse->SetBinError(i + 1, j + 1, 0);
            }
            else
            {
                reverse->SetBinContent(i + 1, j + 1, 0);
                reverse->SetBinError(i + 1, j + 1, 0);
            }
        }
    }

    for (int i = 0; i < binx; i++)
    {
        double scale;
        for (int j = 0; j < binx; j++)
        {
            if (i == j)
                continue;
            scale = -temp->GetBinContent(i + 1, j + 1) / temp->GetBinContent(i + 1, i + 1);
            RowTransform0(i, scale, j, temp);
            RowTransform0(i, scale, j, reverse);
        }
        scale = 1.0 / temp->GetBinContent(i + 1, i + 1);
        RowScale0(i, scale, temp);
        RowScale0(i, scale, reverse);
    }

    for (int i = 0; i < binx; i++)
    {
        for (int j = 0; j < binx; j++)
        {
            double sum = 0;
            for (int k = 0; k < binx; k++)
                sum = sum + matrix->GetBinContent(i + 1, k + 1) * reverse->GetBinContent(k + 1, j + 1);
        }
    }

    delete temp;
}
void MatrixDotVector(TH2D *matrix, TH1D *vec, TH1D *result)
{

    int binx = matrix->GetXaxis()->GetNbins();
    int biny = matrix->GetYaxis()->GetNbins();


    for (int i = 0; i < biny; i++)
    {
        double sum = 0;
        for (int j = 0; j < binx; j++)
            sum = sum + matrix->GetBinContent(j + 1, i + 1) * vec->GetBinContent(j + 1);
        result->SetBinContent(i + 1, sum);
        result->SetBinError(i + 1, 0);
    }
}

void SolveLinearEquation(TH2D *A, TH1D *X, TH1D *B)
{

    int binx = A->GetXaxis()->GetNbins();
    int biny = A->GetYaxis()->GetNbins();

    TH2D *A_Reverse = (TH2D *)A->Clone("A_Reverse");
    ReverseMatrix(A, A_Reverse);
    MatrixDotVector(A_Reverse, B, X);

    delete A_Reverse;
}

void VectorDotVector(TH1D *vec1, TH1D *vec2, double &result)
{


    int binx = vec1->GetXaxis()->GetNbins();

    result = 0;

    for (int i = 0; i < binx; i++)
        result = result + vec1->GetBinContent(i + 1) * vec2->GetBinContent(i + 1);
}
void VectorDotVector(TH1D *vec1, TH1D *vec2, TH2D *result)
{

    int binx = vec1->GetXaxis()->GetNbins();

    for (int i = 0; i < binx; i++)
        for (int j = 0; j < binx; j++)
        {
            result->SetBinContent(i + 1, j + 1, vec1->GetBinContent(i + 1) * vec2->GetBinContent(j + 1));
            result->SetBinError(i + 1, j + 1, 0);
        }
}
void SearchEigenVector(TH2D *matrix, double &val, TH1D *vec, double lim)
{

    int binx = matrix->GetXaxis()->GetNbins();
    int biny = matrix->GetYaxis()->GetNbins();

    TH1D *temp_vec = (TH1D *)vec->Clone("temp_vec");
    TH1D *temp_vec_last = (TH1D *)vec->Clone("temp_vec_last");
    TH1D *temp_normvec_last = (TH1D *)vec->Clone("temp_normvec_last");
    TH1D *temp_delta = (TH1D *)vec->Clone("temp_delta");

    for (int i = 0; i < binx; i++)
    {
        temp_vec->SetBinContent(i + 1, matrix->GetBinContent(i + 1, i + 1));
        temp_vec->SetBinError(i + 1, 0);
    }

    double scale;
    double precision;
    do
    {
        VectorDotVector(temp_vec, temp_vec, scale);
        scale = sqrt(scale);
        for (int i = 0; i < binx; i++)
        {
            temp_vec_last->SetBinContent(i + 1, temp_vec->GetBinContent(i + 1));
            temp_normvec_last->SetBinContent(i + 1, temp_vec->GetBinContent(i + 1) / scale);

            temp_vec_last->SetBinError(i + 1, 0);
            temp_normvec_last->SetBinError(i + 1, 0);
        }

        MatrixDotVector(matrix, temp_vec_last, temp_vec);

        for (int i = 0; i < binx; i++)
        {
            temp_delta->SetBinContent(i + 1, temp_vec->GetBinContent(i + 1) - temp_vec_last->GetBinContent(i + 1));
            temp_delta->SetBinError(i + 1, 0);
        }

        VectorDotVector(temp_delta, temp_delta, precision);
        precision = sqrt(precision);
    } while (precision > lim);

    VectorDotVector(temp_vec, temp_vec, scale);
    scale = sqrt(scale);
    for (int i = 0; i < binx; i++)
    {
        vec->SetBinContent(i + 1, temp_vec->GetBinContent(i + 1) / scale);
        vec->SetBinError(i + 1, 0);
    }

    MatrixDotVector(matrix, vec, temp_vec);
    val = temp_vec->GetBinContent(1) / vec->GetBinContent(1);

    delete temp_vec;
    delete temp_vec_last;
    delete temp_normvec_last;
    delete temp_delta;
}

void SearchAllEigenVector(TH2D *matrix, double *val, TH1D **vec, double lim)
{

    int binx = matrix->GetXaxis()->GetNbins();
    int biny = matrix->GetYaxis()->GetNbins();

    TH2D *temp_matrix = (TH2D *)matrix->Clone("temp_matrix");
    TH2D *temp_remove = (TH2D *)matrix->Clone("temp_remove");
    TH1D *temp_vec = (TH1D *)vec[0]->Clone("temp_vec");

    for (int i = 0; i < binx; i++)
    {
        SearchEigenVector(temp_matrix, val[i], vec[i], lim);

        double scale;
        VectorDotVector(vec[i], vec[i], scale);
        scale = sqrt(scale);

        for (int j = 0; j < binx; j++)
        {
            temp_vec->SetBinContent(j + 1, vec[i]->GetBinContent(j + 1) / scale);
            temp_vec->SetBinError(j + 1, 0);
        }

        VectorDotVector(temp_vec, temp_vec, temp_remove);
        temp_remove->Scale(val[i]);

        temp_matrix->Add(temp_remove, -1);
    }

    delete temp_matrix;
    delete temp_remove;
    delete temp_vec;
}

#endif
