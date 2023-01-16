/* 
    NOTES: 
    1)I use ENGLISH language for comments because who knows whether your
    encoding algo supports RUSSIAN UTF
    2) I use A LOT of comments here

    Time complexity for serialization and deserialization is O(M + N), where
    M is the number of nodes in the list and N is the number of random node
    pointers. Thus, both serialization and deserialization have linear complexity.

    It also has an O(M) space complexity (worst case), where N is the number of 
    random connections. It is possible to improve space complexity by using more
    complex file structures such as JSON format, but external libs are prohibited
    and I don't want to implement my own JSON parser in a test assignment. 



    - I will make a lot of comments to show my line of thought.
    - I did not heavily use STL algorithms and templates since it may be 
    irrelevant and against the rules.

*/

// Only the C++ standard library
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>


// prev is head, next is tail
// head > node > node > node > node > tail
// prev > node > node > node > node > next
// snek
// ~[: ]}}}}}}}}}}}}}}}}>



// I had to rewrite the classes a bit for them to be valid in C++
// No new fields, no change in logic


class ListNode
{
public:
    
    /// @brief ListNode constructior with optional previous, next, and random nodes
    /// @param data -- data package
    /// @param prev -- previous node (head), optional
    /// @param next -- next node (tail), optional
    /// @param rand -- random node, optional
    ListNode(std::string data,ListNode* prev = nullptr,
            ListNode* next = nullptr,ListNode* rand = nullptr)
    {
        this->Prev = prev;
        this->Next = next;
        this->Data = data;
        this->Rand = rand;
    }
    ~ListNode(){}

    // It is better to make these variables private, but they were public in
    // the assigment, so I will leave them be
    ListNode* Prev = nullptr;
    ListNode* Next = nullptr;
    ListNode* Rand = nullptr;
    std::string Data;

    


    void SetRandomNode(ListNode* randNode)
    {
        this->Rand = randNode;
    }
};


class ListRand
{
public:

    // Initialize empty list
    ListRand()
    {
        this->Count = 0;
        this->Head = nullptr;
        this->Tail = nullptr;
    }
    // Initialize a list with one node
    ListRand(std::string data)
    {
        this->Count = 1;
        
        ListNode* node = new ListNode(data);
        this->Head = node;
        this->Tail = node;
    }
    ~ListRand()
    {
        this->Clear();
    }

    // It is better to make these variables private, but they were public in
    // the assigment, so I will leave them be (x2)
    ListNode* Head;
    ListNode* Tail;
    int Count;

    void Serialize(std::string source)
    {
        if (this->Count == 0)
        {
            std::cout << "List is empty, nothing to serialize" << "\n";
            return;
        }
        
        std::ofstream file;
        file.open(source);
        if (!file)
        {
            std::cout << "ERROR: Cannot open a file to read" << "\n";
            return;
        }
        

        if (file.eof())
        {
            std::cout << "ERROR: Unexpected end of the file reached!\n";
            return;
        }

        // This is a reverse lookup map
        std::map<ListNode*, int> links;

        int counter = 0;
        ListNode* NodeTmp = this->Tail;
        while (NodeTmp != nullptr && NodeTmp->Data != "" )
        {
            // Add indices for all. It will allow O(1) lookup for rand nodes
            // (depends on the implementation, as everything in C++)
            links[NodeTmp] = counter;
            
            file << NodeTmp->Data << "\n";
            NodeTmp = NodeTmp->Next;
            ++counter;
        }


        // if there are random links
        if (links.size() > 0)
        {
            // We need an empty line
            file << "\n";

            // Adds random links in a format:
            // link_from
            // link_to
            for (auto const& pair: links)
            {
                if (pair.first->Rand != nullptr)
                {
                    file << pair.second << "\n" << links[pair.first->Rand] << "\n" ;
                }
                
            }       
        }
        file.close();
    };

    void Deserialize(std::string source)
    {

        // Check if the list has any nodes. Clear them if so
        if (this->Count > 0)
        {
            this->Clear();
        }
        

        std::ifstream file;
        file.open(source);
        if (!file.is_open())
        {
            std::cout << "ERROR: Cannot open a file to read" << "\n";
            return;
        }
        
        if (!file.good())
        {
            std::cout << "ERROR: Unexpected end of the file reached!\n";
            return;
        }

        // A vector with indices
        std::vector<ListNode*> links;
        int counter = 0;
        while (file)
        {
            std::string line;
            std::getline(file,line);
            if (line != "")
            {
                this->PushBack(line);
                links.push_back(this->Head);
                ++counter;
            }
            else
            {
                break;
            }
            this->Count = counter;
        }
        while (file)
        {

            std::string line,line2;
            std::getline(file,line);
            std::getline(file,line2);
            if (line != "" && line2 != "")
            {

                ListNode *source = links[ std::stoi(line) ];
                ListNode *destination = links[ std::stoi(line2) ];
                source->Rand = destination;
            }            

        }
        file.close();
        
    };

