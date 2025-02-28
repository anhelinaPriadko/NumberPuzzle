#include"Solver.h"
#include<iostream>

int main()
{
    try 
    {
        DataManager manager("source.txt", "output.txt");
        manager.readData();

        Solver solver(manager);
        solver.solve();
        cout << "Please, check your output file for the result!" << endl;
    }

    catch (const std::exception& ex) 
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}