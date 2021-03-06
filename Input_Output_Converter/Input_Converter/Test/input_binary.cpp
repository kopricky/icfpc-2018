#include <iostream>
#include <fstream>

using namespace std;

int main(){
    char outfile[] = "file.txt";

    ifstream fin( outfile, ios::in | ios::binary );

    if (!fin){
        cout << "ファイル file.txt が開けません";
        return 1;
    }

    double d;

    while(!fin.eof()){
        fin.read( ( char * ) &d, sizeof( double ) );
        cout << d << endl;
    }

    fin.close();

    return 0;
}
