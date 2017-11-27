#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>


using namespace std;
int main(int argc, char const *argv[]) {
    int filename;

    ofstream myfile;

    cout << "Making A.I. file for " << argv[1] << std::endl;
    std::string cpp("_ai.cpp");
    std::string h("_ai.h");
    std::string name(argv[1]);

    myfile.open((name + h).c_str());
    myfile << "// IMPORTANT: this file is only to be included into drivers.h and nowhere else" << std::endl;
    myfile << "class " << name << "_ai : public Driver_t {";
    myfile << "public:" << std::endl;
    myfile << "    Turn_t steer(Grid_t *grid);" << std::endl;
    myfile << "};" << std::endl;
    myfile.close();


    myfile.open((name + cpp).c_str());
    myfile << "// IMPORTANT: this file is only to be included into drivers.cpp and nowhere else" << std::endl;
    myfile << "Turn_t " << name << "_ai ::steer(Grid_t *grid) {" << std::endl;
    myfile << "    return(getTurn(getJoystickDirection(this->myBike->getDirection()), this->myBike->getDirection()));" << std::endl;
    myfile << "}" << std::endl;
    myfile.close();

    return(0);
}
