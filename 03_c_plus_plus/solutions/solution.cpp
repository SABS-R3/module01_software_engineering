#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <random>
#include <cassert>
#include <array>
#include <vector>
#include <chrono>
#include "Eigen/Core"

// Types, Flow Control & File I/O

void question1() {
    const double x = 1.0;
    const double y = 1.0;

    const double r = std::sqrt(std::pow(x,2) + std::pow(y,2));

    std::cout << "r = "<< r << std::endl;
}


void question2() {
    const int N = 1000;
    double sum = 0.0;
    for (int i = 1; i < N; ++i) {
        sum += 1.0/static_cast<double>(std::pow(i,2));
    }

    std::cout << "pi is about "<< std::sqrt(6.0*sum) << std::endl;
}

void question3() {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> uniform(-1.0,1.0);
    const int N = 1e6;
    int count = 0;
    for (int i = 0; i < N; ++i) {
        const double x = uniform(generator);
        const double y = uniform(generator);
        const double r2 = std::pow(x,2) + std::pow(y,2);

        if (r2 < 1.0) {
            ++count;
        }
    }

    std::cout << "pi is about "<< 4.0*static_cast<double>(count)/static_cast<double>(N) << std::endl;
}

void question4() {
    const int N = 100;
    double a = 1.0;
    double b = 1.0/std::sqrt(2);
    double t = 0.25;
    double p = 1.0;
    for (int i = 1; i < N; ++i) {
        const double an = a;
        const double bn = b;
        a = (an + bn)/2;
        b = std::sqrt(an*bn);
        t -= p*std::pow(a - an,2);
        p *= 2;
    }

    std::cout << "pi is about "<< std::pow(a + b,2)/(4*t) << std::endl;
}

void question5() {
    const double h = 1.0/100.0;
    double y = 1.0;
    std::ofstream output("xy.dat");
    assert(output.is_open());
    for (double x = 0; x < 1; x += h) {
        y /= 1.0 + h;
        std::cout << "outputting x = "<<x<<" y = "<< y << std::endl;
        output << x << " " << y << std::endl;
    }
    output.close();
}

void question6() {
    std::string line;
    std::ifstream input("xy.dat");
    assert(input.is_open());
    double max_error = std::numeric_limits<double>::max();
    double x,y;
    while (std::getline (input,line)) {
        std::istringstream s(line);
        s >> x;
        s >> y;
        std::cout << "reading x = "<<x<<" y = "<< y << std::endl;
        const double error = std::abs(y - std::exp(-x));
        if (max_error > error) {
            max_error = error;
        }
    }
    std::cout << "max error = "<< max_error << std::endl;
    input.close();
}

// Pointers, references and functions 

void question7_f(int *in) {
    std::cout << "old value = "<< *in << std::endl;
    *in = 4;
}

void question7() {
    int x = 3;
    question7_f(&x);
    std::cout << "new value = "<< x << std::endl;
}

void question8_fp(float *x, float *y) {
    float tmp = *x;
    *x = *y;
    *y = tmp;
}

void question8_fr(float &x, float &y) {
    float tmp = x;
    x = y;
    y = tmp;
}

void question8() {
    float x = 1.0;
    float y = 2.0;
    std::cout << "before swap: x = "<< x <<" y = "<< y << std::endl;
    question8_fp(&x,&y);
    std::cout << "after swap: x = "<< x <<" y = "<< y << std::endl;
    question8_fr(x,y);
    std::cout << "after swap: x = "<< x <<" y = "<< y << std::endl;
}



// Array and Vectors

template <long unsigned int N>
double p_norm(const std::array<double,N>& x, const unsigned int p = 2) {
    double result = 0.0;
    for (unsigned i = 0; i < x.size(); ++i) {
        result += std::pow(std::abs(x[i]),p); 
    }

    result = 0.0;
    for (double val: x) {
        result += std::pow(std::abs(val),p); 
    }

    result = 0.0;
    for (auto it = std::begin(x); it != std::end(x); ++it) {
        result += std::pow(std::abs(*it),p); 
    }

    result = std::accumulate(std::begin(x),std::end(x),0.0,
                [&](double accum, double val) { 
                    return accum + std::pow(std::abs(val),p); 
                });

    return result;
}

void question9() {
    std::array<double,5> x = {1, 2, 3, 4, 5};
    std::cout << "p_norm = "<< p_norm(x) << std::endl;
}

