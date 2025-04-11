#include <iostream>
#include <vector>
#include <unistd.h>
#include <fstream>

void clear_terminal() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape codes to clear the screen and move cursor to top-left
    std::cout.flush();
}

struct Field {
    Field(int size) : size(size) {
       array = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
    }

    void print() {
        for(auto& row : array) {
            for(auto& cell : row) {
                if(cell){
                    // std::cout << "X" << " ";
                    std::cout << "\033[91m█\033[0m";
                } else {
                    std::cout << "\033[30m█\033[0m";
                }
            }
            std::cout << std::endl;
        }
    }

    int neighbors_alive(int x, int y){
        int count = 0;
        for(int xx = -1; xx <= 1; xx++){
            for(int yy = -1; yy <= 1; yy++){
                if(xx == 0 && yy == 0){
                    continue;
                }
                int nx = x + xx;
                int ny = y + yy;

                if (nx >=0 && nx < size && ny >= 0 && ny < size){
                    count += array[nx][ny];
                }
            }
        }
        return count;
    }

    void next_generation(){
        std::vector<std::vector<int>> tmp = array;
        int changed{0};
        for(int x = 0; x < size; x++){
            for(int y = 0; y < size; y++){
                int alive = neighbors_alive(x, y);
                if (array[x][y] == 1) { // Is alive
                    if(alive == 2 || alive == 3){
                        tmp[x][y] = 1;
                    } else {
                        tmp[x][y] = 0;
                        changed++;
                    }
                } else { // Is dead
                    if(alive == 3){
                        tmp[x][y] = 1;
                        changed++;
                    } else {
                        tmp[x][y] = 0;
                    }
                }
            }
        }
        array = tmp;
        if(!changed){
            exit(1);
        }
    }

    int set_cell(int x, int y, int value) {



        array.at(x).at(y) = value;
        return 0;
    }


    std::vector<std::vector<int>> array;
    int size;
};

int main() {
    using namespace std;
    int size{30};
    Field field(size);
    field.set_cell(2, 2, 1);
    field.set_cell(2, 3, 1);
    field.set_cell(2, 2, 1);
    field.set_cell(3, 3, 1);
    field.set_cell(2, 4, 1);

    std::srand(std::time(0));

    for(int x=0; x < size; x++){
        for(int y=0; y < size; y++){
            int randombit = std::rand() % 100;
            if(randombit < 25){
                field.set_cell(x, y, randombit);
            }
        }
    }

    ofstream outFile("field.txt");
    for(int x = 0; x<size; x++) {
        for(int y = 0; y< size; y++) {
            if(field.array.at(x).at(y)){
                outFile << "X" << " ";
            } else {
                outFile << "." << " ";
            }
        }
        outFile << std::endl;
    }
    outFile.close();



    for (int i = 0; i < 1000; i++) {
        clear_terminal();
        field.print();
        usleep(300000);
        field.next_generation();
    }

    return 0;
}
