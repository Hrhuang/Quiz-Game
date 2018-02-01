///(1) Upon launch, program displays the top three player scores stored in game history file.
///(2) Game allows 2 players
///(3) Display top ten scores and average of those scores if menu choice 3 is chosen.

///=====================================================================

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const float DIFF_LEVEL_ONE = 1.23;
const float DIFF_LEVEL_TWO = 1.51;
const float DIFF_LEVEL_THREE = 2.02;
const int MAX_NUM_QUESTIONS = 15;

/// Declare 2 struct playerHistory and gameQuestion

struct playerHistory
{
    string date;
    int difficulty;
    float score;
    string alias1;
};

struct gameQuestion
{
    string question;
    char answer;
    string ans1;
    string ans2;
    string ans3;
    string ans4;
};

/// function prototype
void gameInfo();
char menu();
void getQuestion(gameQuestion qBank[], int loopy, ifstream& inQuest);
void gameResults2(string alias1, string alias2, double score1, double score2);
void gameResults1(string alias1, double score1);
void upDateScoreDouble(int difficulty, int loopy, double& score1, double& score2);
void upDateScoreSingle(int difficulty, int loopy, double& score1);
void getHistory (playerHistory pHist[], int loopy, ifstream& inQuest);
void bubblesort (playerHistory pHist[], int length);


