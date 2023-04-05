#include <iostream>
#include <fstream>
#include "BST.h"

using namespace std;

int main(int argc, char* argv[] ) {


    if(argc == 4){
        BST bst;
        string file = argv[1];
        ifstream fin("../tests/" + file);
        string line;
        //read file and insert into the tree
        if (fin.is_open()) {
            while (getline(fin, line)) {
                bst.insert(line);
            }
        }
        fin.close();

        std::cout << bst << std::endl;
        string out_file = argv[2];
        bst.save_tree_to_file(out_file);

        string test_file = argv[3];
        ifstream input("../tests/" + test_file);
        string word;
        string pure_word;
        if (input.is_open()) {
            //loop through each word and search if the word is in the tree
            while (getline(input, word, ' ')) {
                bst.search_tree(word);
            }
        }
        input.close();
    }else{
        cout<<"Please enter the required parameters Arg1 = program file(Assignment_3.exe), Arg2 = file name(dictionary.txt), Arg3 = file name (output.txt), Arg4 = file name(test.txt). \n "
              "Find the output file in output directory"<<endl;
    }


    return 0;
}