    /// @brief clears all nodes in the list
    void Clear()
    {
        // delete Head will call a recursive deletion for all nodes
        delete this->Head;
        for (size_t i = 0; i < this->Count; i++)
        {
            void DeleteHead();
        }
        this->Count = 0;
        this->Head = nullptr;
        this->Tail = nullptr;
    }


    /// @brief adds a node to the place of the tail node
    /// @param data -- data string
    /// @param randNode -- random node (optional)
    void PushFront(std::string data, ListNode* randNode = nullptr)
    {
        if (this->Tail)
        {
            ListNode* node = new ListNode(data, nullptr, this->Tail, randNode);
            this->Tail->Prev = node;
            this->Tail = node;
        }
        else
        {
            // this means that ListRand is empty
            ListNode* node = new ListNode(data, nullptr, nullptr, nullptr);
            this->Head = node;
            this->Tail = node;
        }   
        this->Count++;
    }
    
    /// @brief adds a node to the place of the head node
    /// @param data -- data string
    /// @param randNode -- random node (optional)
    void PushBack(std::string data, ListNode* randNode = nullptr)
    {
        if (this->Head)
        {
            ListNode* node = new ListNode(data, this->Head, nullptr, randNode);
            this->Head->Next = node;
            this->Head = node;
        }
        else
        {
            // this means that ListRand is empty
            ListNode* node = new ListNode(data, nullptr, nullptr, nullptr);
            this->Head = node;
            this->Tail = node;
        }   
        this->Count++;
    }
private:
    void DeleteHead()
    {
        if (Head->Prev != nullptr)
        {
            ListNode* temporaryNode = new ListNode("A");
            temporaryNode= this->Head;
            this->Head=this->Head->Prev;
            delete(temporaryNode);
        }
    }

};


void testPrintList(const ListRand &List)
{
    std::cout << "Printing list of a size: " 
              << List.Count 
              << " From head to tail" << std::endl;

    ListNode* Node = List.Head;
    while (Node)
    {
        std::cout << "Node [" << Node << "], prev: " << Node->Prev 
                  <<" next: " << Node->Next 
                  <<" rand: " << Node->Rand 
                  <<" data: " << Node->Data
                  <<std::endl;
        Node = Node->Prev;
    }
    std::cout << std::endl;
}

void runTestNodeRandom()
{
    std::string txtPath1 = "list_serialization_test.txt";
    ListRand* List = new ListRand("0");
    std::cout << "Create a list with one node and value  \n" << std::endl;
    testPrintList(*List);

    
    std::cout << "Serializing..." << std::endl;
    List->Serialize(txtPath1); 
    std::cout << "Serialized!" << std::endl;

    std::cout << "Deserializing..." << std::endl;
    List->Deserialize(txtPath1);
    std::cout << "Deserialized result: " << std::endl;
    testPrintList(*List);
    


    std::cout << "Now PushFront five elements \n" << std::endl;
    List->PushFront("-1");
    List->PushFront("-2");
    List->PushFront("-3");
    List->PushFront("-4");
    List->PushFront("-5");

    testPrintList(*List);
    std::cout << "Make Head node to reference itself \n" << std::endl;
    
    List->Head->SetRandomNode(List->Head);
    testPrintList(*List);

    std::cout << "PushFront five elements and make Tail to reference Head \n" << std::endl;


    List->PushBack("1");
    List->PushBack("2");
    List->PushBack("3");
    List->PushBack("4");
    List->PushBack("5");
    List->Tail->SetRandomNode(List->Head);
   
    testPrintList(*List);

    std::cout << "Serializing..." << std::endl;
    List->Serialize(txtPath1); 
    std::cout << "Serialized!" << std::endl;

    std::cout << "Deserializing..." << std::endl;
    List->Deserialize(txtPath1);
    std::cout << "Deserialized result: " << std::endl;
    testPrintList(*List);
    
    
    std::cout << "Clear the list and push a string with some garbage \n" << std::endl;
    List->Clear();

    std::string randomStr = "adfa dfe323f f4f _5et 56 ; lgk;'lrkpog+===mp ig4pzm[p'][03.,[anun";
    for (size_t i = 0; i < 10; i++)
    {   
        List->PushBack(randomStr);
    }
    List->Head->SetRandomNode(List->Head);
    
    
    

    testPrintList(*List);

    std::cout << "Serializing..." << std::endl;
    List->Serialize(txtPath1); 
    std::cout << "Serialized!" << std::endl;

    std::cout << "Deserializing..." << std::endl;
    List->Deserialize(txtPath1);
    std::cout << "Deserialized result: " << std::endl;
    testPrintList(*List);



    List->Serialize(txtPath1);
    List->Clear();
    delete List;
}


int main(int argc, const char** argv) {
    runTestNodeRandom();
    return 0;
}