int main()
{

    ///Variable declaration
    int difficulty=3;
    char solution;  ///read and store the question solution
    char userChoice;     ///store user provided solution to questions
    char next;      ///input to pause between questions
    string date = "\"Mar/2/2016\"";
    string question, ans1,ans2,ans3,ans4;
    string temp;    ///store the answer,as a string initially
    string alias1=" ", alias2=" ";
    string alias1FileName, alias2FileName;
    string gameHistory = "gameHistory.txt";
    string scoreNumber;
    int numQuestions=0, posSolutions=0;
    int numberofScores = 0;
    double score1=0, score2=0, totalScore =0;
    ifstream inQuest;
    ofstream outFile1, outFile2, outFile3;
    char menuChoice;

    ///step 1 - display the top 3 players from gameHistory.txt

    ///1.1 Open the gamehistory.txt file
    inQuest.open("gameHistory.txt");
    if(!inQuest)  {
        cout <<"Input file ERROR!!\n\n";
        return 0;  }

    ///1.2 Use a loop here to get the number of records in the gameHistory.txt, then close the file.
    while (getline(inQuest, scoreNumber))
        {
            numberofScores = numberofScores + 1;

        }

    inQuest.close();

    ///1.3 Open the gameHistory.txt file again
    inQuest.open("gameHistory.txt");
    if (!inQuest){
        cout << "Input file ERROR!!\n\n";
        return 0;
    }

    ///1.4 declare an array that is playerHistory type
    playerHistory pHist[numberofScores];

    ///1.5 Call the functions getHistory and bubblesort to load all records from the gamehistory.txt file
    ///and sort the record from hight to low based on the game score
    getHistory(pHist, numberofScores, inQuest);
    bubblesort(pHist, numberofScores );

    ///1.6 display the top 3 players with the highest scores
    cout << "  Top 3 scores: \n\n  " << left << setw(12) << pHist[0].alias1 << right << setw(6) << pHist[0].score << endl;
    cout << "  " << left << setw(12) << pHist[1].alias1 << right << setw(6) << pHist[1].score << endl;
    cout << "  " << left << setw(12) << pHist[2].alias1 << right << setw(6) << pHist[2].score << endl;
    cout << endl;

    ///close the gameHistory.txt file again
    inQuest.close();

    ///Declare an array that is the gameQuestion type
    gameQuestion qBank[MAX_NUM_QUESTIONS];

    ///step 2 - starts the menu
    ///Get user menu choice by calling the function menu()
    menuChoice = menu();

    ///step 3 - starts the loop based on the user choice

    while (menuChoice !='1' ||
           menuChoice !='2' ||
           menuChoice !='3'||
           menuChoice !='4')
    {
        ///3.1 exit the program if user chose option 4
        if(menuChoice == '4')
            {
            cout <<"\nExiting.\n";
            return 0;
            }
        ///3.2 If user chose option 3, display gameInfo and the top 10 scores sorted from high to low.
        else if(menuChoice == '3')
            {
            ///3.2.1 call the function gamInfo() to display the game description
            gameInfo();

            ///3.2.2 cout the top 10 scores(high to low) and the average score of the top 10 players



            inQuest.open("gameHistory.txt");
            if (!inQuest){
                cout << "Input file ERROR!!\n\n";
                return 0;
            }

            numberofScores=0;
            while (getline(inQuest, scoreNumber))
            {
                numberofScores = numberofScores + 1;

            }

            inQuest.close();


            inQuest.open("gameHistory.txt");
            if (!inQuest){
                cout << "Input file ERROR!!\n\n";
                return 0;
            }

            getHistory(pHist, numberofScores, inQuest);
            bubblesort(pHist, numberofScores );


            cout << fixed << setprecision(2);
            cout << "  Top 10 Scores: \n";
            for(int i=0; i<10; i++)
            {

            cout << "  " << left << setw(12) << pHist[i].alias1 << right << setw(6) << pHist[i].score << endl;
            }

            float avgScore;
            avgScore = pHist[0].score + pHist[1].score +pHist[2].score +pHist[3].score +
                pHist[4].score + pHist[5].score + pHist[6].score + pHist[7].score +
                pHist[8].score + pHist[9].score;
                avgScore = avgScore/10;
            cout << "\n  Average of top 10 Scores: " << avgScore << endl << endl;

            inQuest.close();

            }
        ///3.3 If user chose option 2, get info for the two players, and starts the game. You will ask for a date for
        ///both players, then get the alias for each player.
        else if(menuChoice == '2')
            {
            ///3.3.1 initialize score1 and score2 to 0 before each new play
            score1 = score2 =0;     //initialize to zero every new play
            cout <<"\nTWO PLAYERS! There will be 3 questions for each player.\n";
            cout <<"Enter the date(example \"Feb/18/2016\"): ";
            cin >> date;

            ///3.3.2 get alias for player 1 to create a file for player1
            cout <<"Enter first player game alias(example \"codeDog\"): ";
            cin >> alias1;

            alias1FileName = alias1;
            alias1FileName = alias1FileName.append(".txt");
            outFile1.open(alias1FileName.c_str(), ios::app);
            if(!outFile1)  {
                cout <<"Output file ERROR!!\n\n";
                return 0;  }

            ///3.3.3 get alias for player 2 to create a file for player2
            cout <<"Enter second player game alias: ";
            cin >> alias2;

            alias2FileName = alias2;
            alias2FileName = alias2FileName.append(".txt");
            outFile2.open(alias2FileName.c_str(), ios::app);
            if(!outFile2)  {
                cout <<"Output file ERROR!!\n\n";
                return 0;  }

            ///3.3.4 open gamehistory.txt file as and output file this time to be ready to append both player's
            ///record into it
            outFile3.open(gameHistory.c_str(), ios::app);
            if(!outFile3)  {
                cout <<"Output file ERROR!!\n\n";
                return 0;  }


            ///No need to ask for how many question, since in two player mode, each player will get 3 question
            numQuestions=6;

            ///3.3.5 Create a loop here to make sure the user enter valid difficulty level
            do{
                cout <<"Enter difficulty level: (1,2,3): ";
                cin >>difficulty;
                if (difficulty < 1 || difficulty > 3)
                {
                    cout << "Invalid input!\n";
                }
            }while(difficulty < 1 || difficulty > 3);

            ///3.3.5 load the question file based on the difficulty level chosen
            if(difficulty == 1)  {
                inQuest.open("questions1.txt");
            if(!inQuest)  {
                cout <<"\nERR-opening question file 1.\n";
                return 1;  }
            }

            else if(difficulty == 2)  {
                inQuest.open("questions2.txt");
            if(!inQuest)  {
                cout <<"\nERR-opening question file 2.\n";
                return 1;  }
            }

            else if(difficulty == 3){
                inQuest.open("questions3.txt");
            if(!inQuest){
                cout <<"\nERR-opening question file3.\n";
                return 1;}
            }

            ///3.3.6 create a loop to call the getQuestion function for each question
            for(int loopy=1; loopy<=numQuestions; loopy++)
                {

                getQuestion(qBank, loopy, inQuest);

            ///3.3.7 if statement here to display odd number of questions to player1 and even number of questions to player2
            ///make sure to add the correct score for respective player by calling the function upDateScoreDouble
                if(loopy%2 !=0)
                    cout <<"\nPlayer ONE:";
                else
                    cout <<"\nPlayer TWO";

                cout <<"\nQuestion ("<<loopy<<")\n"<<qBank[loopy].question<<"\n\n";
                cout <<"A) "<<qBank[loopy].ans1<<"\nB) "<<qBank[loopy].ans2<<"\nC) "<<qBank[loopy].ans3<<"\nD) "<<qBank[loopy].ans4;
                cout <<"\n Enter your choice: ";
                cin >> userChoice;
                userChoice = toupper(userChoice);
                cout <<"\nYou chose: "<<userChoice;

                if(userChoice == qBank[loopy].answer){
                 upDateScoreDouble(difficulty, loopy,score1, score2);
                 cout <<"\tCORRECT!  Scores P1= "<<score1<<", P2= "<<score2;}
                else
                 cout <<"\nWrong!     Solution: "<<qBank[loopy].answer<<"     Current Score: " <<score1<<", P2= "<<score2 ;
            //--------------------------------------------------
                //cout <<"\nenter any char to continue:";
                //cin >>next;
                cout <<"\n----------------------------------------\n\n";
                }   ///end of for loop of number of questions

            ///3.3.8 call the function gameResults2 to display the display game results
            gameResults2(alias1, alias2, score1, score2);

            ///3.3.9 Append the player1 and player2 record to the gameHistory.txt file and to the 2 files for each of the players.
            outFile1 <<date<<"\t"<<difficulty<<"\t"<<score1<<"\n";
            outFile2 <<date<<"\t"<<difficulty<<"\t"<<score2<<"\n";
            outFile3 <<alias1<<"\t"<<score1<<"\t"<<difficulty<<"\t"<<date<<"\n";
            outFile3 <<alias2<<"\t"<<score2<<"\t"<<difficulty<<"\t"<<date<<"\n";

            cout <<"\n\n\n\n";

            ///close infiles and outfiles
            inQuest.close();
            outFile1.close();
            outFile2.close();
            outFile3.close();
            } ///end of menu option 2

        ///step 3.4 - If user chose option 1, get info of the player, and starts the game.
        else if(menuChoice == '1')
            {
             ///3.4.1 reset score1 to 0 first
             score1=0;

             ///3.4.2 ask for the date and game alias, the game alias will be used as the file name for the players record file
             cout <<"\nEnter the date(example \"Feb/18/2016\"): ";
             cin >> date;
             cout <<"Enter your game alias(example \"codeDog\"): ";
             cin >> alias1;
             alias1FileName = alias1;
             alias1FileName = alias1FileName.append(".txt");
             outFile1.open(alias1FileName.c_str(), ios::app);
             if(!outFile1)
                {
                cout <<"Output file ERROR!!\n\n";
                return 0;  }

            ///3.4.3 Open the gameHistory file to be ready to append player's record to it as well
             outFile3.open(gameHistory.c_str(), ios::app);
             if(!outFile2)
                {
                cout <<"Output file ERROR!!\n\n";
                return 0;  }

            ///3.4.4 create a loop here to as for the number of questions the player want
            ///if the player enters invalid number, repeat the question over and over again
                do{
                    cout <<"How many questions? ( 1 - 15 ): ";
                    cin >>numQuestions;
                    if (numQuestions < 1 || numQuestions > 15)
                        {
                            cout << "Invalid input!\n";
                        }
                    }while(numQuestions > 15 || numQuestions < 1);


            ///3.4.5 created a loop here to get the level of difficulty from player
            ///if player enters invalid number, repeat the question over and over again
                do{
                    cout <<"Enter difficulty level: (1,2,3): ";
                    cin >>difficulty;
                    if (difficulty < 1 || difficulty > 3)
                        {
                            cout << "Invalid input!\n";
                        }
                    }while(difficulty < 1 || difficulty > 3);

            ///3.4.6 load the game file based on the difficulty chosen by player
                if(difficulty == 1)
                  {
                    inQuest.open("questions1.txt");
                    if(!inQuest)  {
                      cout <<"\nERR-opening question file 1.\n";
                      return 1;   }
                  }

                else if(difficulty == 2)
                  {
                    inQuest.open("questions2.txt");
                    if(!inQuest)  {
                      cout <<"\nERR-opening question file 2.\n";
                      return 1;   }
                  }

                else if(difficulty == 3)
                  {
                    inQuest.open("questions3.txt");
                    if(!inQuest)  {
                      cout <<"\nERR-opening question file3.\n";
                      return 1;   }
                   }

            ///3.4.7 create a loop here to call the function getQuestion based on the number of questions
                for(int loopy=1; loopy<=numQuestions; loopy++)
                {
                    getQuestion(qBank, loopy, inQuest);

                    cout <<"\nQuestion ("<<loopy<<")\n"<<qBank[loopy].question<<"\n\n";
                    cout <<"A) "<<qBank[loopy].ans1<<"\nB) "<<qBank[loopy].ans2<<"\nC) "<<qBank[loopy].ans3<<"\nD) "<<qBank[loopy].ans4;

                    cout <<"\nEnter your choice: ";
                    cin >> userChoice;
                    userChoice = toupper(userChoice);
                    cout <<"\nYou chose: "<<userChoice;
                //-------------------------------------------
                    if(userChoice == qBank[loopy].answer)  {
                     upDateScoreSingle(difficulty, loopy, score1);
                     cout << "\nCorrect!      Current Score: " << score1;
                    }
                    else
                    cout <<"\nWrong!    Solution: "<<qBank[loopy].answer << "     Current score: " << score1;
                //--------------------------------------------------
                    //cout <<"\nEnter any char to continue:";
                    //cin >>next;
                    cout <<"\n----------------------------------------\n\n";
                }   ///end of for loop of number of questions

            ///3.4.7 call the function gameResults1 to displayer the game results
                gameResults1(alias1, score1);

            ///3.4.8 append player record to both gamehistory.txt file and player record file(the file that has player alias as its file name)
                outFile1 <<date<<"\t"<<difficulty<<"\t"<<score1<<"\n";
                outFile3 <<alias1<<"\t\t"<<score1<<"\t"<<difficulty<<"\t"<<date<<"\n";

                cout <<"\n\n\n\n";

            ///close input and output files
                inQuest.close();
                outFile1.close();
                outFile2.close();
                outFile3.close();
            }//end of menuChoice 1

        menuChoice = menu();
    } //end of while (menu)

    return 0;
}

