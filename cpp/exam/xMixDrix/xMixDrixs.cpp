#include <iostream> 
#include <string>

enum playerType{playerX, playerO};

/*board indexes:
| 0 | 1 | 2
 ----------
| 3 | 4 | 5
-----------
| 6 | 7 | 8 */

class game{
    private:
        int boardA = 0;
        int boardB = 0;
        playerType last_step;

        static const int FIRST_ROW_MASK     = 0b111000000;//0,1,2
        static const int SECOND_ROW_MASK    = 0b111 << 3;//3,4,5
        static const int THIRD_ROW_MASK     = 0b111 << 6;//6,7,8
        static const int FIRST_COLUMN_MASK  = 0b001001001;//0,3, 6
        static const int SECOND_COLUMN_MASK = 0b010010010;//1,4,7
        static const int THIRD_COLUMN_MASK  = 0b100100100;//2,5,8
        static const int FIRST_DIAG_MASK    = 0b100010001;//0,4,8
        static const int SECOND_DIAG_MASK   = 0b001010100;//2,4,6

        bool checkWin(int board){
            if((board & FIRST_ROW_MASK) == FIRST_ROW_MASK) return true;
            if((board & SECOND_ROW_MASK) == SECOND_ROW_MASK) return true;
            if((board & THIRD_ROW_MASK) == THIRD_ROW_MASK) return true;
            if((board & FIRST_COLUMN_MASK) == FIRST_COLUMN_MASK) return true;
            if((board & SECOND_COLUMN_MASK) == SECOND_COLUMN_MASK) return true;
            if((board & THIRD_COLUMN_MASK) == THIRD_COLUMN_MASK) return true;
            if((board & FIRST_DIAG_MASK) == FIRST_DIAG_MASK) return true;
            if((board & SECOND_DIAG_MASK) == SECOND_DIAG_MASK) return true;
            return false;
        }

        void printBoard(int board, playerType player){
            char p = player == playerX ? 'X' : 'O'; 
            char p2 = player == playerX ? 'O' : 'X';
            for(int i = 0; i < 9; i++){
                if(i % 3 == 0) { std::cout << std::endl; }
                if((board & (1 << i)) != 0){
                    std::cout << p << " ";
                }
                else{
                    std::cout << p2 << " ";
                }
            }
            std::cout << std::endl;
            
        }

    public:
        void markStep(playerType player, int stepPosotion){
           if(last_step == player){
            std::cout << "same player" << std::endl;
            return;
           }

           if(player == playerX ){
            if(boardB &  (1 << stepPosotion)){
                std::cout << "occupied" << std::endl;
                return;
            }

            boardA |= (1 << stepPosotion);
           }
           else if(player == playerO){
             if(boardA & (1 << stepPosotion)){
                std::cout << "occupied" << std::endl;
                return;
            }
            boardB |= (1 << stepPosotion);
           }
           last_step = player;

           if(checkWin(boardA)){
            std::cout << "player X won" << std::endl;
            printBoard(boardA, playerX);
            return;
           }
           if(checkWin(boardB)){
            std::cout << "player O won" << std::endl;
            printBoard(boardB, playerO);
            return;
           }
        }


        
};

int main(){
    game g;
    g.markStep(playerX, 0);
    
    g.markStep(playerX, 2);
    g.markStep(playerO, 3);
    g.markStep(playerX, 4);
    g.markStep(playerO, 5);
    g.markStep(playerX, 6);
    g.markStep(playerO, 7);
    g.markStep(playerX, 8);
}