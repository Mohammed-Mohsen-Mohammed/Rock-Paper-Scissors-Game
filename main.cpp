#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

enum enGameChoice { stone = 1, paper = 2, scissor = 3 };

enum enWinner { player = 1, computer = 2, draw = 3 };

struct stRoundInfo
{
	short roundNumber = 0;
	enGameChoice playerChoice;
	enGameChoice computerChoice;
	enWinner winner;
	string winnerName;
};

struct stGameResult
{
	short gameRounds = 0;
	short playerWinTimes = 0;
	short computerWinTimes = 0;
	short drawTimes = 0;
	enWinner winner;
	string winnerName;
};

enGameChoice readPlayerChoice() 
{
	short choice;

	do {
		cout << "\nEnter your choice: [1]: Stone, [2]: Paper, [3]: Scissor ? ";
		cin >> choice;
	} while (choice < 1 || choice>3);

	return enGameChoice(choice);
}

int randomNumber(int from, int to) 
{

	return rand() % (to - from + 1) + from;
}

enGameChoice getComputerChoice() 
{

	return enGameChoice(randomNumber(1, 3));
}

enWinner whoWonTheRound(stRoundInfo roundInfo) 
{
	if (roundInfo.playerChoice == roundInfo.computerChoice)return enWinner::draw;

	switch (roundInfo.playerChoice)
	{
	case enGameChoice::stone:
		return (roundInfo.computerChoice == enGameChoice::scissor) ? enWinner::player : enWinner::computer;
	case enGameChoice::paper:
		return (roundInfo.computerChoice == enGameChoice::stone) ? enWinner::player : enWinner::computer;
	case enGameChoice::scissor:
		return (roundInfo.computerChoice == enGameChoice::paper) ? enWinner::player : enWinner::computer;
	}
}

enWinner whoWonTheGame(short playerWinTimes, short computerWinTimes) 
{
	if (playerWinTimes > computerWinTimes)return enWinner::player;
	else if (playerWinTimes < computerWinTimes)return enWinner::computer;
	else return enWinner::draw;
}

string choiceName(enGameChoice choice)
{
	static string arrGameChoice[] = { "Stone","Paper","Scissor" };
	return arrGameChoice[choice - 1];
}

string winnerName(enWinner winner)
{
	static string arrWinnerName[] = { "Player","Computer","Draw" };
	return arrWinnerName[winner - 1];
}

short readHowMeanyRounds()
{
	short roundsNumber;

	do {
		cout << "How many rounds you want [1 to 10]?\n";
		cin >> roundsNumber;
	} while (roundsNumber < 1 || roundsNumber > 10);

	return roundsNumber;
}

void setWinnerScreenColor(enWinner winner) 
{
	switch (winner)
	{
	case enWinner::player:
		system("color 2F");
		break;
	case enWinner::computer:
		system("color 4F");
		cout << "\a";
		break;
	default:
		system("color 6F");
	}
}

void printRoundResults(stRoundInfo roundInfo)
{
	cout << "\n____________ Round [" << roundInfo.roundNumber << "] ____________\n\n";
	cout << "Player Choice  : " << choiceName(roundInfo.playerChoice) << endl;
	cout << "Computer Choice: " << choiceName(roundInfo.computerChoice) << endl;
	cout << "Round Winner   : [" << roundInfo.winnerName << "]\n";
	cout << "___________________________________\n" << endl;

	setWinnerScreenColor(roundInfo.winner);
}

stGameResult playGame(short howManyRounds) 
{
	stRoundInfo roundInfo;
	short playerWinTimes = 0, computerWinTimes = 0, drawTimes = 0;

	for (short i = 1; i <= howManyRounds; i++)
	{
		cout << "\nRound [" << i << "] begins:\n";
		roundInfo.roundNumber = i;
		roundInfo.playerChoice = readPlayerChoice();
		roundInfo.computerChoice = getComputerChoice();
		roundInfo.winner = whoWonTheRound(roundInfo);
		roundInfo.winnerName = winnerName(roundInfo.winner);

		if (roundInfo.winner == enWinner::computer)
			computerWinTimes++;
		else if (roundInfo.winner == enWinner::player)
			playerWinTimes++;
		else drawTimes++;

		printRoundResults(roundInfo);
	}

	enWinner finalWinnar = whoWonTheGame(playerWinTimes, computerWinTimes);

	return{ howManyRounds,playerWinTimes,computerWinTimes,drawTimes,finalWinnar,winnerName(finalWinnar) };
}

void showGameOverScreen()
{

	cout << "\t\t____________________________________________________________________\n\n";
	cout << "\t\t                    +++ G a m e  O v e r +++\n";
	cout << "\t\t____________________________________________________________________\n\n";
}

void showFinalGameResult(stGameResult gameResult)
{
	cout << "\t\t______________________ [G a m e  R e s u l t] ______________________\n\n";
	cout << "\t\tGame rounds         : " << gameResult.gameRounds << endl;
	cout << "\t\tPlayer won times    : " << gameResult.playerWinTimes << endl;
	cout << "\t\tComputer won times  : " << gameResult.computerWinTimes << endl;
	cout << "\t\tDraw times          : " << gameResult.drawTimes << endl;
	cout << "\t\tFinal winner        : " << gameResult.winnerName << endl;
	cout << "\t\t____________________________________________________________________";

	setWinnerScreenColor(gameResult.winner);
}

void resetScreen()
{
	system("cls");
	system("color 0F");
}

void startGame() 
{
	char playAgain;

	do {
		resetScreen();
		stGameResult gameresult = playGame(readHowMeanyRounds());
		showGameOverScreen();
		showFinalGameResult(gameresult);

		cout << "\n\t\tDo you want to play again? [Y/N] ";
		cin >> playAgain;
	} while (playAgain == 'y' || playAgain == 'Y');
}

int main() 
{
	srand(time(nullptr));

	startGame();

	return 0;
}