///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=.
///=-=-=-=-=- end of main =-=-=-=-=-=-=-=-=-=-=-=
///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=.

///this function just displayer the game info if user chose option 3 on the menu
void gameInfo()
{
    cout <<"\n-------------------- About the Game ----------------------------------";

    cout <<"\n\n The game begins by prompting for the user information\n";
    cout <<" (the date and user game alias1). The user game alias1\n";
    cout <<" is used as the name of the user game score history output\n";
    cout <<" file. Format of this output file is same as the sample input\n";
    cout <<" files for project 1, and output for project 2. The user is asked\n";
    cout <<" for the number of questions and the difficulty level of the\n";
    cout <<" game. If the number of questions entered by the user is not\n";
    cout <<" within the specified acceptable range (1-15), then the user is\n";
    cout <<" repeatedly prompted until a valid value is entered. If the difficulty\n";
    cout <<" level entered by the user is not within the acceptable\n";
    cout <<" range (1-3), an error msg is displayed and the program terminates.\n";
    cout <<" A running score is calculated, displayed, and written to each\n";
    cout <<" userHistory.txt output file at game end. The contents\n";
    cout <<" of the gameHistory.txt file is appended with the latest game\n";
    cout <<" results for each new player results.\n";
    cout <<" sorted results are written to the gameHistory.txt output file.\n";
    cout <<" Some of the new to this version:\n";
    cout <<" - gameHistory.txt contains game info for all users sorted by score.\n";
    cout <<" - User history is stored for both users in two-player mode.\n";
    cout <<" - Game options are presented with a menu of 4 options.\n";

    cout << " Program Description: This program plays a quiz game." << endl;
    cout << " Programmer: Huan Huang" << endl;
    cout << " Email: hrhuang@live.com" << endl;
    cout << " Play the game and look at your project directory.\n Examine the files";
    cout << " that are created. A game history file and user history files.\n";
    cout << "----------------------------------------------------------------------\n\n";
};