void question10() {
    const size_t N = 3;
    auto lp_norm = [](const std::array<double,N>& x, const unsigned int p = 2) {
        double result = 0.0;
        for (double val: x) {
            result += std::pow(std::abs(val),p); 
        }
        return result;
    };
    const double p = 2;
    auto lp_norm_cap = [p](const std::array<double,N>& x) {
        double result = 0.0;
        for (double val: x) {
            result += std::pow(std::abs(val),p); 
        }
        return result;
    };
    std::array<double,N> x = {1, 2, 3};

    std::cout << "p_norm = "<< lp_norm(x) << std::endl;
    std::cout << "p_norm = "<< lp_norm_cap(x) << std::endl;
}

double p_norm(const std::vector<double>& x, const unsigned int p = 2) {
    double result = 0.0;
    for (unsigned i = 0; i < x.size(); ++i) {
        result += std::pow(std::abs(x[i]),p); 
    }

    result = 0.0;
    for (double val: x) {
        result += std::pow(std::abs(val),p); 
    }

    result = 0.0;
    for (auto it = std::begin(x); it != std::end(x); ++it) {
        result += std::pow(std::abs(*it),p); 
    }

    result = std::accumulate(std::begin(x),std::end(x),0.0,
                [&](double accum, double val) { 
                    return accum + std::pow(std::abs(val),p); 
                });

    return result;
}


void question11() {
    const size_t n = 100;
    std::vector<double> x(n,1);
    std::cout << "p_norm = "<< p_norm(x) << std::endl;
}

std::vector<double> multiply(std::vector<double>& A, 
                             const std::array<size_t,2> Asize,
                             std::vector<double>& B,
                             const std::array<size_t,2> Bsize) {
    assert(Asize[1] == Bsize[0]);
    assert(Asize[0]*Asize[1] == A.size());
    assert(Bsize[0]*Bsize[1] == A.size());
    std::vector<double> C(Asize[0]*Bsize[1],0);

    for (size_t i = 0; i < Asize[0]; ++i) {
        for (size_t j = 0; j < Bsize[1]; ++j) {
            for (size_t k = 0; k < Asize[1]; ++k) {
                C[i*Bsize[1]+j] += A[i*Asize[1]+k] * B[k*Bsize[1]+j]; 
            }
        }
    }
    return C;
}


void question12() {
    std::vector<double> A = {5, 8, 2, 8, 3, 1, 5, 3, 9};
    std::vector<double> B = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> C = multiply(A, {3,3}, B, {3,3});

    std::cout << "C = " << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "| ";
        for (int j = 0; j < 3; ++j) {
            std::cout << C[i*3 + j];
            if (j == 2) {
                std::cout << " |" << std::endl;
            } else {
                std::cout << ", ";
            }
        }
    }
}

// Extension

// implements C += A*B
void multiply_and_add(const std::vector<double>& A, 
                      const std::array<size_t,2> Asize,
                      const std::vector<double>& B,
                      const std::array<size_t,2> Bsize,
                      std::vector<double>& C) {
    assert(Asize[1] == Bsize[0]);
    assert(Asize[0]*Asize[1] == A.size());
    assert(Bsize[0]*Bsize[1] == A.size());
    assert(C.size() == Asize[0]*Bsize[1]);

    for (size_t i = 0; i < Asize[0]; ++i) {
        for (size_t j = 0; j < Bsize[1]; ++j) {
            for (size_t k = 0; k < Asize[1]; ++k) {
                C[i*Bsize[1]+j] += A[i*Asize[1]+k] * B[k*Bsize[1]+j]; 
            }
        }
    }
}

// block = A[block_row_index:block_row_index+block_size[0],
//           block_col_index:block_col_index+block_size[1]]
void copy_block(const std::vector<double>& A, 
            const std::array<size_t,2> Asize,
            const std::array<size_t,2> block_size,
            const size_t block_row_index, 
            const size_t block_col_index,
            std::vector<double>& block) {
 
    const size_t real_row_index = block_row_index*block_size[0];
    const size_t real_col_index = block_col_index*block_size[1];
    for (size_t i = 0; i < block_size[0]; ++i) {
        for (size_t j = 0; j < block_size[1]; ++j) {
            block[i*block_size[1] + j] = A[real_row_index*Asize[1]+real_col_index];
        }
    }
}

// block = 0
void zero_block(std::vector<double>& block, 
            const std::array<size_t,2> block_size) {
 
    for (size_t i = 0; i < block_size[0]; ++i) {
        for (size_t j = 0; j < block_size[1]; ++j) {
            block[i*block_size[1] + j] = 0;
        }
    }
}

