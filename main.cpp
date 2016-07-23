#include <iostream>

#include <Reactor/Reactor.hpp>


void test_int()
{
    sw::Function<sw::Int(sw::Int, sw::Int)> function;
    {
        sw::Int x = function.Arg<0>();
        sw::Int y = function.Arg<1>();

        sw::Int sum = x + y;

        sw::Return(sum);
    }

    sw::Routine* routine = function(L"sum_function");
    int (*callable)(int,int) = (int(*)(int,int))routine->getEntry();
    int result = callable(2, 3);

    std::cout << "test_int: " << (result == (2+3)) << std::endl;
    delete routine;
}


void test_double_assignement()
{
    sw::Function<sw::Void(sw::Double, sw::Pointer<sw::Double>)> function;
    {
        sw::Double x = function.Arg<0>();
        sw::Pointer<sw::Double> y = function.Arg<1>();

        *y = x;

        sw::Return();
    }

    sw::Routine* routine = function(L"sum_function");
    void (*callable)(double,double*) = (void(*)(double,double*))routine->getEntry();
    double dest = 0.0;
    callable(1e150, &dest);

    std::cout << "test_double_assignement: " << (dest == 1e150) << std::endl;
    delete routine;
}


void test_double_const_assignement()
{
    double value = 1e-150;

    sw::Function<sw::Void(sw::Pointer<sw::Double>)> function;
    {
        sw::Pointer<sw::Double> y = function.Arg<0>();

        *y = sw::Double(value);

        sw::Return();
    }

    sw::Routine* routine = function(L"sum_function");
    void (*callable)(double*) = (void(*)(double*))routine->getEntry();
    double dest = 0.0;
    callable(&dest);

    std::cout << "test_double_const_assignement: " << (dest == value) << std::endl;
    delete routine;
}


void test_double_simple_math()
{

    sw::Function<sw::Void(sw::Double, sw::Double, sw::Double, sw::Pointer<sw::Double>)> function;
    {
        sw::Double x = function.Arg<0>();
        sw::Double y = function.Arg<1>();
        sw::Double z = function.Arg<2>();
        sw::Pointer<sw::Double> res = function.Arg<3>();

        sw::Double w = x + y * z / x - sw::Double(0.00000000010);
        w += z;
        w *= x;
        w -= z;
        w /= sw::Double(2.0);

        *res = w;

        sw::Return();
    }

    double a = 0.001;
    double b = 0.101;
    double c = 0.011;
    double d = a + b * c / a - 0.00000000010;
    d += c;
    d *= a;
    d -= c;
    d /= 2.0;
    double ref_value = d;

    sw::Routine* routine = function(L"sum_function");
    void (*callable)(double,double,double,double*) = (void(*)(double,double,double,double*))routine->getEntry();
    double dest = 0.0;
    callable(a, b, c, &dest);

    std::cout << "test_double_simple_math: " << (dest == ref_value) << std::endl;
    delete routine;
}


int main(int argc, char *argv[])
{
    test_int();
    test_double_assignement();
    test_double_const_assignement();
    test_double_simple_math();


    return 0;
}
