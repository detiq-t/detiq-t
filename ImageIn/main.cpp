#include <iostream>

#include "Image.h"
#include "Algorithm.h"
#include "AlgorithmCollection.h"

using namespace std;
using namespace imagein;

int main(int argc, char* argv[])
{
    //Image ref("../QtInterface/Widgets/NavBar/test.png");
    Image ref("samples/Basketball_bug.png");
    
    cout << "cp" << endl;

    ref.save("samples/temp.png");
    
    return 0;
}
