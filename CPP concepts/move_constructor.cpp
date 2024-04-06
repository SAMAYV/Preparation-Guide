#include <iostream>
#include <vector>

class Container {
    int * m_Data;
public:
    Container() {
        //Allocate an array of 20 int on heap
        m_Data = new int[20];

        std::cout << "Constructor: Allocation 20 int" << std::endl;
    }
    ~Container() {
        if (m_Data) {
            delete[] m_Data;
            m_Data = NULL;
        }
    }
    //Copy Constructor
    Container(const Container & obj) {
        //Allocate an array of 20 int on heap
        m_Data = new int[20];

        //Copy the data from passed object
        for (int i = 0; i < 20; i++)
            m_Data[i] = obj.m_Data[i];

        std::cout << "Copy Constructor: Allocation 20 int" << std::endl;
    }

    //Assignment Operator
    Container & operator=(const Container & obj) {

        if(this != &obj)
        {
            //Allocate an array of 20 int on heap
            m_Data = new int[20];

            //Copy the data from passed object
            for (int i = 0; i < 20; i++)
                m_Data[i] = obj.m_Data[i];

            std::cout << "Assigment Operator: Allocation 20 int" << std::endl;
        }
    }

    // Move Constructor
    Container(Container && obj)
    {
        // Just copy the pointer
        m_Data = obj.m_Data;

        // Set the passed object's member to NULL
        obj.m_Data = NULL;

        std::cout<<"Move Constructor"<<std::endl;
    }

    // Move Assignment Operator
    Container& operator=(Container && obj)
    {
        if(this != &obj)
        {
            // Just copy the pointer
            m_Data = obj.m_Data;

            // Set the passed object's member to NULL
            obj.m_Data = NULL;

            std::cout<<"Move Assignment Operator"<<std::endl;
        }
    }

};

// Create am object of Container and return
Container getContainer()
{
    Container obj;
    return obj;
}
int main() {
    // Create a vector of Container Type
    std::vector<Container> vecOfContainers;

    //Add object returned by function into the vector
    vecOfContainers.push_back(getContainer());

    Container obj;
    obj = getContainer();

    return 0;
}