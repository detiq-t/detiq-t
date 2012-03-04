#include <iostream>

#include "Image.h"

using namespace std;
using namespace imagein;

int main(int argc, char* argv[])
{
    Image ref("samples/Basketball_bug.png");
    ref.save("samples/Basketball_bug_wrote.png");
    
    return 0;
}
