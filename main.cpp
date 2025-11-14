#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.
     g++ -g -O0 main.cpp LinkedList.cpp -DMAIN -o program.o
*/

int main() {
    /*
    LinkedList<int>* hehe = new LinkedList<int>();
    (*hehe).addTail(1);
    hehe->addTail(2);
    (*hehe).addTail(3);
    (*hehe).addHead(0);
    std::cout << "Expected: 3 2 1 0" << std::endl;
    (*hehe).printReverse();
    std::cout << "Expected: 0 1 2 3" << std::endl;
    (*hehe).printForward();
    (*hehe).removeHead(); 
    (*hehe).removeTail();
    std::cout << "Expected: 1 2" << std::endl;
    (*hehe).printForward();
    (*hehe).Clear();
    std::cout << "Expected: nothing" << std::endl;
    (*hehe).printReverse();
    (*hehe).addHead(6);
    (*hehe).addTail(7);
    LinkedList<int>* haha = new LinkedList<int>(*hehe);
    LinkedList<int>* ruhroh = new LinkedList<int>();
    *ruhroh = *hehe;
    std::cout << "Expected: 6 7" << std::endl;
    (*haha).printForward();
    std::cout << "Expected: 7 6" << std::endl;
    (*ruhroh).printReverse();
    std::cout << "Expected: 6 7" << std::endl;
    (*hehe).printForward(); 
    LinkedList<int>* moveIt = new LinkedList<int>();
    (*moveIt) = std::move(*hehe);
    std::cout << "Expected: nothing" << std::endl;
    (*hehe).printReverse();
    std::cout << "Expected: 6 7" << std::endl;
    (*moveIt).printForward();
    */

    ABS<int>* bleh = new ABS<int>();
    bleh->push(1);
    bleh->push(2);
    bleh->push(3);
    bleh->push(4);
    std::cout << bleh->peek() << std::endl; 
    ABS<int>* blah = new ABS<int>(*bleh);
    std::cout << blah->peek() << std::endl; 
    ABS<int>* moved = new ABS<int>();
    moved = std::move(blah);
    std::cout << moved->peek() << std::endl; 
    bleh->push(2);
    std::cout << bleh->peek() << std::endl;
    // should print out 2;
    bleh->pop();
    bleh->pop();
    bleh->pop();
    // 
    std::cout << bleh->peek() << std::endl;

    return 0;
}


#endif