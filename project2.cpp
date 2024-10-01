#include <iostream>
#include <string>
using namespace std;

class Chip {
private:
    char chipType;      // Type of the chip (A: Addition, S: Subtraction, etc.)
    string id;          // Unique identifier for the chip
    Chip* input1;       // Pointer to the first input chip
    Chip* input2;       // Pointer to the second input chip (can be NULL)
    Chip* output;       // Ptr to the output chip (is NULL for output chips)
    double inputValue;  // For the input chip

public:
    // Constructor
    Chip(char type, const string& id){
        chipType = type;
        this->id = id;
        input1 = NULL;
        input2 = NULL;
        output = NULL;
        inputValue = 0.0;
    }

    // Method to set inputs and outputs
    void setInput1(Chip* inputChip){
        if (input1 == NULL) {
            input1 = inputChip;
        } else {
            cout << "Warning: " << id << " already has Input 1 connected!" << endl;
        }
    }

    void setInput2(Chip* inputChip){
        if (input2 == NULL) {
            input2 = inputChip;
        } else {
            cout << "Warning: " << id << " already has Input 2 connected!" << endl;
        }
    }

    void setOutput(Chip* outputChip){
        if (output == NULL) {
            output = outputChip;
        } else {
            cout << "Warning: " << id << " already has an output connected!" << endl;
        }
    }

    void setInputValue(double value) {
        inputValue = value;
    }

    string getid() const { return id; }
    char getChipType() const { return chipType; }
    Chip* getInput1() const { return input1; }
    Chip* getInput2() const { return input2; }
    Chip* getOutput() const { return output; }
//    double getInputValue() const { return inputValue; }

    void compute(){

        //cout << "Computing " << id << endl;
        if (chipType == 'A') {
            double result = input1->getInputValue() + input2->getInputValue();
//            cout << "Computing A(" << input1->getId() << " + " << input2->getId() << ") = " << result << endl;
            output->setInputValue(result);
            setInputValue(result);
        } else if (chipType == 'S') {
            double result = input1->getInputValue() - input2->getInputValue();
//            cout << "Computing S(" << input1->getId() << " - " << input2->getId() << ") = " << result << endl;
            output->setInputValue(result);
            setInputValue(result);
        } else if (chipType == 'M') {
            double result = input1->getInputValue() * input2->getInputValue();
//            cout << "Computing M(" << input1->getId() << " * " << input2->getId() << ") = " << result << endl;
            output->setInputValue(result);
            setInputValue(result);
        } else if (chipType == 'D') {
            double result = input1->getInputValue() / input2->getInputValue();
//            cout << "Computing D(" << input1->getId() << " / " << input2->getId() << ") = " << result << endl;
            output->setInputValue(result);
            setInputValue(result);
        } else if (chipType == 'N') {
            double result = -input1->getInputValue();
 //           cout << "Computing N(-" << input1->getId() << ") = " << result << endl;
            output->setInputValue(result);
            setInputValue(result);
        } else if (chipType == 'I') {
            output->setInputValue(getInputValue());
        } else if (chipType == 'O') {
            cout << "The output value from this circuit is " << inputValue << endl;
        }
    }

    void display() const {
        cout << id << ", ";
        if (chipType == 'I') {
            cout <<"Output = " << output->getId() << endl;
        }
        else if (chipType == 'O'){
            cout <<"Input 1 = " << input1->getId() << endl;
        }
        else if (chipType == 'N'){
            cout << "Input 1 = " << input1->getId() << ", Input 2 = Nope" << ", Output = " << output->getId() << endl;
        }
        else {
            cout << "Input 1 = " << input1->getId() << ", Input 2 = " << input2->getId() << ", Output = " << output->getId() << endl;
        }
    }

    string getId() const { return id; }
    double getInputValue() const { return inputValue; }
};

int main () {
    int numChips;
    Chip** allChips;
    int numCommands;
    string word1;


//    cout << "The number of chips" << endl;
    cin >> numChips;

    allChips = new Chip*[numChips];  // Dynamically allocate memory for chips

    for (int i = 0; i < numChips; i++) {
        cin >> word1;
        allChips[i] = new Chip(word1[0], word1);  // Create chip objects based on type and id
    }
    
    string targetId = "O50";
    int targetIndex = -1;
    
    // Search for the chip with ID "O50"
    for (int i = 0; i < numChips; i++) {
        if (allChips[i]->getId() == targetId) {
            targetIndex = i;
            break;
        }
    }
    
    // If the chip is found and it is not already the last chip
    if (targetIndex != -1 && targetIndex != numChips - 1) {
        // Swap the found chip with the last chip
        Chip* temp = allChips[targetIndex];
        allChips[targetIndex] = allChips[numChips - 1];
        allChips[numChips - 1] = temp;
    }

//    cout << "Number of commands including input command and the output command" << endl;
    cin >> numCommands;

    int* chipIndex = new int[numCommands];  //Create an array to store the index of the chips as entered from the command inputs

    int index = 0;
    for (int i = 0; i < numCommands; i++) {
        string chipId1, chipId2, chipId3;
        double num = 0.0;

        if (i < numCommands - 1) {
            cin >> chipId1 >> chipId2 >> chipId3;
        } else {
            cin >> chipId1 >> chipId2;
        }

        Chip* chip1 = nullptr;
        Chip* chip2 = nullptr;
        Chip* chip3 = nullptr;

        // Search for the chips by their IDs
        for (int j = 0; j < numChips; j++) {
            if (allChips[j]->getId() == chipId2) {
                chip2 = allChips[j];
                chipIndex[index] = j;
                index++;
            }
            if (allChips[j]->getId() == chipId3) {
                chip3 = allChips[j];
            }
        }
        // Set input/output connections or values
        if (chipId1 == "I") {
            num = stoi(chipId3);
            chip2->setInputValue(num);
        }

        if (chip2 && chip3) {
            chip2->setOutput(chip3); // Example connection
            if (chip3->getInput1() == nullptr) {
                chip3->setInput1(chip2); // Set input for chip3 if first input is NULL
            }
            else {
                chip3->setInput2(chip2); // Set input for chip3 if first input is already set
            }
        }

        if (chipId1 == "O") {
            cout << "Computation Starts" << endl;
            for (int x = 0; x < numChips - 1; x++) {
                allChips[chipIndex[x]]->compute();  // Perform computation on each chip based on the array from the index of commands
            }
            allChips[numChips-1]->compute(); // Perform computation on the last chip
        }
    }

    cout << "***** Showing the connections that were established" << endl;
    for (int i = 0; i < numChips; i++) {
        allChips[i]->display();
    }

    // Clean up dynamically allocated memory
    for (int i = 0; i < numChips; i++) {
        delete allChips[i];
    }
    delete[] allChips;

    return 0;
}
