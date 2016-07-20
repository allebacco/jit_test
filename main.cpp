#include <iostream>

#include <Reactor/Reactor.hpp>


int main(int argc, char *argv[])
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

    std::cout << "Result: " << result << std::endl;
    return 0;
}