///this function displays the option menu and gets the user choice and return it back to the main function
char menu()
{
    char choice;

    cout <<"  Option Menu:\n";
    cout <<"\n  1  Single play";
    cout <<"\n  2  Two player";
    cout <<"\n  3  Game info";
    cout <<"\n  4  Exit\n";
    cout << "\n  Enter: ";

    cin >> choice;
    return choice;

};

///this function will display the game result onto console for two players
///make sure to also display who is the winner or if the game is a tie
void gameResults2(string alias1, string alias2, double score1, double score2){
        cout <<"\nGame Results!";
        cout <<"\n  "<<alias1<<" = "<<score1<<" pts.";
        cout <<"\n  "<<alias2<<" = "<<score2<<" pts.";
        if(score1 > score2)
            cout <<"\n"<<alias1<<" wins!";
        else if(score2 > score1)
            cout <<"\n"<<alias2<<" wins!";
        else
            cout <<"\nIt's a tie!";
}

///this function displays the game result of single player
void gameResults1(string alias1, double score1){
        cout <<"\n  Game Results!";
        cout <<"\n  "<<alias1<<" = "<<score1<<" pts.";
}

///this function update the score for two players
///if its is odd number question add score to player1 based on difficulty level
///if its is even number question add score to player2 based on difficulty level
void upDateScoreDouble(int difficulty, int loopy, double& score1, double& score2){
    if((difficulty == 1) && (loopy%2 !=0)){
            score1 += DIFF_LEVEL_ONE;     }
    else if((difficulty == 2) && (loopy%2 !=0)){
            score1 += DIFF_LEVEL_TWO;     }
    else if((difficulty == 3) && (loopy%2 !=0)){
            score1 += DIFF_LEVEL_THREE;   }
//---------player 2---------------------------
    else if((difficulty == 1) && (loopy%2 ==0)){
            score2 += DIFF_LEVEL_ONE;     }
    else if((difficulty == 2) && (loopy%2 ==0)){
            score2 += DIFF_LEVEL_TWO;     }
    else if((difficulty == 3) && (loopy%2 ==0)){
            score2 += DIFF_LEVEL_THREE;   }
}
///this function update the score for single player
void upDateScoreSingle(int difficulty, int loopy, double& score1) {
    if(difficulty == 1){
            score1 += DIFF_LEVEL_ONE;     }
    else if(difficulty == 2){
            score1 += DIFF_LEVEL_TWO;     }
    else if(difficulty == 3){
            score1 += DIFF_LEVEL_THREE;   }
}


