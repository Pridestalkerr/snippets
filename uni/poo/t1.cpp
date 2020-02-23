#include<fstream>
#include<iostream>
#include<list>
#include<vector>
class complex_matrix;
class complex{
    float real_part;
    float imaginary_part;
public:
    complex()
    {
        real_part = 0;
        imaginary_part = 0;
    }
    complex(const float real_part_value, const float imaginary_part_value)
    {
        real_part = real_part_value;
        imaginary_part = imaginary_part_value;
    }
    complex operator + (const complex summand)
    {
        complex sum(real_part + summand.real_part, imaginary_part + summand.imaginary_part);
        return sum;
    }
    complex operator - (const complex subtrahend)
    {
        complex difference(real_part - subtrahend.real_part, imaginary_part - subtrahend.imaginary_part);
        return difference;
    }
    complex operator * (const complex factor)
    {
        complex product((real_part * factor.real_part) - (imaginary_part * factor.imaginary_part), (real_part * factor.imaginary_part) + (imaginary_part * factor.real_part));
        return product;
    }
    complex operator / (const complex divisor)
    {
        complex division(((real_part * divisor.real_part) + (imaginary_part * divisor.imaginary_part)) / ((divisor.real_part * divisor.real_part) + (divisor.imaginary_part * divisor.imaginary_part)), ((imaginary_part * divisor.real_part) - (real_part * divisor.imaginary_part)) / ((divisor.real_part * divisor.real_part) + (divisor.imaginary_part * divisor.imaginary_part)));
        return division;
    }
    friend std::ostream& operator << (std::ostream& out, const complex to_print);
    friend std::istream& operator >> (std::istream& in, complex &to_scan);
    friend std::istream& operator >> (std::istream& in, complex_matrix &to_scan);
    friend complex_matrix;
};
std::ostream& operator << (std::ostream& out, const complex to_print)
{
    /* too lazy to do this also need to find a better way cause this is too ugly
    bool is_zero = true;
    if(to_print.real_part != 0)
    {
        out << to_print.real_part;
        is_zero = false;
    }
    if(to_print.imaginary_part != 0)
    {
        if(is_zero == false)
            out << std::showpos << to_print.imaginary_part << std::noshowpos << "i";
        else
            out << to_print.imaginary_part << "i";
        is_zero = false;
    }
    if(is_zero == true)
        out << 0;
    */
    out << to_print.real_part << std::showpos << to_print.imaginary_part << std::noshowpos << "i";
    return out;
}
std::istream& operator >> (std::istream& in, complex &to_scan)
{
    in >> to_scan.real_part >> to_scan.imaginary_part;
    in.ignore(1); //needed?
    return in;
}