// A[block_row_index:block_row_index+block_size[0],
//   block_col_index:block_col_index+block_size[1]] = block
void write_block(std::vector<double>& A, 
                 const std::array<size_t,2> Asize,
                 const std::vector<double>& block, 
                 const std::array<size_t,2> block_size,
                 const size_t block_row_index, 
                 const size_t block_col_index) {
 
    const size_t real_row_index = block_row_index*block_size[0];
    const size_t real_col_index = block_col_index*block_size[1];
    for (size_t i = 0; i < block_size[0]; ++i) {
        for (size_t j = 0; j < block_size[1]; ++j) {
            A[real_row_index*Asize[1]+real_col_index] = block[i*block_size[1] + j];
        }
    }
}

// returns A*B using blocking, or tiling technique
std::vector<double> multiply_blocking(const std::vector<double>& A, 
                             const std::array<size_t,2> Asize,
                             const std::vector<double>& B,
                             const std::array<size_t,2> Bsize,
                             const std::array<size_t,2> block_size) {
    assert(Asize[1] == Bsize[0]);
    assert(Asize[0]*Asize[1] == A.size());
    assert(Bsize[0]*Bsize[1] == A.size());
    std::array<size_t,2> Csize = {Asize[0],Bsize[1]};
    std::vector<double> C(Asize[0]*Bsize[1],0);

    const size_t total_block_size = block_size[0]*block_size[1];

    // pre-allocate blocks
    std::vector<double> Ablock(total_block_size);
    std::vector<double> Bblock(total_block_size);
    std::vector<double> Cblock(total_block_size);

    // loop through all blocks (i,j) calculating:
    // C(i,j) = A(i,k)*B(k,j)
    for (size_t i = 0; i < Asize[0]/block_size[0]; ++i) {
        for (size_t j = 0; j < Bsize[1]/block_size[1]; ++j) {
            zero_block(Cblock,block_size);
            for (size_t k = 0; k < Asize[1]/block_size[1]; ++k) {
                copy_block(A,Asize,block_size,i,k,Ablock);
                copy_block(B,Bsize,block_size,k,j,Bblock);
                multiply_and_add(Ablock,block_size,
                                 Bblock,block_size,
                                 Cblock);
            }
            write_block(C,Csize,Cblock,block_size,i,j);
        }
    }
    return C;
}

void question13() {
    const size_t n = 1000;
    std::vector<double> A(n*n);
    std::vector<double> B(n*n);
    std::default_random_engine generator;
    std::uniform_real_distribution<double> uniform(0.0,1.0);
    for (size_t i = 0; i < n*n; ++i) {
        A[i] = uniform(generator);
        B[i] = uniform(generator);
    }

    // Calculate C = A*B using naive method
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<double> C = multiply(A,{n,n},B,{n,n});
    auto t2 = std::chrono::high_resolution_clock::now();
    auto my_time = std::chrono::duration_cast<
                        std::chrono::microseconds>(t2 - t1).count();

    // Calculate C = A*B using blocking
    t1 = std::chrono::high_resolution_clock::now();
    std::vector<double> C2 = multiply_blocking(A,{n,n},B,{n,n},{n/10,n/10});
    t2 = std::chrono::high_resolution_clock::now();
    auto my_blocking_time = std::chrono::duration_cast<
                        std::chrono::microseconds>(t2 - t1).count();

    Eigen::MatrixXd Aeigen = Eigen::MatrixXd::Random(n,n);
    Eigen::MatrixXd Beigen = Eigen::MatrixXd::Random(n,n);

    // Calculate C = A*B using Eigen
    t1 = std::chrono::high_resolution_clock::now();
    Eigen::MatrixXd Ceigen = Aeigen*Beigen;
    t2 = std::chrono::high_resolution_clock::now();
    auto eigen_time = std::chrono::duration_cast<
                        std::chrono::microseconds>(t2 - t1).count();

    // Output timings
    std::cout << "multiply without blocking = "<< my_time << 
                 " versus multiply with blocking = "<< my_blocking_time <<
                 " versus eigen time = "<< eigen_time << std::endl;
}


int main(void) {
    question1();
    question2();
    question3();
    question4();
    question5();
    question6();
    question7();
    question8();
    question9();
    question10();
    question11();
    question12();
    question13();
        
    return 0;
}