///this function will load question, answer, and choices from the question file
///make sure to use array to store these data
void getQuestion(gameQuestion qBank[], int loopy, ifstream& inQuest){
    string temp;
    getline(inQuest, qBank[loopy].question, '\n');   //get question
    getline(inQuest, temp, '\n');        //get the answer
    qBank[loopy].answer = temp[0];     //pull the character out
    getline(inQuest, qBank[loopy].ans1); //get the four choices
    getline(inQuest, qBank[loopy].ans2);
    getline(inQuest, qBank[loopy].ans3);
    getline(inQuest, qBank[loopy].ans4);
}

///this function loads the players record from the gameHistory.txt file
///make sure to user array to store these data
void getHistory (playerHistory pHist [], int loopy, ifstream& inQuest){
    for (int i=0; i<loopy; i++)
    {
    inQuest >> pHist[i].alias1;
    inQuest >> pHist[i].score;
    inQuest >> pHist[i].difficulty;
    inQuest >> pHist[i].date;
    }
}

///this function sorts the player history array from high to low based on the score
void bubblesort (playerHistory pHist[], int length){
    playerHistory temp [length];
    int iteration;
    int index;
    for (iteration = 1; iteration < length; iteration ++){
        for (index = 0; index < length - iteration; index ++){
            if (pHist[index].score < pHist[index+1].score){
                temp[index] = pHist[index];
                pHist[index] = pHist[index+1];
                pHist[index +1] = temp[index];
            }

        }

    }
}

