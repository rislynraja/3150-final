#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./include/doctest.h"

#include <iostream>
#include <chrono>
#include <thread> 
#include <unistd.h>

#include "TimedSharedPtr.h" // control timed shared is already in timed shared
#include "Node.h"

using namespace std;

TEST_CASE("Expected Output Test") {
    TimedSharedPtr<Node> myNode(new Node(7), 100); 
    // Node holds data of 7 and expires in 100 milliseconds
    // Note: the 100 is an argument to the TimedSharedPtr constructor
    TimedSharedPtr<Node> myOtherNode = myNode;

    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // sleep for 50 milliseconds
    cout << "myNode.get() address: <" << myNode.get() << ">" << endl;

    cout << "myNode.use_count(): " << myNode.use_count() << endl;
    cout << "myOtherNode.use_count(): " << myOtherNode.use_count() << endl;

    this_thread::sleep_for(chrono::milliseconds(25)); // sleep for 25 more milliseconds
    cout << "myNode.get() address: <" << myNode.get() << ">" << endl;

    this_thread::sleep_for(chrono::milliseconds(75)); // sleep for 75 more milliseconds
    cout << "The ptr should have expired: " << endl;
    cout << "myNode.get() address: <" << myNode.get() << ">" << endl;

    cout << "-----------" << endl;
    TimedSharedPtr<int> p(new int(42));

    cout << p.get() << endl;
    cout << "p.use_count(): " << p.use_count() << endl;

    TimedSharedPtr<int> q = p;
    cout << "p.use_count(): " << p.use_count() << endl;
    cout << "q.use_count(): " << q.use_count() << endl;

}

TEST_CASE("Testing Creating TimedSharedPtr") {

    cout << "------------------------------------------------------------------------" << endl;
    cout << "END OF EXPECTED OUTPUT TEST AND START OF OUTPUT FROM TEST CASES - IGNORE" << endl;
    cout << "------------------------------------------------------------------------" << endl;

    TimedSharedPtr<Node> myNode(new Node(4), 150); // node data is 4 and expires in 150
    CHECK(myNode.get() != nullptr);  // make sure the ptr is made properly

    this_thread::sleep_for(chrono::milliseconds(50));
    CHECK(myNode.get() != nullptr);  // still valid

    this_thread::sleep_for(chrono::milliseconds(100));
    CHECK(myNode.get() == nullptr);  // expired by now - expect yeo!
}

TEST_CASE("Testing TimedSharedPtr Copy Constructor") {

    cout << "------------------------------------------" << endl;
    cout << "END OF FIRST TEST AND START OF SECOND TEST" << endl;
    cout << "------------------------------------------" << endl;

    TimedSharedPtr<Node> myNode(new Node(7), 100);
    TimedSharedPtr<Node> myOtherNode = myNode; // copy to this

    CHECK(myNode.use_count() == 2);  // use count of original of 2 after copying
    CHECK(myOtherNode.use_count() == 2);  // use count of copy of 2 after copying

    this_thread::sleep_for(chrono::milliseconds(50));
    CHECK(myNode.get() != nullptr);  // valid
    CHECK(myOtherNode.get() != nullptr);  // also valid

    this_thread::sleep_for(chrono::milliseconds(50));
    CHECK(myNode.get() == nullptr);  // expired - yeo!
    CHECK(myOtherNode.get() == nullptr); // copy should also expire since it should get the same time - yeo!
}


TEST_CASE("Testing TimedSharedPtr Expiration") {

    cout << "------------------------------------------" << endl;
    cout << "END OF SECOND TEST AND START OF THIRD TEST" << endl;
    cout << "------------------------------------------" << endl;

    TimedSharedPtr<Node> myNode(new Node(7), 100);  // 100ms expiration

    this_thread::sleep_for(chrono::milliseconds(50));
    CHECK(myNode.get() != nullptr);  // still valid - no yeo

    this_thread::sleep_for(chrono::milliseconds(75));
    CHECK(myNode.get() == nullptr);  // expired - yeo!
}

TEST_CASE("Testing TimedSharedPtr with Default Time") {

    cout << "------------------------------------------" << endl;
    cout << "END OF THIRD TEST AND START OF FOURTH TEST" << endl;
    cout << "------------------------------------------" << endl;

    TimedSharedPtr<int> p(new int(42));  // no second input so should default to 1000
    CHECK(p.get() != nullptr);  // valid

    CHECK(p.use_count() == 1);  // one at first

    TimedSharedPtr<int> q = p;  // using copy constructor
    CHECK(p.use_count() == 2);  // now 2
    CHECK(q.use_count() == 2);  // copy should also be 2

    this_thread::sleep_for(chrono::milliseconds(500));
    CHECK(p.get() != nullptr);  // valid
    CHECK(q.get() != nullptr);  // copy valid

    this_thread::sleep_for(chrono::milliseconds(500));
    CHECK(p.get() == nullptr);  // expire - yeo!
    CHECK(q.get() == nullptr);  // copy should also expire - yeo!
}

TEST_CASE("Testing TimedSharedPtr Construction and Expiration") {

    cout << "------------------------------------------" << endl;
    cout << "END OF FOURTH TEST AND START OF FIFTH TEST" << endl;
    cout << "------------------------------------------" << endl;
    
    TimedSharedPtr<Node> myNode(new Node(1), 100);  // 100ms time
    CHECK(myNode.get() != nullptr);

    this_thread::sleep_for(chrono::milliseconds(50));
    CHECK(myNode.get() != nullptr);  // valid

    this_thread::sleep_for(chrono::milliseconds(50));
    CHECK(myNode.get() == nullptr);  // expired - yeo!
    
}