class complex_matrix{
    int height, width;
    std::list <std::pair <int, std::list <std::pair <int, complex>>>> data;
    void getCofactor(std::vector <std::vector <complex>> A, std::vector <std::vector <complex>> &temp, int p, int q, int n)
    {
        int i = 0, j = 0;

        // Looping for each element of the matrix
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                //  Copying into temporary matrix only those element
                //  which are not in given row and column
                if (row != p && col != q)
                {
                    temp[i][j++] = A[row][col];

                    // Row is filled, so increase row index and
                    // reset col index
                    if (j == n - 1)
                    {
                        j = 0;
                        i++;
                    }
                }
            }
        }
    }
    void adjoint(std::vector <std::vector <complex>> A, std::vector <std::vector <complex>> &adj)
    {
        if (height == 1)
        {
            adj[0][0] = complex(1, 0);
            return;
        }

        // temp is used to store cofactors of A[][]
        complex sign(1, 0);
        std::vector <std::vector <complex>> temp(height, std::vector <complex> (width, complex(0, 0)));

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                // Get cofactor of A[i][j]
                getCofactor(A, temp, i, j, height);

                // sign of adj[j][i] positive if sum of row
                // and column indexes is even.
                sign.real_part = ((i+j)%2==0)? 1: -1;

                // Interchanging rows and columns to get the
                // transpose of the cofactor matrix
                adj[j][i] = (sign)*det(height-1, temp);
            }
        }
    }
    complex det(int n, std::vector <std::vector <complex>> mat)
    {
        int c, i, j;
        complex d;
        if (n == 2)
        {
            return( (mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
        }
        else
        {
            for(c = 0; c < n; c++)
            {
                std::vector <std::vector <complex>> submat;
                for(i = 1; i < n; i++)
                {
                    std::vector <complex> submat_line;
                    for(j = 0; j < n; j++)
                    {
                        if (j == c)
                        {
                            continue;
                        }
                        submat_line.push_back(mat[i][j]);
                    }
                    submat.push_back(submat_line);
                }
                complex x(c%2 ? -1 : 1, 0);
                d = d + (x  * mat[0][c] * det(n - 1 , submat));
            }
        }
        return d;
    }
    std::vector <std::vector <complex>> extend()
    {
        std::vector <std::vector <complex>> extended;
        auto itr = data.begin();
        for(int i = 0; i < height; ++i)
        {
            std::vector <complex> extended_line;
            if((*itr).first != i || itr == data.end())
            {
                for(int j = 0; j < width; ++j)
                {
                    complex zero(0, 0);
                    extended_line.push_back(zero);
                }
            }
            else
            {
                auto itr2 = (*itr).second.begin();
                for(int j = 0; j < width; ++j)
                {
                    if((*itr2).first != j || itr2 == (*itr).second.end())
                    {
                        complex zero(0, 0);
                        extended_line.push_back(zero);
                    }
                    else
                    {
                        extended_line.push_back((*itr2).second);
                        if(itr2 != (*itr).second.end())
                            itr2++;
                    }
                }
                if(itr != data.end())
                    itr++;
            }
            extended.push_back(extended_line);
        }
        return extended;
    }
public:
    complex_matrix operator + (const complex_matrix summand)
    {
        complex_matrix sum;
        if(this->height != summand.height || this->width != summand.width)
        {
            std::cout<<std::endl<<"Matrices of different sizes. Can't perform addition. Returning (presumably) empty matrix."<<std::endl;
            return sum;
        }
        sum.height = summand.height;
        sum.width = summand.width;
        auto term1_itr = this->data.begin();
        auto term2_itr = summand.data.begin();
        while(term1_itr != this->data.end() || term2_itr != summand.data.end())
        {
            if(term1_itr == this->data.end())
            {
                sum.data.push_back(*term2_itr);
                term2_itr++;
                continue;
            }
            if(term2_itr == summand.data.end())
            {
                sum.data.push_back(*term1_itr);
                term1_itr++;
                continue;
            }
            //we split to not dereference pointers
            if(term1_itr->first > term2_itr->first)
            {
                sum.data.push_back(*term2_itr);
                term2_itr++;
                continue;
            }
            if(term1_itr->first < term2_itr->first)
            {
                sum.data.push_back(*term1_itr);
                term1_itr++;
                continue;
            }
            //sum case
            auto term1_line_itr = term1_itr->second.begin();
            auto term2_line_itr = term2_itr->second.begin();
            std::list <std::pair <int, complex>> line_sum;
            while(term1_line_itr != term1_itr->second.end() || term2_line_itr != term2_itr->second.end())
            {
                if(term1_line_itr == term1_itr->second.end())
                {
                    line_sum.push_back(*term2_line_itr);
                    term2_line_itr++;
                    continue;
                }
                if(term2_line_itr == term2_itr->second.end())
                {
                    line_sum.push_back(*term1_line_itr);
                    term1_line_itr++;
                    continue;
                }
                //we split to not dereference pointers
                if(term1_line_itr->first > term2_line_itr->first)
                {
                    line_sum.push_back(*term2_line_itr);
                    term2_line_itr++;
                    continue;
                }
                if(term1_line_itr->first < term2_line_itr->first)
                {
                    line_sum.push_back(*term1_line_itr);
                    term1_line_itr++;
                    continue;
                }
                //sum case
                line_sum.push_back({term1_line_itr->first, term1_line_itr->second + term2_line_itr->second});
                term1_line_itr++;
                term2_line_itr++;
            }
            sum.data.push_back({term1_itr->first, line_sum});
            term1_itr++;
            term2_itr++;
        }
        return sum;
    }
    complex_matrix operator * (const complex_matrix factor)
    {
        complex_matrix product;
        if(this->width != factor.height)
        {
            std::cout<<std::endl<<"Matrices of different sizes. Can't perform multiplication. Returning (presumably) empty matrix."<<std::endl;
            return product;
        }
        product.height = this->height;
        product.width = factor.width;
        auto term1_itr = this->data.begin();
        std::list <std::pair <int, complex>> null_line;
        for(int i = 0; i < product.width; ++i)
            null_line.push_back({i, complex(0, 0)});
        for(int i = 0; i < product.height; ++i)
        {
            if(term1_itr == this->data.end())
            {
                for(int j = i; j < product.height; ++j)
                    product.data.push_back({j, null_line});
                break;
            }

            if(term1_itr->first != i)
            {
                //null line
                product.data.push_back({i, null_line});
            }
            else
            {
                std::list <std::pair <int, complex>> new_line;
                for(int j = 0; j < product.width; ++j)
                {
                    //line (t1) isnt null
                    complex value_to_push;
                    auto term1_line_itr = term1_itr->second.begin();
                    auto term2_itr = factor.data.begin();
                    while(term1_line_itr != term1_itr->second.end() && term2_itr != factor.data.end())
                    {
                        if(term1_line_itr->first < term2_itr->first)
                        {
                            term1_line_itr++;
                            continue;
                        }
                        if(term1_line_itr->first > term2_itr->first)
                        {
                            term2_itr++;
                            continue;
                        }
                        //look for column (j) in term2 line
                        for(auto term2_line_itr = term2_itr->second.begin(); term2_line_itr != term2_itr->second.end() && term2_line_itr->first <= j; ++term2_line_itr)
                        {
                            if(term2_line_itr->first == j)
                            {
                                value_to_push = value_to_push + (term1_line_itr->second * term2_line_itr->second);
                            }
                        }
                        term1_line_itr++;
                        term2_itr++;
                    }
                    if(value_to_push.real_part != 0 || value_to_push.imaginary_part != 0)
                        new_line.push_back({j, value_to_push});
                }
                if(new_line.size() != 0)
                    product.data.push_back({i, new_line});
                term1_itr++;
            }
        }
        return product;
    }
    complex determinant()
    {
        if(width!=height)
        {
            std::cout << "Called determinant on non square matrix. Returning 0.";
            complex zero(0, 0);
            return zero;
        }
        auto extended = extend();
        return det(height, extended);
    }
    void inverse() //rights to geeksforgeeks.com
    {
        // Find determinant of A[][]
        complex det = determinant();
        if (det.imaginary_part == 0 && det.real_part == 0)
        {
            std::cout << "Singular matrix, can't find its inverse.";
            return;
        }

        // Find adjoint
        auto extended = extend();
        std::vector <std::vector <complex>> adj(height, std::vector <complex> (width, complex(0, 0)));
        adjoint(extended, adj);

        // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
                std::cout << adj[i][j] / det<< ' ';
            std::cout<<std::endl;
        }
    }
    friend std::ostream& operator << (std::ostream& out, complex_matrix &to_print);
    friend std::istream& operator >> (std::istream& in, complex_matrix &to_scan);
};
std::ostream& operator << (std::ostream& out, complex_matrix &to_print)
{
    auto itr = to_print.data.begin();
    for(int i = 0; i < to_print.height; ++i)
    {
        if((*itr).first != i || itr == to_print.data.end())
        {
            for(int j = 0; j < to_print.width; ++j)
                std::cout << "0+0i ";
        }
        else
        {
            auto itr2 = (*itr).second.begin();
            for(int j = 0; j < to_print.width; ++j)
            {
                if((*itr2).first != j || itr2 == (*itr).second.end())
                    std::cout << "0+0i ";
                else
                {
                    std::cout << (*itr2).second << " ";
                    if(itr2 != (*itr).second.end())
                        itr2++;
                }
            }
            if(itr != to_print.data.end())
                itr++;
        }
        std::cout << "\n";
    }
    return out;
}
std::istream& operator >> (std::istream& in, complex_matrix &to_scan)
{
    in >> to_scan.height >> to_scan.width;
    for(int i = 0; i < to_scan.height; ++i)
    {
        std::list <std::pair <int, complex>> line;
        for(int j=0; j < to_scan.width; ++j)
        {
            complex value;
            in >> value;
            if(value.real_part != 0 || value.imaginary_part != 0)
                line.push_back({j, value});
        }
        if(line.size() != 0)
            to_scan.data.push_back({i, line});
    }
    return in;
}

int main()
{
    std::ifstream f("uwu.in");
    complex_matrix a,b,c;
    f>>a>>c;
    std::cout<<a<<c;
    b = a+c;
    std::cout<<b;
    b= a*c;
    std::cout<<b;
    complex_matrix d;
    f>>d;
    std::cout<<d.determinant()<<std::endl;
    d.inverse();
    return 0;
}
