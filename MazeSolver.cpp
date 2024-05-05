/*
   program:         Maze Solver
   author:          Smit Patel
*/

#include <cstdio>
#include <cstring>

typedef unsigned int ui;

class MazeSolver {
   private:                          // PRIVATE member data
      char maze[1226];
      char path[71];
      ui columnWidth;
   public:                           // PUBLIC member functions
      MazeSolver(const char *);      // parameter constructor ONLY
      ui findTreasure( );
      const char* findPath( );
      ui countBlanks( );
      void showMaze( );
};


int main( ) {

   char maze1[211] = { "-------------------+\n"
                       "@                  |\n"
                       "| | --+ | | -------+\n"
                       "| |   | | |      # |\n"
                       "| +-+ | | +-+ | ---+\n"
                       "|   | | |   | |    |\n"
                       "| | | +-+ | +-+----+\n"
                       "| | |   | |        |\n"
                       "| | |   | |        |\n"
                       "+-+-+---+-+--------+\n" };

   char maze2[760] = { "-------------------------------+\n"
                       "@                              |\n"
                       "| --+ --+ --+ | --------+ | |  |\n"
                       "|   |   |   | |         | | |  |\n"
                       "| --+---+-+ | +-+ | | | +-+ |  |\n"
                       "|         | |   | | | |   | |  |\n"
                       "| ------+ | | | | | | | | +-+  |\n"
                       "|       | | |#| | | | | |   |  |\n"
                       "| ------+ +-+ | +-+-+-+ +-+ +--+\n"
                       "|       |   | |       |   |    |\n"
                       "| --+ --+ --+ +-----+ +-+ +-+  |\n"
                       "|   |   |   |       |   |   |  |\n"
                       "| --+ | | --+-+ | --+ | | | |  |\n"
                       "|   | | |     | |   | | | | |  |\n"
                       "| | +-+ | | | +-+ --+ | +-+ |  |\n"
                       "| |   | | | |   |   | |   | |  |\n"
                       "| | --+-+ +-+---+ --+-+ | +-+--+\n"
                       "| |     |       |     | |      |\n"
                       "| +---+ | ------+-+ --+ | --+  |\n"
                       "|     | |         |   | |   |  |\n"
                       "| ----+ +-+ | --+ +-+ | | --+--+\n"
                       "|     |   | |   |   | | |      |\n"
                       "+-----+---+-+---+---+-+-+------+\n" };

   char studentPath[41];
   MazeSolver m1(maze1), m2(maze2);

   printf("m1 maze...\n");
   m1.showMaze( );
   printf("m1 path...%s\n", m1.findPath( ));
   printf("m1 blanks...%u\n", m1.countBlanks( ));

   printf("===========================================\n");

   strcpy(studentPath, m2.findPath( ));

   printf("m2 maze...\n");
   m2.showMaze( );
   printf("m2 path:   %s\n", studentPath);
   printf("m2 blanks: %u\n", m2.countBlanks( ));

   return 0;
}

MazeSolver::MazeSolver(const char *s)
{

    strcpy(maze, s);
    path[0] = '\0';

    ui index = 0;

    for (index = 0; maze[index] != '\n'; index++);
        
    columnWidth = index;
}

void MazeSolver::showMaze()
{
    printf("%s", maze);
}

const char *MazeSolver::findPath()
{

    int count = 0, i = 0;
    char revPath[71];

    for (count; maze[count] != '#'; count++);

    for (i; maze[count] != '@';)
    {
        if (maze[count - 1] == 0x20)
        {
            revPath[i] = 'E';
            count--;
            i++;
        }

        else if (maze[count - columnWidth - 1] == 0x20)
        {
            revPath[i] = 'S';
            count = count - 1 - columnWidth;
            i++;
        }

        else if (maze[count - 1] == '@')
        {
            revPath[i] = 'E';
            i++;
            break;
        }

    }

    revPath[i] = '\0';

    int index;

    for (index = 0 ; revPath[index] != '\0'; index++)
    {
        path[index] = revPath[i - 1];
        i--;
    }

    return path;
}

ui MazeSolver::countBlanks()
{

    ui numOfBlanks = 0, lastIndex, i;

    for (lastIndex = 0 ; maze[lastIndex] != '\0'; lastIndex++);

    for (i = 0 ; i <= lastIndex;)
    {
        if (maze[i] == 0x20)
        {
            numOfBlanks++;
        }

        i++;
    }

    return numOfBlanks;
}

ui MazeSolver::findTreasure( ){
    
    ui count;

    for (count = 0; maze[count] != '#'; count++);

    return count;

}