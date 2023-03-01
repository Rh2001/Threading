// Threading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//A beginner program in C++ comparing the different execution times of a single threaded application compared to that of multithreaded ones





#include <iostream>  //standard input output stream
#include <thread>    //threading capabilities for C++11 and higher
#include <chrono>    //time retrieval and display : refer to chrono documentation
#include <fstream>   //standard file stream




void func1(int loop_count)   //simple function 
{
    int i1{ 0 };   //decleration method used in modern C++ ---- is the same as int i1 = 0;
    int i2{ 0 };
    int temp{ 0 }; 
    std::cout << "executing" << std::endl;
    std::cout << "sleeping this thread for 2 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));        //thread should stop executing for 2 seconds

    for (int i =0;i< loop_count; i++)     //time consuming empty for loop for the sake of demonstration 
    {
        std::cout << "Starting swap algorithm loop: " << i << std::endl;
        temp = i1;
        i1 = i2;
        i2 = temp;

        temp = i2;
        i2 = i1;
        temp = i2;

        std::cout << "Swap algorithm number: " << i << " finished execution"  << std::endl;

    }
    std::cout << "executing" << std::endl;
    std::cout << "returning to main" << std::endl;

}
void func2(int loop_count)
{
    int i1{ 0 };   
    int i2{ 0 };
    int temp{ 0 };

    std::cout << "executing" << std::endl;
    std::cout << "sleeping this thread for 1 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));      //thread should stop executing for 1 second
    std::cout << "executing" << std::endl;
    for (int i = 0;i < loop_count; i++)     //time consuming swap algorithm for the sake of demonstration 
    {
        std::cout << "Starting swap algorithm loop: " << i << std::endl;
        temp = i1;
        i1 = i2;
        i2 = temp;

        temp = i2;
        i2 = i1;
        temp = i2;

        std::cout << "Swap algorithm number: " << i << " finished execution" << std::endl;

    }
    std::cout << "returning to main" << std::endl;

}


int main()
{
    bool userchoice;
    int *loop_count = new int;      //allocate 4 bytes of data for loop_count variable

    std::cout << "A test for the amount of time spent running the same functions on the main thread vs separating them into two threads" << std::endl;
    std::cout << "enter the number 0 for single thread execution time and 1 for multithreading execution time" << std::endl;
    std::cin >> userchoice;

    std::cout << "Now enter the number of loops the swap algorithm should execute on each thread:" << std::endl;
    std::cout << "Note: results may vary depending on the number of loops you enter" << std::endl;

    std::cin >> *loop_count;




    std::cout << "\n starting the proccess.... " << std::endl;

    if (userchoice == 0) {
        auto start_time = std::chrono::system_clock::now();
        func1(*loop_count);   //pass by value 
        func2(*loop_count);
        auto end_time = std::chrono::system_clock::now();;

        std::cout << "Executiog finished..." << std::endl;
        std::cout << "Ran " << *loop_count << " loops on one thread sequentially " << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::chrono::duration<double> timeSpent = end_time - start_time;
        std::cout << "execution took: " <<  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << " milliseconds" << std::endl;  //turns the start_time and end_time variables into a printable one
        std::cout << "and " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " nanoseconds" << std::endl;




        std::ofstream file;
        file.open("log.txt");
        file << "loop count: " << *loop_count;
        file << " time spent: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << " milliseconds";
        file << " time spent: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " nanoseconds";
        file.close();
        delete loop_count;
    }
    else
    {
        auto start_time = std::chrono::system_clock::now();

       

        std::thread t1(func1, *loop_count);   //run func1 on thread called t1 which is separated from main thread of the application and takes the parameter loop_count
        std::thread t2(func2, *loop_count);
        std::cout << "Waiting on threads to finish their execution...." << std::endl;
        t1.join();
        t2.join();
        auto end_time = std::chrono::system_clock::now();;
        std::cout << "Execution finished..." << std::endl;
        std::cout << "Ran " << *loop_count << " loops on 2 threads each " << std::endl;
       
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));



        std::chrono::duration<double> timeSpent = end_time - start_time;
        std::cout << "execution took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << " milliseconds" << std::endl;
        std::cout << "and " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " nanoseconds" << std::endl;



        std::ofstream file;   //for logging the results
        file.open("log.txt");
        file << "loop count: " << *loop_count;
        file << " time spent: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        file << " time spent: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " nanoseconds";
        file.close();
        delete loop_count;

    }

    

    std::cout << "Press any key to terminate the application" << std::endl;
    
   
    
}


//conclusion drawn from this example demonstrates how multi threading is not always the fastest


