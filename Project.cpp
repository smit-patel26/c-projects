/*

author:  Smit Patel
date:    november 25, 2023
*/

#include <iostream>
#include <cstring>
#include <new>
using namespace std;

class Crossword {
   private:
      char *board, *mask;
      int score, rowAndColSize;
      char playerName[31];
   public:
      Crossword(const char *crossword, int size, const char *name);
      int convertCoord(const char *coord);
      void loadWord(const char *coord, const char *word, char dir);
      void updateGameBoard(const char *coord);
      friend ostream& operator<<(ostream &os, Crossword &r);
      void displayTitle( );
      void displayScore( );
      ~Crossword( );
};


int main( ) {
   char gameBoard[2048] = "  123456789ABCDEFGHIJK \n"
                          "1|....................|\n"
                          "2|....................|\n"
                          "3|....................|\n"
                          "4|....................|\n"
                          "5|....................|\n"
                          "6|....................|\n"
                          "7|....................|\n"
                          "8|....................|\n"
                          "9|....................|\n"
                          "A|....................|\n"
                          "B|....................|\n"
                          "C|....................|\n"
                          "D|....................|\n"
                          "E|....................|\n"
                          "F|....................|\n"
                          "G|....................|\n"
                          "H|....................|\n"
                          "I|....................|\n"
                          "J|....................|\n"
                          "K|....................|\n";

   Crossword langs(gameBoard, 20, "Smit Patel");

   langs.loadWord("4B", "C++", 'H');
   langs.loadWord("65", "LUA", 'V');
   langs.loadWord("84", "JAVASCRIPT", 'H');
   langs.loadWord("8C", "PYTHON", 'V');
   langs.loadWord("GF", "SWIFT", 'H');
   langs.loadWord("H5", "RUBY", 'H');
   langs.loadWord("H5", "RUST", 'V');

   cout << langs << endl; // should call stream operator<<( ) friend function
                             // to display initial empty game board (containing only '.' and titles and score).



   langs.updateGameBoard("36"); // no letter found at 36
   langs.updateGameBoard("85"); // should find the 'A' at 85 and then also find V, A, S, C, R, I, P, T, J, U, A
                                // and update score to 60 points

   langs.updateGameBoard("A7"); // no letter found at A7

   langs.updateGameBoard("DC"); // should find the 'N' at DC and then also find O, H, T, Y, P
                                // and update score to 90 points
                                // NOTE: Character 'P' was counted twice (OK for this assignment).

   return 0;
}

Crossword::Crossword(const char *crossword, int size, const char *name)
{
   unsigned int totalBytes;

   rowAndColSize = size;
   strcpy(playerName, name);
   score = 0;

   totalBytes = ((size + 1) * (size * 4)) + 1;

   board = new char[totalBytes];
   mask = new char[totalBytes];

   strcpy(board, crossword);
   strcpy(mask, crossword);
}

int Crossword::convertCoord(const char *coord)
{
   int row, column;
   int index;

   if (coord[0] >= 49 && coord[0] <= 57)
   {
      row = coord[0] - 48;
   }

   else if (coord[0] >= 65 && coord[0] <= 90)
   {
      row = coord[0] - 55;
   }

   if (coord[1] >= 49 && coord[1] <= 57)
   {
      column = coord[1] - 48;
   }

   else if (coord[1] >= 65 && coord[1] <= 90)
   {
      column = coord[1] - 55;
   }

   index = (24 * row) + column + 2 - 1;

   return index;
}

void Crossword::loadWord(const char *coord, const char *word, char dir)
{
   int index;
   int count = 0;
   int length = strlen(word);

   index = convertCoord(coord);

   if (dir == 'H')
   {
      for (; count < length; count++)
      {
         board[index + count] = word[count];
      }
   }

   else if (dir == 'V')
   {
      for (; count < length; count++)
      {
         board[index + (count * 24)] = word[count];
      }
   }
}

void Crossword::updateGameBoard(const char *coord)
{
   int index;

   index = convertCoord(coord);

   if (index >= 0 && index < (rowAndColSize * rowAndColSize))
   {

      if ((board[index] >= 'A' && board[index] <= 'Z') && board[index] != '~' && board[index] != '.')
      {
         mask[index] = board[index];
         score += 5;

         for (; board[index - 24] != '.' && board[index - 24] != '~';)
         {
            mask[index - 24] = board[index - 24];
            score += 5;
            index -= 24;
         }

         index = convertCoord(coord);

         for (; board[index + 24] != '.' && board[index + 24] != '~';)
         {
            mask[index + 24] = board[index + 24];
            score += 5;
            index += 24;
         }

         index = convertCoord(coord);

         for (; board[index - 1] != '.' && board[index - 1] != '~';)
         {
            mask[index - 1] = board[index - 1];
            score += 5;
            index -= 1;
         }

         index = convertCoord(coord);

         for (; board[index + 1] != '.' && board[index + 1] != '~';)
         {
            mask[index + 1] = board[index + 1];
            score += 5;
            index += 1;
         }
      }

      else
      {
         board[index] = '~';
         mask[index] = '~';
      }
   }

   displayTitle();
   cout << mask;
   displayScore();
}

ostream &operator<<(ostream &os, Crossword &r)
{

   r.displayTitle();
   os << r.mask;
   r.displayScore();

   return os;
}

void Crossword::displayTitle()
{
   cout << "  C++ Crossword Puzzle... By: " << playerName << endl;
}

void Crossword::displayScore()
{
   cout << " Current Score: " << score << endl
        << endl;
}

Crossword::~Crossword()
{
   delete[] board;
   delete[] mask;
}